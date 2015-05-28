#include "matrix.h"
#include "QDebug"

MyMatrix::MyMatrix(int row, int col, double data) : intdata(0)
{
	rows=row;
	cols=col;
	createMatrix();
	fill(data);
	//intdata = new double[row][col];
	return;
}

MyMatrix::~MyMatrix()
{
	//qDeleteAll(intdata);
}

double MyMatrix::getData(int row, int col)
{
	if (row < 0 || row > rows)
		return 0;
	if (col < 0 || col > cols)
		return 0;
	return intdata[row][col];
}

void MyMatrix::createMatrix()
{
	if (rows<1) rows = 1;
	if (cols<1) cols = 1;
	if (intdata)
	{
		delete(intdata);
		intdata = 0;
	}

	intdata=new double* [this->rows];
	for(int i=0; i<rows;i++)
		intdata[i]=new double [this->cols];
}
int MyMatrix::getRows() const
{
	return rows;
}

int MyMatrix::getCols() const
{
	return cols;
}


void MyMatrix::RelativeFrequency()
{
	qDebug()<<"Делим на частоту ";
	for (int j=0;j<rows;j++)
	{
	double buff = intdata[j][j];
		for (int i=0;i<cols;i++)
		{
			qDebug()<<intdata[j][i]<<" "<<buff;
			intdata[j][i] = intdata[j][i]/buff;
		}
	}
	qDebug()<<"конец Делим на частоту";
}

MyMatrix MyMatrix::RelativeFrequency(MyMatrix m)
{
	MyMatrix result = m;
	result.RelativeFrequency();
	return result;
}

MyMatrix MyMatrix::transposition(MyMatrix m)
{
	MyMatrix result(m.getCols(),m.getRows());// m.getCols(),m.getRows());
	for (int j=0;j<result.getRows();j++)
		for (int i=0;i<result.getCols();i++)
			result.setData(j,i,m.getData(i,j));
	return result;
}

MyMatrix MyMatrix::multiBitwise(MyMatrix m1, MyMatrix m2)
{
	if (m1.getCols() != m2.getCols())
		return MyMatrix(1,1);
	MyMatrix result(m1.getRows(),m1.getCols());
	qDebug()<<"-----------";
	for (int j=0;j<m1.getRows();j++)
		for (int i=0;i<m1.getCols();i++)
		{
			result.setData(j,i,m1.getData(j,i)*m2.getData(0,i));
			qDebug()<<result.getData(j,i);
		}
	qDebug()<<"-----------";
	return result;
}

MyMatrix MyMatrix::multi(MyMatrix m1, MyMatrix m2)
{

	if (m1.getCols() != m2.getRows())
		return MyMatrix(1,1);
	MyMatrix result(m1.getRows(),m2.getCols());
	for (int j=0;j<m1.getRows();j++)
		for (int i=0;i<m2.getCols();i++)
			for (int k=0;k<m1.getCols();k++)
				result.setData(j,i,result.getData(j,i) + m1.getData(i,k)*m2.getData(k,j));
	return result;
}


void MyMatrix::setData(int row, int col,double data)
{
	if (row < 0 || row > rows)
		return;
	if (col < 0 || col > cols)
		return;
	intdata[row][col] = data;
}

void MyMatrix::fill(double data)
{
	for (int j=0;j<rows;j++)
	{
		for (int i=0;i<cols;i++)
		{
			intdata[j][i] = data;
		};
	}
	return;
}

double &MyMatrix::operator()(int row, int col)
{
	if(row<0 || row>=rows || col<0 || col>=cols)
		exit(2);
	return intdata[row][col];

}

const double &MyMatrix::operator()(int row, int col) const
{
	return intdata[row][col];
}


void MyMatrix::display()
{
	for (int j=0;j<rows;j++)
	{
		QString str = "";
		for (int i=0;i<cols;i++)
		{
			str += QString::number(intdata[j][i]) + " "; // печатаем колонки
		}
		qDebug()<<str;
	}
}
