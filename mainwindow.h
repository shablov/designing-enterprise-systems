#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "scene.h"
#include <QMainWindow>
#include <QGraphicsView>
#include <QHBoxLayout>
class QAction;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);

private:
	void createAction();

	void createMenuBar();
	void createFileMenu();
	void createBlockMenu();
	void createInitialMenu();
	void createCalculationMenu();

	void createToolBar();
	void createFileTool(QToolBar *toolBar);
	void createEditTool(QToolBar *toolBar);

	void createCentralWidget();

	//void addItem(QGraphicsItem *item);
private slots:
	void addItemProcess();
	void addItemData();
private:
	QGraphicsView *pView;
	Scene   *pScene;

	QAction *pOpenFile;
	QAction *pSaveFile;
	QAction *pSaveFileAs;
	QAction *pAddDataBlock;
	QAction *pAddProcessBlock;
};

#endif // MAINWINDOW_H
