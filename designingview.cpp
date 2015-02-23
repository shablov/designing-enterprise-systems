#include "designingview.h"

#include "item.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMenu>
#include <QDebug>
#include <QVBoxLayout>

DesigningView::DesigningView(QWidget *parent) : QWidget(parent)
{
	pGraphicsView = new QGraphicsView(this);
	pGraphicsScene = new QGraphicsScene(this);
	pGraphicsView->setScene(pGraphicsScene);
	pGraphicsView->setAcceptDrops(true);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(pGraphicsView);

	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(QPoint)), SLOT(onCustomContextMenuRequested(QPoint)));
}

DesigningView::~DesigningView()
{

}
void DesigningView::createAction()
{
	//pAddRelations = new QAction(tr("add relations"), this);
	//pAddDataItem = new QAction(tr("Add data block"), this);
	//pAddProcessItem = new QAction(tr("Add process block"), this);

}
void DesigningView::onCustomContextMenuRequested(const QPoint &point)
{
	pLastPoint = QWidget::mapFromParent(point);//временное решение?
	pLastObj = pGraphicsView->itemAt(point);
	QMenu *ContextMenu = new QMenu(tr("File"),pGraphicsView);
	ContextMenu->popup(QWidget::mapToGlobal(point));
	if  (pLastObj) 	ContextMenu->addAction(tr("add relations"));
	ContextMenu->addAction(tr("Add process block"),this,SLOT(addProcessItem()));
	ContextMenu->addAction(tr("Add data block"),this,SLOT(addDataItem()));
	if  (pLastObj) ContextMenu->addAction(tr("delete block"),this,SLOT(deleteItem()));

	qDebug()<<pGraphicsView->itemAt(point);
	//qDebug()<<point;
}

void DesigningView::addItem(ItemType type, QPoint point)
{
	QGraphicsItem *item = new ItemSource(type);
	pGraphicsScene->addItem(item);
	item->setAcceptDrops(true);
	item->setFlags(QGraphicsItem::ItemIsMovable);
	item->setPos(point);
}

void DesigningView::addDataItem()
{
	addItem(dataItem,pLastPoint);
}

void DesigningView::deleteItem()
{
	//qDebug()<<pLastObj;
	qDebug()<<pGraphicsView->itemAt(pLastPoint);//????
	pGraphicsScene->removeItem(pLastObj);
}

void DesigningView::addProcessItem()
{
	addItem(processItem,pLastPoint);
}
