#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "designingview.h"
#include <QMainWindow>

class QAction;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);

public slots:
	void onOpenFile();

private:
	void createAction();

	void createMenuBar();
	void createFileMenu();
	void createBlockMenu();
	void createInitialMenu();
	void createCalculationMenu();

	void createCentralWidget();
private slots:
	void addDataItem();
	void addProcessItem();
private:
	DesigningView *DView;


	QAction *pOpenFile;
	QAction *pSaveFile;
	QAction *pSaveFileAs;
	QAction *pAddDataBlock;
	QAction *pAddProcessBlock;
};

#endif // MAINWINDOW_H
