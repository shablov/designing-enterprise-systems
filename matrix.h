#ifndef MATRIX_H
#define MATRIX_H


class MyMatrix
{

public:
	MyMatrix(int row=1, int col=1,float data = 0); // конструктор
	~MyMatrix();
	void display();
	void fill(float data);

	void setData(int col, int row, float data);
	float getData(int row, int col);
	int getRows() const;
	int getCols() const;
//	void transposition();
	void RelativeFrequency();
	static MyMatrix RelativeFrequency(MyMatrix m);

	static MyMatrix transposition(MyMatrix m);
	static MyMatrix multiBitwise(MyMatrix m1,MyMatrix m2);
	static MyMatrix multi(MyMatrix m1,MyMatrix m2);


	float &operator()(int row, int col);
	const float &operator()(int row, int col) const;
private:
	void createMatrix();
	int rows;
	int cols;
	float **intdata;


	struct m_float
	{float i;};

};
#endif // MATRIX_H
