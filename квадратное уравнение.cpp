#include <stdio.h>
#include <TXLib.h>
#include <math.h>

/// Указывает, какого типа уравнение
enum EquationType {
                   LINEAR = 1, ///< Указывает на то, что уравнение линейное
                   QUADRATIC = 2 ///< Указывает на то, что уравнение квадратное
                   };

/// Указывает, сколько решений имеет уравнение
enum NumberOfSolutions {
                        ZERO = 0, ///< Указывает на то, что уравнение имеет 0 решений
                        ONE = 1, ///< Указывает на то, что уравнение имеет 1 решение
                        TWO = 2, ///< Указывает на то, что уравнение имеет 2 решения
                        INF = -1 ///< Указывает на то, что уравнение имеет бесконечно решений
                        };

struct solutions {enum EquationType type;
                  enum NumberOfSolutions amount;
                  double answer1;
                  double answer2;};

//--------------------------ВВОД--------------------------------------------------------
void InputAndOutputFormat(int * input, int * output); // выяснение формата ввода/вывода
void InputCleaning(void); // очистка ввода
void OutputFormat(int input, int output);

//--------------------------РЕШЕНИЕ-----------------------------------------------------
void SquareSolver(double a, double b , double c, struct solutions *); // выяснение типа уравнения
void linearEquation(double b , double c, struct solutions *); // решение линейного уравнения
void QuadraticEquation(double a, double b , double c, struct solutions *); // решение квадратного уравнения

//--------------------------ВЫВОД-------------------------------------------------------
int DoubleComparison(double a, double b); // сравнение чисел с точностью 0.0000001
void DerivationOfDecisions(double a, double b , double c,int outputformat, struct solutions * answers); // вывод решений в нужном формате

/**
    \brief основная функция
    @param [in] a {a - коэффицент уравнения}
    @param [in] b {b - коэффицент уравнения}
    @param [in] c {c - коэффицент уравнения}
    \return {нулевое значение}
*/
int main(void)
{
    int input = 1, output = 1;
    InputAndOutputFormat(&input, &output);

    FILE * read = stdin;
    if (input == 2)
    {
        read = fopen("read.txt", "r");
        if (read == NULL)
        {
            printf("\nОШИБКА!!! Файл read.txt не был найден.\n");
            exit(1);
        }
    }
    OutputFormat(input, output);

    struct solutions answers = {LINEAR, ZERO, 0, 0};
    double a = 0, b = 0, c = 0;

    while(fscanf(read, "%lg%lg%lg", &a, &b, &c) == 3)
        {
            SquareSolver(a, b, c, &answers);
            DerivationOfDecisions(a, b, c, output, &answers);
            if (input == 1)
                printf("Введите три коэффицента квадратного уравнения a, b, c или q для завершения программы:");
        }

    return 0;
}

/**
    \brief Выяснение формата ввода/вывода
    {Функция спращивает у пользователя, в каком формате будет происходить ввод и вывод.
    Так же функция позволяет пользователю исправить неправильно введенные данные
    с помощью функции InputAndOutputFormat}
    @param [out] *input {указатель на переменную, содержащую информацию о формате ввода}
    @param [out] *output {указатель на переменную, содержащую информацию о формате вывода}
    \return {ничего}
*/
void InputAndOutputFormat(int * input, int * output)
{
    printf("Здравствуйте, эта программа решает квадратное уравнение вида: a * x^2 + b * x + c = 0.\n\n"
    "Если вы хотите вводить данные с клавиатуры, то введите 1, если считывать из файла, то 2: ");
    while (scanf("%d", input) != 1)
    {
        InputCleaning();
        printf(" не является допустимым значением. Будте внимательнее, и введите 1 или 2: ");
    }
    printf("Отлично!\n"
           "Если вы хотите выводить данные на экран, то введите 1, если записывать в файл, то 2: ");
    while (scanf("%d", output) != 1)
    {
        InputCleaning();
        printf(" не является допустимым значением. Будте внимательнее, и введите 1 или 2: ");
    }
}

