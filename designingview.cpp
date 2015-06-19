#include "designingview.h"

#include "block.h"
#include "graphicsview.h"
#include "math.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMenu>
#include <QDebug>
#include <QVBoxLayout>
#include <QKeyEvent>
#include "blockcontextmenu.h"

#include <QtXML/QDomNodeList>
#include <QtCore/QTextStream>


DesigningView::DesigningView(QWidget *parent) : QWidget(parent),treeData(0),treeProcess(0)
{
	setAcceptDrops(true);
	pGraphicsScene = new QGraphicsScene();
	pGraphicsScene->setFocus(Qt::MouseFocusReason);
	pGraphicsView = new GraphicsView(pGraphicsScene, this);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(pGraphicsView);

	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(QPoint)), SLOT(onCustomContextMenuRequested(QPoint)));
	createAction();
	createContextMenu();

	pGraphicsView->setCacheMode(QGraphicsView::CacheBackground);
	pGraphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	pGraphicsView->setRenderHint(QPainter::Antialiasing);
	pGraphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	pGraphicsView->scale(qreal(0.8), qreal(0.8));

	//startFunc();
}

DesigningView::~DesigningView()
{

}
void DesigningView::createAction()
{
	pAddRelation = new QAction(tr("Добавить связь"), this);
	pAddProcessBlock = new QAction(tr("Добавить процесс"),this);
	pAddDataBlock = new QAction(tr("Добавить данные"),this);
	pDeleteBlock = new QAction(tr("Удалить"),this);
	pSettings =  new QAction(tr("Настройки"),this);
	//pLineDel =  new QAction(tr("Delete line"),this);

	connect(pAddRelation, SIGNAL(triggered()), this, SLOT(addRelation()));
	connect(pAddProcessBlock, SIGNAL(triggered()), this, SLOT(addProcessBlock()));
	connect(pAddDataBlock, SIGNAL(triggered()), this, SLOT(addDataBlock()));
	connect(pDeleteBlock, SIGNAL(triggered()), this, SLOT(deleteBlock()));
	connect(pSettings, SIGNAL(triggered()), this, SLOT(settingsBlock()));
	//connect(pLineDel, SIGNAL(triggered()), this, SLOT(lineDelete()));
}
void DesigningView::createContextMenu()
{
	pContextMenu = new QMenu(tr("Block"),pGraphicsView);
	pContextMenu->addAction(pAddRelation);
	pContextMenu->addAction(pAddProcessBlock);
	pContextMenu->addAction(pAddDataBlock);
	pContextMenu->addAction(pDeleteBlock);
	pContextMenu->addAction(pSettings);
	//pContextMenu->addAction(pLineDel);
}
myTree *DesigningView::getTreeProcess() const
{
	return treeProcess;
}

void DesigningView::setTreeProcess(myTree *value)
{
	treeProcess = value;
}

void DesigningView::addLinePaint(BlockItem *bi1, BlockItem *bi2)
{
	pGraphicsView->addLinePaint(bi1,bi2);
}

myTree *DesigningView::getTreeData() const
{
	return treeData;
}

void DesigningView::setTreeData(myTree *value)
{
	treeData = value;
}

QString DesigningView::getBracketProcess() const
{
	return bracketProcess;
}

void DesigningView::setBracketProcess(const QString &value)
{
	bracketProcess = value;
}

QString DesigningView::getBracketData() const
{
	return bracketData;
}

void DesigningView::setBracketData(const QString &value)
{
	bracketData = value;
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
	QGraphicsLineItem *line = qgraphicsitem_cast<QGraphicsLineItem *>(pGraphicsView->itemAt(point));

	pAddRelation->setVisible(bi);
	pDeleteBlock->setVisible(bi);
	pSettings->setVisible(bi);
	pAddDataBlock->setVisible(!bi);
	pAddProcessBlock->setVisible(!bi);
	//pLineDel->setVisible(line);:ToDo : если будет время.
	pContextMenu->exec(QWidget::mapToGlobal(point));
}


