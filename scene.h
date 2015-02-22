#ifndef SCENE_H
#define SCENE_H

#include "item/itemdata.h"
#include "item/itemprocess.h"
#include <QGraphicsScene>
#include <QList>

class Scene : public QGraphicsScene {
	Q_OBJECT
public:
	Scene(QObject *parent = 0);
	~Scene();

signals:
public slots:
protected:
	//virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
//	QList<QGraphicsItem> *l_ItemData;
//s	QList<QGraphicsItem> *l_ItemProcess;
};

#endif // SCENE_H
