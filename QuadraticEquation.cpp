#include <stdio.h>
#include <TXLib.h>
#include <math.h>

enum NumberOfSolutions {ZERO = 0, ONE = 1, TWO = 2, INF = -1, MEANINGLESS = -2};
enum EquationType {LINEAR = 1, QUADRATIC = 2};

struct solutions {int type;
                  int amount;
                  double answer1;
                  double answer2;};

void InputAndOutputFormat(void); // выяснение формата ввода/вывода
void InputCleaning(void); // очистка ввода
void EnteringCoefficients(int input, int output); // получение коэффицентов уравнения
void DerivationOfDecisions(int a, int b , int c, int outputformat); // вывод решений в нужном формате
void SquareSolver(int a, int b, int c, struct solutions *); // выяснение типа уравнения
void linearEquation(int b, int c, struct solutions *); // решение линейного уравнения
void QuadraticEquation(int a, int b , int c, struct solutions *); // решение квадратного уравнения

int main(void)
{
    InputAndOutputFormat();
    return 0;
}

void InputAndOutputFormat(void)
{
    int input = 1, output = 1;
    printf("Здравствуйте, эта программа решает квадратное уравнение вида: a * x^2 + b * x + c = 0.\n\n"
    "Если вы хотите вводить данные с клавиатуры, то введите 1, если считывать из файла, то 2: ");
    while (scanf("%d", &input) != 1)
    {
        InputCleaning();
        printf(" не является допустимым значением. Будте внимательнее, и введите 1 или 2: ");
    }
    printf("Отлично!\n"
           "Если вы хотите выводить данные на экран, то введите 1, если записывать в файл, то 2: ");
    while (scanf("%d", &output) != 1)
    {
        InputCleaning();
        printf(" не является допустимым значением. Будте внимательнее, и введите 1 или 2: ");
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
        if(output == 1) //ввод с клавиатуры, вывод на экран
        {
            printf("\nВы будетете вводить данные с клавиатуры и получать ответы на экране.\n\n");
            printf("Введите три коэффицента квадратного уравнения a, b, c или q для завершения программы:");
        }
        else //ввод с клавиатуры, вывод в файл
        {
            printf("\nВы будетете вводить данные с клавиатуры и получать ответы в файл write.txt, который создастся автоматически.\n\n");
            printf("Введите три коэффицента квадратного уравнения a, b, c или q для завершения программы:");
        }
        while(scanf("%d%d%d", &a, &b, &c) == 3)
        {
            DerivationOfDecisions(a, b, c, output);
            printf("Введите три коэффицента квадратного уравнения a, b, c или q для завершения программы:");
        }
    }
    else
    {
        FILE * read;
        read = fopen("read.txt", "r");
        if (read != NULL)
        {
            printf("\nНужный файл успешно найден!\n");
            if(output == 1) //ввод из файла, вывод на экран
            {
                printf("Программа будет считывать данные из файла read.txt и выводить ответы на экран.\n\n");
            }
            else //ввод из файла, вывод в файл
            {
                printf("Программа будет считывать данные из файла read.txt и записывать ответы в файл write.txt,\n"
                       "который создастся автоматически.\n");
            }
            while(fscanf(read, "%d%d%d", &a, &b, &c) == 3)
            {
                DerivationOfDecisions(a, b, c, output);
            }
        }
        else
        {
            printf("\nОШИБКА!!! Файл read.txt не был найден.\n");
            exit(1);
        }
    }
}

void DerivationOfDecisions(int a, int b , int c, int outputformat)
{
    struct solutions answers = {0, 0, 0, 0};
    SquareSolver(a, b, c, &answers);
    if (outputformat == 1) // вывод на экран
    {
        if(answers.type == LINEAR) // линейное
        {
            if(answers.amount == INF)
            {
                printf("Уравнение вида: 0 * x^2 + 0 * x = 0 имеет бесконечное количество решений.\n\n");
            }
            else if(answers.amount == MEANINGLESS)
            {
                printf("Уравнение вида: %d = 0 не имеет смысла.\n\n", c);
            }
            else if(answers.amount == ONE && answers.answer1 == 0.0)
            {
                printf("Уравнение вида: %d * x = 0 имеет единственное решение равное 0.\n\n", b);
            }
            else
            {
                printf("Уравнение умеет вид: %d * x + %d = 0 и является линейным.\n"
                       "Решением этого уравнения яляется: %.3f.\n\n", b, c, answers.answer1);
            }
        }
        else // квадратное
        {
            if(answers.amount == ONE && answers.answer1 == 0.0)
            {
                printf("Уравнение вида: %d * x^2 = 0 имеет единственное решение равное 0.\n\n", a);
            }
            else if(answers.amount == TWO && answers.answer1 == 0.0)
            {
                printf("Уравнение имеет вид: %d * x^2 + %d * x = 0\n"
                    "и его решениями являются: 0, %.3f.\n\n", a, b, answers.answer2);
            }
            else
            {
                printf("Уравнение умеет вид: %d * x^2 + %d * x + %d = 0 и является квадратным.\n", a, b, c);
                if (answers.amount == ZERO)
                {
                    printf("Т.к. значение дискриминанта меньше 0,\n"
                           "это уравнение не имеет решений.\n\n");
                }
                else if (answers.amount == ONE) //одно решение
                {
                    printf("Т.к. значение дискриминанта равно 0,\n"
                           "это уравнение имеет одно решение, равное: %.3f.\n\n", answers.answer1);
                }
                else
                {
                    printf("Т.к. значение дискриминанта больше 0,\n"
                           "это уравнение имеет два решения, равных: %.3f, %.3f.\n\n",
                           answers.answer1, answers.answer2);
                }
            }
        }
    }
    else // вывод в файл
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
        answers->type = LINEAR; // является линейным
        linearEquation(b, c, answers);
    }

    else // a != 0
    {
        answers->type = QUADRATIC; // является квадратным
        QuadraticEquation(a, b, c, answers);
    }
}

void linearEquation(int b, int c, struct solutions * answers)
{
    if (b == 0)
    {
        if (c == 0)
        {
            answers->amount = INF; // бесконечное количество решений
        }
        else // c != 0
        {
            answers->amount = MEANINGLESS; // не имеет смысла
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
        int D = b * b - 4 * a * c; //значение дискриминанта
        if (D < 0) //решений нет
        {
            answers->amount = ZERO;
        }
        else if (D == 0) //одно решение
        {
            answers->amount = ONE;
            answers->answer1 = ((-1.0) * b) / (2 * a);
        }
        else //два решения
        {
            double d = sqrt((double)D);
            answers->amount = TWO;
            answers->answer1 = ((-1.0) * b + d) / (2 * a);
            answers->answer2 = ((-1.0) * b - d) / (2 * a);
        }
    }
}
