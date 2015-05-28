#ifndef MATH_H
#define MATH_H
#include "block.h"
#include "matrix.h"
#include <QList>
#include <QGenericMatrix>
#include "windowsbracketrecording.h"
#include <QMessageBox>
class math
{
public:
	math();
	~math();
	QString coefficients(MyMatrix matrix);
	QStringList newTreeList();
	MyMatrix convertFromList(QList<BlockItem *> pListData,QList<BlockItem *> pListProces,myTree *tree = 0);
private:
	bool checkReturnName(myTree *tree);
	void calc();
	//void addName();
	void calc(myTree *tree);
	void calc(QList<BlockItem *> listData, QList<BlockItem *> listProces, const int aX, const int aY);
	void setListTree(myTree* tree);
	void unionMatrix(QList<myTree*> tree);

	QStringList list;
	QStringList checklist;
	QList<myTree *> listTree;
	myTree *pTree;
	MyMatrix matrix;

};

#endif // MATH_H
