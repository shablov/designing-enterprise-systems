#include "designingview.h"

#include <QGraphicsScene>

#include <QDebug>

DesigningView::DesigningView(QWidget *parent) : QGraphicsView(parent)
{
	pGraphicsScene = new QGraphicsScene(this);
	setScene(pGraphicsScene);
}

DesigningView::~DesigningView()
{

}
