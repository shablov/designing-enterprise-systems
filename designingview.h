#ifndef DESIGNINGVIEW_H
#define DESIGNINGVIEW_H

#include <QGraphicsView>

class QGraphicsScene;

class DesigningView : public QGraphicsView
{
	Q_OBJECT
public:
	DesigningView(QWidget *parent =- 0);
	~DesigningView();

private:
	QGraphicsScene *pGraphicsScene;
};

#endif // DESIGNINGVIEW_H
