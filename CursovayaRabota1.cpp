#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <chrono>
#include <ctime> 
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

//////////////ПЕРВАЯ ЛАБОРАТОРНАЯ
void LabaOne()
{
	cout << "How much memory each data type takes: \n";
	cout << "int size: " << sizeof(int) << endl;
	cout << "short int size: " << sizeof(short int) << endl;
	cout << "long int size: " << sizeof(long int) << endl;
	cout << "float size: " << sizeof(float) << endl;
	cout << "double size: " << sizeof(double) << endl;
	cout << "long double size: " << sizeof(long double) << endl;
	cout << "char size: " << sizeof(char) << endl;
	cout << "bool size: " << sizeof(bool) << endl;
	cout << "\n";

	cout << "Displaying the binary representation of an integer.\n";

	string repeat = "no";
	do
	{
		cout << "Enter int value: ";
		int value = 0;
		cin >> value;
		int mask = 1 << 32 - 1;

		for (int i = 0; i < 32; i++) {

			putchar(value & mask ? '1' : '0');
			value <<= 1;

			if (i % 31 == 0)
			{
				putchar(' ');
			}
			if (i % 8 == 0)
			{
				putchar(' ');
			}
		}

		cout << endl;
		cout << "Enter another value? (no/yes) - ";
		cin >> repeat;
		cout << endl;
	} while (repeat == "yes");


	cout << "Displaying the binary representation of an float.\n";

	repeat = "no";
	do
	{
		cout << "Enter float value: ";
		union {
			float f;
			int i;
		} u;
		cin >> u.f;

		int mask = 1 << 32 - 1;

		for (int i = 0; i < 32; i++)
		{
			putchar(u.i & mask ? '1' : '0');

			u.i <<= 1;

			if (i % 31 == 0)
			{
				putchar(' ');
			}
			if (i % 8 == 0)
			{
				putchar(' ');
			}
		}

		cout << endl;
		cout << "Enter another value? (no/yes) - ";
		cin >> repeat;
		cout << endl;
	} while (repeat == "yes");


	cout << "Displaying the binary representation of an double.\n";

	repeat = "no";
	do
	{
		cout << "Enter double value: ";
		int discharge = 0;
		union {
			double d;
			int i[2];
		} u;
		cin >> u.d;

		int mask = 1 << 31;
		for (int x = 0; x < 2;) {
			for (int i = 0; i < 32; i++)
			{
				putchar(u.i[x] & mask ? '1' : '0');
				u.i[x] <<= 1;

				discharge++;
				if (discharge == 1)
				{
					putchar(' ');
				}
				if (discharge == 12)
				{
					putchar(' ');
				}
			}
			x++;
		}

		cout << endl;
		cout << "Enter another value? (no/yes) - ";
		cin >> repeat;
		cout << endl;
	} while (repeat == "yes");


	cout << "End\n";
}
//////////////ПЕРВАЯ ЛАБОРАТОРНАЯ


//////////////ВТОРАЯ ЛАБОРАТОРНАЯ

typedef chrono::high_resolution_clock Clock;
typedef chrono::duration<double> sec;

int arrInt[100]; // изначальный массив
int arrIntSort[100]; // отсортированный массив

int minI;
int maxI;

int repeat = 0;

float average = 0;

Clock::time_point timeStart;
Clock::time_point timeEnd;

void CreateArray(); // создаем массив
void SortingArray(); // сортируем массив
void FindMin(); // находим минимальные элементы массивов
void FindMax(); // находим максимальные элементы массивов
void AverageValue(); // среднее значение мин/мах
void FindIdenticalElements(); // поиск одинаковых элементов равных среднему значению мин/мах
void SmallerNumbers(); // кол-во чисел меньших числа А
void BiggerNumbers(); // кол-во чисел больших числа Б
void BinaryNumberSearch(); // бинарный поиск введенного числа в массиве
void ReplacementElements(); // замена двух элементов местами

void SortingShaker(); // для индивидуального задания

void CreateArray() {
	for (int i = 0; i < size(arrInt); i++) {
		arrInt[i] = rand() % 199 - 99;
		arrIntSort[i] = arrInt[i]; // копия массива
	}
}

