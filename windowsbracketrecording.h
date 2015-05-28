#ifndef WINDOWSBRACKETRECORDING_H
#define WINDOWSBRACKETRECORDING_H

#include <QObject>
#include <QWidget>
#include <QApplication>

#include <QCompleter>
#include <QTextEdit>
#include <QKeyEvent>
#include <QList>
#include <QGridLayout>
#include "block.h"
//#include "designingview.h"
#include <QDebug>
class DesigningView;
struct myTree
{
	QString MyName;
	myTree *parent;
	QList<myTree*> child;
};


class WindowsBracketRecording : public QWidget
{
	Q_OBJECT
public:
	~WindowsBracketRecording();
	WindowsBracketRecording( BlockType Type,DesigningView *DV, QWidget *parent = 0);
	void savePublic(bool showMsg);
	//void checkTreeName(myTree *tree);
protected:
	bool eventFilter(QObject *obj, QEvent * event);
	void keyPressEvent(QKeyEvent *event);
	myTree *BuildTree(QString str);
	void AddTheMissingBranches();
	void checkTreeName(myTree *tree);
	\
	int doublesSign(QString str,int i,QString parametr = "");
private slots:
	void save();
	void insertCompletion(const QString &completion);
	void exit();
	void saveParametr(bool saveTree = false);


private:

	QString checkTheSameName(QList<BlockItem *> list);

	bool correct();
	bool checkCorrectName(QString str);
	bool nextCompleter();
	QString parser();
	QStringList stringList;
	QStringList witchAddTheMissingBranches;
	QCompleter* completer;
	int index;
	QTextEdit *TextEdit;
	DesigningView *DView;
	BlockType type;
	QString ErrorNames;
	QStringList checkName;
	myTree *pTree;
};



#endif // WINDOWSBRACKETRECORDING_H
