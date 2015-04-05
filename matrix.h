#ifndef MATRIX_H
#define MATRIX_H


class matrix
{

public:
	matrix(int row=1, int col=1,float data = 0); // конструктор
	~matrix();
	void display();
	void fill(float data);

	void setData(int col, int row, float data);
	float getData(int row, int col);
	int getRows() const;
	int getCols() const;
//	void transposition();
	void RelativeFrequency();
	static matrix RelativeFrequency(matrix m);

	static matrix transposition(matrix m);
	static matrix multiBitwise(matrix m1,matrix m2);
	static matrix multi(matrix m1,matrix m2);


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
