#include <iostream>
#include <cmath>
#include <iomanip>

#define EPS 1e-3
using namespace std;

void LU(double A[4][4], double L[4][4], double U[4][4]);
void solveLU(double L[4][4], double U[4][4], double b[4]);
void seidel(double A[4][4], double b[4]);

int main()
{
    double A[4][4] =
    {
        {-1.13, -0.04,  0.21, -1.16},
        { 0.25, -1.23,  0.14, -0.09},
        {-0.21,  0.14,  0.80, -0.13},
        { 0.15, -1.31,  0.06,  0.87}
    };

    double b[4] = {-1.24, 0.87, 2.56, -1.13};

    double L[4][4];
    double U[4][4];

    LU(A, L, U);

    cout << fixed << setprecision(6);

    cout << "Матрица L:\n";
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << setw(12) << L[i][j];
        }
        cout << endl;
    }

    cout << "\nМатрица U:\n";
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << setw(12) << U[i][j];
        }
        cout << endl;
    }

    solveLU(L, U, b);

    seidel(A, b);

    return 0;
}

void LU(double A[4][4], double L[4][4], double U[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            L[i][j] = 0;
            U[i][j] = 0;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int k = i; k < 4; k++)
        {
            double sum = 0;
            for (int j = 0; j < i; j++)
            {
                sum += L[i][j] * U[j][k];
            }
            U[i][k] = A[i][k] - sum;
        }

        for (int k = i; k < 4; k++)
        {
            if (i == k)
            {
                L[i][i] = 1;
            }
            else
            {
                double sum = 0;
                for (int j = 0; j < i; j++)
                {
                    sum += L[k][j] * U[j][i];
                }
                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }
    }
}

void solveLU(double L[4][4], double U[4][4], double b[4])
{
    double y[4];
    double x[4];

    for (int i = 0; i < 4; i++)
    {
        double sum = 0;
        for (int j = 0; j < i; j++)
        {
            sum += L[i][j] * y[j];
        }
        y[i] = b[i] - sum;
    }

    for (int i = 3; i >= 0; i--)
    {
        double sum = 0;
        for (int j = i + 1; j < 4; j++)
        {
            sum += U[i][j] * x[j];
        }
        x[i] = (y[i] - sum) / U[i][i];
    }

    cout << "\nРешение методом LU:\n";
    for (int i = 0; i < 4; i++)
    {
        cout << "x" << i+1 << " = " << setw(10) << x[i] << endl;
    }
}

void seidel(double A[4][4], double b[4])
{
    double x[4] = {0,0,0,0};
    double oldX[4];

    int iteration = 0;

    cout << "\nМетод Зейделя:\n";
    cout << setw(5)  << "N" << setw(12) << "x1" << setw(12) << "x2" << setw(12) << "x3"
         << setw(12) << "x4" << setw(12) << "eps" << endl;

    while(true)
    {
        for (int i = 0; i < 4; i++)
        {
            oldX[i] = x[i];
        }

        for (int i = 0; i < 4; i++)
        {
            double sum = b[i];

            for (int j = 0; j < 4; j++)
            {
                if (i != j)
                {
                    sum -= A[i][j] * x[j];
                }
            }

            x[i] = sum / A[i][i];
        }

        double maxDiff = 0;
        for (int i = 0; i < 4; i++)
        {
            double diff = fabs(x[i] - oldX[i]);
            if (diff > maxDiff)
            {
                maxDiff = diff;
            }
        }

        iteration++;

        cout << setw(5)  << iteration << setw(12) << x[0] << setw(12) << x[1] << setw(12) << x[2]
             << setw(12) << x[3] << setw(12) << maxDiff << endl;

        if (maxDiff < EPS)
        {
            break;
        }

        if (iteration > 1000)
        {
            cout << "Метод не сошелся.\n";
            break;
        }
    }
}