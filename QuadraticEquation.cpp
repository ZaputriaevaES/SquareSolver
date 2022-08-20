#include <stdio.h>
#include <TXLib.h>
#include <math.h>

void InputAndOutputFormat(void); // ��������� ������� �����/������
void EnteringCoefficients(int input, int output); // ��������� ������������ ���������
void DerivationOfDecisions(int a, int b , int c, int outputformat); // ����� ������� � ������ �������
void SquareSolver(int a, int b, int c, double  * solutions); // ��������� ���� ���������
void linearEquation(int b, int c, double  * solutions); // ������� ��������� ���������
void QuadraticEquation(int a, int b , int c, double  * solutions); // ������� ����������� ���������

int main(void)
{
    InputAndOutputFormat();
    return 0;
}

void InputAndOutputFormat(void)
{
    int input = 1, output = 1, ch;
    printf("������������, ��� ��������� ������ ���������� ��������� ����: a * x^2 + b * x + c = 0.\n\n"
    "���� �� ������ ������� ������ � ����������, �� ������� 1, ���� ��������� �� �����, �� 2: ");
    while (scanf("%d", &input) != 1)
    {
        while ((ch = getchar()) != '\n')
            putchar(ch);
        printf(" �� �������� ���������� ���������. ����� ������������, � ������� 1 ��� 2: ");
    }
    printf("�������!\n"
           "���� �� ������ �������� ������ �� �����, �� ������� 1, ���� ���������� � ����, �� 2: ");
    while (scanf("%d", &output) != 1)
    {
        while ((ch = getchar()) != '\n')
            putchar(ch);
        printf(" �� �������� ���������� ���������. ����� ������������, � ������� 1 ��� 2: ");
    }
    EnteringCoefficients(input, output);
}

void EnteringCoefficients(int input, int output)
{
    int a = 0, b = 0, c = 0;
    if(input == 1)
    {
        if(output == 1) //���� � ����������, ����� �� �����
        {
            printf("\n�� �������� ������� ������ � ���������� � �������� ������ �� ������.\n\n");
            printf("������� ��� ����������� ����������� ��������� a, b, c ��� q ��� ���������� ���������:");
        }
        else //���� � ����������, ����� � ����
        {
            printf("\n�� �������� ������� ������ � ���������� � �������� ������ � ���� write.txt, ������� ��������� �������������.\n\n");
            printf("������� ��� ����������� ����������� ��������� a, b, c ��� q ��� ���������� ���������:");
        }
        while(scanf("%d%d%d", &a, &b, &c) == 3)
        {
            DerivationOfDecisions(a, b, c, output);
            printf("������� ��� ����������� ����������� ��������� a, b, c ��� q ��� ���������� ���������:");
        }
    }
    else
    {
        FILE * read;
        read = fopen("read.txt", "r");
        if (read != NULL)
        {
            printf("\n������ ���� ������� ������!\n");
            if(output == 1) //���� �� �����, ����� �� �����
            {
                printf("��������� ����� ��������� ������ �� ����� read.txt � �������� ������ �� �����.\n\n");
            }
            else //���� �� �����, ����� � ����
            {
                printf("��������� ����� ��������� ������ �� ����� read.txt � ���������� ������ � ���� write.txt,\n"
                       "������� ��������� �������������.\n");
            }
            while(fscanf(read, "%d%d%d", &a, &b, &c) == 3)
            {
                DerivationOfDecisions(a, b, c, output);
            }
        }
        else
        {
            printf("\n������!!! ���� read.txt �� ��� ������.\n");
            exit(1);
        }
    }
}

