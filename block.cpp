#include "block.h"

#include <QBrush>
#include <QDebug>
#include <QPainter>
BlockItem::BlockItem(BlockType type, QString name ,QGraphicsItem *parent)
	:  height(100), width(100),QGraphicsRectItem(parent),pType(type),
	  frequencyOfActivation(1),allocated(false)
{
	setZValue(5);
	setRect(-height/2,-width/2,height,width);
	//setPen(Qt::black);

	setFlags(QGraphicsItem::ItemIsMovable);
	setFlags(QGraphicsItem::ItemIsFocusable);
    setAcceptDrops(true);
	textItem = new QGraphicsTextItem(this);
	textItem->setPos(-width / 2, -height / 2);
	textItem->setPlainText(name);
	textItem->setZValue(4);

	textFrequency =  new QGraphicsTextItem(this);
	textFrequency->setPos(-width / 2, -height / 2 + 15);
	textFrequency->setPlainText(QString("Частота:") + QString::number(frequencyOfActivation,'f',2));
	textFrequency->setZValue(4);

	switch (type)

	{
	case processBlock:
		setBrush(Qt::yellow);
		setPen( QPen(Qt::darkBlue) );
		break;
	case dataBlock:
		setBrush(Qt::green);
		setPen( QPen(Qt::darkBlue) );
		//textFrequency->setVisible(false);
		break;
	}
	connect(textItem, SIGNAL(destroyed()),this, SLOT(deleteLater()));//????
}


BlockItem::~BlockItem()
{
	for(int i = 0;i<pReference.count();i++)
	{
		pReference[i]->deleteLine(pLineList);
		pReference[i]->removeReference(this);
	}
	qDeleteAll(pLineList);

	//for(int i = 0;i<pLineList.count();i++)
	//{
	//	delete(pLineList.at(i));
	//}
}

void BlockItem::removeReferenceAndLine(BlockItem *bi)
{
	foreach (QGraphicsLineItem* line, pLineList)
	{
		if (bi->isLineItem(line))
		{
			bi->deleteLine(line);
			bi->removeReference(this);
			removeReference(bi);
		}
	}
}

void BlockItem::addReference(BlockItem* bi)
{
	pReference.append(bi);
}

void BlockItem::removeReference(BlockItem *bi)
{
	pReference.removeAll(bi);
}

QList<BlockItem*> BlockItem::reference()
{
	return pReference;
}

bool BlockItem::isReference(BlockItem *bi)
{
	if(pReference.indexOf(bi) == -1)
		return false;
	return true;
}

bool BlockItem::isLineItem(QGraphicsLineItem *line)
{
	if (pLineList.count(line) >= 0) return true;
	else return false;
}

void BlockItem::addLineItem(QGraphicsLineItem *line)
{
	pLineList.append(line);
}

void BlockItem::deleteLine(QList<QGraphicsLineItem *> list)
{
	for (int i=0;i<list.count();i++)
		pLineList.removeAll(list[i]);
}

void BlockItem::deleteLine(QGraphicsLineItem *lineitem)
{
	pLineList.removeAll(lineitem);
}



QString BlockItem::getName() const
{
	return textItem->toPlainText();
}

void BlockItem::setName(const QString name)
{
	textItem->setPlainText(name);
}

void BlockItem::rePaintLine()
{
	for(int i = 0;i<pLineList.count();i++)
	{
		QLineF line1,line2;
		line1.setPoints(pos(), pLineList[i]->line().p1());
		line2.setPoints(pos(), pLineList[i]->line().p2());
		if (line1.length() < line2.length())
			pLineList[i]->setLine(line1);
		else
			pLineList[i]->setLine(line1);
	}
}
double BlockItem::getFrequencyOfActivation() const
{
	return frequencyOfActivation;
}

void BlockItem::setFrequencyOfActivation(double value)
{
	frequencyOfActivation = value;
	textFrequency->setPlainText(QString("Частота:") + QString::number(frequencyOfActivation,'f',2));
}

void BlockItem::paint(QPainter *painter, const QStyleOptionGraphicsItem* option,  QWidget* widget)
{
	rePaintLine();
	QGraphicsRectItem::paint(painter,option,widget);
}