void SortingArray() {
	int temp; // временная переменная для обмена элементов местами

	timeStart = Clock::now();
	for (int i = 0; i < size(arrIntSort) - 1; i++) { // Сортировка массива пузырьком
		for (int j = 0; j < size(arrIntSort) - i - 1; j++) {
			if (arrIntSort[j] > arrIntSort[j + 1]) {
				// меняем элементы местами
				temp = arrIntSort[j];
				arrIntSort[j] = arrIntSort[j + 1];
				arrIntSort[j + 1] = temp;
			}
		}
	}
	timeEnd = Clock::now();
	cout << sec(timeEnd - timeStart).count() << " время затраченное на сортировку массива. (Bubble sort)\n" << endl;

	for (int i = 0; i < size(arrIntSort); i++) {
		cout << arrIntSort[i] << " ";
	}
	cout << " отсортированный массив" << endl;

	cout << endl;
}

void FindMin() {

	minI = 100;

	timeStart = Clock::now();
	for (int i = 0; i < size(arrInt) - 1; i++) { // поиск минимального в неотсортированном массиве
		if (arrInt[i] < minI) {
			minI = arrInt[i];
		}
	}
	timeEnd = Clock::now();
	cout << "Минимальный элемент:" << minI << ".\nВремени на нахождение потребовалось в неотсортированном массиве: " << sec(timeEnd - timeStart).count() << " сек." << endl;

	minI = 100;
	timeStart = Clock::now();
	for (int i = 0; i < size(arrIntSort) - 1; i++) { // поиск минимального в отсортированном массиве
		if (arrIntSort[i] < minI) {
			minI = arrIntSort[i];
		}
	}
	timeEnd = Clock::now();
	cout << "Времени на нахождение потребовалось в отсортированном: " << sec(timeEnd - timeStart).count() << " сек." << endl;

	cout << endl;
}

void FindMax() {

	maxI = -100;

	timeStart = Clock::now();
	for (int i = 0; i < size(arrInt) - 1; i++) { // поиск максимального в неотсортированном массиве
		if (arrInt[i] > maxI) {
			maxI = arrInt[i];
		}
	}
	timeEnd = Clock::now();
	cout << "Минимальный элемент:" << maxI << ".\nВремени на нахождение потребовалось в неотсортированном массиве: " << sec(timeEnd - timeStart).count() << " сек." << endl;

	maxI = -100;
	timeStart = Clock::now();
	for (int i = 0; i < size(arrIntSort) - 1; i++) { // поиск максимального в отсортированном массиве
		if (arrIntSort[i] > maxI) {
			maxI = arrIntSort[i];
		}
	}
	timeEnd = Clock::now();
	cout << "Времени на нахождение потребовалось в отсортированном: " << sec(timeEnd - timeStart).count() << " сек." << endl;

	cout << endl;
}

void AverageValue() {
	average = (minI + maxI) / 2;
	cout << "Среднее значение минимального и максимального элемента массива: " << average << endl;
}

void FindIdenticalElements() {
	int countIdentidal = 0;

	cout << "Индексы элементов равных среднему MIN/MAX: ";
	for (int i = 0; i < size(arrIntSort) - 1; i++) {
		if (arrIntSort[i] == average) {
			cout << i << " ";
			countIdentidal++;
		}
	}
	cout << "\nКоличество элементов равных среднему MIN/MAX: " << countIdentidal << endl;

	cout << endl;
}

void SmallerNumbers() {
	int inputValue = 0;
	cout << "Введите число до которого будет подсчет меньших чисел: ";
	cin >> inputValue;

	int count = 0;

	for (int i = 0; i < size(arrIntSort) - 1; i++) {
		if (arrIntSort[i] < inputValue) {
			count++;
		}
	}
	cout << "Количество чисел меньших числа " << inputValue << ": " << count << endl;

	cout << endl;
}

void BiggerNumbers() {
	int inputValue = 0;
	cout << "Введите число до которого будет подсчет больших чисел: ";
	cin >> inputValue;

	int count = 0;

	for (int i = 0; i < size(arrIntSort); i++) {
		if (arrIntSort[i] > inputValue) {
			count++;
		}
	}
	cout << "Количество чисел меньших числа " << inputValue << ": " << count << endl;

	cout << endl;
}

