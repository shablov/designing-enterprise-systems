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
	pGraphicsView = new GraphicsView(pGraphicsScene,this);
	pGraphicsView->setScene(pGraphicsScene);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(pGraphicsView);

	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(QPoint)), SLOT(onCustomContextMenuRequested(QPoint)));
	createAction();
	createContextMenu();
}

DesigningView::~DesigningView()
{

}
void DesigningView::createAction()
{
	//pAddRelations = new QAction(tr("add relations"), this);
	//pAddProcessBlock = new QAction(tr("Add process block"),this,SLOT(addProcessBlock()));
	//pAddDataBlock = new QAction(tr("Add data block"),this,SLOT(addDataBlock()));
	//pDeleteBlock = new QAction(tr("delete block"),this,SLOT(deleteBlock()));
	//pSettings =  new QAction(tr("Settings"),this,SLOT(settingsBlock()),);
}
void DesigningView::createContextMenu()
{
	pContextMenu = new QMenu(tr("Block"),pGraphicsView);
	//pContextMenu->addAction(pAddRelations);
	//pContextMenu->addAction(pAddProcessBlock);
	//pContextMenu->addAction(pAddDataBlock);
	//pContextMenu->addAction(pDeleteBlock);

	pContextMenu->addAction(tr("add relations"), this,SLOT(addRelation()));
	pContextMenu->addAction(tr("Add process block"),this,SLOT(addProcessBlock()));
	pContextMenu->addAction(tr("Add data block"),this,SLOT(addDataBlock()));
	pContextMenu->addAction(tr("delete block"),this,SLOT(deleteBlock()));
	pContextMenu->addAction(tr("Settings"),this,SLOT(settingsBlock()));

}
QList<QGraphicsRectItem *> DesigningView::getListData() const
{
	return pListData;
}


QList<QGraphicsRectItem *> DesigningView::getListProces() const
{
	return pListProces;
}




void DesigningView::onCustomContextMenuRequested(const QPoint &point)
{
	pLastKeyPoint =QPointF (pGraphicsView->mapToScene(point)).toPoint();

	QPoint p = QPointF(pGraphicsView->mapFromGlobal(QWidget::mapToGlobal(point))).toPoint();

	BlockItem *bi = refOnBlockItem(p);
	pContextMenu->exec(QWidget::mapToGlobal(point));




	if (!bi)
	{//TODO:vis or no to vis

	}
	else
	{

	}

}


void DesigningView::addBlock(BlockType type, QPoint point)
{
	QGraphicsRectItem *item;

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

	//	if (!bi)// and  !pGraphicsView->itemAt(point)->parentItem())
	//		bi = qgraphicsitem_cast<BlockItem *>(pGraphicsView->itemAt(point)->parentItem());

	//qDebug()<<"123" <<pGraphicsView->itemAt(point)->type();
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
		bcm= new BlockContextMenu(bi);
		bcm->show();
	}
}
