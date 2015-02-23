#ifndef DESIGNINGVIEW_H
#define DESIGNINGVIEW_H

#include <QWidget>

class QGraphicsScene;
class QGraphicsView;

class DesigningView : public QWidget
{
	Q_OBJECT
public:
	DesigningView(QWidget *parent =- 0);
	~DesigningView();

private slots:
	void onCustomContextMenuRequested(const QPoint &point);

private:
	QGraphicsView *pGraphicsView;
	QGraphicsScene *pGraphicsScene;
};

#endif // DESIGNINGVIEW_H
