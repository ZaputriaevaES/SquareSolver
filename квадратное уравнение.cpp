#include <iostream>
#include <TXLib.h>
#include <math.h>

void SquareSolver(int, int, int);
void lineynoe(int, int);
void qwadratnoe(int, int, int);

int main(void)
{
    int a = 0, b = 0, c = 0;
    printf("��� ��������� ������ ���������� ��������� c ������ ������������� ����: a * x^2 + b * x + c\n");
    printf("������� ��� ����������� ����������� ��������� a, b, c ��� q ��� ���������� ���������:");
    while(scanf("%d%d%d", &a, &b, &c) == 3)
    {
        SquareSolver(a, b, c);
    }
    return 0;
}

void SquareSolver(int a, int b, int c)
{
    if (a == 0)
    {
        lineynoe(b, c);
    }
    else
    {
        qwadratnoe(a, b, c);
    }
}

void lineynoe(int b, int c)
{
    printf("��������� ����� ���: %d * x + %d � �������� ��������\n", b, c);

    double x = ((-1.0) * c) / b;

    printf("�������� ����� ��������� �������: %f\n\n", x);

    printf("������� ��� ����������� ����������� ��������� a, b, c ��� q ��� ���������� ���������:");
}

void qwadratnoe(int a, int b, int c)
{
    printf("��������� ����� ���: %d * x^2 + %d * x + %d � �������� ����������\n", a, b, c);

    int D = b * b - 4 * a * c; //�������� �������������

    printf("�.�. �������� ������������� ����� %d", D);
    if (D < 0) //������� ���
    {
        printf(" � ��� ������ 0, ��� ��������� �� ����� �������\n\n");
    }
    else if (D == 0) //���� �������
    {
        double x0 = ((-1.0) * b) / (2 * a);
        printf(", ��� ��������� ����� ���� �������, ������: %.3f\n\n", x0);
    }
    else //��� �������
    {
        double x1 = ((-1.0) * b + sqrt(D)) / (2 * a);
        double x2 = ((-1.0) * b - sqrt(D)) / (2 * a);
        printf(" � ��� ������ 0, ��� ��������� ����� ��� �������, ������: %.3f %.3f\n\n", x1, x2);
    }

    printf("������� ��� ����������� ����������� ��������� a, b, c ��� q ��� ���������� ���������:");
}

