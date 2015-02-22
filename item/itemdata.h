#ifndef ITEMDATA_H
#define ITEMDATA_H
#include "itemsource.h"

class ItemData : public ItemSource
{
public:
	ItemData();
	~ItemData();

	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);
};

#endif // ITEMDATA_H