void BinaryNumberSearch() {

	bool flag = false;
	int l = -99; // левая граница
	int r = 98; // правая граница
	int mid;
	int valueInput;

	cout << "Введите число которое нужно найти: ";
	cin >> valueInput; // считываем ключ

	timeStart = Clock::now();
	while ((l <= r) && (flag != true)) {
		mid = (l + r) / 2; // считываем срединный индекс отрезка

		if (arrIntSort[mid] == valueInput)
			flag = true; //проверяем ключ со серединным элементом
		if (arrIntSort[mid] > valueInput)
			r = mid - 1; // проверяем, какую часть нужно отбросить
		else
			l = mid + 1;
	}
	timeEnd = Clock::now();

	if (flag)
		cout << "Введенный элемент " << valueInput << " существует в данном массиве." << endl;
	else
		cout << "Введенного элемента в массиве нет" << endl;

	cout << endl;
	cout << sec(timeEnd - timeStart).count() << " время затраченное на бинарный поиск элемента." << endl;

	{
		timeStart = Clock::now();
		for (int i = 0; i < size(arrIntSort) - 1; i++) {
			if (arrIntSort[i] == valueInput) {
				maxI = arrIntSort[i];
				break;
			}
		}
		timeEnd = Clock::now();
		cout << sec(timeEnd - timeStart).count() << " время затраченное на обычный поиск элемента." << endl;
	}

	cout << endl;
}

void ReplacementElements() {

	int elemFirst;
	int elemSecond;

	cout << "Введите индексы элементов массива которые нужно поменять местами: " << endl;
	cin >> elemFirst >> elemSecond;
	cout << endl;

	timeStart = Clock::now();
	int elemTemp = arrIntSort[elemFirst];
	arrIntSort[elemFirst] = arrIntSort[elemSecond];
	arrIntSort[elemSecond] = elemTemp;
	timeEnd = Clock::now();

	cout << "Измененный массив:" << endl;
	for (int i = 0; i < size(arrIntSort); i++) {
		cout << arrIntSort[i] << " ";
	}

	cout << endl << sec(timeEnd - timeStart).count() << " времени потребовалось на замену элементов." << endl;

}

void SortingShaker() {
	for (int i = 0; i < size(arrInt); i++) {
		arrIntSort[i] = arrInt[i]; // копия массива
	}

	bool sort_or_not = true;

	timeStart = Clock::now();
	do {
		sort_or_not = true;
		for (int i = 0; i < size(arrIntSort); i++) {
			if (arrIntSort[i] > arrIntSort[i + 1]) {
				swap(arrIntSort[i], arrIntSort[i + 1]);
				sort_or_not = false;
			}
		}
		for (int i = 4; i >= 1; i--) {
			if (arrIntSort[i] < arrIntSort[i - 1]) {
				swap(arrIntSort[i], arrIntSort[i - 1]);
				sort_or_not = false;
			}
		}
	} while (sort_or_not == false);
	timeEnd = Clock::now();

	for (int i = 0; i < size(arrIntSort); i++) {
		cout << arrIntSort[i] << " ";
	}

	cout << endl << sec(timeEnd - timeStart).count() << " времени потребовалось на сортировку элементов. (Shaker Sort)" << endl;
}
//////////////ВТОРАЯ ЛАБОРАТОРНАЯ



////////// ТРЕТЬЯ ЛАБА
void Show(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			cout << arr[(i * size) + j] << ' ';

		cout << '\n';
	}
}

void SpiralFilling(int* arr, short int size) // спиральное заполнение
{
	int* parr = arr;
	CONSOLE_SCREEN_BUFFER_INFO info_y;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_y);
	int y_coord = info_y.dwCursorPosition.Y + 1;
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < size / 2; i++)
	{
		//Верхняя сторона
		for (int j = 0; j < (size - i * 2 - 1); j++)
		{
			*arr = rand() % (size * size) + 1;
			position.X = (j + i) * 4;
			position.Y = y_coord + i;
			SetConsoleCursorPosition(hConsole, position);
			cout << *arr;
			Sleep(50);
			arr++;
		}
		//Правая сторона
		for (int j = 0; j < (size - i * 2 - 1); j++)
		{
			*arr = rand() % (size * size) + 1;
			position.X = (size - i - 1) * 4;
			position.Y = y_coord + (i + j);
			SetConsoleCursorPosition(hConsole, position);
			cout << *arr;
			Sleep(50);
			arr += size;
		}
		//Нижняя сторона
		for (int j = (size - i * 2 - 1); j > 0; j--)
		{
			*arr = rand() % (size * size) + 1;
			position.X = (i + j) * 4;
			position.Y = y_coord + size - 1 - i;
			SetConsoleCursorPosition(hConsole, position);
			cout << *arr;
			Sleep(50);
			arr--;
		}
		//Левая сторона
		for (int j = (size - i * 2 - 1); j > 0; j--)
		{
			*arr = rand() % (size * size) + 1;
			position.X = i * 4;
			position.Y = y_coord + (j + i);
			SetConsoleCursorPosition(hConsole, position);
			cout << *arr;
			Sleep(50);
			arr -= size;
		}
		arr += size + 1;
	}

	position.X = 0;
	position.Y = y_coord + size;
	SetConsoleCursorPosition(hConsole, position);
}

