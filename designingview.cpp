#include "designingview.h"

#include "block.h"
#include "graphicsview.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMenu>
#include <QDebug>
#include <QVBoxLayout>
#include "blockcontextmenu.h"


DesigningView::DesigningView(QWidget *parent) : QWidget(parent)
{
	setAcceptDrops(true);
	pGraphicsScene = new QGraphicsScene(this);
	pGraphicsScene->setFocus(Qt::MouseFocusReason);
	pGraphicsView = new GraphicsView(pGraphicsScene,this);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(pGraphicsView);

	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(QPoint)), SLOT(onCustomContextMenuRequested(QPoint)));
	createAction();
	createContextMenu();

	startFunc();
}

DesigningView::~DesigningView()
{

}
void DesigningView::createAction()
{
	pAddRelation = new QAction(tr("add relations"), this);
	pAddProcessBlock = new QAction(tr("Add process block"),this);
	pAddDataBlock = new QAction(tr("Add data block"),this);
	pDeleteBlock = new QAction(tr("delete block"),this);
	pSettings =  new QAction(tr("Settings"),this);

	connect(pAddRelation, SIGNAL(triggered()), this, SLOT(addRelation()));
	connect(pAddProcessBlock, SIGNAL(triggered()), this, SLOT(addProcessBlock()));
	connect(pAddDataBlock, SIGNAL(triggered()), this, SLOT(addDataBlock()));
	connect(pDeleteBlock, SIGNAL(triggered()), this, SLOT(deleteBlock()));
	connect(pSettings, SIGNAL(triggered()), this, SLOT(settingsBlock()));
}
void DesigningView::createContextMenu()
{
	pContextMenu = new QMenu(tr("Block"),pGraphicsView);
	pContextMenu->addAction(pAddRelation);
	pContextMenu->addAction(pAddProcessBlock);
	pContextMenu->addAction(pAddDataBlock);
	pContextMenu->addAction(pDeleteBlock);
	pContextMenu->addAction(pSettings);
}
QList<BlockItem *> DesigningView::getListData() const
{
	return pListData;
}


QList<BlockItem *> DesigningView::getListProces() const
{
	return pListProces;
}


void DesigningView::onCustomContextMenuRequested(const QPoint &point)
{
	pLastKeyPoint =QPointF (pGraphicsView->mapToScene(point)).toPoint();

	QPoint p = QPointF(pGraphicsView->mapFromGlobal(QWidget::mapToGlobal(point))).toPoint();

	BlockItem *bi = refOnBlockItem(p);

	pAddRelation->setVisible(bi);
	pDeleteBlock->setVisible(bi);
	pSettings->setVisible(bi);
	pAddDataBlock->setVisible(!bi);
	pAddProcessBlock->setVisible(!bi);
	pContextMenu->exec(QWidget::mapToGlobal(point));
}


void DesigningView::addBlock(BlockType type, QPoint point)
{
	BlockItem *item;

	QString name;
	switch (type)
	{
	case processBlock:
		name = QString("Процесс%1").arg(pListProces.count());
		item = new BlockItem(type,name);
		pListProces.append(item);
		break;
	case dataBlock:
		name = QString("данные%1").arg(pListData.count());
		item = new BlockItem(type,name);
		pListData.append(item);;
		break;
	}

	pGraphicsScene->addItem(item);
	item->setAcceptDrops(true);
	item->setFlags(QGraphicsItem::ItemIsMovable);
	item->setPos(point);
}

bool DesigningView::eventFilter(QObject *target, QEvent *event)
{
	QWidget::eventFilter(target,event);
}

BlockItem *DesigningView::refOnBlockItem(QPoint point)
{
	BlockItem *bi = qgraphicsitem_cast<BlockItem *>(pGraphicsView->itemAt(point));
	if (!bi)
	{
		QGraphicsTextItem *ti = qgraphicsitem_cast<QGraphicsTextItem *>(pGraphicsView->itemAt(point));
		if (ti) bi = qgraphicsitem_cast<BlockItem *>(ti->parentItem());
	}

	return bi;
}


void DesigningView::addDataBlock()
{
	addBlock(dataBlock,pLastKeyPoint);
}

void DesigningView::addProcessBlock()
{
	addBlock(processBlock,pLastKeyPoint);
}

void DesigningView::deleteBlock()
{
	QPoint p = QPointF(pGraphicsView->mapFromGlobal(QWidget::mapToGlobal(pGraphicsView->mapFromScene(pLastKeyPoint)))).toPoint();
	BlockItem *bi = refOnBlockItem(p);
	if(bi)
	{
		if(bi->getType() == processBlock)
			pListProces.removeAll(bi);
		if(bi->getType() == dataBlock)
			pListData.removeAll(bi);
		pGraphicsScene->removeItem(bi);
		delete (bi);
	}
}

void DesigningView::addRelation()
{
	pGraphicsView->startLinePaint(pGraphicsView->mapFromScene(pLastKeyPoint));
}

void DesigningView::settingsBlock()
{
	QPoint p = QPointF(pGraphicsView->mapFromGlobal(QWidget::mapToGlobal(pGraphicsView->mapFromScene(pLastKeyPoint)))).toPoint();
	BlockItem *bi = refOnBlockItem(p);
	if(bi)
	{
		bcm = new BlockContextMenu(bi);
		bcm->show();
	}
}

void DesigningView::startFunc()
{
	addBlock(processBlock,QPoint(360,100));
	addBlock(processBlock,QPoint(360,300));
	addBlock(processBlock,QPoint(360,500));
	pListProces.at(0)->setFrequencyOfActivation(1);
	pListProces.at(1)->setFrequencyOfActivation(2);
	pListProces.at(2)->setFrequencyOfActivation(5);

	addBlock(dataBlock,QPoint(160,200));
	addBlock(dataBlock,QPoint(160,400));
	addBlock(dataBlock,QPoint(560,200));
	addBlock(dataBlock,QPoint(560,400));

	pGraphicsView->addLinePaint(pListData.at(0),pListProces.at(0));
	pGraphicsView->addLinePaint(pListData.at(0),pListProces.at(1));
	pGraphicsView->addLinePaint(pListData.at(1),pListProces.at(2));
	pGraphicsView->addLinePaint(pListData.at(2),pListProces.at(0));
	pGraphicsView->addLinePaint(pListData.at(2),pListProces.at(1));
	pGraphicsView->addLinePaint(pListData.at(3),pListProces.at(1));
	pGraphicsView->addLinePaint(pListData.at(3),pListProces.at(2));
}
