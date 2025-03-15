// 随机生成两组int型数字，一组个数为M，一组个数N，M和N均从控制台输入（非宏定义），分别对两组数字进行排序，并计算其均值和方差，
// 然后将两组排序好的数据合并成一组有序数据，并计算均值和方差。
// 对合并后的数据可进行插入删除操作，在控制台运行insert命令，提示插入一个数字，要求插入后数据仍然是有序，
// 在控制台运行delete命令，提示输入某一个需要删除的数字的序号（如3，表示删除有序数列中的第三个数字）。
// 输入end命令，结束操作。在没有输入end之前，可重复的执行插入删除操作。
// 要求：不能采用数组的形式，所有内存分配采用动态内存分配（提示：必须在M,N已知的情况才能分配内存），
// 排序和计算均值方差是一个独立的子函数，合并数据并计算均值和方差是一个独立的子函数，插入功能是一个独立的函数，删除功能是一个独立的函数。



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

typedef struct Node {
    int num;
    struct Node* next;
} Linklist;

Linklist* createRandomList(int size);
Linklist* sortListWithStats(Linklist* head, double* mean, double* var);
Linklist* mergeLists(Linklist* list1, Linklist* list2, double* mean, double* var);
Linklist* insertNode(Linklist* head, int value);
Linklist* deleteNode(Linklist* head, int position);
void printList(Linklist* head);
void freeList(Linklist* head);
int isNumberExists(Linklist* head, int num);

int main() 
{
    int M, N;
    printf("Please enter M and N (1-10): ");
    scanf("%d %d", &M, &N);
    
    if (M == N || M > 10 || N > 10 || M < 1 || N < 1) {
        printf("Invalid input! M and N must be different and between 1-10\n");
        return 1;
    }

    srand(time(NULL));
    
    Linklist* list1 = createRandomList(M);
    Linklist* list2 = createRandomList(N);
    
    printf("\nFirst group original num: ");
    printList(list1);
    printf("Second group original num: ");
    printList(list2);
    
    double mean1, variance1, mean2, variance2;
    list1 = sortListWithStats(list1, &mean1, &variance1);
    list2 = sortListWithStats(list2, &mean2, &variance2);
    
    printf("\nFirst group after sorting: ");
    printList(list1);
    printf("Mean: %.2f, Variance: %.2f\n", mean1, variance1);
    
    printf("Second group after sorting: ");
    printList(list2);
    printf("Mean: %.2f, Variance: %.2f\n", mean2, variance2);
    
    double meanMerged, varianceMerged;
    Linklist* mergedList = mergeLists(list1, list2, &meanMerged, &varianceMerged);
    
    printf("\nMerged num: ");
    printList(mergedList);
    printf("Merged Mean: %.2f, Variance: %.2f\n", meanMerged, varianceMerged);
    
    char command[10];
    while (1) {
        printf("\nEnter command (insert/delete/end): ");
        scanf("%s", command);
        
        if (strcmp(command, "end") == 0) {
            break;
        } else if (strcmp(command, "insert") == 0) {
            int value;
            printf("Enter number to insert: ");
            scanf("%d", &value);
            mergedList = insertNode(mergedList, value);
            printf("Data after insertion: ");
            printList(mergedList);
        } else if (strcmp(command, "delete") == 0) {
            int position;
            printf("Enter position to delete: ");
            scanf("%d", &position);
            mergedList = deleteNode(mergedList, position);
            printf("Data after deletion: ");
            printList(mergedList);
        }
    }
    
    freeList(mergedList);
    return 0;
}

