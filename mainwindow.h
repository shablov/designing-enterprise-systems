#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "designingview.h"
#include <QMainWindow>
#include "frequencywindow.h"
#include <QLineEdit>

class QAction;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);

public slots:
	void onOpenFile();

private:
	//public:
	void createAction();

	void createMenuBar();
	void createFileMenu();
	void createDataMenu();
	void createProcesMenu();

	void createCalculationMenu();
	void createInitialMenu();
	void createCentralWidget();



private slots:
	void newProject();
	void addDataBlock();
	void addProcessBlock();
	void AddFrequencyProcess();
	void AddFrequencyData();
	//void calc();
	void viewData();
	void viewProcess();
	void saveFile();
	void saveFileAs();
	void ViewBracketData();
	void ViewCoefficientsData();
	void ViewBracketProces();
	void ViewCoefficientsProces();
private:
	DesigningView *DView;

	QAction *pOpenFile;
	QAction *pSaveFile;
	QAction *pSaveFileAs;
	QAction *pAddDataBlock;
	QAction *pAddProcessBlock;
	QAction *pAddFrequencyProcess;
	QAction *pAddFrequencyData;
	QAction *pViewData;
	QAction *pViewProcess;
	QAction *pViewBracketData;
	QAction *pViewCoefficientsData;
	QAction *pViewBracketProces;
	QAction *pViewCoefficientsProces;
	QAction *pNew;

	QLineEdit *processEdit;
	QLineEdit *dataEdit;

	QString path;


};

#endif // MAINWINDOW_H
