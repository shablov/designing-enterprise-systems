#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QDebug>
#include <QAction>
#include <QDomNodeList>
#include <QtXml/QDomDocument>
#include <QFile>
#include <QTextStream>
#include "mathem.h"
#include "designingviewf.h"
#include "frequencywindow.h"
#include "windowsbracketrecording.h"
#include "QFileDialog"
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{//
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


//	pExit = new QAction(tr("Выход"), this);

	pSaveFile->setShortcut(QKeySequence("CTRL+S"));
	pSaveFileAs = new QAction(tr("Сохранить как..."), this);
	pSaveFileAs->setShortcut(QKeySequence("CTRL+Shift+S"));
	pAddDataBlock = new QAction(tr("Добавить данные"), this);
	pAddProcessBlock = new QAction(tr("Добавить процесс"), this);


	pViewProcess = new QAction(tr("Просмотр"), this);
	pViewData = new QAction(tr("Просмотр"), this);
	pViewBracketData = new QAction(tr("Объединение"), this);
	pViewCoefficientsData = new QAction(tr("Коэфиценты"), this);
	pViewBracketProces = new QAction(tr("Объединение"), this);
	pViewCoefficientsProces = new QAction(tr("Коэфиценты"), this);

	//connect(pExit, SIGNAL(triggered()), this, SLOT(exit()));
	connect(pNew, SIGNAL(triggered()), this, SLOT(newProject()));
	connect(pOpenFile, SIGNAL(triggered()), this, SLOT(onOpenFile()));
	connect(pViewProcess,SIGNAL(triggered()),this,SLOT(viewProcess()));
	connect(pViewData,SIGNAL(triggered()),this,SLOT(viewData()));
	connect(pSaveFile,SIGNAL(triggered()),this,SLOT(saveFile()));
	connect(pSaveFileAs,SIGNAL(triggered()),this,SLOT(saveFileAs()));
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
	fileMenu->addAction(tr("Выход"),this,SLOT(close()));
	//fileMenu->addAction(pExit);
	menuBar()->addMenu(fileMenu);
}

void MainWindow::createProcesMenu()
{
	QMenu *procesMenu = new QMenu(tr("Процессы"));
	procesMenu->addAction(tr("Настройки"),this,SLOT(AddFrequencyProcess()));
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
	calculationMenu->addAction(tr("Настройки процессов"),this,SLOT(AddFrequencyProcess()));
	calculationMenu->addAction(tr("Настройки данных"),this,SLOT(AddFrequencyData()));
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
	QMessageBox msgBox;
	msgBox.setText("Сохранить проект?" );
	msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
	msgBox.setButtonText(QMessageBox::Save,tr("Сохранить"));
	msgBox.setButtonText(QMessageBox::Discard,tr("Не сохранять"));
	msgBox.setButtonText(QMessageBox::Cancel,tr("Отмена"));
	msgBox.setDefaultButton(QMessageBox::Save);

	int ret = msgBox.exec();
	switch (ret)
	{
	case QMessageBox::Save:
		saveFile();
		delete DView;
		createCentralWidget();
		path = "";
		break;
	case QMessageBox::Discard:
		delete DView;
		path = "";
		createCentralWidget();
		break;
	case QMessageBox::Cancel:
		break;
	default:
		break;
	}
}

