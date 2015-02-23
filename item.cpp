#include "item.h"

#include <QBrush>
#include <QPainter>
ItemSource::ItemSource(ItemType type, QGraphicsItem *parent)
	: QGraphicsItem(parent), height(20), width(40),pType(type)
{
	setFlags(QGraphicsItem::ItemIsMovable);
	setAcceptDrops(true);

}
QRectF ItemSource::boundingRect() const
{
  return QRectF(-width / 2, -height / 2, width, height);
}
ItemSource::~ItemSource()
{

}

void ItemSource::paint(QPainter *painter, const QStyleOptionGraphicsItem*,  QWidget*)
{
	//ToDo: не совпадает прорисовка и QRectF, исправить
	switch (pType)
	{
	case dataItem:
		painter->setPen(Qt::red);
		painter->setBrush(Qt::green);
		break;
	case processItem:
		painter->setPen(Qt::black);
		painter->setBrush(Qt::yellow);
		break;
	default:
		break;
	}
	//painter->setPen(Qt::black);
	//painter->setBrush(Qt::white);
	//	QPoint
	//	   p0(-width/2,-height/2), p1(width/2,-height/2),
	//	   p2(width/2,height/2), p3(-width/2,height/2);
	//	 painter->drawLine(p0, p1);
	//	 painter->drawLine(p1, p2);
	//	 painter->drawLine(p2, p3);
	//	 painter->drawLine(p3, p0);

	 painter->drawRect(boundingRect());

}



