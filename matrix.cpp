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

matrix::~matrix()
{
	//qDeleteAll(intdata);
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
	delete(intdata);
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

//void matrix::transposition()
//{
//	matrix m(cols,rows);
//	for (int j=0;j<rows;j++)
//		for (int i=0;i<cols;i++)
//			m.setData(i,j,getData(j,i));

//	cols = m.getCols();
//	rows = m.getCols();
//	createMatrix();
//	for (int j=0;j<rows;j++)
//		for (int i=0;i<cols;i++)
//			setData(i,j,m.getData(i,j));
//}

void matrix::RelativeFrequency()
{
	for (int j=0;j<rows;j++)
	{
	int buff = intdata[j][j];
		for (int i=0;i<cols;i++)
		{
			qDebug()<<intdata[j][i]<<" "<<buff;
			intdata[j][i] = intdata[j][i]/buff;
		}
	}
}

matrix matrix::RelativeFrequency(matrix m)
{
	matrix result = m;
	result.RelativeFrequency();
	return result;
}

matrix matrix::transposition(matrix m)
{
	matrix result(m.getCols(),m.getRows());// m.getCols(),m.getRows());
	for (int j=0;j<result.getRows();j++)
		for (int i=0;i<result.getCols();i++)
			result.setData(j,i,m.getData(i,j));
	return result;
}

matrix matrix::multiBitwise(matrix m1, matrix m2)
{
	if (m1.getCols() != m2.getCols())
		return matrix(1,1);
	matrix result(m1.getRows(),m1.getCols());
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
