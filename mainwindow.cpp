#include "mainwindow.h"
//#include "designingview.h"

#include <QMenu>
#include <QMenuBar>

#include <QVBoxLayout>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle(tr("Designing enterprise systems"));

	createAction();
	createMenuBar();
	createCentralWidget();
}

void MainWindow::createAction()
{
	pOpenFile = new QAction(tr("Open"), this);
	pSaveFile = new QAction(tr("Save"), this);
	pSaveFileAs = new QAction(tr("Save as..."), this);

	pAddDataBlock = new QAction(tr("Add data block"), this);
	pAddProcessBlock = new QAction(tr("Add process block"), this);

	connect(pOpenFile, SIGNAL(triggered()), this, SLOT(onOpenFile()));
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

	blocksMenu->addAction(tr("Add data block"), this, SLOT(addDataItem()));
	blocksMenu->addAction(tr("Add process block"), this, SLOT(addProcessItem()));

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

void MainWindow::createCentralWidget()
{
	DView = new DesigningView;
	setCentralWidget(DView);
}

void MainWindow::onOpenFile()
{
}

void MainWindow::addDataItem()
{
	DView->addItem(dataItem);
}

void MainWindow::addProcessItem()
{
	DView->addItem(processItem);
}
