#include "frequencywindow.h"
#include <QPushButton>
#include <QSpinBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QDebug>
FrequencyWindow::FrequencyWindow(QList<BlockItem *> listRect, QWidget *parent) : QWidget(parent)
{
	listBlock = listRect;

	QPushButton *bOk= new QPushButton(tr("Ok"),this);
	QPushButton *bCansel = new QPushButton(tr("Cansel"),this);
	QGridLayout *layout = new QGridLayout;

	for (int i = 0;i <listBlock.count();++i)
	{
		QSpinBox *sb = new  QSpinBox;
		sb->setValue(listBlock[i]->getFrequencyOfActivation());
		sb->setMinimum(1);
		listSpin.append(sb);
		QLineEdit *le = new  QLineEdit;
		le->setText(listBlock[i]->getName());
		listLine.append(le);

		layout->addWidget(le,0,i);
		layout->addWidget(sb,1,i);
	}
	qDebug()<<listBlock.count();
	if (listBlock.count()==0)
	{
		layout->addWidget(bOk,0,1);
		layout->addWidget(bCansel,0,2);
	}else if(listBlock.count()==1)
	{
		layout->addWidget(bOk,2,1);
		layout->addWidget(bCansel,2,2);
	}else
	{
		layout->addWidget(bOk,2,listBlock.count()-2);
		layout->addWidget(bCansel,2,listBlock.count()-1);
	}

	setLayout(layout);
	connect(bCansel,SIGNAL(clicked()),this,SLOT(close()));
	connect(bOk,SIGNAL(clicked()),this,SLOT(save()));
}

FrequencyWindow::~FrequencyWindow()
{
	//ToDo deleteall list
	qDeleteAll(listSpin);
	qDeleteAll(listLine);
}



FrequencyWindow::save()
{
	for(int i =0;i<listBlock.count();i++)
	{
		listBlock[i]->setFrequencyOfActivation(listSpin[i]->value());
		listBlock[i]->setName(listLine[i]->text());
	}
	close();
}

