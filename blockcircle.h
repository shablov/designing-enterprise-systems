#ifndef BLOCKCIRCLE_H
#define BLOCKCIRCLE_H

#include <QGraphicsEllipseItem>
#include <QList>
#include <QPoint>
//#include <QObject>

class BlockItemF;

class BlockCircle :public QObject, public QGraphicsItem
{
	Q_OBJECT
public:

	explicit BlockCircle(BlockItemF* stBlock,double stRelativeFrequency,BlockItemF *enBlock,double enRelativeFrequency, QGraphicsItem *w = 0);
	void rePaint(bool b);

protected:
	//QPoint startPoint; //0
	//QPoint endPoint; //1
	QGraphicsLineItem *lineItem;
};

struct linkPaint
{
bool direction; //0->1
BlockCircle *blockCircle;
};
#endif // BLOCKITEM_H
