#ifndef MATH_H
#define MATH_H
#include "block.h"
#include "matrix.h"
#include <QList>
#include <QGenericMatrix>

class math
{
public:
	math();
	~math();
	matrix convertFromList(QList<BlockItem *> pListData,QList<BlockItem *> pListProces);
	void calc(QList<BlockItem *> listData, QList<BlockItem *> listProces, const int aX, const int aY);
private:

};

#endif // MATH_H
