#include "windowsbracketrecording.h"
#include <QGridLayout>
#include "block.h"
#include "QLineEdit"
#include <QTextCursor>
#include <QCompleter>
#include <QMessageBox>
//#include <QScrollBar>
#include <designingview.h>
#include <QCompleter>
#include <QKeyEvent>
#include <QAbstractItemView>
#include <QtDebug>
#include <QApplication>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QScrollBar>



WindowsBracketRecording::WindowsBracketRecording(BlockType Type, DesigningView *DV, QWidget *parent)
	: QWidget(parent),DView(DV),type(Type),pTree(0)
{
	QList <BlockItem *>list;
	TextEdit = new QTextEdit;
	TextEdit->installEventFilter(this);

	switch (type)
	{
	case processBlock:

		TextEdit->setText(DView->getBracketProcess());
		list = DView->getListProces();
		break;
	case dataBlock:
		TextEdit->setText(DView->getBracketData());
		list = DView->getListData();
		break;
	}
	QString SameName = checkTheSameName(list);
	if (SameName != "")
	{
		QMessageBox msgBox;
		msgBox.setText("Имеются повторяющиеся имена :\"" + SameName + "\". Расчеты могут быть неверные"  );
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.exec();
	}

	//QStringList stringList;
	for(int i = 0; i < list.count();i++)
	{
		stringList.append(list.at(i)->getName());
		//qDebug()<<stringList.back();
	}
	//	completer = new QCompleter(stringList);
	//	index = 0;


	//	completer->setWidget(TextEdit);
	//	completer->setCompletionMode(QCompleter::PopupCompletion);
	//	completer->setCaseSensitivity(Qt::CaseInsensitive);
	//	QObject::connect(completer, SIGNAL(activated(QString)),
	//					 this, SLOT(insertCompletion(QString)));



	QPushButton *bOk= new QPushButton(tr("Сохранить"),this);
	QPushButton *bCansel = new QPushButton(tr("Отмена"),this);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(TextEdit,0,0,5,5);
	layout->addWidget(bOk,6,4);
	layout->addWidget(bCansel,6,5);
	setLayout(layout);
	connect(bCansel,SIGNAL(clicked()),this,SLOT(exit()));
	connect(bOk,SIGNAL(clicked()),this,SLOT(save()));
}



WindowsBracketRecording::~WindowsBracketRecording()
{

}

bool WindowsBracketRecording::eventFilter(QObject *obj, QEvent *event)
{

	if (obj == TextEdit && event->type() == QEvent::KeyPress)
	{
		QKeyEvent *event = new QKeyEvent ( event->KeyPress, event->key(), event->modifiers());
		keyPressEvent(event);

	}
	return QWidget::eventFilter(obj,event);
}

void WindowsBracketRecording::keyPressEvent(QKeyEvent *event)
{
	//qDebug()<<event->key();
	bool isShortcut = ((event->modifiers() & Qt::ControlModifier) && event->key() == Qt::Key_E);


	if(isShortcut)
	{
		qDebug()<<event->KeyPress;
		//completer->popup()->show();
		//if((!nextCompleter())&&(!nextCompleter()))
		//	return;
		//TextEdit->setText(completer->currentCompletion());
		//return;
	}//else
	//QTextEdit::keyPressEvent(event);
	//completer->setCompletionPrefix(TextEdit->toPlainText());
	//index = 0;
}

myTree *WindowsBracketRecording::BuildTree(QString str)
{
	qDebug()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
	qDebug()<<str.size()<<" "<<str;
	if (str == "") return 0;
	if (str == " ") return 0;
	if (str == ",") return 0;
	if (str == "\"")return 0;

	myTree *tree = new myTree;
	if (stringList.indexOf(str) != -1)
	{
		tree->MyName = str;
		return tree;
	}




	int start = 0;
	int end = 0;
	for (int j = 0;j< str.size();j++)
	{
		QChar currentChar = str.at(j);
		if (str.at(j) == ')') return 0;

		if (str.at(j) == '(')
		{

			QString string = str.mid(start,j - start + 1);
			if (stringList.indexOf(string) != -1)
			{
				myTree *treeChild = new myTree;
				treeChild->MyName = string;
				tree->child.append(treeChild);
			}

			int i = doublesSign(str,j,"()");
			myTree *treeChild;

			treeChild = BuildTree(str.mid(j+1,i - j - 2));
			if(treeChild)
			{
				tree->child.append(treeChild);
			}
			j = i;
			start = j;

		}else if (str.at(j) == '\"')
		{
			QString string = str.mid(start,j - start + 1);
			if (stringList.indexOf(string) != -1)
			{
				myTree *treeChild = new myTree;
				treeChild->MyName = string;
				tree->child.append(treeChild);
			}

			int index = str.indexOf("\"",j+1);
			string = str.mid(j+1,index - j-1);

			start = j;
			if (stringList.indexOf(string) != -1)
			{
				myTree *treeChild = new myTree;
				treeChild->MyName = string;
				tree->child.append(treeChild);
			}
			j = index + 1;
		}else if (str.at(j) == ' ' or str.at(j) == ',')
		{
			qDebug()<<",";
			QString string = str.mid(start,j - start);
			start = j+1;

			if (stringList.indexOf(string) != -1)
			{
				myTree *treeChild = new myTree;
				treeChild->MyName = string;
				tree->child.append(treeChild);
			}
		}else if (j ==str.size() - 1)
		{
			QString string = str.mid(start,j - start + 1);
			if (stringList.indexOf(string) != -1)
			{
				myTree *treeChild = new myTree;
				treeChild->MyName = string;
				tree->child.append(treeChild);
			}
		}
	}
	if (tree->child.count() == 0) return 0;
	if (tree->child.count() == 1)
	{
		return tree->child.at(0);
		delete tree;
	}
	tree->MyName = "(";
	for(int i = 0;i< tree->child.count();i++)
		tree->MyName+= tree->child[i]->MyName + ",";
	tree->MyName=tree->MyName.left(tree->MyName.count() -1) + ")";

	return tree;
}

