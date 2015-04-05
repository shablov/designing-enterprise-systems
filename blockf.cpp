#include "blockf.h"
#include "blockcircle.h"
#include <QBrush>
#include <QDebug>
#include <QPainter>
BlockItemF::BlockItemF(QString name , QGraphicsItem *parent)
	:  height(100), width(100),QGraphicsRectItem(parent)
{
	setFlags(QGraphicsItem::ItemIsMovable);
	setFlags(QGraphicsItem::ItemIsFocusable);
	setAcceptDrops(true);

	setZValue(5);
	setRect(-height/2,-width/2,height,width);

	setFlags(QGraphicsItem::ItemIsMovable);
	setFlags(QGraphicsItem::ItemIsFocusable);
	setAcceptDrops(true);
	textItem = new QGraphicsTextItem(this);
	textItem->setPos(-width / 2, -height / 2);
	textItem->setPlainText(name);
	textItem->setZValue(4);
	
//	connect(textItem, SIGNAL(destroyed()),this, SLOT(deleteLater()));//????
}


BlockItemF::~BlockItemF()
{
	
}

void BlockItemF::addLineCircle(BlockCircle *circle, bool b)
{
//	linkPaint lp;
//	lp.blockCircle = circle;
//	lp.direction = b;
//	pLineCircleList.append(lp);
}

void BlockItemF::rePaintCircle()
{
	
}

void BlockItemF::paint(QPainter *painter, const QStyleOptionGraphicsItem* option,  QWidget* widget)
{
	rePaintCircle();
	QGraphicsRectItem::paint(painter,option,widget);
}