void VerticalSwipe(int* arr, int size)
{
	int temp;
	int* parr = arr;
	for (int i = 0; i < (size / 2); i++)
	{
		for (int j = 0; j < (size / 2); j++) // левая половина матрицы
		{
			temp = *(parr + (i * size) + j);
			*(parr + (i * size) + j) = *(parr + ((i + size / 2) * size) + j);
			*(parr + ((i + size / 2) * size) + j) = temp;
		}
		for (int j = 0; j < (size / 2); j++) // правая половина
		{
			temp = *(parr + (i * size) + j + (size / 2));
			*(parr + (i * size) + j + (size / 2)) = *(parr + ((i + size / 2) * size) + j + (size / 2));
			*(parr + ((i + size / 2) * size) + j + (size / 2)) = temp;
		}
	}
}

void Sorting(int* arr, int size) //Сортировка пузырьком
{
	int temp;
	int* psort1 = arr;
	int* psort2 = arr + 1;

	for (int i = 0; i < (size * size - 1); i++)
	{
		for (int j = i + 1; j < (size * size); j++)
		{
			if (*psort1 > *psort2)
			{
				temp = *psort1;
				*psort1 = *psort2;
				*psort2 = temp;
			}
			psort2++;
		}
		psort1++;
		psort2 = psort1 + 1;
	}

	Show(arr, size);
}
////////// ТРЕТЬЯ ЛАБА

////////// ЧЕТВЕРТАЯ ЛАБА
void RemovingDuplicateCharacters(char *strs) {
	int point = 0;
	string str = string(strs);

	for (int i = 0; i < size(str); i++) { // удаление повторных символов
		point = 0;
		for (int j = 0; j < size(str); j++) {
			if (!isalpha((unsigned char)str[j])) {
				if (str[j] == str[j + 1]) {
					if (str[j] == '.') {
						point++;
						if (point >= 3)
							str.erase(j, 1);
					}
					else
						str.erase(j, 1);

				}
			}
		}
	}
	strcpy(strs, str.c_str());

	cout << str << endl << endl;
	setlocale(0, "RU");
}

void RegisterControll(char * str) {
	for (int i = 2; i < strlen(str); i++) // выравниваем регистр
	{
		str[0] = toupper(str[0]);

		if (str[i - 2] == '.' || str[i - 1] == '.' || str[i - 2] == '?' || str[i - 1] == '?') {
			str[i] = toupper(str[i]);
		}
		else {
			if (str[i - 1] != ' ')
				str[i] = tolower(str[i]);
			else
				str[i] = str[i];
		}
	}
	cout << str << endl << endl;
	setlocale(0, "RU");
}

void WordStartLetter(char pch[500]) {
	char *pchh = new char(500);
	pchh = strtok(pch, " ,.-");
	while (pchh != NULL) // пока есть лексемы
	{
		string str = string(pchh);
		for (int i = 1; i < size(str); i++) {
			if (str[0] == str[i])
				cout << pchh << "\n";
		}
		pchh = strtok(NULL, " ,.-)*");
	}
	cout << endl;
	setlocale(0, "RU");
}

void NumberRedact(char pch[500]) {
	char vC = ' ';
	char *pchh = new char(500);
	pchh = strtok(pch, " ");
	while (pchh != NULL) // пока есть лексемы
	{
		char varC = ' ';
		for (int i = 1; i < strlen(pchh) - 1; i++) {
			if (isdigit((unsigned char)pchh[i]))
				varC = pchh[i];
			if (pchh[i] == ' ' || pchh[i + 1] == '*' || pchh[i + 1] == ')' || pchh[i + 1] == ',')
				varC = ' ';

			if (varC != ' ') {
				vC = pchh[i + 1];
				pchh[i + 1] = pchh[i];
				pchh[i] = vC;
			}
		}

		cout << pchh << " ";
		pchh = strtok(NULL, " ");
	}
	cout << endl << endl;
	setlocale(0, "RU");
}

