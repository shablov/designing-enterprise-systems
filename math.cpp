#include "math.h"
#include <QDebug>
math::math()
{

}

math::~math()
{

}

void math::convertFromList(QList<QGraphicsRectItem *> pListData, QList<QGraphicsRectItem *> pListProces)
{
	qDebug()<<"!!";
	//MatB
	QList<BlockItem*> listData,listProces;
	BlockItem *bi;
	for(int i =0;i<pListData.count();i++)
	{
		bi = qgraphicsitem_cast<BlockItem *>(pListData[i]);
		if(bi)listData.append(bi);
		else qDebug()<<"!!!!";
	}
	for(int i =0;i<pListProces.count();i++)
	{
		bi = qgraphicsitem_cast<BlockItem *>(pListProces[i]);
		if(bi)listProces.append(bi);
		else qDebug()<<"!!!!";
	}
//	int x = listData->count();
//	int y = listProces->count();
//	//calc(listData,listProces,x,y);



//	QGenericMatrix<4,3,int> matB;//fix plis
//	for(int j = 0;j<listProces->count();j++)
//	{
//		for(int i = 0; i <listData->count(); i++)
//			matB(i,j) = listProces->at(j)->isReference(listData->at(i));

//	}
//	qDebug()<<matB;
//	QGenericMatrix<1,3,int> matR;
//	for(int i = 0; i < listProces->count(); i++)
//		matR(0,i) = listProces->at(i)->getFrequencyOfActivation();
	//	qDebug()<<matR;
}

void math::calc(QList<BlockItem *> listData, QList<BlockItem *> listProces, const int aX, const int aY)
{
//	QGenericMatrix<aX,aY,int> matR;
}

