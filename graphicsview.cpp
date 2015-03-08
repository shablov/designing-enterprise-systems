#include "graphicsview.h"
#include "block.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QMouseEvent>

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent)
	:QGraphicsView(scene,parent),pPaintLine(false)
{
	
}

GraphicsView::~GraphicsView()
{
	
}

void GraphicsView::mousePressEvent(QMouseEvent * event)
{
	if(pPaintLine)
		endLinePaint(QPointF(mapFromGlobal(QWidget::mapToGlobal(event->pos()))).toPoint());

	QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
	QGraphicsView::mouseReleaseEvent(event);
}


void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
	if(pPaintLine)
		LineRePaint(QPointF(mapFromGlobal(QWidget::mapToGlobal(event->pos()))).toPoint());
	QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
	if(!pPaintLine)
		startLinePaint( QPointF(mapFromGlobal(QWidget::mapToGlobal(event->pos()))).toPoint());

	QGraphicsView::mouseDoubleClickEvent(event);
}

void GraphicsView::startLinePaint(QPoint point)
{
	BlockItem *bi = qgraphicsitem_cast<BlockItem *>(itemAt(point));
	if (!bi)
	{
		//bi =  qgraphicsitem_cast<BlockItem *>(itemAt(point)->parentItem());
		QGraphicsTextItem *ti = qgraphicsitem_cast<QGraphicsTextItem *>(itemAt(point));
		if (ti) bi =  qgraphicsitem_cast<BlockItem *>(ti->parentItem());
	}
	if (bi)
	{
		pPaintLine = true;
		QLineF line;

		line.setP1(bi->pos());
		line.setP2(mapToScene(point));

		pLineItem = scene()->addLine(line);
		pLineItem->setZValue(10);
	}
}

void GraphicsView::LineRePaint(QPoint point)
{
	if (pPaintLine)
	{
		QLineF line(pLineItem->line().p1(),mapToScene(point));
		pLineItem->setLine(line);
	}
}

void GraphicsView::endLinePaint(QPoint point)
{
	pPaintLine = false;
	pLineItem->setZValue(0);
	BlockItem *bi1 = qgraphicsitem_cast<BlockItem *>(itemAt(mapFromScene(pLineItem->line().p1())));
	BlockItem *bi2 = qgraphicsitem_cast<BlockItem *>(itemAt(point));

	if (!bi1) bi1 = qgraphicsitem_cast<BlockItem *>(itemAt(mapFromScene(pLineItem->line().p1()))->parentItem());
	if (!bi2) bi2 = qgraphicsitem_cast<BlockItem *>(itemAt(point)->parentItem());

	if (bi1 && bi2 and bi1 != bi2 and bi1->getType() != bi2->getType() and !bi1->isReference(bi2))
	{
		QLineF line(bi1->pos(),bi2->pos());
		QGraphicsLineItem *lineItem = scene()->addLine(line);
		bi1->addLineItem(lineItem);
		bi2->addLineItem(lineItem);

		bi1->addReference(bi2);
		bi2->addReference(bi1);
	}
	scene()->removeItem(pLineItem);

}


