#ifndef ITEMSOURCE_H
#define ITEMSOURCE_H

#include <QGraphicsRectItem>

enum ItemType
{
	dataItem,
	processItem
};

class ItemSource : public QGraphicsRectItem
{
public:
	ItemSource(ItemType type, QGraphicsItem *parent = 0);
	~ItemSource();

protected:
	virtual QRectF boundingRect() const;
	float height, width;

private:
	ItemType type;
};

#endif // ITEMSOURCE_H
