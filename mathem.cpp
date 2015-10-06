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

QString math::coefficients(MyMatrix matrix)
{
	matrix.display();
	QString result;
	double N,Ks,KSin,KSout,KSOin,KSOout;
	result = "Ks = %1 \nKsin = %2 \nKSout = %3 \nKSOin = %4 \nKSOout = %5 \n";

	KSin = 0;
	KSout = 0;
	Ks = 0;
	for(int i = 0;i<matrix.getCols();i++)
		for(int j = 0;j<matrix.getRows();j++)
		{
			Ks +=  matrix.getData(i,j);
			if (i != j)
				KSout += matrix.getData(i,j);
			else
				KSin += matrix.getData(i,j);
		}
	N = (matrix.getCols() * matrix.getRows());
	KSin = KSin / N;
	KSout = KSout / N;
	Ks = Ks / N;

	KSOin =  KSin/Ks;
	KSOout = KSout/Ks;

	return  result.arg(Ks).arg(KSin).arg(KSout).arg(KSOin).arg(KSOout);
}

MyMatrix math::convertFromList(QList<BlockItem *> listData, QList<BlockItem *> listProces, myTree *tree)
{
	pTree = tree;
	//qDebug()<<"!!!";
	//MatB
	//QList<BlockItem*> listData,listProces;


	MyMatrix matB(listData.count(),listProces.count()) ; //= new QGenericMatrix<listData.count(),listProces.count(),int>;
	MyMatrix matFp(1,listProces.count());

	//listProces.
	list.clear();
	for(int i = 0; i <listData.count(); i++)
		list.append(listData.at(i)->getName());
	for(int j = 0;j<listProces.count();j++)
		for(int i = 0; i <listData.count(); i++)
			matB.setData(i,j,listProces.at(j)->isReference(listData.at(i)));
	//qDebug()<<"B";
	matB.display();
	for(int i = 0; i < listProces.count(); i++)
		matFp.setData(0,i, listProces[i]->getFrequencyOfActivation());
	//qDebug()<<"Fp";
	matFp.display();


	MyMatrix matBuff = MyMatrix::multiBitwise(matB,matFp);
	//qDebug()<<"Buff";
	matBuff.display();

	MyMatrix matBuff2 = MyMatrix::transposition(matB);

	//qDebug()<<"Buff2";
	matBuff2.display();

	MyMatrix matAf = MyMatrix::multi(matBuff,matBuff2);
	//qDebug()<<"Af";
	matAf.display();
	MyMatrix matS = MyMatrix::RelativeFrequency(matAf);
	qDebug()<<"S";
	matS.display();

	matrix = matS;
	calc();


	return matrix;
}

void math::calc()
{
	if(pTree)
	{
		checklist = list;
		bool b = true;
		for(int i = 0;i < list.count()-1;i++)
			for(int j = i+1;j < list.count();j++)
				if (list.at(i) == list.at(j))
				{
					QMessageBox msgBox;
					msgBox.setText("Имеются повторяющиеся имена :\"" + list.at(i) + "\". Расчеты могут быть неверные"  );
					msgBox.setStandardButtons(QMessageBox::Ok);
					msgBox.setIcon(QMessageBox::Warning);
					msgBox.exec();
					b = false;
				}

		//pTree->MyName;
		if (b)
			//		if(!checkReturnName(pTree))
		{
			//			addName();
			qDebug()<<"add Name"<<pTree->MyName;
			setListTree(pTree);

			QList<myTree *> buff = listTree;

			QList<int > buff2;

			for(int i = 0;i<listTree.count();i++)
			{
				qDebug()<<buff.at(i)->MyName<<" "<<list.indexOf(buff.at(i)->MyName);
				buff2.append(list.indexOf(buff.at(i)->MyName));
			}
			listTree.clear();

			int integer = 0;
			for(int i = 0;i<buff2.count();i++)
			{
				listTree.append(buff.at(buff2.indexOf(i)));
			}
			calc(pTree);
		}
	}

}

void math::calc(QList<BlockItem *> listData, QList<BlockItem *> listProces, const int aX, const int aY)
{

}

void math::setListTree(myTree *tree)
{


	if (tree->child.count()!= 0)
	{
		for(int i = 0;i<tree->child.count();i++)
		{
			setListTree(tree->child.at(i));
		}
	}else
		listTree.append(tree);
}
void math::calc(myTree *tree)
{
	QList<myTree *> mTree;

	if(listTree.indexOf(tree) == -1);

	for (int i = 0;i<tree->child.count();i++)
	{
		if (listTree.indexOf(tree->child.at(i)) == -1)
			calc(tree->child.at(i));
		mTree.append(tree->child.at(i));
	}
	if (tree!= pTree) unionMatrix(mTree);
}

