// matrix_red.h: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class matrix 
{public:
	matrix();
	matrix(int _cols, int _rows);
	matrix(const matrix &Matrix);
	matrix(int _rows, int _columns, int time);
	~matrix();
	void get_line(int k);
	void get_from_file(string _name);
	void print_matrix();
	void copy_matrix(const matrix &Matrix);
	matrix &operator=(const matrix &Matrix);
   friend matrix operator+(const matrix &matrix_1, const matrix &matrix_2);
   friend matrix operator*(const matrix &matrix_1, const matrix &matrix_2);
   int *operator[] (int i);
   void get_sum_r(const matrix &matrix_1, const matrix &matrix_2, int s);
   void get_multi_r(const matrix &matrix_1, const matrix &matrix_2, int m);
   void create_memory();
   int get_num_rows();
   int get_num_cols();
	int get(int rows, int columns) const;
	void set(int row, int columns, int set);

private:
   int rows;
   int columns;
   int **_matrix;
};



//Конструктор по умолчанию
matrix::matrix() :rows(0), columns(0), _matrix(nullptr)
{
	
}



//конструктор с параметрами кол-во строк, кол-во столбцов
matrix::matrix(int _rows, int _columns): rows(_rows),  columns(_columns)
{
	create_memory();
	for (int i = 0; i < rows; i++) { 
		for (int j = 0; j < columns; j++) _matrix[i][j] = 0;
	};
}




//конструктор случайной матрицы
matrix::matrix(int _rows, int _columns, int time) :rows(_rows), columns(_columns)
{
	create_memory();
	srand(time);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
		{
			
			_matrix[i][j] = rand() % 10;
		}
	};
}



//конструктор (глубокого) копирования 
matrix::matrix(const matrix & matrix): rows(matrix.rows), columns(matrix.columns)
{
	create_memory();
	copy_matrix(matrix);
}



// Заполение матрицы из файла 
void matrix::get_from_file(string name)
{
	string full_name;
	full_name = name +".txt";
	ifstream fin(full_name); 
	if (fin.is_open()) {
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				fin >> _matrix[i][j];
		fin.close(); 
	}
	else {
		cout << "Ошибка, попробуйте еще раз";
		exit(100);
	}
}



 // деструктор
matrix::~matrix()
{
	for (int i = 0; i < rows; i++)
		delete[] _matrix[i];

	delete[] _matrix;
}



// печать матрицы
void matrix::print_matrix() 
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << "   " << _matrix[i][j];
		};
		cout << "\n";
	};
}


void matrix::get_line(int k)
{
	int *row_matrix;  //указатель
	row_matrix = _matrix[k];
	for (int i = 0; i < columns; i++)
		cout << " " << row_matrix[i];
}


// копирование матрицы
void matrix::copy_matrix(const matrix & matrix)  
{
	for (int i = 0; i <rows; i++)
		for ( int j = 0; j < columns; j++)
			_matrix[i][j] = matrix._matrix[i][j];
}


// перегрузка оператора = 
matrix & matrix::operator=(const matrix & matrix) {
        if (this != &matrix) { //перегруженный оператор присваивания
            for (int i = 0; i < rows; i++)
                delete[] _matrix[i];
            delete[] _matrix;
            columns = matrix.columns;
            rows = matrix.rows;
            _matrix = new int *[rows];
            for (int j = 0; j<rows; j++)
            {
                _matrix[j] = new int[columns];
                for (int i = 0; i < columns; i++)
                {
                    _matrix[j][i] = matrix._matrix[j][i];
                }

            }
        }
        return *this;
    }



 // передача номера строки, столбца и значения
void matrix::set(int row, int columns, int set)
{
	_matrix[row][columns] = set;
}


// взятие элемента 
int matrix::get(int row, int columns) const 
{
	return _matrix[row][columns];
} 



// сумма построчно
void matrix::get_sum_r(const matrix &matrix_1, const matrix &matrix_2, int i) 
{
	for (int j = 0; j < get_num_cols(); j++)
		set(i, j, matrix_1.get(i, j) + matrix_2.get(i, j));
}



 //перегрузка оператора + 
matrix operator+(const matrix &matrix_1, const matrix &matrix_2)
{
	matrix matrix(matrix_1.rows, matrix_1.columns);//создаем новую матрицу 

	for (int i = 0; i < matrix.rows; i++)
		matrix.get_sum_r(matrix_1, matrix_2, i);
	return matrix;
};


//перегрузка оператора * 
matrix operator*(const matrix &matrix_1, const matrix &matrix_2) {
	matrix matrix(matrix_1.rows, matrix_2.columns);
	for (int i = 0; i < matrix.rows; i++)
		matrix.get_multi_r(matrix_1, matrix_2, i);
	return matrix;
};

// количество строк
int matrix::get_num_rows() 
{
	return rows;
}


 // Произведение
void matrix::get_multi_r(const matrix &matrix_1, const matrix &matrix_2, int i)
{
	int value = 0;
	for (int row = 0; row < matrix_1.rows; row++) {
		for (int col = 0; col < matrix_2.columns; col++) {
			for (int inner = 0; inner < matrix_2.rows; inner++) {
				value += matrix_1._matrix[row][inner] * matrix_2._matrix[inner][col];
			}
			set(row, col, value);
			value = 0;
		}
	}
};



//Количество столбцов
int matrix::get_num_cols()
{
	return columns;
}


// выделяем память
void matrix::create_memory() 
{
	_matrix = new int*[rows];

	for (int i = 0; i < rows; i++)
		_matrix[i] = new int[columns];
}



// перегрузка оператора [] 
int* matrix::operator [] (int i)
{
	int *Getline = new int[columns];// одномерный массив для хранения столбцов
	for (int j = 0; j < columns; j++)
		Getline[j] = _matrix[i][j];
	return Getline;

}
