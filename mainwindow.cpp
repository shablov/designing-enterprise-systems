#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QDebug>
#include <QAction>
#include <QtXml/QDomDocument>
#include <QFile>
#include <QTextStream>
#include "mathem.h"
#include "designingviewf.h"
#include "frequencywindow.h"
#include "windowsbracketrecording.h"
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
	pNew  = new QAction(tr("Новый"), this);
	pNew->setShortcut(QKeySequence("CTRL+N"));
	pOpenFile = new QAction(tr("Открыть"), this);
	pOpenFile->setShortcut(QKeySequence("CTRL+O"));
	pSaveFile = new QAction(tr("Сохранить"), this);
	pSaveFile->setShortcut(QKeySequence("CTRL+S"));
	pSaveFileAs = new QAction(tr("Сохранить как..."), this);
	pSaveFileAs->setShortcut(QKeySequence("CTRL+Shift+S"));
	pAddDataBlock = new QAction(tr("Add data block"), this);
	pAddProcessBlock = new QAction(tr("Add process block"), this);


	pViewProcess = new QAction(tr("Просмотр"), this);
	pViewData = new QAction(tr("Просмотр"), this);
	pViewBracketData = new QAction(tr("Объединение"), this);
	pViewCoefficientsData = new QAction(tr("Коэфиценты"), this);
	pViewBracketProces = new QAction(tr("Объединение"), this);
	pViewCoefficientsProces = new QAction(tr("Коэфиценты"), this);

	connect(pNew, SIGNAL(triggered()), this, SLOT(newProject()));
	connect(pOpenFile, SIGNAL(triggered()), this, SLOT(onOpenFile()));
	connect(pViewProcess,SIGNAL(triggered()),this,SLOT(viewProcess()));
	connect(pViewData,SIGNAL(triggered()),this,SLOT(viewData()));
	connect(pSaveFile,SIGNAL(triggered()),this,SLOT(saveFile()));
	connect(pViewBracketData,SIGNAL(triggered()),this,SLOT(ViewBracketData()));
	connect(pViewCoefficientsData,SIGNAL(triggered()),this,SLOT(ViewCoefficientsData()));
	connect(pViewBracketProces,SIGNAL(triggered()),this,SLOT(ViewBracketProces()));
	connect(pViewCoefficientsProces,SIGNAL(triggered()),this,SLOT(ViewCoefficientsProces()));
}

void MainWindow::createMenuBar()
{
	menuBar();
	createFileMenu();
	createDataMenu();
	createProcesMenu();
	//createInitialMenu();
	//createCalculationMenu();
}

void MainWindow::createFileMenu()
{
	QMenu *fileMenu = new QMenu(tr("Файл"));
	fileMenu->addSeparator();
	fileMenu->addAction(pNew);
	fileMenu->addAction(pOpenFile);
	fileMenu->addAction(pSaveFile);
	fileMenu->addAction(pSaveFileAs);
	fileMenu->addSeparator();
	fileMenu->addAction(tr("Выход"), this, SLOT(close()));
	menuBar()->addMenu(fileMenu);
}


void MainWindow::createProcesMenu()
{
	QMenu *procesMenu = new QMenu(tr("Процессы"));
	procesMenu->addAction(tr("Настройки"),this,SLOT(AddFrequencyData()));
	procesMenu->addAction(pViewProcess);
	procesMenu->addAction(pViewBracketProces);
	procesMenu->addAction(pViewCoefficientsProces);
	menuBar()->addMenu(procesMenu);
}

void MainWindow::createDataMenu()
{
	QMenu *dataMenu = new QMenu(tr("Данные"));
	dataMenu->addAction(tr("Настройки"),this,SLOT(AddFrequencyData()));
	dataMenu->addAction(pViewData);
	dataMenu->addAction(pViewBracketData);
	dataMenu->addAction(pViewCoefficientsData);
	menuBar()->addMenu(dataMenu);

	//	blocksMenu->addAction(tr("Add data block"), this, SLOT(addDataBlock()));
	//	blocksMenu->addAction(tr("Add process block"), this, SLOT(addProcessBlock()));
}

void MainWindow::createInitialMenu()
{
	QMenu *initialMenu = new QMenu(tr("Initial data"));
	menuBar()->addMenu(initialMenu);
}
void MainWindow::createCalculationMenu()
{
	QMenu *calculationMenu = new QMenu(tr("Calculation"));
	//calculationMenu->addAction(tr("calc"),this,SLOT(calc()));
	calculationMenu->addAction(tr("Setting Process"),this,SLOT(AddFrequencyProcess()));
	calculationMenu->addAction(tr("Setting Data"),this,SLOT(AddFrequencyData()));
	calculationMenu->addAction(pViewProcess);
	calculationMenu->addAction(pViewData);
	calculationMenu->addAction(pViewBracketData);
	calculationMenu->addAction(pViewCoefficientsData);
	menuBar()->addMenu(calculationMenu);
}

void MainWindow::createCentralWidget()
{
	//	QVBoxLayout *layout = new QVBoxLayout;
	//	processEdit = new QLineEdit;
	//	dataEdit = new QLineEdit;
	//	layout->addWidget(processEdit);
	//	layout->addWidget(dataEdit);
	//	layout->addWidget(DView);
	//	setLayout(layout);
	DView = new DesigningView;
	setCentralWidget(DView);
}

