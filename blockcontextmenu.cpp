#include "blockcontextmenu.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include "block.h"
#include <QList>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
BlockContextMenu::BlockContextMenu(BlockItem* blockItem,QWidget *parent) : QWidget(parent),pBlockItem(blockItem)
{
	QPushButton *bOk= new QPushButton(tr("Сохранить"),this);
	QPushButton *bCansel = new QPushButton(tr("Отмена"),this);
	leName = new QLineEdit(blockItem->getName(),this);
	sbFrequency = new QDoubleSpinBox(this);
	sbFrequency->setValue(blockItem->getFrequencyOfActivation());
	sbFrequency->setMinimum(0.01);
	sbFrequency->setSingleStep(0.01);
	QGridLayout *layout = new QGridLayout;
	QList<QLabel*> listLabel;

	int i = 0;
	layout->addWidget(leName,i,0,1,2);
    //if (blockItem->getType() == processBlock)
	{
		++i;
		layout->addWidget(sbFrequency,i,0,1,2);
	}//else sbFrequency->setVisible(false);

	QList<BlockItem*> list = blockItem->reference();
	for(int j = 0;j <list.count();j++)
	{
		++i;
		QHBoxLayout *hlayout = new QHBoxLayout;
		QPushButton *button = new QPushButton();
		button->setProperty("action", j);
		//button->setMaximumWidth(button->he()) ;
//		button->setText(tr("Удалить"));
		button->setIcon(QIcon(":/img/source/cross.png")); //ToDo: ширину поправить
		{
			button->setAutoFillBackground(true);
			QPalette palette = button->palette();
			palette.setColor(QPalette::Window, QColor(Qt::red));
			button->setPalette(palette);
			button->setFixedWidth(32);
		}



		//button->setMaximumWidth(32);

		lPushButton.append(button);
		listLabel.append(new QLabel(list[j]->getName(),this));
		hlayout->addWidget(button);
		hlayout->addWidget(listLabel[j]);
		layout->addLayout(hlayout,i,0,1,2);

		connect(button,SIGNAL(clicked()),this,SLOT(addToRemove()));
//		QPushButton *button = new QPushButton();
//		button->setProperty("action", j);
//		int k = button->property("action").toInt();
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
	BlockItem * bi;
	foreach (BlockItem * bi,lToRemove)
			pBlockItem->removeReferenceAndLine(bi);

	this->close();
}

void BlockContextMenu::addToRemove()
{
	QPushButton * button =(QPushButton *) sender();
	QList<BlockItem*> list = pBlockItem->reference();
	lToRemove.append(list[button->property("action").toInt()]);
	//button->setText(tr("Удалено"));
	button->setIcon(QIcon(":/img/source/crossBlack.png"));
	{
		button->setAutoFillBackground(true);
		QPalette palette = button->palette();
		palette.setColor(QPalette::Window, QColor(Qt::black));
		button->setPalette(palette);
	}
}
BlockContextMenu::~BlockContextMenu()
{

}

