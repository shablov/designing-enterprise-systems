#include "mathem.h"
#include <QDebug>
#include "matrix.h"

enum mat
{
    col = 5,
    row = 5
};

math::math()
{//

}

math::~math()
{

}

QString math::coefficients(MyMatrix matrix)
{
    qDebug()<<"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    matrix.display();

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

    return  result.arg(Ks,0,'f',2).arg(KSin,0,'f',2).arg(KSout,0,'f',2).arg(KSOin,0,'f',2).arg(KSOout,0,'f',2);
}

MyMatrix math::convertFromList(QList<BlockItem *> listData, QList<BlockItem *> listProces, myTree *tree)
{
    pTree = tree;
    //qDebug()<<"!!!";
    //MatB
    //QList<BlockItem*> listData,listProces;
    Vichisleniya = "";

    MyMatrix matB(listData.count(),listProces.count()) ; //= new QGenericMatrix<listData.count(),listProces.count(),int>;
    MyMatrix matFp(1,listProces.count());

    //listProces.
    list.clear();
    for(int i = 0; i <listData.count(); i++)
        list.append(listData.at(i)->getName());
    for(int j = 0;j<listProces.count();j++)
        for(int i = 0; i <listData.count(); i++)
            matB.setData(i,j,listProces.at(j)->isReference(listData.at(i)));
    SaveResultInStr("B",matB);
    //qDebug()<<"B";
    matB.display();
    for(int i = 0; i < listProces.count(); i++)
        matFp.setData(0,i, listProces[i]->getFrequencyOfActivation());
    SaveResultInStr("Fp",matFp);
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
    SaveResultInStr("Af",matAf);
    matAf.display();
    MyMatrix matS = MyMatrix::RelativeFrequency(matAf);
    SaveResultInStr("S:",matS,&list);
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



            qDebug()<< "qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq";
            matrixDel.display();
            matrix.display();

            qDebug()<< "qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";

            calc(pTree);

            matrix.display();
            matrixDel.display();
            for (int i = 0;i< matrix.getCols();i++)
            {
                for (int j = 0;j< matrix.getRows();j++)
                {
                    int val = matrixDel.getData(j,i);
                    if(val != 0)
                    {
                        matrix.setData(j,i,matrix.getData(j,i)/val);
                    }
                }
            }
           // SaveResultInStr("Объединение:",matrix,listTree);
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

    MyMatrix newMat(matrix.getRows(),matrix.getCols(),0);
    matrixDel = newMat;

    for(int i = 0; i <  matrix.getRows();i++)
        for(int j = 0; j <  matrix.getCols();j++)
            if (matrix.getData(i,j) != 0 )
                matrixDel.setData(i,j,1);
            else
                matrixDel.setData(i,j,0);


    mainList =  QList<QList<myTree *>>();
    treeToList(tree,0);

    qDebug()<<"00000000000000000000000000000000000000000000000000";

    for(int i = 0; i < mainList.count() ;i++)

        for(int j = 0; j < mainList.at(i).count();j++)
            qDebug()<<mainList.count()*100 + i<<" "<<mainList.at(i).count()*100 + j << " " + mainList.at(i).at(j)->MyName;

    if (mainList.count() < 2) return;

    for(int i = mainList.count() - 1; i > 0;i--)
    {
        for(int j = 0; j < mainList.at(i).count();j++)
        {
            qDebug()<<i;
            QList<myTree *> mTree;// =  QList<myTree *>;
            for (int k = 0;k< mainList.at(i).at(j)->child.count();k++)
            {
                mTree.append(mainList.at(i).at(j)->child.at(k));
            }
            if (mTree.count() > 1)
                unionMatrix(mTree);
        }

        for (int i = 0;i< matrix.getCols();i++)
        {
            for (int j = 0;j< matrix.getRows();j++)
            {
                int val = matrixDel.getData(j,i);
                if(val != 0)
                {
                    matrix.setData(j,i,matrix.getData(j,i)/val);
                }
            }
        }
        SaveResultInStr("Объединение:",matrix,listTree);

        MyMatrix newMat(matrix.getRows(),matrix.getCols(),0);
        matrixDel = newMat;

        for(int i = 0; i <  matrix.getRows();i++)
            for(int j = 0; j <  matrix.getCols();j++)
                if (matrix.getData(i,j) != 0 )
                    matrixDel.setData(i,j,1);
                else
                    matrixDel.setData(i,j,0);

    }



    /*
    for (int i = 0;i<tree->child.count();i++)
    {
        if (listTree.indexOf(tree->child.at(i)) == -1)
            calc(tree->child.at(i));
        mTree.append(tree->child.at(i));
    }
    if (tree!= pTree) unionMatrix(mTree);*/
}

void math::treeToList(myTree *tree,int level)
{
    QList<myTree *> a = QList<myTree *>();
    qDebug()<<tree->MyName;
    while(mainList.count() <= level)
        mainList.append(QList<myTree *>());
    qDebug()<<'b';

    mainList[level].append(tree);
    qDebug()<<'c';

    for(int i = 0; i <tree->child.count(); i++)
        treeToList( tree->child.at(i),level + 1);

}



