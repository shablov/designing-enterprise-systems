#include "designingviewf.h"

#include "blockf.h"
#include "blockcircle.h"
#include "graphicsview.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMenu>
#include <QDebug>
#include <QVBoxLayout>
#include "blockcontextmenu.h"

DesigningViewF::DesigningViewF(matrix mat, QWidget *parent) : QWidget(parent)
{
	setAcceptDrops(true);
	pGraphicsScene = new QGraphicsScene(this);
	pGraphicsView = new QGraphicsView(pGraphicsScene,this);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(pGraphicsView);
	visibleGraph(mat);
}
DesigningViewF::~DesigningViewF()
{

}

void DesigningViewF::visibleGraph(matrix mat)
{
	BlockItemF *qgri = new BlockItemF("123");
	pGraphicsScene->addItem(qgri);
	qgri->setPos(300,300);

	BlockItemF *qgri2 = new BlockItemF("1234");
	pGraphicsScene->addItem(qgri2);
	qgri2->setPos(100,100);

//	BlockCircle *circle = new BlockCircle(qgri,5,qgri2,10);

//	pGraphicsScene->addItem(circle);


	pGraphicsScene->addLine(QLine(0,0,360,0));
	pGraphicsScene->addLine(QLine(0,0,0,360));

}
