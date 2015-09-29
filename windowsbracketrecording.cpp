#include "windowsbracketrecording.h"
#include <QGridLayout>
#include "block.h"
#include "QLineEdit"
#include <QTextCursor>
#include <QCompleter>
#include <QMessageBox>
#include <designingview.h>
#include <QCompleter>
#include <QKeyEvent>
#include <QAbstractItemView>
#include <QtDebug>
#include <QApplication>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QScrollBar>



WindowsBracketRecording::~WindowsBracketRecording()
{

}

WindowsBracketRecording::WindowsBracketRecording(BlockType Type, DesigningView *DV, QWidget *parent)
	: QWidget(parent),DView(DV),type(Type),pTree(0)
{
	TextEdit = new QTextEdit;
	TextEdit->installEventFilter(this);
	QList<BlockItem *> bi;
	switch (type)
	{
	case processBlock:
		TextEdit->setText(DView->getBracketProcess());
		bi = DView->getListProces();
		break;
	case dataBlock:
		TextEdit->setText(DView->getBracketData());
		bi = DView->getListData();
		break;
	}
	listName = BlockToList(bi);
	completer = new QCompleter(listName);
	completer->setWidget(TextEdit);
	completer->setCompletionMode(QCompleter::PopupCompletion);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	QObject::connect(completer, SIGNAL(activated(QString)),
					 this, SLOT(insertCompletion(QString)));

	QPushButton *bOk = new QPushButton(tr("Сохранить"),this);
	QPushButton *bCansel = new QPushButton(tr("Отмена"),this);
	QPushButton *bCheck = new QPushButton(tr("Проверить"),this);


	QGridLayout *layout = new QGridLayout;
	layout->addWidget(TextEdit,0,0,5,5);
	layout->addWidget(bOk,6,3);
	layout->addWidget(bCansel,6,4);
	layout->addWidget(bCheck,6,0);
	setLayout(layout);
	connect(bCansel,SIGNAL(clicked()),this,SLOT(exit()));
	connect(bOk,SIGNAL(clicked()),this,SLOT(save()));
	connect(bCheck,SIGNAL(clicked()),this,SLOT(check()));
}

QString WindowsBracketRecording::isRepeating(QStringList list, bool concludedMsgBox)
{

	QStringList strlst;
	for (int i = 0;i < list.count()-1;i++)
		for (int j = i+1;j < list.count();j++)
			if (list.at(i) == list.at(j))
				if (strlst.count(list.at(i)) == 0)
					strlst.append(list.at(i));
	if(strlst.count() == 0) return "";


	QString str;
	for (int i = 0;i < strlst.count();i++)
		str +=  " \"" + strlst.at(i) + "\", ";// + (i == strlst.count() - 1)?", ":".";

	if(concludedMsgBox)
	{
		QMessageBox msgBox;
		msgBox.setText("Имеются повторяющиеся имена:" + str + " расчеты могут быть неверные. ");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.exec();
	}
	return "Имеются повторяющиеся имена:" + str;
}

QString WindowsBracketRecording::isRepeating(QList<BlockItem *> list, bool concludedMsgBox)
{
	return isRepeating(BlockToList(list),concludedMsgBox);
}

QString WindowsBracketRecording::isCorrectFirstCheck(QString string, QList<BlockItem *> list, bool concludedMsgBox)
{
	return isCorrectFirstCheck(string,BlockToList(list),concludedMsgBox);
}

QString WindowsBracketRecording::isCorrectFirstCheck(QString string, QStringList list, bool concludedMsgBox)
{
	if (string == "") return "";
	//if(!list) list = listName;
	QString result;
	QString text = string.replace("\t", " ");
	text = string.replace("\n", " ");

	result = isRepeating(list);
	if (result == "" && list.count(string) != 0) return "";

	int i = text.count(")");
	int j = text.count("(");
	if ( i != j)
	{
		QString str = "\"%1\" больше чем \"%2\" на %3. ";
		if (i > j) str = str.arg(")").arg("(").arg(i - j);
		else str = str.arg("(").arg(")").arg(j - i);
		result += str;
	}

	if (text.count("\"") % 2 == 1)
		result += "Не хватает кавычек. ";

	if (result == "")
	{
		QStringList buff = listName;
		listName = list;
		result += isCorrect(text);
		listName = buff;
	}

	if (result != "")
	{
		if (concludedMsgBox)
		{
			QMessageBox msgBox;
			msgBox.setText("Имеются ошибки :" + result);
			msgBox.setStandardButtons(QMessageBox::Ok);
			msgBox.setIcon(QMessageBox::Warning);
			msgBox.exec();
		}
	}
	return result;
}

QStringList WindowsBracketRecording::BlockToList(QList<BlockItem *> list)
{
	QStringList sList;
	for(int i = 0;i<list.count();i++)
	{
		sList.append(list[i]->getName());
	}
	return sList;
}

