#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 11  // 迷宫大小 (必须为奇数)
#define WALL 1  // 墙
#define PATH 0  // 路径
#define START_X 0
#define START_Y 0
#define END_X (MAX - 1)
#define END_Y (MAX - 1)

typedef struct
{
    int x;
    int y;
    int step;
}node;

int maze[MAX][MAX];
int directions[4][2]= {{0,1},{1,0},{0,-1},{-1,0}};

// 随机生成迷宫 (基于随机化Prim算法)
void generateMaze() {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            maze[i][j] = WALL;  // 初始化为全墙
        }
    }

    maze[START_X][START_Y] = PATH;  // 起点为路径

    int walls[MAX * MAX][2];
    int wallCount = 0;

    // 将起点周围的墙加入墙列表
    for (int i = 0; i < 4; i++) {
        int nx = START_X + directions[i][0];
        int ny = START_Y + directions[i][1];
        if (nx >= 0 && nx < MAX && ny >= 0 && ny < MAX) {
            walls[wallCount][0] = nx;
            walls[wallCount++][1] = ny;
        }
    }

    srand(time(NULL));  // 随机种子

    while (wallCount > 0) {
        int randIndex = rand() % wallCount;
        int wx = walls[randIndex][0];
        int wy = walls[randIndex][1];

        // 将随机墙移到列表末尾，并减少墙计数
        walls[randIndex][0] = walls[--wallCount][0];
        walls[randIndex][1] = walls[wallCount][1];

        // 检查墙两侧是否只有一侧是路径
        int pathCount = 0;
        int px = -1, py = -1;

        for (int i = 0; i < 4; i++) {
            int nx = wx + directions[i][0];
            int ny = wy + directions[i][1];
            if (nx >= 0 && nx < MAX && ny >= 0 && ny < MAX && maze[nx][ny] == PATH) {
                pathCount++;
                px = nx;
                py = ny;
            }
        }

        if (pathCount == 1) {
            maze[wx][wy] = PATH;  // 将墙变为路径

            // 将新路径周围的墙加入墙列表
            for (int i = 0; i < 4; i++) {
                int nx = wx + directions[i][0];
                int ny = wy + directions[i][1];
                if (nx >= 0 && nx < MAX && ny >= 0 && ny < MAX && maze[nx][ny] == WALL) {
                    walls[wallCount][0] = nx;
                    walls[wallCount++][1] = ny;
                }
            }
        }
    }
}

int isvalid(int x,int y,int visited[MAX][MAX])
{
    return x>=0 && x<MAX && y>=0 && y<MAX && maze[x][y]==PATH && !visited[x][y];
}

int BFS(int prev[MAX][MAX][2])
{
    node queue[MAX*MAX];
    int front=0,rear=0;
    int visited[MAX][MAX]= {0};
    visited[START_X][START_Y]=1;
    queue[rear++]=(node){START_X,START_Y,0};

    while(front<rear)
    {
        node current=queue[front++];
        if(current.x==END_X && current.y==END_Y)
        {
            return current.step;
        }

        for(int i=0;i<4;i++)
        {
            int nx=current.x+directions[i][0];
            int ny=current.y+directions[i][1];
            if(isvalid(nx,ny,visited))
            {
                visited[nx][ny]=1;
                queue[rear++]=(node){nx,ny,current.step+1};
                prev[nx][ny][0]=current.x;
                prev[nx][ny][1]=current.y;
            }
        }
    }
    return -1;
}

void printPATH(int prev[MAX][MAX][2])
{
    int x=END_X,y=END_Y;
    while(x!=-1 && y!=-1)
    {
        maze[x][y]=2;
        int nx=prev[x][y][0];
        int ny=prev[x][y][1];
        x=nx;
        y=ny;
    }
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++) 
        {
            if (maze[i][j] == WALL)
                printf("#");
            else if (maze[i][j] == PATH)
                printf(" ");
            else
                printf("*"); 
        }
        printf("\n");
    }
}

int main() {
    generateMaze();  // 随机生成迷宫

    int prev[MAX][MAX][2];
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            prev[i][j][0] = -1;
            prev[i][j][1] = -1;
        }
    }

    int result = BFS(prev);

    if (result != -1) {
        printPATH(prev);
        printf("最短路径长度为: %d\n", result);
    } else {
        printf("无法到达终点。\n");
    }

    return 0;
}