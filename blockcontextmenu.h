#ifndef BLOCKCONTEXTMENU_H
#define BLOCKCONTEXTMENU_H

#include <QWidget>
#include "block.h"
#include <QLineEdit>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QList>
class BlockContextMenu : public QWidget
{
	Q_OBJECT
public:

	~BlockContextMenu();
	explicit BlockContextMenu(BlockItem *blockItem, QWidget *parent = 0);
signals:

public slots:
	void reNameBlock();
	void addToRemove();
private:
	QLineEdit *leName;
	QDoubleSpinBox *sbFrequency;
	BlockItem *pBlockItem;
	QList<BlockItem*> lToRemove;
	QList<QPushButton*> lPushButton;
};

#endif // BLOCKCONTEXTMENU_H
