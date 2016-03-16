#include "matrix_red.h"
int main()
{
	string name_of_file;
	char answer[4];
	setlocale(LC_ALL, "Russian");
	cout << "Введите количество строк и столбцов" << endl;
	int m, n;
	cin >> m;
	cin >> n;
	cout << "Введите имя файла" << "\n";
	cin >> name_of_file;
	matrix _matrix(m, n);
	_matrix.get_from_file(name_of_file);
	cout << "Матрица из файла " <<name_of_file<< " :\n";
	_matrix.print_matrix();
	cout << "--------------------------------------\n";
	cout << "Введите число для генерации случайной матртицы" << "\n";
	int time;
	cin >> time;
	matrix rand_matrix(m, n, time);
	cout << "Рандомная матрица:" << "\n";
	rand_matrix.print_matrix();
	cout << "------------------------------------------------\n";
	cout << "Хотите сложить рандомную матрицу и матрицу из файла?(yes|no)" << "\n";
	cin >> answer;
	if (strcmp("yes", answer) == 0)
	{
		matrix sum_matrix(m, n);
		sum_matrix = _matrix + rand_matrix;
		sum_matrix.print_matrix();
	}
	cout << "------------------------------------------------\n";
	cout << "Хотите умножить рандомную матрицу на матрицу из файла?(yes|no)" << "\n";
	cin >> answer;
	if (strcmp("yes", answer) == 0)
	{
		matrix mult_matrix(m, n);
		mult_matrix = _matrix * rand_matrix;
		mult_matrix.print_matrix();
	}
	cout << "------------------------------------------------\n";
	cout << "Какую строку вывести из матрицы из файла?" << "\n";
	int k;
	cin >> k;
	_matrix.get_line(k);
	cout << "\n------------------------------------------------\n";
	cout << "\n";
	cout << "Количество столбцов и строк: " << "\n";
	cout << " " << _matrix.get_num_cols() << " строк и ";
	cout << " " << _matrix.get_num_rows() <<" столбцов" << endl;
	cout << "\n------------------------------------------------\n";
	system("pause");
    return 0;
}

