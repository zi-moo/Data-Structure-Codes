// 实现两个x的多项式的求和，
// 要求：采用链表实现。
// 1）每个多项式的信息均从控制台输入创建链表，输入数据完成后，链表创建完成。随后可在屏幕上输出两个多项式的信息。
// 2）链表创建完成后，可删除多项式中的任意一项，也可增加任意一项，形成新的多项式，删除和插入命令可在控制台输入一个命令实现。
// 3）实现两个多项式的求和运算。

#include <stdio.h>
#include <stdlib.h>


typedef struct polynomial {
    int cons;
    int exp;
    struct polynomial *next;
} Linklist;

Linklist* CreatePolynomial();
Linklist* MergePolynomial(Linklist *head1, Linklist *head2);
Linklist* InsertPolynomial(Linklist *head);
Linklist* DeletePolynomial(Linklist *head);
Linklist* SortPolynomial(Linklist *head);
void PrintPolynomial(Linklist *head);

int main()
{
    Linklist *poly1 = CreatePolynomial();
    Linklist *poly2 = CreatePolynomial();
    printf("\n第一个多项式: ");
    PrintPolynomial(poly1);
    printf("\n第二个多项式: ");
    PrintPolynomial(poly2);
    
    int choice = 0;
    while (choice != 4)
    {
        printf("请选择操作:\n");
        printf("1. 插入多项式\n");
        printf("2. 删除多项式\n");
        printf("3. 合并多项式\n");
        printf("4. 退出\n");
        scanf("%d", &choice);
        
        if (choice == 1) {
            int choice2;
            printf("请选择要插入的多项式(1/2):\n");
            scanf("%d", &choice2);
            if (choice2 == 1){
                poly1 = InsertPolynomial(poly1);
                printf("\n第一个多项式: ");
                PrintPolynomial(poly1);
            }
            else if (choice2 == 2){
                poly2 = InsertPolynomial(poly2);
                printf("\n第二个多项式: ");
                PrintPolynomial(poly2);
            }
        }
        else if (choice == 2) {
            int choice3;
            printf("请选择要删除的多项式(1/2):\n");
            scanf("%d", &choice3);
            if (choice3 == 1){
                poly1 = DeletePolynomial(poly1);
                printf("\n第一个多项式: ");
                PrintPolynomial(poly1);
            }
            else if (choice3 == 2){
                poly2 = DeletePolynomial(poly2);
                printf("\n第二个多项式: ");
                PrintPolynomial(poly2);
            }
        }
        else if (choice == 3) {
            Linklist* poly3 = MergePolynomial(poly1, poly2);
            printf("\n合并后的多项式: ");
            PrintPolynomial(poly3);
            free(poly3);
        }
    }
    
    free(poly1);
    free(poly2);
    return 0;
}


Linklist* CreatePolynomial()
{
    static int count = 1;
    Linklist *head = (Linklist*)malloc(sizeof(Linklist));
    head->next = NULL;
    Linklist *p = head;
    int cons, exp;
    int n;
    printf("请输入多项式%d的项数:", count);
    scanf("%d", &n);
    if (n == 0){
        count++;
        return head;
    }
    printf("请输入多项式的系数和指数:\n");
    for (int i = 0; i < n ; i++)
    {
        printf("第%d项", i+1);
        scanf("%d %d", &cons, &exp);
        Linklist *newnode = (Linklist*)malloc(sizeof(Linklist));
        newnode->cons = cons;
        newnode->exp = exp;
        newnode->next = NULL;
        p->next = newnode;
        p = newnode;
    }
    count++;
    return head;
}

void PrintPolynomial(Linklist *head)
{
    if (head->next == NULL){
        printf("0\n");
        return;
    }
    
    Linklist *p = head->next;
    if(p == NULL)
    {
        printf("0\n");
        return;
    }
    
    int first = 1;
    while (p != NULL)
    {
        if (!first && p->cons > 0) {
            printf("+");
        }
        first = 0;
        
        if (p->exp == 0) {
            printf("%d", p->cons);
        } else if (p->exp == 1) {
            printf("%dx", p->cons);
        } else {
            printf("%dx^%d", p->cons, p->exp);
        }
        p = p->next;
    }
    printf("\n");
}

