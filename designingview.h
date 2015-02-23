#ifndef DESIGNINGVIEW_H
#define DESIGNINGVIEW_H

#include <QWidget>
#include <item.h>
class QGraphicsScene;
class QGraphicsView;

class DesigningView : public QWidget
{
	Q_OBJECT

public slots:


public:
	DesigningView(QWidget *parent =- 0);
	~DesigningView();

	void addItem(ItemType type, QPoint point = QPoint(0,0));
private slots:
	void onCustomContextMenuRequested(const QPoint &point);
	void addProcessItem();
	void addDataItem();
	void deleteItem();
private:
	QPoint pLastPoint;
	QGraphicsItem *pLastObj;

	QAction *pAddRelations;
	QAction *pAddDataItem ;
	QAction *pAddProcessItem;

	QGraphicsView *pGraphicsView;
	QGraphicsScene *pGraphicsScene;
	void createAction();
};

#endif // DESIGNINGVIEW_H
