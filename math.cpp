#include "math.h"
#include <QDebug>
#include "matrix.h"

enum mat
{
	col = 5,
	row = 5
};

math::math():x(5),y(2)
{

}

math::~math()
{

}

void math::convertFromList(QList<QGraphicsRectItem *> pListData, QList<QGraphicsRectItem *> pListProces)
{
	qDebug()<<"!!!";
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

	matrix matB(listData.count(),listProces.count()) ; //= new QGenericMatrix<listData.count(),listProces.count(),int>;
	matrix matFp(1,listProces.count());


	for(int j = 0;j<listProces.count();j++)
		for(int i = 0; i <listData.count(); i++)
			matB.setData(i,j,listProces.at(j)->isReference(listData.at(i)));
	matB.display();
	for(int i = 0; i < listProces.count(); i++)
		matFp.setData(0,i, listProces[i]->getFrequencyOfActivation());
	matFp.display();
	matrix ma = matFp.transposition();
	ma.display();

	ma = matrix::multi(matB,matB.transposition());
	ma.display();
}

void math::calc(QList<BlockItem *> listData, QList<BlockItem *> listProces, const int aX, const int aY)
{
//	QGenericMatrix<aX,aY,int> matR;
}

