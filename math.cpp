#include "math.h"
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

matrix math::convertFromList(QList<BlockItem *> listData, QList<BlockItem *> listProces)
{
	qDebug()<<"!!!";
	//MatB
	//QList<BlockItem*> listData,listProces;


	matrix matB(listData.count(),listProces.count()) ; //= new QGenericMatrix<listData.count(),listProces.count(),int>;
	matrix matFp(1,listProces.count());

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


	matrix matBuff = matrix::multiBitwise(matB,matFp);
	qDebug()<<"Buff";
	matBuff.display();

	matrix matBuff2 = matrix::transposition(matB);

	qDebug()<<"Buff2";
	matBuff2.display();

	matrix matAf = matrix::multi(matBuff,matBuff2);
	qDebug()<<"Af";
	matAf.display();
	matrix matS = matrix::RelativeFrequency(matAf);
	qDebug()<<"S";
	matS.display();
	return matS;
}

void math::calc(QList<BlockItem *> listData, QList<BlockItem *> listProces, const int aX, const int aY)
{

}