void MainWindow::onOpenFile()
{
/*
	QMessageBox msgBox;
	msgBox.setText("Сохранить проект?" );
	msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
	msgBox.setButtonText(QMessageBox::Save,tr("Сохранить"));
	msgBox.setButtonText(QMessageBox::Discard,tr("Не сохранять"));
	msgBox.setButtonText(QMessageBox::Cancel,tr("Отмена"));
	msgBox.setDefaultButton(QMessageBox::Save);

	int ret = msgBox.exec();
	switch (ret)
	{
	case QMessageBox::Save:
		saveFile();
		delete DView;
		path = "";
		createCentralWidget();
		break;
	case QMessageBox::Discard:
		delete DView;
		path = "";
		createCentralWidget();
		break;
	case QMessageBox::Cancel:
		return;
		break;
	default:
		return;
		break;
	}
*/


	path = QFileDialog::getOpenFileName(this,
										"Select file",
										"",
										"xml (*.xml)");
	//bool load(const QString &fileName)

	//	QString fileName = "text.xml";
	QFile file(path);

	if (!file.open(QIODevice::ReadOnly))
	{
		//			emit error(FileOpenedError, file.errorString());
		//			return false;
	}
	QByteArray data = file.readAll();


	file.close();

	QDomDocument doc("scene");
	if (!doc.setContent(data))
	{
		//		return false;
	}
	QList <ReadFile> readFile;
	QDomElement rootElement = doc.documentElement();
	QDomNodeList processNodes = rootElement.childNodes();
	for (int i = 0; i < processNodes.count(); i++)
	{
		QDomNode processDomNode = processNodes.at(i);
		QDomElement processDomElement = processDomNode.toElement();
		bool b = false;

		BlockItem *bi;
		double  x  = processDomElement.attribute("x",QString()).toDouble();
		double  y  = processDomElement.attribute("y",QString()).toDouble();

		QString typeBlock = processDomElement.tagName();
		if (typeBlock == "Process")
		{
			DView->addBlock(processBlock,QPoint(x,y));
			bi = DView->getListProces().back();
			b = true;
		}
		else if (typeBlock == "Data")
		{
			DView->addBlock(dataBlock,QPoint(x,y));
			bi = DView->getListData().back();
			b = true;
		}
		else if (typeBlock == "BracketProcess")
			DView->setBracketProcess( processDomElement.attribute("Text",QString()));
		else if (typeBlock == "BracketData")
			DView->setBracketData(processDomElement.attribute("Text",QString()));


		if (b)
		{
			bi->setName(processDomElement.attribute("Name", QString()));
			bi->setFrequencyOfActivation( processDomElement.attribute("Frequency", QString()).toDouble());

			ReadFile newBlock;
			newBlock.id = processDomElement.attribute("ID", QString());
			newBlock.blockItem = bi;
			QDomNodeList referenceNodes = processDomElement.childNodes();
			for (int j = 0; j < referenceNodes.count(); j++)
			{
				QDomNode referenceDomNode = referenceNodes.at(j);
				QDomElement referenceDomElement = referenceDomNode.toElement();
				newBlock.ReferenceID.append(referenceDomElement.attribute("id", QString()));
			}
			readFile.append(newBlock);
		}

	}
	for(int i = 0; i < readFile.count() -1;i++)
	{
		for(int j = 0; j < readFile.at(i).ReferenceID.count() ;j++)
		{
			for(int k = i + 1; k < readFile.count() ;k++)
			{
				if (readFile.at(i).ReferenceID.at(j) == readFile.at(k).id)//&& readFile.at(i).blockItem->type() != readFile.at(k).blockItem->type())
				{
					DView->addLinePaint(readFile.at(i).blockItem,readFile.at(k).blockItem);
					//break;
				}
			}
		}
	}
	//return true;

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
	math m;
	//<<<<<<< HEAD
	WindowsBracketRecording *w = new WindowsBracketRecording(dataBlock,DView);
	if (w->check(true))
	{
		MyMatrix mat = m.convertFromList(DView->getListData(),DView->getListProces(), DView->getTreeData());
		QList<BlockItem *> listData = DView->getListData();
		QStringList treeList = m.newTreeList();
		DesigningViewF* d = new DesigningViewF(mat, listData, treeList);
		myTree *tree = w->buildTree();
		d->setAttribute(Qt::WA_DeleteOnClose);
		d->show();
	}else
	{
		QMessageBox msgBox;
		msgBox.setText("Обнаружены ошибки при разборе объединения,построение будет без объединения");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setButtonText(QMessageBox::Ok,tr("Продолжить"));
		msgBox.exec();

		MyMatrix mat = m.convertFromList(DView->getListData(),DView->getListProces(),0);
		QList<BlockItem *> listData = DView->getListData();
		QStringList treeList = m.newTreeList();
		DesigningViewF* d = new DesigningViewF(mat, listData, treeList);
		myTree *tree = w->buildTree();
		d->setAttribute(Qt::WA_DeleteOnClose);
		d->show();
	}
	delete w;
	//=======
//	MyMatrix mat = m.convertFromList(DView->getListData(),DView->getListProces(),DView->getTreeData());
//	QList<BlockItem *> listData = DView->getListData();
//	QStringList treeList = m.newTreeList();
//	DesigningViewF* d = new DesigningViewF(mat, listData, treeList);
//	d->setAttribute(Qt::WA_DeleteOnClose);
//	d->show();
	//>>>>>>> origin/master
}
void MainWindow::viewProcess()
{
	math m;
	WindowsBracketRecording *w = new WindowsBracketRecording(processBlock,DView);


	//<<<<<<< HEAD
	//=======

//	MyMatrix mat = m.convertFromList(DView->getListProces(),DView->getListData(), DView->getTreeProcess());
//	QList<BlockItem *> listData = DView->getListProces();
//	QStringList treeList = m.newTreeList();
//	DesigningViewF* d = new DesigningViewF(mat, listData, treeList);
	//>>>>>>> origin/master

	if (w->check(true))
	{
		MyMatrix mat = m.convertFromList(DView->getListProces(),DView->getListData(), DView->getTreeProcess());
		QList<BlockItem *> listProcess = DView->getListProces();

		QStringList treeList = m.newTreeList();


		DesigningViewF* d = new DesigningViewF(mat, listProcess, treeList);
		myTree *tree = w->buildTree();
		d->setAttribute(Qt::WA_DeleteOnClose);
		d->show();
	}else
	{
		QMessageBox msgBox;
		msgBox.setText("Обнаружены ошибки при разборе объединения,построение будет без объединения");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setButtonText(QMessageBox::Ok,tr("Продолжить"));
		msgBox.exec();

		MyMatrix mat = m.convertFromList(DView->getListProces(),DView->getListData(),0);
		QList<BlockItem *> listProcess = DView->getListProces();
		QStringList treeList = m.newTreeList();
		DesigningViewF* d = new DesigningViewF(mat, listProcess, treeList);
		myTree *tree = w->buildTree();
		d->setAttribute(Qt::WA_DeleteOnClose);
		d->show();
	}
	delete w;
}