void WindowsBracketRecording::AddTheMissingBranches()
{
	if (!pTree)
	{
		pTree = new myTree;
		pTree->MyName = "(";
		witchAddTheMissingBranches = stringList;
	}else
	{
		witchAddTheMissingBranches = stringList;
		checkTreeName(pTree);
		//pTree->MyName = pTree->MyName.left(pTree->MyName.count() - 1) + ",";
	}
	for(int i = 0; i<witchAddTheMissingBranches.count();i++)
	{
		myTree *tree = new myTree;
		tree->MyName += witchAddTheMissingBranches.at(i);
		tree->parent = pTree;
		pTree->MyName += tree->MyName + ",";
		pTree->child.append(tree);
	}
	pTree->MyName = pTree->MyName.left(pTree->MyName.count() - 1) + ")";
	qDebug()<<pTree->MyName;
}

void WindowsBracketRecording::checkTreeName(myTree *tree)
{
	if (tree->child.count() == 0)
		witchAddTheMissingBranches.removeAll(tree->MyName);
	else
	{
		for(int i = 0; i<tree->child.count();i++)
		{
			checkTreeName(tree->child[i]);
			tree->child[i]->parent = tree;
		}
	}
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

void WindowsBracketRecording::save()
{
	if (correct() == true)
	{
		QString str;
		str = TextEdit->toPlainText().replace("\t"," ");
		str = str.replace("\n"," ");
		pTree = BuildTree(str.remove(QRegExp("[\\n\\t\\r]")));
		if(pTree)
			qDebug()<<"Name"<< pTree->MyName;

		saveParametr(true);
		exit();
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setText("Обнаружены ошибки:" );
		msgBox.setInformativeText(ErrorNames);
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		msgBox.setButtonText(QMessageBox::Save,tr("Сохранить"));
		msgBox.setButtonText(QMessageBox::Discard,tr("Не сохранять"));
		msgBox.setButtonText(QMessageBox::Cancel,tr("Отмена"));
		msgBox.setDefaultButton(QMessageBox::Save);

		int ret;
		ret = msgBox.exec();

		switch (ret) {
		case QMessageBox::Save:
			saveParametr();
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

void WindowsBracketRecording::insertCompletion(const QString &completion)
{
	QTextCursor tc = TextEdit->textCursor();
	int extra = completion.length() - completer->completionPrefix().length();
	tc.movePosition(QTextCursor::Left);
	tc.movePosition(QTextCursor::EndOfWord);
	tc.insertText(completion.right(extra));

	TextEdit->setTextCursor(tc);
}

void WindowsBracketRecording::exit()
{
	close();
}

void WindowsBracketRecording::saveParametr(bool saveTree)
{
	AddTheMissingBranches();
	switch (type)
	{
	case processBlock:
		DView->setBracketProcess(TextEdit->toPlainText());
		if (saveTree) DView->setTreeProcess(pTree);
		else DView->setTreeProcess(0);
		break;
	case dataBlock:
		DView->setBracketData(TextEdit->toPlainText());
		if (saveTree) DView->setTreeData(pTree);
		else DView->setTreeData(0);
		break;
	}
}

void WindowsBracketRecording::savePublic(bool showMsg)
{
	if (correct() == true)
	{
		QString str;
		str = TextEdit->toPlainText().replace("\t"," ");
		str = str.replace("\n"," ");
		pTree = new myTree;
		pTree = BuildTree(str.remove(QRegExp("[\\n\\t\\r]")));
		//qDebug()<<"Name"<< pTree->MyName;

		saveParametr(true);
		//exit();
	}
	else
	{

	}

}

QString WindowsBracketRecording::checkTheSameName(QList<BlockItem *> list)
{
	for(int i = 0;i < list.count() - 1;i++)
		for(int j = i + 1;j < list.count();j++)
			if( list[i]->getName() == list[j]->getName())
				return  list[i]->getName();
	return "";
}

bool WindowsBracketRecording::correct()
{

	QString text = TextEdit->toPlainText();
	if (text == "") return true;
	ErrorNames = "";
	checkName.clear();
	int i = text.count(")");
	int j = text.count("(");
	if ( i != j)
	{
		QString str = "\"%1\" больше чем \"%2\" на %3.";
		if (i > j) str = str.arg(")").arg("(").arg(i - j);
		else str = str.arg("(").arg(")").arg(j - i);
		ErrorNames += str;
		return false;
	}
	if (text.count("\"") % 2 == 1)
	{
		ErrorNames += "Не хватает кавычек. ";
		return false;
	}
	QString str;
	str = TextEdit->toPlainText().replace("\t"," ");
	str = str.replace("\n"," ");

	return checkCorrectName(str.remove(QRegExp("[\\n\\t\\r]")));
	//stringList.count();
	//for (int i = 0;i < )

}

bool WindowsBracketRecording::checkCorrectName(QString str)
{
	qDebug()<<"-------------------------------------";
	qDebug()<<str.size()<<" "<<str;
	if (str == "") return true;
	if (str == " ") return true;
	if (str == ",") return true;
	if (str == "\"")
	{
		ErrorNames +="Внутри кавычек скобки, программа так не может. ";
		return false;
	}
	if ( str.count("(") != 0)
	{
		qDebug()<<"()";
		int count = 1;
		int i = str.indexOf("(");
		int j = i+1;

		while (j < str.size() && count != 0)
		{
			if (str.at(j) == '(') count++;
			if (str.at(j) == ')') count--;
			j++;
		}
		if (count != 0 && i ==  str.size())
		{
			ErrorNames +="К последней скобке не нашел парную. ";
			return false;
		}
		j = j - 1;
		qDebug()<<i<<" "<<j;

		bool b0,b1,b2;
		if (i == 0) b0 = true;
		else b0 = checkCorrectName(str.left(i));

		b1 = checkCorrectName(str.mid(i + 1,j - i - 1));

		if (j == str.size() - 1) b2 = true;
		else b2 = checkCorrectName(str.right(str.size() - j - 1));

		return b0 && b1 && b2;
	}

	if ( str.count("\"") != 0)
	{
		if (str.count("\"") == 1)
		{
			ErrorNames+="При разборе строк, осталась кавычка, проверте правильность записи. ";
			return false;
		}
		qDebug()<<"\"";
		int i = str.indexOf("\"");
		int j = str.indexOf("\"",i+1);
		qDebug()<<i<<" "<<j;
		bool b0,b1,b2;

		if (i == 0) b0 = true;
		else b0 = checkCorrectName(str.left(i));

		b1 = checkCorrectName(str.mid(i + 1,j - i - 1));

		if (j == str.size() - 1) b2 = true;
		else b2 = checkCorrectName(str.right(str.size() - j - 1));

		return b0 && b1 && b2;
	}


	if (stringList.indexOf(str) != -1)
	{
		if (checkName.indexOf(str) != -1)
		{
			ErrorNames+="Найдено повторяющееся имя:\""  + str.simplified() + "\".";
			return false;
		}else
		{
			checkName.append(str);
			return true;
		}
	}
	if ( str.count(",") != 0)
	{
		qDebug()<<",";
		bool b0,b1;
		int i = str.indexOf(",");
		qDebug()<<i<<" "<<str.size() - 1<<" "<<str.left(i)<<" "<<str.right(str.size() - i - 1);

		if (i == 0) b0 = true;
		else b0 =  checkCorrectName(str.left(i));

		if (i == str.size()  ) b1 = true;
		else b1 =  checkCorrectName(str.right(str.size() - i - 1));

		return b0 && b1;
	}

	if ( str.count(" ") != 0)
	{
		qDebug()<<" ";
		bool b0,b1;
		int i = str.indexOf(" ");
		qDebug()<<i;
		qDebug()<<checkCorrectName(str.left(i));
		qDebug()<<checkCorrectName(str.right(str.size() - i - 1));
		if (i == 0) b0 = true;
		else b0 = checkCorrectName(str.left(i));

		if (i == str.size() -1 ) b1 = true;
		else  b1 = checkCorrectName(str.right(str.size() - i - 1));
		qDebug()<<b0,b1;
		//qDebug()<<str.left(i);
		//qDebug()<<str.right(str.size() - i - 1);
		return b0 && b1;
	}
	ErrorNames += "Не найдено имя: \"" + str.simplified() + "\".";
	return false;
}

bool WindowsBracketRecording::nextCompleter()
{
	if(completer->setCurrentRow(index++)) return true;
	index = 0;
	return false;
}

QString WindowsBracketRecording::parser()
{
	QString str;
	str = TextEdit->toPlainText();
	if(str.count("\"" ) % 2 == 1)
	{
		qDebug()<<str.right(str.size() - str.count("\"" ));
		return str.right(str.size() - str.count("\"" ) );
	}else
	{

	}
}
