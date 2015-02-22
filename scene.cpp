#include "scene.h"
#include "item/itemdata.h"
#include "item/itemprocess.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{

}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//	qDebug()<<event->button();

//	QGraphicsItem *item;// = this->addItem();

//	switch (event->button())
//	{
//	case 1://right
//		item = new ItemData();

//		break;
//	case 2://left
//		item = new itemProcess();
//		break;
//	}
//	//this->addItem(item);

//	item->setPos(event->scenePos());
//	//addItem(item);
//	//item->setAcceptDrops(true);
//	//item->setFlags(QGraphicsItem::ItemIsMovable);
}


Scene::~Scene()
{

}

