#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct {
    int x, y;
    int di;
    int visited;
}Node;

typedef struct {
    Node data[20];
    int top;
}Stack;

void initStack(Stack *s) {
    s->top = -1;
}

void push(Stack *s, Node node) {
    s->data[++s->top] = node;
}

Node pop(Stack *s) {
    return s->data[s->top--];
}

Node peek(Stack *s) {
    return s->data[s->top];
}

Stack MazePath(int maze[10][10], int start_x, int start_y, int end_x, int end_y) {
    Stack path;
    initStack(&path);
    Node start;
    start.x = start_x;
    start.y = start_y;
    start.di = 0; //0right, 1down, 2left, 3up
    maze[start_x][start_y] = 2;
    push(&path, start);
    int direction[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};//right, down, left, up
    int current_x = start_x;
    int current_y = start_y;
    while (path.top >= -1) {
        Node current = peek(&path);
        current.x = current_x;
        current.y = current_y;
        bool found = false;
        for (int i = 0; i < 4; i++) {
            if (maze[current_x + direction[i][0]][current_y + direction[i][1]] == 0 
                && maze[current_x + direction[i][0]][current_y + direction[i][1]] != 2) 
            {
                current_x += direction[i][0];
                current_y += direction[i][1];
                current.di = i;
                push(&path, current);
                found = true;
                break;
            }
        }

        if (current_x == end_x && current_y == end_y) {
            return path;
        }

        if (!found) {
            Node temp = pop(&path);
            maze[temp.x][temp.y] = 0;
        }

    }
        
    
}




int main(void) {
    int maze[10][10] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 1, 0, 0, 0, 1, 0, 1,
    1, 0, 0, 1, 0, 0, 0, 1, 0, 1,
    1, 0, 0, 0, 0, 1, 1, 0, 0, 1,
    1, 0, 1, 1, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 1, 0, 0, 1,
    1, 0, 1, 1, 1, 0, 1, 1, 0, 1,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    };
    int start_x = 1;
    int start_y = 1;
    int end_x = 8;
    int end_y = 8;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
    Stack path = MazePath(maze, start_x, start_y, end_x, end_y);
    printf("迷宫路径：\n");
    printf("(%d, %d) ", start_x + 1, start_y + 1);
    for (int i = 0; i <= path.top; i++) {
        printf("->(%d, %d) ", path.data[i].x + 1, path.data[i].y + 1);
    }
    return 0;
}

