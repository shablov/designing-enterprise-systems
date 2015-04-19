#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QDebug>
#include <QAction>
#include "mathem.h"
#include "designingviewf.h"
#include "frequencywindow.h"
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle(tr("Designing enterprise systems"));
	setGeometry(100,100,720,720);
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
	pViewF = new QAction(tr("view"), this);
	connect(pOpenFile, SIGNAL(triggered()), this, SLOT(onOpenFile()));
	connect(pViewF,SIGNAL(triggered()),this,SLOT(viewF()));
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

	blocksMenu->addAction(tr("Add data block"), this, SLOT(addDataBlock()));
	blocksMenu->addAction(tr("Add process block"), this, SLOT(addProcessBlock()));

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
	calculationMenu->addAction(tr("calc"),this,SLOT(calc()));
	calculationMenu->addAction(tr("Frequency"),this,SLOT(AddFrequency()));
	calculationMenu->addAction(pViewF);
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

void MainWindow::addDataBlock()
{
	DView->addBlock(dataBlock);
}

void MainWindow::addProcessBlock()
{
	DView->addBlock(processBlock);
}

void MainWindow::AddFrequency()
{
	FrequencyWindow * fw = new FrequencyWindow(DView->getListProces());
	//ToDo: fw->exec
	fw->show();//??
}

void MainWindow::calc()
{
	math m;
	m.convertFromList(DView->getListData(),DView->getListProces());
}

void MainWindow::viewF()
{
	math m;
	DesigningViewF* d = new DesigningViewF(m.convertFromList(DView->getListData(),DView->getListProces()),
										   DView->getListData());
	d->setAttribute(Qt::WA_DeleteOnClose);
	d->show();
}
