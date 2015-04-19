#include "designingviewf.h"

#include "blockf.h"
#include "blockcircle.h"
#include "graphicsview.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMenu>
#include <QDebug>
#include <QVBoxLayout>
#include <QKeyEvent>
#include "blockcontextmenu.h"

#include "node.h"
#include "edge.h"
#include <math.h>

DesigningViewF::DesigningViewF(MyMatrix mat, QList<BlockItem *> blockItems, QWidget *parent)
	: QWidget(parent), pListBlockItem(blockItems), timerId(0)
{
	setAcceptDrops(true);
	pScene = new QGraphicsScene;
	pScene->setItemIndexMethod(QGraphicsScene::NoIndex);
	pScene->setSceneRect(0,0,720, 720);

	pView = new QGraphicsView(this);
	pView->setScene(pScene);
	pView->setCacheMode(QGraphicsView::CacheBackground);
	pView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	pView->setRenderHint(QPainter::Antialiasing);
	pView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	pView->scale(qreal(0.8), qreal(0.8));
	setMinimumSize(720, 720);
	visibleGraph(mat);
	shuffle();
}
DesigningViewF::~DesigningViewF()
{

}

void DesigningViewF::visibleGraph(MyMatrix mat)
{
	QList<Node*> nodes;
	for (int i = 0; i < pListBlockItem.count(); i++)
	{
		Node *node = new Node(this, pListBlockItem.at(i)->getName());
		nodes << node;
		scene()->addItem(node);
	}

	for (int i = 0; i < mat.getRows(); i++)
	{
		for (int j = 0; j < mat.getCols(); j++)
		{
			qreal freq = mat.getData(i,j);
			if (freq == 0)
			{
				continue;
			}
			scene()->addItem(new Edge(nodes.at(i), nodes.at(j), freq));
		}
	}
}

void DesigningViewF::itemMoved()
{
	if (!timerId)
		timerId = startTimer(1);
}

QGraphicsScene *DesigningViewF::scene()
{
	return pScene;
}
//! [2]

//! [3]
void DesigningViewF::keyPressEvent(QKeyEvent *event)
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
//! [3]

//! [4]
void DesigningViewF::timerEvent(QTimerEvent *event)
{
	Q_UNUSED(event);

	static int count = 0;
	if (count++ > 1000)
	{
		killTimer(timerId);
		timerId = 0;
		return;
	}

	QList<Node *> nodes;
	foreach (QGraphicsItem *item, scene()->items()) {
		if (Node *node = qgraphicsitem_cast<Node *>(item))
			nodes << node;
	}

	foreach (Node *node, nodes)
		node->calculateForces();

	bool itemsMoved = false;
	foreach (Node *node, nodes) {
		if (node->advance())
			itemsMoved = true;
	}

	if (!itemsMoved) {
		killTimer(timerId);
		timerId = 0;
	}
}
//! [4]

#ifndef QT_NO_WHEELEVENT
//! [5]
void DesigningViewF::wheelEvent(QWheelEvent *event)
{
	scaleView(pow((double)2, -event->delta() / 240.0));
}
//! [5]
#endif

//! [7]
void DesigningViewF::scaleView(qreal scaleFactor)
{
	qreal factor = pView->transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
	if (factor < 0.07 || factor > 100)
		return;

	pView->scale(scaleFactor, scaleFactor);
}
//! [7]

void DesigningViewF::shuffle()
{
	foreach (QGraphicsItem *item, scene()->items()) {
		if (qgraphicsitem_cast<Node *>(item))
			item->setPos(300 + qrand() % 300, 300 + qrand() % 300);
	}
}

void DesigningViewF::zoomIn()
{
	scaleView(qreal(1.2));
}

void DesigningViewF::zoomOut()
{
	scaleView(1 / qreal(1.2));
}
