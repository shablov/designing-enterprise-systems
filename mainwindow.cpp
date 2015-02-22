#include "mainwindow.h"
#include "scene.h"
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QGraphicsScene>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle(tr("Designing enterprise systems"));

	createAction();
	createMenuBar();
	createToolBar();	/// TODO: may be not need
	createCentralWidget();
}

void MainWindow::createAction()
{
	pOpenFile = new QAction(tr("Open"), this);
	pSaveFile = new QAction(tr("Save"), this);
	pSaveFileAs = new QAction(tr("Save as..."), this);

	pAddDataBlock = new QAction(tr("Add data block"), this);
	pAddProcessBlock = new QAction(tr("Add process block"), this);
}

void MainWindow::createMenuBar()
{
	menuBar();
	createFileMenu();
	createBlockMenu();
	createInitialMenu();
	createCalculationMenu();
}

void MainWindow::createFileMenu()
{
	QMenu *fileMenu = new QMenu(tr("File"));
	fileMenu->addAction(pOpenFile);
	fileMenu->addAction(pSaveFile);
	fileMenu->addAction(pSaveFileAs);
	fileMenu->addSeparator();
	fileMenu->addAction(tr("Exit"), this, SLOT(close()));
	menuBar()->addMenu(fileMenu);
}

void MainWindow::createBlockMenu()
{
	QMenu *blocksMenu = new QMenu(tr("Blocks"));
	//blocksMenu->addAction(pAddDataBlock, this, SLOT(addItemData()));
	//blocksMenu->addAction(pAddProcessBlock, this, SLOT(addItemProcess())););

	//blocksMenu->addSeparator();//?????
	blocksMenu->addAction(tr("Add data block"), this, SLOT(addItemData()));
	blocksMenu->addAction(tr("Add process block"), this, SLOT(addItemProcess()));

	menuBar()->addMenu(blocksMenu);
}

void MainWindow::createInitialMenu()
{
	QMenu *initialMenu = new QMenu(tr("Initial data"));
	menuBar()->addMenu(initialMenu);
}
void MainWindow::createCalculationMenu()
{
	QMenu *calculationMenu = new QMenu(tr("Calculation"));
	menuBar()->addMenu(calculationMenu);
}

void MainWindow::createToolBar()
{
	QToolBar *toolBar = new QToolBar(tr("File && Edit"));
	addToolBar(Qt::TopToolBarArea, toolBar);
	createFileTool(toolBar);
	toolBar->addSeparator();
	createEditTool(toolBar);
}

void MainWindow::createFileTool(QToolBar *toolBar)
{

}

void MainWindow::createEditTool(QToolBar *toolBar)
{

}

void MainWindow::createCentralWidget()
{
	pScene = new Scene;
	pView = new QGraphicsView;
	pView->setScene(pScene);
	setCentralWidget(pView);

}

void MainWindow::addItemProcess()
{
	QGraphicsItem *item;
	item = new itemProcess();
	pScene->addItem(item);
}

void MainWindow::addItemData()
{
	QGraphicsItem *item;
	item = new ItemData();
	pScene->addItem(item);
}
