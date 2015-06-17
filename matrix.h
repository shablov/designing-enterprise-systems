#ifndef MATRIX_H
#define MATRIX_H


class MyMatrix
{

public:
	MyMatrix(int row=1, int col=1,double data = 0); // конструктор
	~MyMatrix();
	void display();
	void fill(double data);

	void setData(int col, int row, double data);
	void PlusData(int col, int row, double data);
	double getData(int row, int col);
	int getRows() const;
	int getCols() const;
//	void transposition();
	void RelativeFrequency();
	static MyMatrix RelativeFrequency(MyMatrix m);

	static MyMatrix transposition(MyMatrix m);
	static MyMatrix multiBitwise(MyMatrix m1,MyMatrix m2);
	static MyMatrix multi(MyMatrix m1,MyMatrix m2);


	double &operator()(int row, int col);
	const double &operator()(int row, int col) const;
private:
	void createMatrix();
	int rows;
	int cols;
	double **intdata;


	struct m_double
	{double i;};

};
#endif // MATRIX_H