Linklist* SortPolynomial(Linklist *head)  // bubble sort
{
    if (head->next == NULL || head->next->next == NULL) {
        return head;
    }
    
    Linklist *i, *j;
    int tempcons, tempexp;
    for (i = head->next; i->next != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (i->exp > j->exp)  // 改为从小到大排序
            {
                tempcons = i->cons;
                tempexp = i->exp;
                i->cons = j->cons;
                i->exp = j->exp;
                j->cons = tempcons;
                j->exp = tempexp;
            }
        }
    }
    return head;
}

Linklist* InsertPolynomial(Linklist *head)
{
    int cons, exp;
    Linklist *current = head;
    printf("请输入要插入的系数和指数:");
    scanf("%d %d", &cons, &exp);
    
    Linklist *newnode = (Linklist*)malloc(sizeof(Linklist));
    newnode->cons = cons;
    newnode->exp = exp;
    newnode->next = NULL;
    
    if (current->next == NULL || current->next->exp > exp) {
        newnode->next = current->next;
        current->next = newnode;
        return head;
    }
    
    while (current->next != NULL && current->next->exp < exp) {
        current = current->next;
    }
    
    if (current->next != NULL && current->next->exp == exp) {
        current->next->cons += cons;
        free(newnode);  // 释放不需要的新节点
        
        if (current->next->cons == 0) {
            Linklist *temp = current->next;
            current->next = temp->next;
            free(temp);
        }
    } 
    else {
        newnode->next = current->next;
        current->next = newnode;
    }
    
    return head;
}

Linklist* DeletePolynomial(Linklist *head)
{
    int expd;
    printf("请输入要删除的项的指数:");
    scanf("%d", &expd);
    Linklist *current = head;
    while (current->next != NULL && current->next->exp != expd)
    {
        current = current->next;
    }
    if (current->next == NULL){
        printf("要删除的项不存在\n");
    }
    else{
        Linklist *temp = current->next;
        current->next = temp->next;
        free(temp);
    }
    return head;
}

Linklist* MergePolynomial(Linklist *head1, Linklist *head2)
{
    head1 = SortPolynomial(head1);  // 先确保两个多项式都是按指数从小到大排序
    head2 = SortPolynomial(head2);
    
    Linklist *result = (Linklist*)malloc(sizeof(Linklist));
    result->next = NULL;
    Linklist *current = result;
    Linklist *p1 = head1->next;
    Linklist *p2 = head2->next;
    
    while (p1 != NULL && p2 != NULL)
    {
        Linklist *temp = (Linklist*)malloc(sizeof(Linklist));
        if (p1->exp < p2->exp){
            temp->cons = p1->cons;
            temp->exp = p1->exp;
            p1 = p1->next;
        }
        else if (p1->exp > p2->exp){
            temp->cons = p2->cons;
            temp->exp = p2->exp;
            p2 = p2->next;
        }
        else{
            temp->cons = p1->cons + p2->cons;
            temp->exp = p1->exp;
            p1 = p1->next;
            p2 = p2->next;
            if (temp->cons == 0) {  // 如果系数和为0，跳过这一项
                free(temp);
                continue;
            }
        }
        temp->next = NULL;
        current->next = temp;
        current = current->next;
    }
    
    // 处理剩余项
    while (p1 != NULL){
        Linklist *temp = (Linklist*)malloc(sizeof(Linklist));
        temp->cons = p1->cons;
        temp->exp = p1->exp;
        temp->next = NULL;
        current->next = temp;
        current = current->next;
        p1 = p1->next;
    }
    
    while (p2 != NULL){
        Linklist *temp = (Linklist*)malloc(sizeof(Linklist));
        temp->cons = p2->cons;
        temp->exp = p2->exp;
        temp->next = NULL;
        current->next = temp;
        current = current->next;
        p2 = p2->next;
    }
    
    return result;
}