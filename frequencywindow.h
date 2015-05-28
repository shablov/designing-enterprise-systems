#ifndef FREQUENCYWINDOW_H
#define FREQUENCYWINDOW_H
#include <QWidget>
#include "block.h"
#include <QDoubleSpinBox>
#include <QLineEdit>
class FrequencyWindow: public QWidget
{
	Q_OBJECT
public:
	FrequencyWindow(QList<BlockItem *> listRect, QWidget *parent = 0);
	~FrequencyWindow();

private slots:
	save();
private:
	QList<BlockItem *>  listBlock;
	QList<QDoubleSpinBox *> listSpin;
	QList<QLineEdit *> listLine;
};

#endif // FREQUENCYWINDOW_H
