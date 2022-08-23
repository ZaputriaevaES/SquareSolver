#include <stdio.h>
#include <TXLib.h>
#include <math.h>

enum NumberOfSolutions {ZERO = 0, ONE = 1, TWO = 2, INF = -1, MEANINGLESS = -2};
enum EquationType {LINEAR = 1, QUADRATIC = 2};

struct solutions {int type;
                  int amount;
                  double answer1;
                  double answer2;};

void InputAndOutputFormat(void); // ��������� ������� �����/������
void InputCleaning(void); // ������� �����
void EnteringCoefficients(int input, int output); // ��������� ������������ ���������
void DerivationOfDecisions(int a, int b , int c, int outputformat); // ����� ������� � ������ �������
void SquareSolver(int a, int b, int c, struct solutions *); // ��������� ���� ���������
void linearEquation(int b, int c, struct solutions *); // ������� ��������� ���������
void QuadraticEquation(int a, int b , int c, struct solutions *); // ������� ����������� ���������

int main(void)
{
    InputAndOutputFormat();
    return 0;
}

void InputAndOutputFormat(void)
{
    int input = 1, output = 1;
    printf("������������, ��� ��������� ������ ���������� ��������� ����: a * x^2 + b * x + c = 0.\n\n"
    "���� �� ������ ������� ������ � ����������, �� ������� 1, ���� ��������� �� �����, �� 2: ");
    while (scanf("%d", &input) != 1)
    {
        InputCleaning();
        printf(" �� �������� ���������� ���������. ����� ������������, � ������� 1 ��� 2: ");
    }
    printf("�������!\n"
           "���� �� ������ �������� ������ �� �����, �� ������� 1, ���� ���������� � ����, �� 2: ");
    while (scanf("%d", &output) != 1)
    {
        InputCleaning();
        printf(" �� �������� ���������� ���������. ����� ������������, � ������� 1 ��� 2: ");
    }
    EnteringCoefficients(input, output);
}

void InputCleaning(void)
{
    int ch;
    while ((ch = getchar()) != '\n')
        putchar(ch);
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
    struct solutions answers = {0, 0, 0, 0};
    SquareSolver(a, b, c, &answers);
    if (outputformat == 1) // ����� �� �����
    {
        if(answers.type == LINEAR) // ��������
        {
            if(answers.amount == INF)
            {
                printf("��������� ����: 0 * x^2 + 0 * x = 0 ����� ����������� ���������� �������.\n\n");
            }
            else if(answers.amount == MEANINGLESS)
            {
                printf("��������� ����: %d = 0 �� ����� ������.\n\n", c);
            }
            else if(answers.amount == ONE && answers.answer1 == 0.0)
            {
                printf("��������� ����: %d * x = 0 ����� ������������ ������� ������ 0.\n\n", b);
            }
            else
            {
                printf("��������� ����� ���: %d * x + %d = 0 � �������� ��������.\n"
                       "�������� ����� ��������� �������: %.3f.\n\n", b, c, answers.answer1);
            }
        }
        else // ����������
        {
            if(answers.amount == ONE && answers.answer1 == 0.0)
            {
                printf("��������� ����: %d * x^2 = 0 ����� ������������ ������� ������ 0.\n\n", a);
            }
            else if(answers.amount == TWO && answers.answer1 == 0.0)
            {
                printf("��������� ����� ���: %d * x^2 + %d * x = 0\n"
                    "� ��� ��������� ��������: 0, %.3f.\n\n", a, b, answers.answer2);
            }
            else
            {
                printf("��������� ����� ���: %d * x^2 + %d * x + %d = 0 � �������� ����������.\n", a, b, c);
                if (answers.amount == ZERO)
                {
                    printf("�.�. �������� ������������� ������ 0,\n"
                           "��� ��������� �� ����� �������.\n\n");
                }
                else if (answers.amount == ONE) //���� �������
                {
                    printf("�.�. �������� ������������� ����� 0,\n"
                           "��� ��������� ����� ���� �������, ������: %.3f.\n\n", answers.answer1);
                }
                else
                {
                    printf("�.�. �������� ������������� ������ 0,\n"
                           "��� ��������� ����� ��� �������, ������: %.3f, %.3f.\n\n",
                           answers.answer1, answers.answer2);
                }
            }
        }
    }
    else // ����� � ����
    {
        FILE * write;
        write = fopen("write.txt", "a");
        if(answers.amount == INF || answers.amount == MEANINGLESS || answers.amount == ZERO)
        {
            fprintf(write, "%d\n", answers.amount);
        }
        else if(answers.amount == ONE)
        {
             fprintf(write, "1 : %.3g\n", answers.answer1);
        }
        else
        {
             fprintf(write, "2 : %.3g %.3g\n", answers.answer1, answers.answer2);
        }
    }
}

void SquareSolver(int a, int b, int c, struct solutions * answers)
{
    if (a == 0)
    {
        answers->type = LINEAR; // �������� ��������
        linearEquation(b, c, answers);
    }

    else // a != 0
    {
        answers->type = QUADRATIC; // �������� ����������
        QuadraticEquation(a, b, c, answers);
    }
}

void linearEquation(int b, int c, struct solutions * answers)
{
    if (b == 0)
    {
        if (c == 0)
        {
            answers->amount = INF; // ����������� ���������� �������
        }
        else // c != 0
        {
            answers->amount = MEANINGLESS; // �� ����� ������
        }
    }
    else // b != 0
    {
        if (c == 0)
        {
            answers->amount = ONE;
            answers->answer1 = 0.0;
        }
        else // c != 0
        {
            answers->amount = ONE;
            answers->answer1 = (-1.0 * c) / b;
        }
    }
}

void QuadraticEquation(int a, int b, int c, struct solutions * answers)
{
    if (c == 0)
    {
        if (b == 0)
        {
            answers->amount = ONE;
            answers->answer1= 0.0;
        }
        else // b != 0
        {
            answers->amount = TWO;
            answers->answer1 = 0.0;
            answers->answer2 = (-1.0 * b) / a;
        }
    }
    else // c != 0
    {
        int D = b * b - 4 * a * c; //�������� �������������
        if (D < 0) //������� ���
        {
            answers->amount = ZERO;
        }
        else if (D == 0) //���� �������
        {
            answers->amount = ONE;
            answers->answer1 = ((-1.0) * b) / (2 * a);
        }
        else //��� �������
        {
            double d = sqrt((double)D);
            answers->amount = TWO;
            answers->answer1 = ((-1.0) * b + d) / (2 * a);
            answers->answer2 = ((-1.0) * b - d) / (2 * a);
        }
    }
}
