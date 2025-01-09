#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;

const int m = 6, n = 7;

void view_file(char* name)
{
    setlocale(LC_ALL, ".1251");
    FILE* f;
    char s[100];
    if (fopen_s(&f, name, "rt") != 0 || f == 0) {
        cout << "Неможливо вiдкрити файл" << endl;
        return;
    }
    cout << "Перегляд файлу: " << name << endl;
    while (fgets(s, 100, f)) {
        s[strlen(s) - 1] = '\0';
        puts(s);
    }
    fclose(f);
}

void create_matrix(double matr[m][n], char* name)
{
    setlocale(LC_ALL, ".1251");
    FILE* f;
    char s[100], * t;
    int i = 0, j;
    if (fopen_s(&f, name, "rt") != 0 || f == 0) {
        cout << "Неможливо вiдкрити файл" << endl;
        return;
    }

    while (fgets(s, 100, f)) {
        j = 0;
        t = strtok(s, " \t");
        while (t != NULL && j < n) {
            matr[i][j] = atof(t);
            t = strtok(NULL, " \t");
            j++;
        }
        i++;
    }
    fclose(f);
}

void output_matrix(double matr[m][n], char* name2)
{
    setlocale(LC_ALL, ".1251");
    int i, j;
    FILE* f2;
    if (fopen_s(&f2, name2, "wt") != 0 || f2 == 0) {
        cout << "Неможливо вiдкрити файл" << endl;
        return;
    }
    printf("\n\nПерегляд файлу:\n");
    fprintf(f2, "Перегляд матрицi:\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            cout << fixed << setprecision(2) << matr[i][j] << "\t";
            fprintf(f2, "%7.2f\t", matr[i][j]);
        }
        cout << endl;
        fprintf(f2, "%s", "\n");
    }
    fclose(f2);
}

void minsum(double matr[m][n], char* name2)
{
    setlocale(LC_ALL, ".1251");
    FILE* f2;
    if (fopen_s(&f2, name2, "at") != 0 || f2 == 0) {
        cout << "Неможливо вiдкрити файл" << endl;
        return;
    }
    double min_sum = DBL_MAX;
    int num_diagonals = m + n - 1;
    int offset, row, col;
    for (int diag = 0; diag < num_diagonals; diag++) {
        double sum = 0.0;
        if (diag < n) {
            offset = diag;
            row = 0;
            col = n - 1 - offset;
        }
        else {
            offset = diag - n + 1;
            row = offset;
            col = 0;
        }
        while (row < m && col < n) {
            sum += fabs(matr[row][col]);
            row++;
            col++;
        }
        if (sum < min_sum)
            min_sum = sum;
    }
    cout << "\nМiнiмум серед сум модулiв елементiв дiагоналей = " << fixed << setprecision(2) << min_sum << endl;
    fprintf(f2, "\nМiнiмум серед сум модулiв елементiв дiагоналей = %7.2f", min_sum);
}

int main()
{
    double a[m][n] = { 0 };
    char name1[] = "Iashchuk.ex2.1.txt";
    char name2[] = "Iashchuk.ex2.2.txt";
    view_file(name1);
    create_matrix(a, name1);
    output_matrix(a, name2);
    minsum(a, name2);
    return 0;
}