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
	DesigningViewF(MyMatrix mat, QList<BlockItem*> blockItems,QStringList list,QWidget *parent = 0);
	//DesigningViewF(MyMatrix mat, QStringList stringlist,BlockType Type,QWidget *parent = 0);
	~DesigningViewF();

	void itemMoved();

	QGraphicsScene *scene();

public slots:
	void shuffle();
	void zoomIn();
	void zoomOut();

protected:
	void resizeEvent(QResizeEvent *event);
	void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
#ifndef QT_NO_WHEELEVENT
	void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
#endif

	void scaleView(qreal scaleFactor);

private:
	int timerId;
	int count;
protected:
	void timerEvent(QTimerEvent *);


private:
	void visibleGraph(MyMatrix mat);
	QList<BlockItem *> pListBlockItem;
	QStringList pstringList;
	QGraphicsScene *pScene;
	BlockType type;
	QGraphicsView *pView;
	int integer;


};

#endif // DESIGNINGVIEW_H