myTree *WindowsBracketRecording::buildTree()
{
	myTree *tree = buildTree(TextEdit->toPlainText());

	nameNoInTree = listName;

	if (!tree)
	{
		tree = new myTree;
		for(int i = 0;i<listName.count();i++)
		{
			myTree *buffTree = new myTree;
			buffTree->MyName = nameNoInTree[i];
			tree->child.append(buffTree);
			tree->MyName += (i!=0?", ":"") + nameNoInTree[i];
		}
		return tree;
	}


	checkNameInTree(tree);
	if (nameNoInTree.count() == 0) return tree;
	myTree *result = new myTree;
	result->child.append(tree);
	result->MyName = tree->MyName;
	for(int i = 0;i<nameNoInTree.count();i++)
	{
		myTree *buffTree = new myTree;
		buffTree->MyName = nameNoInTree[i];
		result->child.append(buffTree);
		result->MyName += ", " + nameNoInTree[i];
	}
	return result;
}

myTree *WindowsBracketRecording::buildTree(QString string)
{
	qDebug()<<"!!!!!!!!!!!!!!!!!!!!!";
	qDebug()<<string.size()<<" "<<string;
	if (string == "") return 0;
	if (string == " ") return 0;
	if (string == ",") return 0;
	if (string == "\"")return 0;
	if (string == "(")return 0;
	if (string == ")")return 0;

	if(listName.indexOf(string) != -1)
	{
		myTree *tree = new myTree;
		tree->MyName = string;
		return tree;
	}


	myTree *tree22 =  checkComma(string);
	if (checkComma(string)) return tree22;




	int i = string.indexOf('\"');
	int j = string.indexOf('(');
	if (i != -1 || j != -1)
	{
		if((i < j && i !=-1) || (j ==-1))
		{
			myTree *tree = new myTree;
			if (i != 0)
			{
				myTree *tree1 = buildTree(string.left(i));
				if (tree1) tree->child.append(tree1);
			}

			j =string.indexOf("\"",i + 1);
			if (j != -1)
			{
				myTree *tree1 = buildTree(string.mid(i+1,j - i - 2));
				if (tree1) tree->child.append(tree1);

				if (j +1 != string.count())
				{
					myTree *tree2 = buildTree( string.mid(j+1,string.count()));
					if (tree2) tree->child.append(tree2);
				}
			}
			if (tree->child.count() == 0) return 0;
			if (tree->child.count() == 1) return tree->child.at(0);
			tree->MyName = "(";
			for(int i = 0;i < tree->child.count();i++)
			{
				tree->MyName +=tree->child.at(i)->MyName +(((i+1)!=tree->child.count()?", ":")"));
				tree->child.at(i)->parent = tree;
			}
			return tree;
		}else
		{
			myTree *tree = new myTree;
			if (j != 0)
			{
				myTree *tree1 = buildTree(string.left(j));
				if (tree1) tree->child.append(tree1);
			}

			i = doublesSign(string,j,"()");
			if (i != -1)
			{
				myTree *tree1 = buildTree(string.mid(j+1,i - j - 2));
				if (tree1) tree->child.append(tree1);

				if (i +1 != string.count())
				{
					myTree *tree2 = buildTree( string.mid(i+1,string.count()));
					if (tree2) tree->child.append(tree2);

				}
			}
			if (tree->child.count() == 0) return 0;
			if (tree->child.count() == 1) return tree->child.at(0);
			tree->MyName = "(";
			for(int i = 0;i < tree->child.count();i++)
			{
				tree->MyName +=tree->child.at(i)->MyName + ((i+1)!=tree->child.count()?", ":")");
				tree->child.at(i)->parent = tree;
			}
			return tree;
		}
	}

	i = string.indexOf(',');
	if (i == -1)
	{
		i = string.indexOf(' ');
		if (i ==-1)return 0;
	}
	myTree *tree = new myTree;
	myTree	*tree1 = buildTree(string.left(i));
	if(tree1) tree->child.append(tree1);
	tree1 = buildTree(string.mid(i+1,string.count()));
	if(tree1) tree->child.append(tree1);
	if (tree->child.count() == 0) return 0;
	if (tree->child.count() == 1) return tree->child.at(0);
	tree->MyName = "(";
	for(int i = 0;i < tree->child.count();i++)
	{
		tree->MyName +=tree->child.at(i)->MyName + ((i+1)!=tree->child.count()?", ":")");
		tree->child.at(i)->parent = tree;
	}
	return tree;
}

void WindowsBracketRecording::checkNameInTree(myTree *tree)
{
	if (tree->child.count() == 0) nameNoInTree.removeAll(tree->MyName);
	else
	{
		for(int i =0; i < tree->child.count();i++)
		{
			checkNameInTree(tree->child.at(i));
		}
	}
}

