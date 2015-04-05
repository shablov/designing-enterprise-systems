#ifndef BLOCKITEMF_H
#define BLOCKITEMF_H

#include <QGraphicsItem>
#include <QList>

class BlockCircle;


class BlockItemF :public QObject, public QGraphicsRectItem
{
	Q_OBJECT
public:
	BlockItemF( QString name = "", QGraphicsItem *parent = -0);
	~BlockItemF();
	
	void addLineCircle(BlockCircle * circle,bool b);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	
protected:
	float height, width;
	QGraphicsTextItem *textItem;
private:
	void rePaintCircle();
	QList<BlockItemF*> pLineCircleList;
};

#endif // BLOCKITEM_H