int isNumberExists(Linklist* head, int num) {
    Linklist* current = head;
    while (current != NULL) {
        if (current->num == num) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Linklist* createRandomList(int size) {  // 新数据插入到表头
//     Linklist* head = NULL;
//     int i = 0;
//     while (i < size) {
//         int newNum = rand() % 100;
//         if (!isNumberExists(head, newNum)) {
//             Linklist* newNode = (Linklist*)malloc(sizeof(Linklist));
//             newNode->num = newNum;
//             newNode->next = head;
//             head = newNode;
//             i++;
//         }
//     }
//     return head;
// }


Linklist* createRandomList(int size)    // 新数据插入到表尾
{
    Linklist* head, *end;
    head = (Linklist*)malloc(sizeof(Linklist));
    head->next = NULL;
    end = head;
    for (int i = 0; i < size; i++)
    {
        int newNum = rand() % 100;
        if (!isNumberExists(head->next, newNum))  // 从第一个实际节点开始检查
        {
            Linklist* newNode = (Linklist*)malloc(sizeof(Linklist));
            newNode->num = newNum;
            newNode->next = NULL;
            end->next = newNode;
            end = newNode;
        }
    }
    return head->next;
}


Linklist* sortListWithStats(Linklist* head, double* mean, double* var) 
{
    if (head == NULL || head->next == NULL) return head;
    
    Linklist* current;
    Linklist* nextNode;
    int swapped = 1;
    int count = 0;
    double sum = 0;
    
    current = head;
    while (current != NULL) {
        sum += current->num;
        count++;
        current = current->next;
    }
    
    *mean = sum / count;
    
    while (swapped) {
        swapped = 0;
        current = head;
        while (current->next != NULL) {
            if (current->num > current->next->num) {
                int temp = current->num;
                current->num = current->next->num;
                current->next->num = temp;
                swapped = 1;
            }
            current = current->next;
        }
    }
    
    sum = 0;
    current = head;
    while (current != NULL) {
        sum += pow(current->num - *mean, 2);
        current = current->next;
    }
    *var = sum / count;
    
    return head;
}

Linklist* mergeLists(Linklist* list1, Linklist* list2, double* mean, double* var) {
    Linklist* dummy = (Linklist*)malloc(sizeof(Linklist));
    Linklist* current = dummy;
    int count = 0;
    double sum = 0;
    
    while (list1 != NULL && list2 != NULL) {
        if (list1->num <= list2->num) {
            current->next = list1;
            sum += list1->num;
            list1 = list1->next;
        } else {
            current->next = list2;
            sum += list2->num;
            list2 = list2->next;
        }
        count++;
        current = current->next;
    }
    
    while (list1 != NULL) {
        current->next = list1;
        sum += list1->num;
        count++;
        current = current->next;
        list1 = list1->next;
    }
    
    while (list2 != NULL) {
        current->next = list2;
        sum += list2->num;
        count++;
        current = current->next;
        list2 = list2->next;
    }
    
    *mean = sum / count;
    
    sum = 0;
    current = dummy->next;
    while (current != NULL) {
        sum += pow(current->num - *mean, 2);
        current = current->next;
    }
    *var = sum / count;
    
    Linklist* result = dummy->next;
    free(dummy);
    return result;
}

Linklist* insertNode(Linklist* head, int value) {
    Linklist* newNode = (Linklist*)malloc(sizeof(Linklist));
    newNode->num = value;
    
    if (head == NULL || value <= head->num) {
        newNode->next = head;
        return newNode;
    }
    
    Linklist* current = head;
    while (current->next != NULL && current->next->num < value) {
        current = current->next;
    }
    
    newNode->next = current->next;
    current->next = newNode;
    return head;
}

Linklist* deleteNode(Linklist* head, int position) {
    if (head == NULL || position < 1) return head;
    
    if (position == 1) {
        Linklist* temp = head->next;
        free(head);
        return temp;
    }
    
    Linklist* current = head;
    int i = 1;
    while (i < position - 1 && current != NULL) {
        current = current->next;
        i++;
    }
    
    if (current == NULL || current->next == NULL) {
        printf("Invalid position\n");
        return head;
    }
    
    Linklist* temp = current->next;
    current->next = temp->next;
    free(temp);
    return head;
}

void printList(Linklist* head) {
    Linklist* current = head;
    while (current != NULL) {
        printf("%d ", current->num);
        current = current->next;
    }
    printf("\n");
}

void freeList(Linklist* head) {
    Linklist* current = head;
    while (current != NULL) {
        Linklist* temp = current;
        current = current->next;
        free(temp);
    }
}