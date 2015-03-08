#ifndef BLOCKCONTEXTMENU_H
#define BLOCKCONTEXTMENU_H

#include <QWidget>
#include "block.h"
#include <QLineEdit>
#include <QSpinBox>
class BlockContextMenu : public QWidget
{
	Q_OBJECT
public:

	~BlockContextMenu();
	explicit BlockContextMenu(BlockItem *blockItem, QWidget *parent = 0);
signals:

public slots:
	void reNameBlock();
private:

	QLineEdit *leName;
	QSpinBox *sbFrequency;
	BlockItem *pBlockItem;
};

#endif // BLOCKCONTEXTMENU_H
