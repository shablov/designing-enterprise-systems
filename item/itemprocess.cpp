#include "itemprocess.h"
#include <QPainter>
itemProcess::itemProcess()
{

}

itemProcess::~itemProcess()
{

}

void itemProcess::paint(QPainter *painter, const QStyleOptionGraphicsItem*,  QWidget*)
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

	 QPoint
		p10(-width/4,-height/4), p11(width/4,-height/4),
		p12(width/4,height/4), p13(-width/4,height/4);
	 painter->drawLine(p10, p11);
	 painter->drawLine(p11, p12);
	 painter->drawLine(p12, p13);
	 painter->drawLine(p13, p10);
}

