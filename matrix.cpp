#include "matrix.h"
#include "QDebug"

matrix::matrix(int row, int col, float data)
{
	rows=row;
	cols=col;
	createMatrix();
	fill(data);
	//intdata = new float[row][col];
	return;
}

float matrix::getData(int row, int col)
{
	if (row < 0 || row > rows)
		return 0;
	if (col < 0 || col > cols)
		return 0;
	return intdata[row][col];
}

void matrix::createMatrix()
{
	if (rows<1) rows = 1;
	if (cols<1) cols = 1;

	intdata=new float* [this->rows];
	for(int i=0; i<rows;i++)
		intdata[i]=new float [this->cols];

}
int matrix::getRows() const
{
	return rows;
}

int matrix::getCols() const
{
	return cols;
}

matrix matrix::transposition()
{
	matrix m(cols,rows);
	for (int j=0;j<rows;j++)
		for (int i=0;i<cols;i++)
			m.setData(i,j,getData(j,i));
	return m;
}

matrix matrix::multi(matrix m1, matrix m2)
{

	if (m1.getCols() != m2.getRows())
		return matrix(1,1);
	matrix result(m1.getRows(),m2.getCols());
	for (int j=0;j<m1.getRows();j++)
		for (int i=0;i<m2.getCols();i++)
			for (int k=0;k<m1.getCols();k++)
				result.setData(j,i,result.getData(j,i) + m1.getData(i,k)*m2.getData(k,j));
	return result;
}


void matrix::setData(int row, int col,float data)
{
	if (row < 0 || row > rows)
		return;
	if (col < 0 || col > cols)
		return;
	intdata[row][col] =data;
}

void matrix::fill(float data)
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

float &matrix::operator()(int row, int col)
{
	if(row<0 || row>=rows || col<0 || col>=cols)
		exit(2);
	return intdata[row][col];

}

const float &matrix::operator()(int row, int col) const
{
	return intdata[row][col];
}


void matrix::display()
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
