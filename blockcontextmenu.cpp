#include "blockcontextmenu.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include "block.h"
#include <QList>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
BlockContextMenu::BlockContextMenu(BlockItem* blockItem,QWidget *parent) : QWidget(parent),pBlockItem(blockItem)
{
	QPushButton *bOk= new QPushButton(tr("Ok"),this);
	QPushButton *bCansel = new QPushButton(tr("Cansel"),this);
	leName = new QLineEdit(blockItem->getName(),this);
	sbFrequency = new QSpinBox(this);
	sbFrequency->setValue(blockItem->getFrequencyOfActivation());
	sbFrequency->setMinimum(1);
	QGridLayout *layout = new QGridLayout;
	QList<QLabel*> listLabel;

	int i = 0;
	layout->addWidget(leName,i,0,1,2);
	if (blockItem->getType() == processBlock)
	{
		++i;
		layout->addWidget(sbFrequency,i,0,1,2);
	}else sbFrequency->setVisible(false);

	QList<BlockItem*> list = blockItem->reference();
	for(int j = 0;j <list.count();j++)
	{
		++i;
		listLabel.append(new QLabel(list[j]->getName(),this));
		layout->addWidget(listLabel[j],i,0,1,2);
	}
	++i;
	layout->addWidget(bOk,i,0);
	layout->addWidget(bCansel,i,1);
	setLayout(layout);

	connect(bCansel,SIGNAL(clicked()),this,SLOT(close()));
	connect(bOk,SIGNAL(clicked()),this,SLOT(reNameBlock()));
}

void BlockContextMenu::reNameBlock()
{
	pBlockItem->setName(leName->text());
	pBlockItem->setFrequencyOfActivation(sbFrequency->value());
	this->close();
}
BlockContextMenu::~BlockContextMenu()
{

}

