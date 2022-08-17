#include <stdio.h>
#include <TXLib.h>
#include <math.h>

double sqrtmy(float);
void SquareSolver(int, int, int);
void lineynoe(int, int);
void qwadratnoe(int, int, int);

int main(void)
{
    int a = 0, b = 0, c = 0;
    printf("��� ��������� ������ ���������� ��������� c ������ ������������� ����: a * x^2 + b * x + c\n");
    printf("������� ��� ����������� ����������� ��������� a, b, c ��� q ��� ���������� ���������:");
    while(scanf("%d%d%d", &a, &b, &c) == 3 )
    {
        SquareSolver(a, b, c);
    }
    return 0;
}

double sqrtmy(float x)
{
    float a = 1.0, b = x, c = (a + b) / 2;
    while(fabs(c * c - x) > 0.001)
    {
        if ((c * c - x) * (a * a - x) < 0)
            b = c;
        else
            a = c;
        c = (a + b) / 2;
    }
    return c;
}

void SquareSolver(int a, int b, int c)
{
    if (a == 0 && b != 0)
    {
        lineynoe(b, c);
    }
    else if (a != 0)
    {
        qwadratnoe(a, b, c);
    }
    else
    {
        printf("�� ����� ������������ ��������, ���������� ��� ���\n");
        printf("������� ��� ����������� ����������� ��������� a, b, c ��� q ��� ���������� ���������:");
    }
}

void lineynoe(int b, int c)
{
    printf("��������� ����� ���: %d * x + %d � �������� ��������\n", b, c);

    double x = ((-1.0) * c) / b;

    printf("�������� ����� ��������� �������: %.3f\n\n", x);

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
        double x1 = ((-1.0) * b + sqrtmy((float)D)) / (2 * a);
        double x2 = ((-1.0) * b - sqrtmy((float)D)) / (2 * a);
        printf(" � ��� ������ 0, ��� ��������� ����� ��� �������, ������: %.3f %.3f\n\n", x1, x2);
    }

    printf("������� ��� ����������� ����������� ��������� a, b, c ��� q ��� ���������� ���������:");
}
