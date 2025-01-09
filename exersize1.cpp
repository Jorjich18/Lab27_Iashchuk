#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;

const int m = 5, n = 4;

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
            cout << fixed << setprecision(0) << matr[i][j] << "\t";
            fprintf(f2, "%7.2f\t", matr[i][j]);
        }
        cout << endl;
        fprintf(f2, "%s", "\n");
    }
    fclose(f2);
}

void greater_than_average(double matr[m][n], char* name2)
{
    setlocale(LC_ALL, ".1251");
    FILE* f2;
    if (fopen_s(&f2, name2, "at") != 0 || f2 == 0) {
        cout << "Неможливо вiдкрити файл" << endl;
        return;
    }
    double sum = 0.0, avg = 0.0;
    int count = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            sum += matr[i][j];
    avg = sum / (m * n);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (matr[i][j] > avg) count++;
    cout << "\nСереднє значення елементiв матрицi = " << fixed << setprecision(2) << avg << endl;
    cout << "\nКiлькiсть елементiв бiльше за середнє = " << count << endl;
    fprintf(f2, "\nСереднє значення елементiв матрицi = ", avg);
    fprintf(f2, "\nКiлькiсть елементiв бiльше за середнє = ", avg);
}

int main()
{
    double a[m][n] = { 0 };
    char name1[] = "Iashchuk.ex1.1.txt";
    char name2[] = "Iashchuk.ex1.2.txt";
    view_file(name1);
    create_matrix(a, name1);
    output_matrix(a, name2);
    greater_than_average(a, name2);
    return 0;
}
