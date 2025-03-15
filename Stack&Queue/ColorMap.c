#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_NUMBERS 20  
#define NUM_COLORS 4     

// 堆栈基本操作
typedef struct {
    int number;     
    int color;      
} StackNode;

typedef struct {
    StackNode data[MAX_NUMBERS];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

bool push(Stack* s, StackNode node) {
    if (s->top >= MAX_NUMBERS - 1) return false;
    s->data[++s->top] = node;
    return true;
}

bool pop(Stack* s, StackNode* node) {
    if (s->top < 0) return false;
    *node = s->data[s->top--];
    return true;
}

bool peek(Stack* s, StackNode* node) {
    if (s->top < 0) return false;
    *node = s->data[s->top];
    return true;
}

// 检查是否可以给顶点着色
bool detection(int v, int color, int graph[MAX_NUMBERS][MAX_NUMBERS], int colors[], int V) {
    for (int i = 0; i < V; i++) {
        if (graph[v][i] && colors[i] == color) {
            return false;
        }
    }
    return true; 
}

void printColor(int color) {
    switch(color) {
        case 1: printf("红色\n"); break;
        case 2: printf("绿色\n"); break;
        case 3: printf("蓝色\n"); break;
        case 4: printf("黄色\n"); break;
    }
}


bool graphColoring(int graph[MAX_NUMBERS][MAX_NUMBERS], int V) {
    Stack stack;
    initStack(&stack);
    
    // 初始化颜色数组（0表示未着色）
    int* colors = (int*)calloc(V, sizeof(int));
    
    // 将第一个顶点压入栈
    StackNode firstNode = {0, 0};  // 顶点0，颜色0
    push(&stack, firstNode);
    
    while (stack.top >= 0) {
        StackNode currentNode;
        peek(&stack, &currentNode);
        
        // 尝试下一个颜色
        currentNode.color++;
        
        // 如果已经尝试了所有颜色，回溯
        if (currentNode.color > NUM_COLORS) {
            pop(&stack, &currentNode);
            if (stack.top >= 0) {
                colors[currentNode.number] = 0;  // 清除颜色
            }
            continue;
        }
        
        // 更新栈顶节点的颜色
        stack.data[stack.top].color = currentNode.color;
        
        // 检查是否可以使用当前颜色
        if (detection(currentNode.number, currentNode.color, graph, colors, V)) {
            colors[currentNode.number] = currentNode.color;
            // 如果所有顶点都已着色，找到解
            if (currentNode.number == V - 1) {
                printf("\n找到可行的着色方案:\n");
                for (int i = 0; i < V; i++) {
                    printf("顶点 %d -> ", i + 1);
                    printColor(colors[i]);
                }
                free(colors);
                return true;
            }
            
            // 处理下一个顶点
            StackNode newNode = {currentNode.number + 1, 0};
            push(&stack, newNode);
        }
    }
    
    printf("\n没有找到可行的着色方案！\n");
    free(colors);
    return false;
}

// 输入图的邻接矩阵
void inputGraph(int graph[MAX_NUMBERS][MAX_NUMBERS], int V) {
    printf("请输入图的邻接矩阵（%d x %d）：\n", V, V);
    printf("（输入1表示两点相连，0表示不相连）\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
}

int main() {
    int V;
    int graph[MAX_NUMBERS][MAX_NUMBERS];
    
    printf("请输入图的顶点数（不超过%d）：", MAX_NUMBERS);
    scanf("%d", &V);
    
    if (V <= 0 || V > MAX_NUMBERS) {
        printf("顶点数无效！\n");
        return 1;
    }
    
    inputGraph(graph, V);
    graphColoring(graph, V);
    
    return 0;
}

