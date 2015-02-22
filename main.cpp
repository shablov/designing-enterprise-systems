#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsView>
#include "scene.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

//	Scene scene(&w);
//	QGraphicsView view(&scene);
//	scene.setSceneRect(-10,-10,640,480);

////	view.show();
//	view.setAcceptDrops(true);

//	QGraphicsItem* item  = scene.addEllipse(0,0,100,100, QPen(), QBrush(Qt::red));
//	item->setAcceptDrops(true);
//	item->setFlags(QGraphicsItem::ItemIsMovable);

//	QGraphicsItem* item2  = scene.addEllipse(0,0,100,100, QPen(), QBrush(Qt::red));
//	item2->setAcceptDrops(true);
//	item2->setFlags(QGraphicsItem::ItemIsMovable);



	return a.exec();
}
