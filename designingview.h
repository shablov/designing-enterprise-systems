#ifndef DESIGNINGVIEW_H
#define DESIGNINGVIEW_H

#include <QWidget>
#include <block.h>
#include "graphicsview.h"
#include "blockcontextmenu.h"
#include "windowsbracketrecording.h"
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
	void addLine(int fromData,int toProcess);

	QList<BlockItem *> getListProces() const;
	QList<BlockItem *> getListData() const;

	QString getBracketData() const;
	void setBracketData(const QString &value);

	QString getBracketProcess() const;
	void setBracketProcess(const QString &value);

	myTree *getTreeData() const;
	void setTreeData(myTree *value);

	myTree *getTreeProcess() const;
	void setTreeProcess(myTree *value);
	void addLinePaint(BlockItem *bi1,BlockItem *bi2);
public slots:
	void zoomOut();
	void zoomIn();

protected:
	void keyPressEvent(QKeyEvent *event);
	void wheelEvent(QWheelEvent *event);
private slots:
	void onCustomContextMenuRequested(const QPoint &point);
	void addProcessBlock();
	//void addProcessBlock(QPoint point);
	void addDataBlock();
	void deleteBlock();
	void addRelation();
	void settingsBlock();
	void lineDelete();

private:
	void startFunc(); //ToDo: del
	void createAction();
	void createContextMenu();

	QPoint pLastKeyPoint;

	QAction *pAddRelation;
	QAction *pAddDataBlock ;
	QAction *pAddProcessBlock;
	QAction *pDeleteBlock;
	QAction *pSettings;
	QAction *pLineDel;


	QMenu *pContextMenu;
	GraphicsView *pGraphicsView;
	QGraphicsScene *pGraphicsScene;

	QList<BlockItem *> pListData;
	QList<BlockItem *> pListProces;


	QString bracketData;
	QString bracketProcess;
	myTree *treeData;
	myTree *treeProcess;

	BlockContextMenu* bcm;
	void scaleView(qreal scaleFactor);
};

#endif // DESIGNINGVIEW_H