bool ReadFile(string FileName)
{
	char chS[400];
	char copyStr[500];
	char *pchS;

	ifstream File;
	File.open(FileName);

	if (!File.is_open())  //  Проверили удалось ли открыть файл
	{
		cout << "Открыть файл не удалось! \n";
		return 0;
	}

	while (!File.eof()) // Читаем все строки из файла и выводим их на экран
		File.getline(chS, 500);
	pchS = chS;
	cout << "Исходный текст:\n" << pchS << endl << endl;
	cout << "\n***************************\n";

	cout << "\n***В этой строке удалены все повторные символы***\n";
	RemovingDuplicateCharacters(pchS); // удаление повторных символов
	cout << "***************************\n";

	cout << "\n***В этой строке выравнен регистр букв***\n";
	RegisterControll(pchS); // выравниваем регистр
	cout << "***************************\n";

	cout << "\n***Слова, в которых есть буквы такие же как и первая буква слова***\n";
	strcpy(copyStr, pchS);
	WordStartLetter(copyStr); // выводим слова, в которых есть буквы такие же как и первая буква слова
	cout << "***************************\n";

	cout << "\n***В этой все буквы в словах передвинуты в конец слова***\n";
	NumberRedact(pchS); // перемещаем буквы в словах в конец слова
	cout << "***************************\n";

	File.close();  // Закрываем файл
	return 1;
}

void WriteText() {
	cin.get();

	char chS[500];
	char copyStr[500];
	char *pchS;

	cout << "Введите текст содержащий от 1 до 50 слов, в каждом из которых от 1 до 10 строчных латинских букв и цифр. Между соседними словами произвольное количество пробелов. За последним символом стоит точка.\nВвод: ";
	cin.getline(chS, 500);

	pchS = chS;
	cout << "\n***************************\n";

	cout << "\n***В этой строке удалены все повторные символы***\n";
	setlocale(0, ".866");
	RemovingDuplicateCharacters(pchS); // удаление повторных символов
	cout << "***************************\n";

	cout << "\n***В этой строке выравнен регистр букв***\n";
	setlocale(0, ".866");
	RegisterControll(pchS); // выравниваем регистр
	cout << "***************************\n";

	cout << "\n***Слова, в которых есть буквы такие же как и первая буква слова***\n";
	strcpy(copyStr, pchS);
	setlocale(0, ".866");
	WordStartLetter(copyStr); // выводим слова, в которых есть буквы такие же как и первая буква слова
	cout << "***************************\n";

	cout << "\n***В этой строке все буквы в словах передвинуты в конец слова***\n";
	setlocale(0, ".866");
	NumberRedact(pchS); // перемещаем буквы в словах в конец слова
	cout << "***************************\n";
}


