#ifndef BLOCKITEM_H
#define BLOCKITEM_H

#include <QGraphicsItem>
#include <QList>

enum BlockType
{
	dataBlock,
	processBlock,
	noneBlock
};

class BlockItem :public QObject, public QGraphicsRectItem
{
	Q_OBJECT
public:
	BlockItem(BlockType type = noneBlock, QString name = "", QGraphicsItem *parent = -0);
	~BlockItem();
	void removeReferenceAndLine(BlockItem* bi);
	void addReference(BlockItem* bi);
	void removeReference(BlockItem* bi);
	QList<BlockItem *> reference();
	bool isReference(BlockItem* bi);

	bool isLineItem(QGraphicsLineItem * line);
	void addLineItem(QGraphicsLineItem * line);
	void deleteLine(QList<QGraphicsLineItem*> list);
	void deleteLine(QGraphicsLineItem* lineitem);

	BlockType getType(){return pType;}
	QString getName() const;
	void setName(const QString name);

	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	double getFrequencyOfActivation() const;
	void setFrequencyOfActivation(double value);

protected:
	float height, width;
	QGraphicsTextItem *textItem;
	QGraphicsTextItem *textFrequency;
private:
	void rePaintLine();
	bool allocated;//toDo выделение объектов
	BlockType pType;
	QList<QGraphicsLineItem*> pLineList;
	QList<BlockItem*> pReference;
	double frequencyOfActivation;

};

#endif // BLOCKITEM_H