void math::unionMatrix(QList<myTree *> tree)
{


    MyMatrix newMat(matrix.getRows() - tree.count() + 1,matrix.getCols() - tree.count() + 1);
    MyMatrix newMatDel(matrix.getRows() - tree.count() + 1,matrix.getCols() - tree.count() + 1);

    newMat.fill(0);
    newMatDel.fill(0);
    MyMatrix matNumberNotNull(matrix.getRows() - tree.count() + 1,matrix.getCols() - tree.count() + 1);
    matNumberNotNull.fill(0);
    QList<myTree *> newTreeList;
    for(int i = 0;i<listTree.count();i++)
        if (tree.indexOf(listTree.at(i)) == -1)
            newTreeList.append(listTree.at(i));
    newTreeList.append(tree.at(0)->parent);


    qDebug()<<"-------------------------------------------------------------------";
    for (int i = 0;i< matrix.getCols();i++)
    {
        for (int j = 0;j< matrix.getRows();j++)
        {
            if(tree.indexOf(listTree.at(j)) != -1 && tree.indexOf(listTree.at(i)) != -1)
            {
                newMat.PlusData(newTreeList.count() - 1,newTreeList.count()-1,matrix.getData(j,i));
                qDebug()<<"\n0 "<<newTreeList.count() - 1<<" "<<newTreeList.count()-1<<matrix.getData(j,i);

                newMatDel.PlusData(newTreeList.count() - 1,newTreeList.count()-1,1);

            }
            else if(tree.indexOf(listTree.at(j)) == -1 && tree.indexOf(listTree.at(i)) == -1)
            {
                newMat.PlusData(newTreeList.indexOf(listTree.at(j)),newTreeList.indexOf(listTree.at(i)),matrix.getData(j,i));
                newMatDel.PlusData(newTreeList.indexOf(listTree.at(j)),newTreeList.indexOf(listTree.at(i)),matrixDel.getData(j,i));

                // qDebug()<<"\n1 "<<newTreeList.indexOf(listTree.at(j))<<" "<<newTreeList.indexOf(listTree.at(i))<<matrix.getData(j,i);

                //newMatDel.PlusData(newTreeList.indexOf(listTree.at(j)),newTreeList.indexOf(listTree.at(i)),1);
            }
            else if (tree.indexOf(listTree.at(j)) == -1 && tree.indexOf(listTree.at(i)) != -1)
            {
                newMat.PlusData(newTreeList.indexOf(listTree.at(j)),newTreeList.count()-1,matrix.getData(j,i));
                newMatDel.PlusData(newTreeList.indexOf(listTree.at(j)),newTreeList.count()-1,matrixDel.getData(j,i));

                //qDebug()<<"\n2 "<<newTreeList.indexOf(listTree.at(j))<<" "<<newTreeList.count()-1<<matrix.getData(j,i);
                //if(matrix.getData(j,i) != 0)
                //     matNumberNotNull.PlusData(newTreeList.indexOf(listTree.at(j)),newTreeList.count()-1,1);
            }
            else
            {
                newMat.PlusData(newTreeList.count()-1,newTreeList.indexOf(listTree.at(i)),matrix.getData(j,i));
                newMatDel.PlusData(newTreeList.count()-1,newTreeList.indexOf(listTree.at(i)),matrixDel.getData(j,i));

                //qDebug()<<"\n3 "<<newTreeList.count()-1<<newTreeList.indexOf(listTree.at(i))<<" "<<matrix.getData(j,i);
                //if(matrix.getData(j,i) != 0)
                //    matNumberNotNull.PlusData(newTreeList.count()-1,newTreeList.indexOf(listTree.at(i)),1);
            }

            //   qDebug()<<"matixA";
            matrix.setData(j,i,0);
            matrix.display();
            //  qDebug()<<"matixB";
            newMat.display();
        }
    }


    newMat = newMat.transposition(newMat);//Надо избавиться!!
    listTree = newTreeList;
    matrix.display();
    matrix = newMat;
    matrixDel = newMatDel;
    //  qDebug()<<"matix";
    matrix.display();


    //SaveResultInStr("Объединение:",matrix,listTree);

    //SaveResultInStr("Объединение1:",matNumberNotNull,listTree);

}

void math::SaveResultInStr(QString str, MyMatrix m, QList<myTree *> list)
{
    Vichisleniya += str + "\n";

    for (int i = 0; i< list.count();i++)
        Vichisleniya+= list.at(i)->MyName + ";";
    Vichisleniya+= "\n";

    for (int i = 0; i< m.getRows();i++)
    {
        for (int j = 0; j< m.getCols();j++)
            Vichisleniya+= QString::number(m.getData(i,j),'f',2) + "\t";
        Vichisleniya+= "\n";
    }
}



void math::SaveResultInStr(QString str, MyMatrix m, QStringList *list)
{
    Vichisleniya += str + "\n";

    for (int i = 0; i< list->count();i++)
        Vichisleniya+= list->at(i) + ";";
    Vichisleniya+= "\n";

    for (int i = 0; i< m.getRows();i++)
    {
        for (int j = 0; j< m.getCols();j++)
            Vichisleniya+= QString::number(m.getData(i,j),'f',2) + "\t";
        Vichisleniya+= "\n";
    }
}

QString math::getVichisleniya() const
{
    return Vichisleniya;
}

void math::setVichisleniya(const QString &value)
{
    Vichisleniya = value;
}


void math::SaveResultInStr( QString str,MyMatrix m)
{

    Vichisleniya += str + "\n";
    for (int i = 0; i< m.getRows();i++)
    {
        for (int j = 0; j< m.getCols();j++)
            Vichisleniya+= QString::number(m.getData(i,j),'f',2) + "\t";
        Vichisleniya+= "\n";
    }
}



QStringList math::newTreeList()
{

    QStringList result;
    for (int i = 0;i< listTree.count();i++)
    {
        result.append(listTree.at(i)->MyName);
    }
    //<<<<<<< HEAD
    if (result.count() != 0) return result;
    return list;
    //=======
    //   return list;
    //>>>>>>> origin/master
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
