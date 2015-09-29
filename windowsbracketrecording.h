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
    WindowsBracketRecording(BlockType Type,DesigningView *DV, QWidget *parent = 0);
    //void savePublic(bool showMsg);
	//void checkTreeName(myTree *tree);
    //static myTree* buildingTree(QString string, QStringList list = 0);

	bool check(bool xz);
    QString isRepeating(QStringList list,bool concludedMsgBox = false);
    QString isRepeating(QList<BlockItem *> list,bool concludedMsgBox = false);


    QString isCorrectFirstCheck(QString string, QList<BlockItem *> list, bool concludedMsgBox = false);//вывод ошибок в строку
    QString isCorrectFirstCheck(QString string, QStringList list, bool concludedMsgBox = false);//вывод ошибок в строку
    QStringList BlockToList(QList<BlockItem *> list);



	myTree *buildTree();
protected:
	myTree* buildTree(QString string);
	void checkNameInTree(myTree *tree);

	//void buildTree(QString string);
    QString isCorrect(QString string);
    //static myTree* buildTree(QString str);
    //bool eventFilter(QObject *obj, QEvent * event);
    //void keyPressEvent(QKeyEvent *event);
    //myTree *BuildTree(QString str);
    //void AddTheMissingBranches();
    //void checkTreeName(myTree *tree);
    int doublesSign(QString str,int i,QString parametr = "");
private slots:
    void save();
    //void insertCompletion(const QString &completion);
    void exit();
    //void saveParametr(bool saveTree = false);
    void check();

private:
	void saveResult(bool saveTree = false);
	myTree* checkComma(QString str);
    //QString checkTheSameName(QList<BlockItem *> list);
    //bool correct();
    //bool checkCorrectName(QString str);
    //bool nextCompleter();
    //QString parser();
    //QStringList stringList;
    //QStringList witchAddTheMissingBranches;
    //int index;
    QTextEdit *TextEdit;
    DesigningView *DView;
    BlockType type;
    //QString ErrorNames;
    QStringList namesForCheck;
    QStringList listName;
	QStringList nameNoInTree;
    QCompleter* completer;
	myTree *pTree;
};



#endif // WINDOWSBRACKETRECORDING_H