void DerivationOfDecisions(int a, int b , int c, int outputformat)
{
    double solutions[4] = {0};
    SquareSolver(a, b, c, solutions);
    if (outputformat == 1.0) // ����� �� �����
    {
        if(solutions[0] == 1.0) // ��������
        {
            if(solutions[1] == -1.0)
            {
                printf("��������� ����: 0 * x^2 + 0 * x = 0 ����� ����������� ���������� �������.\n\n");
            }
            else if(solutions[1] == -2.0)
            {
                printf("��������� ����: %d = 0 �� ����� ������.\n\n", c);
            }
            else if(solutions[1] == 1.0 && solutions[2] == 0.0)
            {
                printf("��������� ����: %d * x = 0 ����� ������������ ������� ������ 0.\n\n", b);
            }
            else
            {
                printf("��������� ����� ���: %d * x + %d = 0 � �������� ��������.\n"
                       "�������� ����� ��������� �������: %.3f.\n\n", b, c, solutions[2]);
            }
        }
        else // ����������
        {
            if(solutions[1] == 1.0 && solutions[2] == 0.0)
            {
                printf("��������� ����: %d * x^2 = 0 ����� ������������ ������� ������ 0.\n\n", a);
            }
            else if(solutions[1] == 2.0 && solutions[2] == 0.0)
            {
                printf("��������� ����� ���: %d * x^2 + %d * x = 0\n"
                    "� ��� ��������� ��������: 0, %.3f.\n\n", a, b, solutions[3]);
            }
            else
            {
                printf("��������� ����� ���: %d * x^2 + %d * x + %d = 0 � �������� ����������.\n", a, b, c);
                if (solutions[1] == 0.0)
                {
                    printf("�.�. �������� ������������� ������ 0,\n"
                           "��� ��������� �� ����� �������.\n\n");
                }
                else if (solutions[1] == 1.0) //���� �������
                {
                    printf("�.�. �������� ������������� ����� 0,\n"
                           "��� ��������� ����� ���� �������, ������: %.3f.\n\n", solutions[2]);
                }
                else
                {
                    printf("�.�. �������� ������������� ������ 0,\n"
                           "��� ��������� ����� ��� �������, ������: %.3f, %.3f.\n\n", solutions[2], solutions[3]);
                }
            }
        }
    }
    else // ����� � ����
    {
        FILE * write;
        write = fopen("write.txt", "a");
        if(solutions[1] == -1.0 || solutions[1] == -2.0 || solutions[1] == 0.0)
        {
            fprintf(write, "%.g\n", solutions[1]);
        }
        else if(solutions[1] == 1.0)
        {
             fprintf(write, "1 : %.3g\n", solutions[2]);
        }
        else
        {
             fprintf(write, "2 : %.3g %.3g\n", solutions[2], solutions[3]);
        }
    }
}

void SquareSolver(int a, int b, int c, double  * solutions)
{
    if (a == 0)
    {
        solutions[0] = 1.0; // �������� ��������
        linearEquation(b, c, solutions);
    }

    else // a != 0
    {
        solutions[0] = 2.0; // �������� ����������
        QuadraticEquation(a, b, c, solutions);
    }
}

void linearEquation(int b, int c, double  * solutions)
{
    if (b == 0)
    {
        if (c == 0)
        {
            solutions[1] = -1.0; // ����������� ���������� �������
        }
        else // c != 0
        {
            solutions[1] = -2.0; // �� ����� ������
        }
    }
    else // b != 0
    {
        if (c == 0)
        {
            solutions[1] = 1.0;
            solutions[2] = 0.0;
        }
        else // c != 0
        {
            solutions[1] = 1.0;
            solutions[2] = (-1.0 * c) / b;
        }
    }
}

void QuadraticEquation(int a, int b, int c, double  * solutions)
{
    if (c == 0)
    {
        if (b == 0)
        {
            solutions[1] = 1.0;
            solutions[2] = 0.0;
        }
        else // b != 0
        {
            solutions[1] = 2.0;
            solutions[2] = 0.0;
            solutions[3] = (-1.0 * b) / a;
        }
    }
    else // c != 0
    {
        int D = b * b - 4 * a * c; //�������� �������������
        if (D < 0) //������� ���
        {
            solutions[1] = 0.0;
        }
        else if (D == 0) //���� �������
        {
            solutions[1] = 1.0;
            solutions[2] = ((-1.0) * b) / (2 * a);
        }
        else //��� �������
        {
            double d = sqrt((double)D);
            solutions[1] = 2.0;
            solutions[2] = ((-1.0) * b + d) / (2 * a);
            solutions[3] = ((-1.0) * b - d) / (2 * a);
        }
    }
}




