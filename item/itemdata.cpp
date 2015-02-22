#include "itemdata.h"
#include <QPainter>
ItemData::ItemData()
{

}

ItemData::~ItemData()
{

}

void ItemData::paint(QPainter *painter, const QStyleOptionGraphicsItem*,  QWidget*)
{
	painter->setPen(Qt::black);
	painter->setBrush(Qt::white);
	QPoint
	   p0(-width/2,-height/2), p1(width/2,-height/2),
	   p2(width/2,height/2), p3(-width/2,height/2);
	 painter->drawLine(p0, p1);
	 painter->drawLine(p1, p2);
	 painter->drawLine(p2, p3);
	 painter->drawLine(p3, p0);
}
