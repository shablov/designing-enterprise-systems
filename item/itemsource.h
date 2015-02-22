#ifndef ITEMSOURCE_H
#define ITEMSOURCE_H
#include <QGraphicsItem>

class ItemSource : public QGraphicsItem
{
public:
	ItemSource();
	~ItemSource();
protected:
	virtual QRectF boundingRect() const;
	float height, width;
};

#endif // ITEMSOURCE_H
