#ifndef MATH_H
#define MATH_H
#include "block.h"
#include <QList>
#include <QGenericMatrix>

class math
{
public:
	math();
	~math();
	virtual void convertFromList(QList<QGraphicsRectItem* > pListData,QList<QGraphicsRectItem* > pListProces);
	void calc(QList<BlockItem *> listData, QList<BlockItem *> listProces, const int aX, const int aY);
private:
	const int x;
	const int y;
};

#endif // MATH_H