void MainWindow::newProject()
{
	delete DView;
	createCentralWidget();
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

void MainWindow::AddFrequencyProcess()
{
	FrequencyWindow * fw = new FrequencyWindow(DView->getListProces());
	//ToDo: fw->exec
	fw->show();//??
}
void MainWindow::AddFrequencyData()
{
	FrequencyWindow * fw = new FrequencyWindow(DView->getListData());
	//ToDo: fw->exec
	fw->show();//??
}

//void MainWindow::calc()
//{
//	math m;
//	m.convertFromList(DView->getListData(),DView->getListProces());
//}

void MainWindow::viewData()
{
	WindowsBracketRecording *w = new WindowsBracketRecording(dataBlock,DView);
	w->savePublic(false);

	math m;
    MyMatrix mat = m.convertFromList(DView->getListData(),DView->getListProces(),DView->getTreeData());
    QList<BlockItem *> listData = DView->getListData();
    QStringList treeList = m.newTreeList();
    DesigningViewF* d = new DesigningViewF(mat, listData, treeList);
	d->setAttribute(Qt::WA_DeleteOnClose);
	d->show();
}
void MainWindow::viewProcess()
{

	WindowsBracketRecording *w = new WindowsBracketRecording(processBlock,DView);
	w->savePublic(false);


	math m;
    MyMatrix mat = m.convertFromList(DView->getListProces(),DView->getListData(), DView->getTreeProcess());
    QList<BlockItem *> listData = DView->getListProces();
    QStringList treeList = m.newTreeList();
    DesigningViewF* d = new DesigningViewF(mat, listData, treeList);

	d->setAttribute(Qt::WA_DeleteOnClose);
	d->show();
}

void MainWindow::saveFile()
{

	QFile file("c:/text.xml");
	if (file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		//	exit();
		QDomDocument docum;

		QDomElement scene = docum.createElement("scene");
		//QDomElement scene = doc.createElement("scene");
		scene.setAttribute("name", "Main Scene");

		QList<BlockItem *> lProces = DView->getListProces();
		QList<BlockItem *> lData = DView->getListData();
		foreach (BlockItem *node, lProces)
		{
			QDomElement block = docum.createElement("Process");
			block.setAttribute("Name", node->getName());
			block.setAttribute("Frequency", node->getFrequencyOfActivation());
			block.setAttribute("ID", lProces.indexOf(node));
			block.setAttribute("x", node->pos().x());
			block.setAttribute("y", node->pos().y());
			//QList<BlockItem *> reference = Proces->reference() ;
			foreach (BlockItem * ref ,node->reference())
			{
				QDomElement reference = docum.createElement("Reference");
				reference.setAttribute("id", lData.indexOf(ref));
				block.appendChild(reference);
			}
			scene.appendChild(block);
		}
		foreach (BlockItem *node, lData)
		{
			QDomElement block = docum.createElement("Data");
			block.setAttribute("Name", node->getName());
			block.setAttribute("Frequency", node->getFrequencyOfActivation());
			block.setAttribute("ID", lData.indexOf(node));
			block.setAttribute("x", node->pos().x());
			block.setAttribute("y", node->pos().y());
			//QList<BlockItem *> reference = Proces->reference() ;
			foreach (BlockItem * ref ,node->reference())
			{
				QDomElement reference = docum.createElement("Reference");
				reference.setAttribute("id", lProces.indexOf(ref));
				block.appendChild(reference);
			}
			scene.appendChild(block);
		}

		//delete Process;

		docum.appendChild(scene);
		QTextStream out(&file);
		out << docum.toString();
	}
	//return 0;

}

void MainWindow::ViewBracketData()
{
	QString *str = new QString;
	WindowsBracketRecording *w = new WindowsBracketRecording(dataBlock,DView);
	w->setAttribute(Qt::WA_DeleteOnClose);
	w->show();
}

void MainWindow::ViewCoefficientsData()
{
	math m;
	QTextEdit *text = new QTextEdit;

	WindowsBracketRecording *w = new WindowsBracketRecording(dataBlock,DView);
	w->savePublic(false);

	text->setText(m.coefficients(m.convertFromList(DView->getListData(),DView->getListProces(),DView->getTreeData())));
	//text->setAttribute(Qt::WA_DeleteOnClose);
	text->setText(text->toPlainText() + "\n Объединение:\n" + DView->getTreeData()->MyName);
	text->show();
}

void MainWindow::ViewBracketProces()
{
	QString *str = new QString;
	WindowsBracketRecording *w = new WindowsBracketRecording(processBlock,DView);
	w->setAttribute(Qt::WA_DeleteOnClose);
	w->show();
}

void MainWindow::ViewCoefficientsProces()
{
	math m;
	QTextEdit *text = new QTextEdit;

	WindowsBracketRecording *w = new WindowsBracketRecording(processBlock,DView);
	w->savePublic(false);

	text->setText(m.coefficients(m.convertFromList(DView->getListProces(),DView->getListData(),DView->getTreeProcess())));
	//text->setAttribute(Qt::WA_DeleteOnClose);
	text->setText(text->toPlainText() + "\nОбъединение:\n" + DView->getTreeProcess()->MyName);
	text->show();
}
