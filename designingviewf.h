#ifndef DESIGNINGVIEWF_H
#define DESIGNINGVIEWF_H

#include <block.h>
#include "designingviewf.h"
#include "designingview.h"
#include "blockcontextmenu.h"
#include "matrix.h"
#include <QGraphicsView>
class QGraphicsScene;


class DesigningViewF : public QWidget
{
	Q_OBJECT

public slots:


public:
	DesigningViewF(MyMatrix mat, QList<BlockItem*> blockItems,QWidget *parent = 0);
	~DesigningViewF();

	void itemMoved();

	QGraphicsScene *scene();

public slots:
	void shuffle();
	void zoomIn();
	void zoomOut();

protected:
	void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
#ifndef QT_NO_WHEELEVENT
	void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
#endif

	void scaleView(qreal scaleFactor);

private:
	int timerId;
protected:
	void timerEvent(QTimerEvent *);


private:
	void visibleGraph(MyMatrix mat);
	QList<BlockItem *> pListBlockItem;
	QGraphicsScene *pScene;
	QGraphicsView *pView;


};

#endif // DESIGNINGVIEW_H