void math::unionMatrix(QList<myTree *> tree)
{

	MyMatrix newMat(matrix.getRows() - tree.count() + 1,matrix.getCols() - tree.count() + 1);
	newMat.fill(0);
	QList<myTree *> newTreeList;
	for(int i = 0;i<listTree.count();i++)
		if (tree.indexOf(listTree.at(i)) == -1)
			newTreeList.append(listTree.at(i));
	newTreeList.append(tree.at(0)->parent);
	//buff row;
	//buff col;
	qDebug()<<"-------------------------------------------------------------------";
	for (int i = 0;i< matrix.getCols();i++)
	{
		for (int j = 0;j< matrix.getRows();j++)
		{
			if(tree.indexOf(listTree.at(j)) != -1 and tree.indexOf(listTree.at(i)) != -1)
			{
				newMat.PlusData(newTreeList.count() - 1,newTreeList.count()-1,matrix.getData(j,i)/tree.count()/tree.count());
				qDebug()<<"\n0 "<<newTreeList.count() - 1<<" "<<newTreeList.count()-1<<matrix.getData(j,i)/tree.count()/tree.count();

			}
			else if(tree.indexOf(listTree.at(j)) == -1 and tree.indexOf(listTree.at(i)) == -1)
			{
				newMat.PlusData(newTreeList.indexOf(listTree.at(j)),newTreeList.indexOf(listTree.at(i)),matrix.getData(j,i));
				qDebug()<<"\n1 "<<newTreeList.indexOf(listTree.at(j))<<" "<<newTreeList.indexOf(listTree.at(i))<<matrix.getData(j,i);
			}
			else if (tree.indexOf(listTree.at(j)) == -1 and tree.indexOf(listTree.at(i)) != -1)
			{
				newMat.PlusData(newTreeList.indexOf(listTree.at(j)),newTreeList.count()-1,matrix.getData(j,i)/tree.count());
				qDebug()<<"\n2 "<<newTreeList.indexOf(listTree.at(j))<<" "<<newTreeList.count()-1<<matrix.getData(j,i);

			}
			else
			{
				newMat.PlusData(newTreeList.count()-1,newTreeList.indexOf(listTree.at(i)),matrix.getData(j,i)/tree.count());
				 qDebug()<<"\n3 "<<newTreeList.count()-1<<newTreeList.indexOf(listTree.at(i))<<" "<<matrix.getData(j,i);
			}

			qDebug()<<"matixA";
			matrix.setData(j,i,0);
			matrix.display();
			qDebug()<<"matixB";
			newMat.display();
		}
	}
	listTree = newTreeList;
	matrix.display();
	matrix = newMat;
	qDebug()<<"matix";
	matrix.display();
}

QStringList math::newTreeList()
{

	QStringList result;
	for (int i = 0;i< listTree.count();i++)
	{
		result.append(listTree.at(i)->MyName);
	}
<<<<<<< HEAD
	if (result.count() != 0) return result;
	return list;
=======
    return list;
>>>>>>> origin/master
}



//void math::addName()
//{
//	if (!pTree)
//	{
//		pTree = new myTree;
//		pTree->MyName = "";
//	}else

//	for(int i = 0; i<checklist.count();i++)
//	{
//		myTree *tree = new myTree;
//		tree->MyName += checklist.at(i);
//		pTree->MyName += tree->MyName + ", ";
//		pTree->child.append(tree);
//	}
//	pTree->MyName =  "(" + pTree->MyName.left(pTree->MyName.count() - 1) + ")";
//	//qDebug()<<pTree->MyName;
//}

//bool math::checkReturnName(myTree *tree)
//{
//	if (tree->child.count()==0)
//		if (checklist.count(tree->MyName) == -1)
//		{
//			QMessageBox msgBox;
//			msgBox.setText("Не известное имя:" + tree->MyName );
//			msgBox.setStandardButtons(QMessageBox::Ok);
//			msgBox.setIcon(QMessageBox::Warning);
//			msgBox.exec();
//			return false;
//		}else
//		{
//			checklist.removeAll(tree->MyName);
//			return true;
//		}
//	else
//	{
//		bool b = true;
//		for (int i = 0;i<tree->child.count();++i)
//		{
//			b &=  checkReturnName(tree->child.at(i));
//		}
//		return b;
//	}
//}
