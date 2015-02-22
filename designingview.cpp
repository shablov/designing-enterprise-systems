#include "designingview.h"

#include "item.h"

#include <QGraphicsView>
#include <QGraphicsScene>

#include <QDebug>
#include <QVBoxLayout>

DesigningView::DesigningView(QWidget *parent) : QWidget(parent)
{
	pGraphicsView = new QGraphicsView(this);
	pGraphicsScene = new QGraphicsScene(this);
	pGraphicsView->setScene(pGraphicsScene);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(pGraphicsView);

	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(QPoint)), SLOT(onCustomContextMenuRequested(QPoint)));
}

DesigningView::~DesigningView()
{

}

void DesigningView::onCustomContextMenuRequested(const QPoint &point)
{
}
