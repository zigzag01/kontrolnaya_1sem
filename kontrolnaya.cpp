// Белошко Елизавета

#include <iostream> 
#include <fstream> 
#include <cstring> 
#include <string> 
#include <cstdlib> 
#include <cctype> 
#include <iomanip> 
#pragma warning (disable: 4996);
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

// четные слова-числа
bool is_even_number(const string& word) {
	for (char c : word) { // проходит по каждому символу в слове
		if (!isdigit(c)) { // является цифрой
			return false;
		}
		string s(1, c); // c - символ из строки word, преобразовываем его в строку s
		// s.c_str() берет строку s, преобразует ее в C-style строку 
		int num = atoi(s.c_str()); // atoi() преобразует C-style строку в число
		if (num % 2 != 0) { // проверка на четность
			return false;
		}
	}
	return true;
}

// сумма столбца матрицы
int sum_of_column(int** Matr, int column, int rows) {
	int sum = 0;
	for (int i = 0; i < rows; i++) {
		sum += Matr[i][column];
	}
	return sum;
}

// сумма цифр числа
int sum_of_nums(int num) {
	int sum = 0;
	while (num > 0) {
		sum += num % 10;
		num /= 10;
	}
	return sum;
}

int main() {
	setlocale(LC_ALL, "rus");
	// входной и выходной потоки файлов
	ifstream input_file;
	ofstream output_file;

	input_file.open("Input.txt");
	if (!input_file) {
		cout << "Не удалось открыть файл Input.txt";
		return 0;
	}
	output_file.open("Output.txt");
	if (!output_file) {
		cout << "Не удалось открыть файл Output.txt";
		return 0;
	}

	int* DArray = new int[80]; // одномерный динамический массив
	string str;
	int count = 0; // счетчик для отслеживания количества элементов, добавленных в DArray

	output_file << "Исходная строка: ";
	// getline автоматически удаляет символ переноса строки \n из строки, которую она читает
	// таким образом, каждая строка str, обрабатываемая внутри цикла while, не включает символ переноса строки
	while (getline(input_file, str)) {
		char* str2 = new char[str.length() + 1]; // новый динамический массив символов, +1 к длине тк нужен доп символ для нулевого символа \0
		strcpy(str2, str.c_str()); // копирует str в str2, c_str() преобразует string в массив символов, чтобы воспользоваться strcpy
		output_file << str2 << " ";
		char* word = strtok(str2, " "); // разделяет строку str2 на токены word по пробелу
		while (word != NULL) {
			if (is_even_number(word)) { // когда в строке находится четное число
				DArray[count] = atoi(word); // оно преобразуется из строки в целое число с помощью ф-ии atoi() 
				count++; // счетчик увеличивается
			}
			word = strtok(NULL, " "); // переходит к следующему слову
		}
		delete[] str2; // освобождает память
	}
	output_file << endl; // добавляет строку в файл Output.txt

	output_file << "Элементы массива DArray: "; 
	for (int i = 0; i < count; i++) { // выводит все эл-ты массива DArray 
		output_file << DArray[i] << " ";
	}
	output_file << endl; // записывает их в файл

	int Max = DArray[0]; // мин и макс эл-ты в массиве DArray
	int Min = DArray[0];
	for (int i = 0; i < count; i++) {
		if (DArray[i] < Min) {
			Min = DArray[i];
		}
		if (DArray[i] > Max) {
			Max = DArray[i];
		}
	}
	// их вывод в файл
	output_file << "Минимальный элемент: " << Min << endl << "Максимальный элемент: " << Max << endl;

	int between_max_min = 0; // кол-во эл-тов в массиве DArray, которые > Min и < Max:
	for (int i = 0; i < count; i++) {
		if (DArray[i] < Max && DArray[i] > Min) {
			between_max_min++;
		}
	}
	// их вывод в файл
	output_file << "Количество эл-тов между мин и макс: " << between_max_min << endl;

	int** Matr = new int* [3]; // матрица размером 3 x between_max_min
	for (int i = 0; i < 3; i++) {
		Matr[i] = new int[between_max_min];
	}
	for (int j = 0; j < between_max_min; j++) {
		Matr[0][j] = DArray[j]; // содержит эл-ты массива DArray
		Matr[1][j] = j; // содержит индексы элементов массива
		Matr[2][j] = sum_of_nums(DArray[j]); // содержит сумму цифр каждого эл-та массива
	}
	for (int i = 0; i < 3; i++) { // выводит матрицу в файле Output.txt
		for (int j = 0; j < between_max_min; j++) {
			output_file << setw(5) << Matr[i][j] << " ";
		}
		output_file << endl;
	}

	int column; // столбец матрицы
	cout << "введите номер столбца матрицы: ";
	cin >> column;

	if (column > 0 && column <= between_max_min) { // проверка, является ли номер столбца допустимым
		int summa = sum_of_column(Matr, column - 1, 3); // если да, то вычисляет сумму эл-тов в этом столбце
		output_file << "сумма столбца матрицы: " << summa << endl; // и выводит ее в файле
	}
	else {
		output_file << "Некорректный номер столбца" << endl; // иначе выводит предупреждение
	}
	for (int i = 0; i < 3; i++) { // освобождает память выделенную под эл-ты двумерного массива Matr
		delete[] Matr[i];
	}

	delete[] Matr; // освобождает память выделенную под массивы
	delete[] DArray;
	input_file.close(); // закрывает выходные файлы
	output_file.close();

	system("pause");
	return 0;
}