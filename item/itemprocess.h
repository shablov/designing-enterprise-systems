#ifndef ITEMPROCESS_H
#define ITEMPROCESS_H
#include "itemsource.h"

class itemProcess: public ItemSource
{
public:
	itemProcess();
	~itemProcess();
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);

};

#endif // ITEMPROCESS_H