void MainWindow::saveFile()
{	
	if (path == "")
	{
		saveFileAs();
		return;
	}



	QFile file(path);
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
		QDomElement block2 = docum.createElement("BracketData");
		block2.setAttribute("Text", DView->getBracketData());
		scene.appendChild(block2);
		block2 = docum.createElement("BracketProcess");
		block2.setAttribute("Text", DView->getBracketProcess());
		scene.appendChild(block2);

		//delete Process;

		docum.appendChild(scene);
		QByteArray BArray = file.readAll();
		BArray = docum.toByteArray();
		QTextStream out(&file);
		out.setCodec("UTF-8");

		out << BArray;
	}else
	{
		QMessageBox msgBox;
		msgBox.setText("Не удалось сохранить файл. Возможно файл открыт другой программой или защищен от записи" );
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setButtonText(QMessageBox::Ok,tr("Продолжить"));
		msgBox.exec();
		//return 0;
	}
}

void MainWindow::saveFileAs()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
													"save.xml",
												tr("Images (*.xml)"));
	if (fileName!= "")
	{
		path = fileName;
		saveFile();
	}
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
	myTree *tree = w->buildTree();
	if (w->check(true))
	{
		text->setText( m.coefficients(m.convertFromList(DView->getListData(),DView->getListProces(),tree)) +
					   "Объединение:\n" + (tree?tree->MyName:"0"));
		text->setText(text->toPlainText() + "\nВычисления:\n" + m.getVichisleniya());

		text->show();
	}else
	{
		QMessageBox msgBox;
		msgBox.setText("Обнаружены ошибки при разборе объединения, коэффиценты будут посчитаны без объединения" );
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setButtonText(QMessageBox::Ok,tr("Продолжить"));
		msgBox.exec();
		text->setText(m.coefficients(m.convertFromList(DView->getListData(),DView->getListProces(),0)) +
					  "Объединение:\n" + "0");
		text->setText(text->toPlainText() + "\nВычисления:\n" + m.getVichisleniya());

		text->show();
	}
	delete w;
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
	myTree *tree = w->buildTree();
	if (w->check(true))
	{
		text->setText(m.coefficients(m.convertFromList(DView->getListProces(),DView->getListData(),tree))+
					  "Объединение:\n" + (tree?tree->MyName:"0"));
		text->setText(text->toPlainText() + "\nВычисления:\n" + m.getVichisleniya());


		text->show();
	}else
	{
		QMessageBox msgBox;
		msgBox.setText("Обнаружены ошибки при разборе объединения, коэффиценты будут посчитаны без объединения" );
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setButtonText(QMessageBox::Ok,tr("Продолжить"));
		msgBox.exec();
		text->setText(m.coefficients(m.convertFromList(DView->getListProces(),DView->getListData(),0)) +
					  "Объединение:\n" + "0");
		text->setText(text->toPlainText() + "\nВычисления:\n" + m.getVichisleniya());

		text->show();
	}
	delete w;
}

void MainWindow::myExit()
{
	SaveMsg();
	close();
}

//void MainWindow::exit()
//{
//
//}

void MainWindow::SaveMsg()
{
	QMessageBox msgBox;
	msgBox.setText("Сохранить проект?" );
	msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
	msgBox.setButtonText(QMessageBox::Save,tr("Сохранить"));
	msgBox.setButtonText(QMessageBox::Discard,tr("Не сохранять"));
	msgBox.setButtonText(QMessageBox::Cancel,tr("Отмена"));
	msgBox.setDefaultButton(QMessageBox::Save);

	int ret = msgBox.exec();
	switch (ret)
	{
	case QMessageBox::Save:
		saveFile();
		delete DView;
		path = "";
		createCentralWidget();
		break;
	case QMessageBox::Discard:
		delete DView;
		path = "";
		createCentralWidget();
		break;
	case QMessageBox::Cancel:
		break;
	default:
		break;
	}

}
