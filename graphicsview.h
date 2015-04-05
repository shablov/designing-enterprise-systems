#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsView>
#include "block.h"
class GraphicsView : public QGraphicsView
{
	Q_OBJECT
public:
	GraphicsView(QGraphicsScene *scene, QWidget * parent = 0);
	~GraphicsView();

	void startLinePaint(QPoint point);
	void endLinePaint(QPoint point);
	void addLinePaint(QGraphicsRectItem *startBI, QGraphicsRectItem *endBI);
signals:


public slots:
protected:
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent*event);
	virtual void mouseDoubleClickEvent(QMouseEvent*event);

private:
	void LineRePaint(QPoint point);

	QGraphicsLineItem *pLineItem;
	bool pPaintLine;

	// QWidget interface
protected:
	void resizeEvent(QResizeEvent *event);
};

#endif // GRAPHICSSCENE_H
