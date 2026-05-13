#include <iostream>
#include <random>
#include <vector>
using namespace std;
// Объявление генератора псевдослучайных чисел для дальнейшего использования в программе
mt19937 gen(random_device{}());

void part1(int M, int N)
{
    uniform_int_distribution nums(-50,50);
    // Инициализация и заполнение массива случайными числами от -50 до 50
    int arrayForPart1[M][N];
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            arrayForPart1[i][j] = nums(gen);
        }
    }
    cout << "Инициализированный массив:\n";
    //Вывод массива
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << arrayForPart1[i][j] << " ";
        }
        cout << endl;
    }
    // Дальше ищем самую длинную последовательность 
    int lenthOfBestLine = 1;
    int bestStart = 0;
    int bestRow = 0;
    for (int i = 0; i < M; i++)
    {
        int lenthOfCurrentLine = 1;
        int currentStart = 0;
        for (int j = 0; j < N - 1; j++)
        {
            if (arrayForPart1[i][j] < arrayForPart1[i][j+1])
            {
                lenthOfCurrentLine++;
                // Ключевой момент поиска: сравниваем длину текущей последовательности и лучшей
                if (lenthOfCurrentLine > lenthOfBestLine)
                {
                    lenthOfBestLine = lenthOfCurrentLine;
                    bestRow = i;
                    bestStart = currentStart;
                }
            }
            else
            {
                lenthOfCurrentLine = 1;
                currentStart = j + 1;
            }
            
        }
    }
    // Инициализируем динамический массив для найденной последовательности и заполняем его
    int* dynamicArrWithLine = new int[lenthOfBestLine];
    for (int i = 0; i < lenthOfBestLine; i++)
    {
        dynamicArrWithLine[i] = arrayForPart1[bestRow][bestStart + i];
    }
    cout << "Лучшая последовательность: ";
    for (int i = 0; i < lenthOfBestLine; i++)
    {
        cout << dynamicArrWithLine[i] << " ";
    }
    delete[] dynamicArrWithLine; // Освобождаем память после вывода динамического массива
    cout << "\nСтрока: " << bestRow + 1 << endl;
    cout << "Длина: " << lenthOfBestLine << endl;
}

vector<int> quickSort(vector<int> nums, bool flag)
{
    // Базовый случай рекурсии
    if (nums.size() <= 1)
    {
        return nums;
    }

    // Опорный элемент (pivot)
    int pivot = nums[nums.size() / 2];

    // Временные массивы
    vector<int> less;
    vector<int> equal;
    vector<int> greater;

    // Разделение элементов
    for (size_t i = 0; i < nums.size(); i++)
    {
        // Сортировка по возрастанию
        if (flag)
        {
            if (nums[i] < pivot)
            {
                less.push_back(nums[i]);
            }
            else if (nums[i] == pivot)
            {
                equal.push_back(nums[i]);
            }
            else
            {
                greater.push_back(nums[i]);
            }
        }

        // Сортировка по убыванию
        else
        {
            if (nums[i] > pivot)
            {
                less.push_back(nums[i]);
            }
            else if (nums[i] == pivot)
            {
                equal.push_back(nums[i]);
            }
            else
            {
                greater.push_back(nums[i]);
            }
        }
    }

    // Рекурсивная сортировка
    less = quickSort(less, flag);
    greater = quickSort(greater, flag);

    // Итоговый массив
    vector<int> sortedArray;

    sortedArray.insert(sortedArray.end(), less.begin(), less.end());
    sortedArray.insert(sortedArray.end(), equal.begin(), equal.end());
    sortedArray.insert(sortedArray.end(), greater.begin(), greater.end());

    return sortedArray;
}

void part2(int M)
{
    uniform_int_distribution nums(100, 200);
    // Инициализация и заполнение массива случайными числами в диапазоне от 100 до 200
    int squareArrayForPart2[M][M];
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < M; j++)
        {
            squareArrayForPart2[i][j] = nums(gen);
        }
    }
    cout << "Сгенерированный массив:\n";
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cout << squareArrayForPart2[i][j] << " ";
        }
        cout << endl;
    }
    int summColumns = 0;
    int countColumns = 0;
    // Считаем сумму элементов чётных столбцов
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if ((j + 1) % 2 == 0)
            {
                summColumns += squareArrayForPart2[i][j];
                countColumns++;
            }
        }
    }
    // Считаем среднее значение всех нечётных строк
    int averageColumns = summColumns / countColumns;
    int summLines = 0;
    int countLines = 0;
    for (int i = 0; i < M; i++)
    {
        if (i % 2 != 0)
        {
            for (int j = 0; j < M; j++)
            {
                summLines += squareArrayForPart2[i][j];
                countLines++;
            }
        }
    }
    int averageLines = summLines / countLines;
    cout << "Среднее значение всех элементов чётных столбцов: " << averageColumns << endl;
    cout << "Среднее значение всех элементов нечётных строк: " << averageLines << endl;
    // Инициализируем вектор для хранения диагонали и заполняем его
    vector<int> diagonal;
    for (int i = 0; i < M; i++)
    {
        diagonal.push_back(squareArrayForPart2[i][i]);
    }
    // Флаг для контроля сортировки
    bool flag = true;
    if (averageColumns > averageLines)
    {
        flag = false;
    }
    else
    {
        flag = true;
    }
    // Сортируем диагональ
    vector<int> sortedDiagonal = quickSort(diagonal, flag);
    // Возвращаем диагональ на место
    for (int i = 0; i < M; i++)
    {
        squareArrayForPart2[i][i] = sortedDiagonal[i];
    }
    cout << "Массив после сортировки:\n";
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cout << squareArrayForPart2[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    cout << "Введите количество строк M: ";
    int M;
    cin >> M;
    cout << "Введите количество столбцов N: ";
    int N;
    cin >> N;
    return 0;
}