int main()
{
	setlocale(0, "RU");
	int labaNumb = -1;

	cout << "Лаборатоные работы:\n";
	cout << "1 - ТИПЫ ДАННЫХ И ИХ ВНУТРЕННЕЕ ПРЕДСТАВЛЕНИЕ В ПАМЯТИ\n";
	cout << "2 - ОДНОМЕРНЫЕ СТАТИЧЕСКИЕ МАССИВЫ\n";
	cout << "3 - УКАЗАТЕЛИ\n";
	cout << "4 - ТЕКСТОВЫЕ СТРОКИ КАК МАССИВЫ СИМВОЛОВ\n\n";

	while (labaNumb != 0) {
		cout << "Введите номер лабораторной работы (1 - 4).\nВвод: ";
		cin >> labaNumb;
		if (labaNumb == 1)
		{//ПЕРВАЯ ЛАБОРАТОРНАЯ
			cout << "ТИПЫ ДАННЫХ И ИХ ВНУТРЕННЕЕ ПРЕДСТАВЛЕНИЕ В ПАМЯТИ\n";
			LabaOne();
		}
		if (labaNumb == 2)
		{//ВТОРАЯ ЛАБОРАТОРНАЯ
			setlocale(LC_ALL, "Russian");
			srand(time(NULL));

			cout << "ОДНОМЕРНЫЕ СТАТИЧЕСКИЕ МАССИВЫ\n\n";

			do {
				CreateArray();

				SortingArray();

				repeat = 0;
				cout << "Повторить? (0 - нет / 1 - да): ";
				cin >> repeat;
				cout << endl;
			} while (repeat == 1);

			do {
				FindMin();
				FindMax();

				repeat = 0;
				cout << "Повторить? (0 - нет / 1 - да): ";
				cin >> repeat;
				cout << endl;
			} while (repeat == 1);

			do {
				AverageValue();
				FindIdenticalElements();

				repeat = 0;
				cout << "Повторить? (0 - нет / 1 - да): ";
				cin >> repeat;
				cout << endl;
			} while (repeat == 1);

			do {
				SmallerNumbers();

				repeat = 0;
				cout << "Повторить? (0 - нет / 1 - да): ";
				cin >> repeat;
				cout << endl;
			} while (repeat == 1);

			do {
				BiggerNumbers();

				repeat = 0;
				cout << "Повторить? (0 - нет / 1 - да): ";
				cin >> repeat;
				cout << endl;
			} while (repeat == 1);

			do {
				BinaryNumberSearch();

				repeat = 0;
				cout << "Повторить? (0 - нет / 1 - да): ";
				cin >> repeat;
				cout << endl;
			} while (repeat == 1);

			do {
				ReplacementElements();

				repeat = 0;
				cout << "Повторить? (0 - нет / 1 - да): ";
				cin >> repeat;
				cout << endl;
			} while (repeat == 1);

			do {
				SortingShaker();

				repeat = 0;
				cout << "Повторить? (0 - нет / 1 - да): ";
				cin >> repeat;
				cout << endl;
			} while (repeat == 1);

			cout << "End.\n";
		}
		if (labaNumb == 3)
		{//ТРЕТЬЯ ЛАБОРАТОРНАЯ
			setlocale(LC_ALL, "rus");
			cout << "УКАЗАТЕЛИ\n";

			srand(time(NULL));

			int number = 5;
			int arr[100];
			int size = 0, numbOperation, actionNumber;

			cout << "1. Заполнить матрицу\n";
			cout << "2. Переставить блоки матрицы вертикально.\n";
			cout << "3. Отсортировать матрицу. (метод пузырьком)\n";
			cout << "4. Уменьшить, увеличить, умножить или поделить на введеное число.\n";
			cout << "0. Завершить.\n";

			cout << endl;

			while (number != 0)
			{
				cout << "Выбери пункт: ";
				cin >> number;
				cout << '\n';

				if (number == 1) { // создание матрицы
					cout << "Выберите число: 6, 8, 10: ";
					cin >> size;
					if ((size == 6) || (size == 8) || (size == 10))
						SpiralFilling(arr, size);
					else
						cout << "Вы ввели некорректное число\n";
				}

				if (number == 2) { // перемещение по вертикали
					VerticalSwipe(arr, size);
					Show(arr, size);
				}

				if (number == 3) { // сортировка
					Sorting(arr, size);
				}

				if (number == 4) {
					cout << "Выберите операцию: \n1 - уменьшить, 2 - увеличить, 3 - умножить, 4 - поделить:\nНомер: ";
					cin >> numbOperation;

					if (numbOperation == 1) {
						cout << "Введите число на которое нужно уменьшить: ";
						cin >> actionNumber;

						for (int i = 0; i < (size * size); i++)
							arr[i] -= actionNumber;

						Show(arr, size);
					}
					else if (numbOperation == 2) {
						cout << "Введите число на которое нужно прибавить: ";
						cin >> actionNumber;

						for (int i = 0; i < (size * size); i++)
							arr[i] += actionNumber;

						Show(arr, size);
					}
					else if (numbOperation == 3) {
						cout << "Введите число на которое нужно умножить: ";
						cin >> actionNumber;

						for (int i = 0; i < (size * size); i++)
							arr[i] *= actionNumber;

						Show(arr, size);
					}
					else if (numbOperation == 4) {
						cout << "Введите число на которое нужно разделить: ";
						cin >> actionNumber;

						for (int i = 0; i < (size * size); i++)
							arr[i] /= actionNumber;

						Show(arr, size);
					}
					else
						cout << "\nВведенного пункта операции не сущетсвует." << endl;
				}

				if (number > 4) {

					cout << "Выберите пункт из доступных." << endl;
				}

			}

			cout << "...\n" << endl;
		}
		if (labaNumb == 4)
		{//ЧЕТВЕРТАЯ ЛАБОРАТОРНАЯ
			setlocale(0, "RU");
			cout << "ТЕКСТОВЫЕ СТРОКИ КАК МАССИВЫ СИМВОЛОВ\n";

			int variant;
			cout << "Выберите способ работы со строкой:\n1 - Напечатать текст вручную\n2 - Вывести текст из файла\nВвод: ";
			cin >> variant;

			if (variant == 1) {
				WriteText();
			}
			else if (variant == 2) {
				string fileName;
				cout << "Введите название файла в формате (test.txt).\n";
				cin >> fileName;

				ReadFile(fileName);
			}
		}
	}
	labaNumb = 0;
}
