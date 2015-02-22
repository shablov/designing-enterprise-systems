#include "itemsource.h"

ItemSource::ItemSource() : height(20), width(40)
{
	this->setFlags(QGraphicsItem::ItemIsMovable);
	this->setAcceptDrops(true);
}
QRectF ItemSource::boundingRect() const
{
  return QRectF(-width / 2, -height / 2, width, height);
}
ItemSource::~ItemSource()
{

}