void DesigningView::addBlock(BlockType type, QPoint point)
{
	BlockItem *item;

	QString name;
	switch (type)
	{
	case processBlock:
		name = QString("П%1").arg(pListProces.count());//Процесс%
		item = new BlockItem(type,name);
		pListProces.append(item);
		break;
	case dataBlock:
		name = QString("Д%1").arg(pListData.count());//"Данные%1
		item = new BlockItem(type,name);
		pListData.append(item);
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

void DesigningView::addLine(int fromData, int toProcess)
{
	if ((pListData.count() > fromData) && (pListProces.count() > toProcess))
	pGraphicsView->addLinePaint(pListData.at(fromData),pListProces.at(toProcess));
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

void DesigningView::lineDelete()
{
	QGraphicsLineItem *line = qgraphicsitem_cast<QGraphicsLineItem *>(pGraphicsView->itemAt(pLastKeyPoint));



//	foreach (BlockItem *block, pListData)
//	{
//		pListData
//	}
}

void DesigningView::startFunc()
{
	//ToDo: Удалить перед релизом
	addBlock(processBlock,QPoint(360,100));
	addBlock(processBlock,QPoint(360,200));
	addBlock(processBlock,QPoint(360,300));
	addBlock(processBlock,QPoint(360,400));


	pListProces.at(0)->setFrequencyOfActivation(5);
	pListProces.at(1)->setFrequencyOfActivation(5);
	pListProces.at(2)->setFrequencyOfActivation(1);
	pListProces.at(3)->setFrequencyOfActivation(1);


	addBlock(dataBlock,QPoint(160,200));
	addBlock(dataBlock,QPoint(160,400));
	addBlock(dataBlock,QPoint(560,200));
	addBlock(dataBlock,QPoint(560,400));
	addBlock(dataBlock,QPoint(560,500));
	pListData.at(0)->setFrequencyOfActivation(10);
	pListData.at(1)->setFrequencyOfActivation(1);
	pListData.at(2)->setFrequencyOfActivation(5);
	pListData.at(3)->setFrequencyOfActivation(10);
	pListData.at(4)->setFrequencyOfActivation(10);

	pGraphicsView->addLinePaint(pListData.at(0),pListProces.at(1));
	pGraphicsView->addLinePaint(pListData.at(0),pListProces.at(2));
	pGraphicsView->addLinePaint(pListData.at(1),pListProces.at(0));
	pGraphicsView->addLinePaint(pListData.at(1),pListProces.at(3));
	pGraphicsView->addLinePaint(pListData.at(2),pListProces.at(2));

	pGraphicsView->addLinePaint(pListData.at(3),pListProces.at(3));
	pGraphicsView->addLinePaint(pListData.at(3),pListProces.at(0));
	pGraphicsView->addLinePaint(pListData.at(4),pListProces.at(0));
	pGraphicsView->addLinePaint(pListData.at(4),pListProces.at(2));
	pGraphicsView->addLinePaint(pListData.at(4),pListProces.at(3));



	bracketData = "(Данные0,Данные1,(Данные2,Данные3)),Данные3";
	bracketProcess = "";
}

void DesigningView::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
	case Qt::Key_Plus:
		zoomIn();
		break;
	case Qt::Key_Minus:
		zoomOut();
		break;
	default:
		QWidget::keyPressEvent(event);
	}
}

#ifndef QT_NO_WHEELEVENT
//! [5]
void DesigningView::wheelEvent(QWheelEvent *event)
{
	scaleView(pow((double)2, -event->delta() / 240.0));
}
//! [5]
#endif

void DesigningView::zoomIn()
{
	scaleView(qreal(1.2));
}

void DesigningView::zoomOut()
{
	scaleView(1 / qreal(1.2));
}

void DesigningView::scaleView(qreal scaleFactor)
{
	qreal factor = pGraphicsView->transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
	if (factor < 0.07 || factor > 100)
		return;

	pGraphicsView->scale(scaleFactor, scaleFactor);
}
