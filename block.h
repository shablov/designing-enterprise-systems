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

	void addReference(BlockItem* bi);
	void removeReference(BlockItem* bi);
	QList<BlockItem *> reference();
	bool isReference(BlockItem* bi);

	void addLineItem(QGraphicsLineItem * line);
	void deleteLine(QList<QGraphicsLineItem*> list);
	void deleteLine(QGraphicsLineItem* lineitem);

	BlockType getType(){return pType;}
	QString getName() const;
	void setName(const QString name);

	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	int getFrequencyOfActivation() const;
	void setFrequencyOfActivation(int value);

protected:
	float height, width;
	QGraphicsTextItem *textItem;
	QGraphicsTextItem *textFrequency;
private:
	void rePaintLine();

	BlockType pType;
	QList<QGraphicsLineItem*> pLineList;
	QList<BlockItem*> pReference;
	int frequencyOfActivation;
};

#endif // BLOCKITEM_H
