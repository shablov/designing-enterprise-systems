#ifndef DESIGNINGVIEW_H
#define DESIGNINGVIEW_H

#include <QWidget>
#include <block.h>
#include "graphicsview.h"
#include "blockcontextmenu.h"
class QGraphicsScene;
class QGraphicsView;


class DesigningView : public QWidget
{
	Q_OBJECT

public slots:


public:
	DesigningView(QWidget *parent =- 0);
	~DesigningView();

	void addBlock(BlockType type, QPoint point = QPoint(0,0));
	bool eventFilter(QObject *target, QEvent *event);
	BlockItem* refOnBlockItem(QPoint point);


	QList<BlockItem *> getListProces() const;
	QList<BlockItem *> getListData() const;


private slots:
	void onCustomContextMenuRequested(const QPoint &point);
	void addProcessBlock();
	//void addProcessBlock(QPoint point);
	void addDataBlock();
	void deleteBlock();
	void addRelation();
	void settingsBlock();


private:
	void startFunc(); //del
	void createAction();
	void createContextMenu();

	QPoint pLastKeyPoint;

	QAction *pAddRelation;
	QAction *pAddDataBlock ;
	QAction *pAddProcessBlock;
	QAction *pDeleteBlock;
	QAction *pSettings;


	QMenu *pContextMenu;
	GraphicsView *pGraphicsView;
	QGraphicsScene *pGraphicsScene;

	QList<BlockItem *> pListData;
	QList<BlockItem *> pListProces;

	BlockContextMenu* bcm;

};

#endif // DESIGNINGVIEW_H
