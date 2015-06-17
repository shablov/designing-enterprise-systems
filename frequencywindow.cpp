#include "frequencywindow.h"
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QDebug>
FrequencyWindow::FrequencyWindow(QList<BlockItem *> listRect, QWidget *parent) : QWidget(parent)
{
	listBlock = listRect;

	//listRect[0]->setFrequencyOfActivation(1.23);

	QPushButton *bOk= new QPushButton(tr("Сохранить"),this);
	QPushButton *bCansel = new QPushButton(tr("Отмена"),this);
	QGridLayout *layout = new QGridLayout;
	int j = 0;
	for (int i = 0;i <listBlock.count();++i)
	{	
		QDoubleSpinBox  *sb = new  QDoubleSpinBox ;
		sb->setValue(listBlock.at(i)->getFrequencyOfActivation());
		sb->setMinimum(0.01);
		sb->setSingleStep(0.01);
		listSpin.append(sb);
		QLineEdit *le = new  QLineEdit;
		le->setText(listBlock.at(i)->getName());
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



void FrequencyWindow::save()
{
	for(int i =0;i<listBlock.count();i++)
	{
		listBlock.at(i)->setFrequencyOfActivation(listSpin[i]->value());
		listBlock.at(i)->setName(listLine[i]->text());
	}
	close();
}

