#include "mathem.h"
#include <QDebug>
#include "matrix.h"

enum mat
{
	col = 5,
	row = 5
};

math::math()
{

}

math::~math()
{

}

MyMatrix math::convertFromList(QList<BlockItem *> listData, QList<BlockItem *> listProces)
{
	qDebug()<<"!!!";
	//MatB
	//QList<BlockItem*> listData,listProces;


	MyMatrix matB(listData.count(),listProces.count()) ; //= new QGenericMatrix<listData.count(),listProces.count(),int>;
	MyMatrix matFp(1,listProces.count());

	//listProces.

	for(int j = 0;j<listProces.count();j++)
		for(int i = 0; i <listData.count(); i++)
			matB.setData(i,j,listProces.at(j)->isReference(listData.at(i)));
	qDebug()<<"B";
	matB.display();
	for(int i = 0; i < listProces.count(); i++)
		matFp.setData(0,i, listProces[i]->getFrequencyOfActivation());
	qDebug()<<"Fp";
	matFp.display();


	MyMatrix matBuff = MyMatrix::multiBitwise(matB,matFp);
	qDebug()<<"Buff";
	matBuff.display();

	MyMatrix matBuff2 = MyMatrix::transposition(matB);

	qDebug()<<"Buff2";
	matBuff2.display();

	MyMatrix matAf = MyMatrix::multi(matBuff,matBuff2);
	qDebug()<<"Af";
	matAf.display();
	MyMatrix matS = MyMatrix::RelativeFrequency(matAf);
	qDebug()<<"S";
	matS.display();
	return matS;
}

void math::calc(QList<BlockItem *> listData, QList<BlockItem *> listProces, const int aX, const int aY)
{

}