/**
    \brief Очишение входного потока
    {Функция считывает, а затем выводит оставленные во входном потоке символы}
    \return {ничего}
*/
void InputCleaning(void)
{
    int ch;
    while ((ch = getchar()) != '\n')
        putchar(ch);
}

/**
    {Выводит на экран выбранный формат ввода/вывода, и если нужно приглашает пользователя на ввод}
    @param input {переменная, содержащая информацию о формате ввода}
    @param output {переменная, содержащая информацию о формате вывода}
    \return {ничего}
*/
void OutputFormat(int input, int output)
{
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

    }
    else
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
    }
}

/**
    \brief Сравнение двух чисел с плавающей запятой
    {Эта функция сравнивает два дробных числа с точность 0.0000001}
    @param [in] a {a - первое число с плавающей запятой}
    @param [in] b {b - второе число с плавающей запятой}
    \return {0, если числа равны
            1, если первое число больше второго
            -1, если второе число больше первого}
*/
int DoubleComparison(double a, double b)
{
    assert(std::isfinite(a));
    assert(std::isfinite(b));
    const double FAULT = 0.0000001;
    if (fabs(a - b) <= FAULT)
        return 0;
    else if ((a - b) > FAULT)
        return 1;
    else
        return -1;
}

/**
    \brief Выяснение типа уравнения
    {По значению коэффицента a функция определяет, является оно линейным или квадратным}
    @param [in] a {a - коэффицент уравнения}
    @param [in] b {b - коэффицент уравнения}
    @param [in] c {c - коэффицент уравнения}
    @param [out] answers {struct solutions * answers - указатель на структуру, содержащую информацию об уравнении}
    \return {ничего}
*/
void SquareSolver(double a, double b , double c, struct solutions * answers)
{
    assert(std::isfinite(a));
    assert(std::isfinite(b));
    assert(std::isfinite(c));

    if (DoubleComparison(a, 0) == 0)
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

/**
    \brief Решение линейного уравнения
    {Функция решает различные типы линейных уравнений и записывает полученные данные в структуру answers}
    @param [in] b {b - коэффицент уравнения}
    @param [in] c {c - коэффицент уравнения}
    @param [out] answers {struct solutions * answers - указатель на структуру, содержащую информацию об уравнении}
    \return {ничего}
*/
void linearEquation(double b , double c, struct solutions * answers)
{
    assert(std::isfinite(b));
    assert(std::isfinite(c));
    if (DoubleComparison(b, 0) == 0)
    {
        if (DoubleComparison(c, 0) == 0)
        {
            answers->amount = INF; // бесконечное количество решений
        }
        else // c != 0
        {
            answers->amount = ZERO; // не имеет смысла
        }
    }
    else // b != 0
    {
        if (DoubleComparison(c, 0) == 0)
        {
            answers->amount = ONE;
            answers->answer1 = 0;
        }
        else // c != 0
        {
            answers->amount = ONE;
            answers->answer1 = (-1 * c) / b;
        }
    }
}

/**
    \brief Решение квадратного уравнения
    {Функция решает различные типы квадратных уравнений и записывает полученные данные в структуру answers}
    @param [in] a {a - коэффицент уравнения}
    @param [in] b {b - коэффицент уравнения}
    @param [in] c {c - коэффицент уравнения}
    @param [out] answers {struct solutions * answers - указатель на структуру, содержащую информацию об уравнении}
    \return {ничего}
*/
void QuadraticEquation(double a, double b , double c, struct solutions * answers)
{
    assert(std::isfinite(a));
    assert(std::isfinite(b));
    assert(std::isfinite(c));
    if (DoubleComparison(c, 0) == 0)
    {
        if (DoubleComparison(b, 0) == 0)
        {
            answers->amount = ONE;
            answers->answer1= 0;
        }
        else // b != 0
        {
            answers->amount = TWO;
            answers->answer1 = 0;
            answers->answer2 = (-1 * b) / a;
        }
    }
    else // c != 0
    {
        double D = b * b - 4 * a * c; //значение дискриминанта
        if (DoubleComparison(D, 0) == -1) //решений нет
        {
            answers->amount = ZERO;
        }
        else if (DoubleComparison(D, 0) == 0) //одно решение
        {
            answers->amount = ONE;
            answers->answer1 = ((-1) * b) / (2 * a);
        }
        else //два решения
        {
            double d = sqrt(D);
            answers->amount = TWO;
            answers->answer1 = ((-1) * b + d) / (2 * a);
            answers->answer2 = ((-1) * b - d) / (2 * a);
        }
    }
}

/**
    \brief Вывод решений в нужном формате
    {По значению параметра output функция определяет, в каком формате должны выводиться данные об уравнении,
    хранящиеся в структуре answers}
    @param [out] a {a - коэффицент уравнения}
    @param [out] b {b - коэффицент уравнения}
    @param [out] c {c - коэффицент уравнения}
    @param [out] output {output - коэффицент уравнения}
    @param [out] answers {struct solutions * answers - указатель на структуру, содержащую информацию об уравнении}
    \return {ничего}
*/
void DerivationOfDecisions(double a, double b , double c, int outputformat, struct solutions * answers)
{
    assert(std::isfinite(a));
    assert(std::isfinite(b));
    assert(std::isfinite(c));
    if (outputformat == 1) // вывод на экран
    {
        if(answers->type == LINEAR) // линейное
        {
            if(answers->amount == INF)
            {
                printf("Уравнение вида: 0 * x^2 + 0 * x = 0 имеет бесконечное количество решений.\n\n");
            }
            else if(answers->amount == ZERO)
            {
                printf("Уравнение вида: %.3lg = 0 не имеет решений.\n\n", c);
            }
            else if(answers->amount == ONE && DoubleComparison(answers->answer1, 0) == 0)
            {
                printf("Уравнение вида: %.3lg * x = 0 имеет единственное решение равное 0.\n\n", b);
            }
            else
            {
                printf("Уравнение умеет вид: %.3lg * x + %.3lg = 0 и является линейным.\n"
                       "Решением этого уравнения яляется: %.3lg.\n\n", b, c, answers->answer1);
            }
        }
        else // квадратное
        {
            if(answers->amount == ONE && DoubleComparison(answers->answer1, 0) == 0)
            {
                printf("Уравнение вида: %.3lg * x^2 = 0 имеет единственное решение равное 0.\n\n", a);
            }
            else if(answers->amount == TWO && DoubleComparison(answers->answer1, 0) == 0)
            {
                printf("Уравнение имеет вид: %.3lg * x^2 + %.3lg * x = 0\n"
                    "и его решениями являются: 0, %.3lg.\n\n", a, b, answers->answer2);
            }
            else
            {
                printf("Уравнение умеет вид: %.3lg * x^2 + %.3lg * x + %.3lg = 0 и является квадратным.\n", a, b, c);
                if (answers->amount == ZERO)
                {
                    printf("Т.к. значение дискриминанта меньше 0,\n"
                           "это уравнение не имеет решений.\n\n");
                }
                else if (answers->amount == ONE) //одно решение
                {
                    printf("Т.к. значение дискриминанта равно 0,\n"
                           "это уравнение имеет одно решение, равное: %.3lg.\n\n", answers->answer1);
                }
                else
                {
                    printf("Т.к. значение дискриминанта больше 0,\n"
                           "это уравнение имеет два решения, равных: %.3lg, %.3lg.\n\n",
                           answers->answer1, answers->answer2);
                }
            }
        }
    }
    else // вывод в файл
    {
        FILE * write;
        write = fopen("write.txt", "a");
        if(answers->amount == INF || answers->amount == ZERO)
        {
            fprintf(write, "%d\n", answers->amount);
        }
        else if(answers->amount == ONE)
        {
             fprintf(write, "1 : %.3lg\n", answers->answer1);
        }
        else
        {
             fprintf(write, "2 : %.3lg %.3lg\n", answers->answer1, answers->answer2);
        }
    }
}
