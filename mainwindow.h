#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:

private:
	QAction *pOpenFile;
	QAction *pSaveFile;
	QAction *pSaveFileAs;
	QAction *pAddDataBlock;
	QAction *pAddProcessBlock;
};

#endif // MAINWINDOW_H
