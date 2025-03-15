//表达式求职，用到数字栈和运算符栈

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    double data[20];
    int top;
}NumberStack;

typedef struct {
    char data[20];
    int top;
}OperatorStack;

//堆栈基本操作
void initNumberStack(NumberStack* stack) {
    stack->top = -1;
}

void initOperatorStack(OperatorStack* stack) {
    stack->top = -1;
}

void pushNumber(NumberStack* stack, double num) {
    if (stack->top < 20 - 1) {
        stack->data[++stack->top] = num;
    }
}

void pushOperator(OperatorStack* stack, char op) {
    if (stack->top < 20 - 1) {
        stack->data[++stack->top] = op;
    }
}

double popNumber(NumberStack* stack) {
    return stack->data[stack->top--];
}

char popOperator(OperatorStack* stack) {
    return stack->data[stack->top--];
}

double cal_operator(double num1, double num2, char op) {
    switch (op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num2 != 0 ? num1 / num2 : 0;
        default: return 0;
    }
}

double getPriority(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '(': return 0;
        default: return -1;
    }
}

double calculateExpression(char* expression) {
    NumberStack numStack;
    OperatorStack opStack;
    initNumberStack(&numStack);
    initOperatorStack(&opStack);
    int len = strlen(expression);
    int i = 0;
    double num1, num2;
    char op;
    while (i < len) {
        if (isspace(expression[i])) {
            i++;
            continue;
        }
        //storage number
        if (isdigit(expression[i]) || expression[i] == '.') {
            char num_store[20] = {0};
            int j = 0;
            while (i <len && (isdigit(expression[i]) || expression[i] == '.')) {
                num_store[j++] = expression[i++];
            }
            pushNumber(&numStack, atof(num_store));
            continue;
        }
        //storage operator
        if (expression[i] == '(') {
            pushOperator(&opStack, expression[i]);
            i++;
            continue;
        }
        else if (expression[i] == ')') {
            while (opStack.top >= 0 && opStack.data[opStack.top] != '(') {
                num2 = popNumber(&numStack);
                num1 = popNumber(&numStack);
                op = popOperator(&opStack);
                pushNumber(&numStack, cal_operator(num1, num2, op));
            }
            //pop left bracket
            if (opStack.top >= 0) {
                popOperator(&opStack);
            }
        }
        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            while (opStack.top >= 0 && getPriority(opStack.data[opStack.top]) > getPriority(expression[i])) {
                num2 = popNumber(&numStack);
                num1 = popNumber(&numStack);
                op = popOperator(&opStack);
                pushNumber(&numStack, cal_operator(num1, num2, op));
            }
            pushOperator(&opStack, expression[i]);
            i++;
        }
    }
    while (opStack.top >= 0) {
        num2 = popNumber(&numStack);
        num1 = popNumber(&numStack);
        op = popOperator(&opStack);
        pushNumber(&numStack, cal_operator(num1, num2, op));
    }
    return numStack.data[0];
}

int main() {
    char expression[50];
    printf("请输入一个表达式：");
    fgets(expression,sizeof(expression),stdin);
    expression[strcspn(expression, "\n")] = 0;
    double result = calculateExpression(expression);
    printf("计算结果：%g\n", result);
    return 0;
}


