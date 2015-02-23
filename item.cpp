#include "item.h"

#include <QBrush>

ItemSource::ItemSource(ItemType type, QGraphicsItem *parent)
	: QGraphicsRectItem(parent), height(20), width(40)
{
	setFlags(QGraphicsItem::ItemIsMovable);
	setAcceptDrops(true);
	switch (type)
	{
	case dataItem:
		setBrush(QBrush(Qt::green));
		break;
	case processItem:
		setBrush(QBrush(Qt::yellow));
		break;
	default:
		break;
	}
}
QRectF ItemSource::boundingRect() const
{
  return QRectF(-width / 2, -height / 2, width, height);
}
ItemSource::~ItemSource()
{

}

