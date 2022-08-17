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
    printf("Эта программа решает квадратные уравнения c целыми коэффицентами вида: a * x^2 + b * x + c\n");
    printf("Введите три коэффицента квадратного уравнения a, b, c или q для завершения программы:");
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
        printf("Вы ввели недопустимые значения, попробуйте еще раз\n");
        printf("Введите три коэффицента квадратного уравнения a, b, c или q для завершения программы:");
    }
}

void lineynoe(int b, int c)
{
    printf("Уравнение умеет вид: %d * x + %d и является линейным\n", b, c);

    double x = ((-1.0) * c) / b;

    printf("Решением этого уравнения яляется: %.3f\n\n", x);

    printf("Введите три коэффицента квадратного уравнения a, b, c или q для завершения программы:");
}

void qwadratnoe(int a, int b, int c)
{
    printf("Уравнение умеет вид: %d * x^2 + %d * x + %d и является квадратным\n", a, b, c);

    int D = b * b - 4 * a * c; //значение дискриминанта

    printf("Т.к. значение дискриминанта равно %d", D);
    if (D < 0) //решений нет
    {
        printf(" и оно меньше 0, это уравнение не имеет решений\n\n");
    }
    else if (D == 0) //одно решение
    {
        double x0 = ((-1.0) * b) / (2 * a);
        printf(", это уравнение имеет одно решение, равное: %.3f\n\n", x0);
    }
    else //два решения
    {
        double x1 = ((-1.0) * b + sqrtmy((float)D)) / (2 * a);
        double x2 = ((-1.0) * b - sqrtmy((float)D)) / (2 * a);
        printf(" и оно больше 0, это уравнение имеет два решения, равных: %.3f %.3f\n\n", x1, x2);
    }

    printf("Введите три коэффицента квадратного уравнения a, b, c или q для завершения программы:");
}
