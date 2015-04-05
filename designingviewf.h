#ifndef DESIGNINGVIEWF_H
#define DESIGNINGVIEWF_H

#include <QWidget>
#include <block.h>
#include "designingviewf.h"
#include "designingview.h"
#include "blockcontextmenu.h"
#include "matrix.h"
class QGraphicsScene;
class QGraphicsView;


class DesigningViewF : public QWidget
{
	Q_OBJECT

public slots:


public:
	DesigningViewF(matrix mat,QWidget *parent =- 0);
	~DesigningViewF();

private slots:


private:
	void visibleGraph(matrix mat);

	QPoint pLastKeyPoint;
	QGraphicsView *pGraphicsView;
	QGraphicsScene *pGraphicsScene;
	QList<BlockItem *> pListBlockitem;


};

#endif // DESIGNINGVIEW_H
