#include "mainwindow.h"

#include <QMenu>
#include <QMenuBar>
#include <QToolBar>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle(tr("Designing enterprise systems"));

	createAction();
	createMenuBar();
	createToolBar();
}

void MainWindow::createAction()
{
}

void MainWindow::createMenuBar()
{
	menuBar();
	createFileMenu();
	createEditMenu();
}

void MainWindow::createFileMenu()
{
}

void MainWindow::createEditMenu()
{
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
