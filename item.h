#ifndef ITEMSOURCE_H
#define ITEMSOURCE_H

#include <QGraphicsItem>

enum ItemType
{
	dataItem,
	processItem
};

class ItemSource : public QGraphicsItem
{
public:
	ItemSource(ItemType type, QGraphicsItem *parent = 0);
	~ItemSource();

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
protected:
	virtual QRectF boundingRect() const;
	float height, width;

private:
	ItemType pType;
};

#endif // ITEMSOURCE_H
