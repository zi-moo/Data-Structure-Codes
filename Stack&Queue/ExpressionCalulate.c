//键盘输入一个表达式，可以计算得到正确的值
//先计算运算符优先级，见到“）”就计算括号内的运算符，运算后的数字要及时推出
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// 定义数字栈和运算符栈
typedef struct {
    double data[MAX_SIZE];
    int top;
} NumberStack;

typedef struct {
    char data[MAX_SIZE];
    int top;
} OperatorStack;

// 初始化数字栈
void initNumberStack(NumberStack* stack) {
    stack->top = -1;
}

// 初始化运算符栈
void initOperatorStack(OperatorStack* stack) {
    stack->top = -1;
}

// 数字入栈
void pushNumber(NumberStack* stack, double num) {
    if (stack->top < MAX_SIZE - 1) {
        stack->data[++stack->top] = num;
    }
}

// 运算符入栈
void pushOperator(OperatorStack* stack, char op) {
    if (stack->top < MAX_SIZE - 1) {
        stack->data[++stack->top] = op;
    }
}

// 数字出栈
double popNumber(NumberStack* stack) {
    if (stack->top >= 0) {
        return stack->data[stack->top--];
    }
    return 0;
}

// 运算符出栈
char popOperator(OperatorStack* stack) {
    if (stack->top >= 0) {
        return stack->data[stack->top--];
    }
    return '\0';
}

// 获取运算符优先级
int getPriority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '(':
            return 0;
        default:
            return -1;
    }
}

// 执行运算
double calculate(double num1, double num2, char op) {
    switch (op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num2 != 0 ? num1 / num2 : 0;
        default: return 0;
    }
}

// 计算表达式
double evaluateExpression(const char* expr) {
    NumberStack numStack;
    OperatorStack opStack;
    initNumberStack(&numStack);
    initOperatorStack(&opStack);

    int len = strlen(expr);
    int i = 0;
    double num1, num2;
    char op;
    while (i < len) {
        // 跳过空格
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        // 处理数字
        if (isdigit(expr[i]) || expr[i] == '.') {
            char numStr[MAX_SIZE] = {0};
            int j = 0;
            while (i < len && (isdigit(expr[i]) || expr[i] == '.')) {
                numStr[j++] = expr[i++];
            }
            pushNumber(&numStack, atof(numStr)); //atof字符串转为浮点数
            continue;
        }

        // 处理运算符
        if (expr[i] == '(') {
            pushOperator(&opStack, expr[i]);
        }
        else if (expr[i] == ')') {
            // 处理括号内的运算
            while (opStack.top >= 0 && opStack.data[opStack.top] != '(') {
                num2 = popNumber(&numStack);
                num1 = popNumber(&numStack);
                op = popOperator(&opStack);
                pushNumber(&numStack, calculate(num1, num2, op));
            }
            // 弹出左括号
            if (opStack.top >= 0) {
                popOperator(&opStack);
            }
        }
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            // 比较运算符优先级
            while (opStack.top >= 0 && 
            getPriority(opStack.data[opStack.top]) >= getPriority(expr[i])) {
                num2 = popNumber(&numStack);
                num1 = popNumber(&numStack);
                op = popOperator(&opStack);
                pushNumber(&numStack, calculate(num1, num2, op));
            }
            pushOperator(&opStack, expr[i]);
        }
        i++;
    }

    // 处理剩余的运算符
    while (opStack.top >= 0) {
        num2 = popNumber(&numStack);
        num1 = popNumber(&numStack);
        op = popOperator(&opStack);
        pushNumber(&numStack, calculate(num1, num2, op));
    }

    // 返回最终结果
    return numStack.data[0];
}

int main() {
    char expr[MAX_SIZE];
    printf("请输入表达式：\n");
    fgets(expr, MAX_SIZE, stdin);
    
    // 去除换行符
    expr[strcspn(expr, "\n")] = 0;
    
    double result = evaluateExpression(expr);
    printf("计算结果：%g\n", result);
    
    return 0;
}
