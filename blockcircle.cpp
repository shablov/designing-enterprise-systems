#include "blockcircle.h"
#include <QPoint>
#include "blockf.h"


BlockCircle::BlockCircle(BlockItemF *stBlock, double stRelativeFrequency, BlockItemF *enBlock, double enRelativeFrequency, QGraphicsItem *w)
{

	lineItem  =  new QGraphicsLineItem(this);
	QLineF line(stBlock->pos(),enBlock->pos());
	lineItem->setLine(line);	//textFrequency->setZValue(4);
}

void BlockCircle::rePaint(bool b)
{
	
}