QString WindowsBracketRecording::isCorrect(QString string)
{
	qDebug()<<"-------------------------------------";
	qDebug()<<string.size()<<" "<<string;
	if (string == "") return "";
	if (string == " ") return "";
	if (string == ",") return "";
	if (string == "\"")return "Ошибка при разборе из-за кавычки, что-то не так со скобками.";

	//int start = 0;
	//int end = 0;

	if(listName.indexOf(string) != -1)
	{
		namesForCheck.append(string);
		return "";
	}
	int i = string.indexOf('\"');
	int j = string.indexOf('(');
	if (i != -1 || j != -1)
	{
		if((i < j && i !=-1) || (j ==-1))
		{
			QString error;

			if (i != 0) error += isCorrect(string.left(i));

			j =string.indexOf("\"",i + 1);;
			if (j == -1) error+= "Ошибка в расположении скобок, не найти парную кавычку";
			else
			{
				error += isCorrect(string.mid(i+1,j - i - 1));
				if (j +1 != string.count())
					error +=isCorrect( string.mid(j+1,string.count()));
			}
			return error;
		}else
		{
			QString error;

			if (j != 0) error += isCorrect(string.left(j));

			i = doublesSign(string,j,"()");
			if (i == -1) error+= "Ошибка в расположении скобок, не найти парную";
			else
			{
				error += isCorrect(string.mid(j+1,i - j - 2));

				if (i +1 != string.count()) error += isCorrect( string.mid(i+1,string.count()));
			}
			return error;
		}
	}

	i = string.indexOf(',');
	if (i == -1)
	{
		i = string.indexOf(' ');
		if (i ==-1)return "Не известное имя:\"" + string + "\".";
	}

	return isCorrect(string.left(i)) + isCorrect(string.mid(i+1,string.count()));
}



int WindowsBracketRecording::doublesSign(QString str, int i, QString parametr)
{
	if (parametr == "()")
	{
		int count = 1;
		int j = i+1;

		while (j < str.size() && count != 0)
		{
			if (str.at(j) == '(') count++;
			if (str.at(j) == ')') count--;
			j++;
		}
		if (count == 0) return j--;
		else return -1;
	}
	if (parametr == "\"")
	{
		return str.indexOf("\"",i++);
	}
}

void WindowsBracketRecording::check()
{
	QMessageBox msgBox;

	namesForCheck.clear();
	QString str = isCorrectFirstCheck(TextEdit->toPlainText(),listName);
	str +=isRepeating(namesForCheck);
	if(str == "")   msgBox.setText("Ошибки не обнаружены");
	else {
		msgBox.setText("Ошибки:");
		msgBox.setInformativeText(str);
	}
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setButtonText(QMessageBox::Ok,tr("Закрыть"));
	msgBox.exec();
}

bool WindowsBracketRecording::check(bool xz)
{
	namesForCheck.clear();
	QString str = isCorrectFirstCheck(TextEdit->toPlainText(),listName);
	str +=isRepeating(namesForCheck);
	if(str == "")  return true;
	else return false;
}

void WindowsBracketRecording::saveResult(bool saveTree)
{
	switch (type)
	{
	case processBlock:
		DView->setBracketProcess(TextEdit->toPlainText());
		DView->setTreeProcess(buildTree());
		//qDebug()<<DView->getTreeProcess()->MyName;
		break;
	case dataBlock:
		DView->setBracketData(TextEdit->toPlainText());
		DView->setTreeData(buildTree());
		//qDebug()<<DView->getTreeData()->MyName;
		break;
	}
}

myTree * WindowsBracketRecording::checkComma(QString str)
{
	qDebug()<<"comma";
	myTree *result = new myTree;

	int pre = 0;
	for (int i = 0;i < str.size();i++)
	{

		if (str.at(i) == '(')
		{
			i = doublesSign(str,i,"()") -1 ;
			if (i ==-1) return 0;
		}
		if	(str.at(i) == '\"')
		{
			i = doublesSign(str,i,"\"") -1 ;
			if (i ==-1) return 0;
		}

		if	(str.at(i) == ',')
		{
			myTree *tree = buildTree(str.mid(pre,i - pre));
			pre = i + 1;
			if(tree)result->child.append(tree);
		}

	}
	if (pre!= 0 )
	{
		myTree *tree = buildTree(str.mid(pre, str.size()));
		if(tree)result->child.append(tree);
	}

	if (result->child.count() == 0) return 0;
	if (result->child.count() == 1) return result->child.at(0);


	result->MyName = "(";
	for(int i = 0;i < result->child.count();i++)
	{
		result->MyName += result->child.at(i)->MyName + ((i+1)!=result->child.count()?", ":")");
		result->child.at(i)->parent = result;
	}
	return result;

}

void WindowsBracketRecording::save()
{
	QString str = isCorrectFirstCheck(TextEdit->toPlainText(),listName) ;
	if (str == "")
	{
		saveResult(true);
		exit();
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setText("Обнаружены ошибки:" );
		msgBox.setInformativeText(str);
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		msgBox.setButtonText(QMessageBox::Save,tr("Сохранить"));
		msgBox.setButtonText(QMessageBox::Discard,tr("Не сохранять"));
		msgBox.setButtonText(QMessageBox::Cancel,tr("Отмена"));
		msgBox.setDefaultButton(QMessageBox::Discard);

		int ret = msgBox.exec();
		switch (ret) {
		case QMessageBox::Save:
			saveResult();
			exit();
			break;
		case QMessageBox::Discard:
			exit();
			break;
		case QMessageBox::Cancel:
			break;
		default:
			break;
		}
	}
}

void WindowsBracketRecording::exit()
{
	close();
}
