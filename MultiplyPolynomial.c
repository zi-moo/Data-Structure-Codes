//链表实现两个多项式的乘法

#include <stdio.h>
#include <stdlib.h>


typedef struct polynomial {
    int cons;
    int exp;
    struct polynomial *next;
} Linklist;

Linklist* CreatePolynomial();
Linklist* MergePolynomial(Linklist *head1, Linklist *head2);
Linklist* MultiplyPolynomial(Linklist *head1, Linklist *head2);
Linklist* SortPolynomial(Linklist *head);
void PrintPolynomial(Linklist *head);

int main(void)
{
    Linklist *head1 = CreatePolynomial();
    Linklist *head2 = CreatePolynomial();
    Linklist *head3 = MultiplyPolynomial(head1, head2);
    PrintPolynomial(head3);
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

// Linklist* MultiplyPolynomial(Linklist *head1, Linklist *head2)
// {
//     Linklist *head3 = (Linklist*)malloc(sizeof(Linklist));
//     Linklist *head4 = (Linklist*)malloc(sizeof(Linklist));
//     Linklist *del;
//     head3->next = NULL;
//     head4->next = NULL;
//     Linklist *temp = head3;
//     Linklist *p1 = head1->next;
//     Linklist *p2 = head2->next;
//     while (p1 != NULL)
//     {
//         while (p2 != NULL)
//         {
//             Linklist *newnode = (Linklist*)malloc(sizeof(Linklist));
//             newnode->cons = p1->cons * p2->cons;
//             newnode->exp = p1->exp + p2->exp;
//             newnode->next = NULL;
//             temp->next = newnode;
//             temp = newnode;
//             p2 = p2->next;
//         }
//         p1 = p1->next;
//         p2 = head2->next;
//         head4 = MergePolynomial(head3, head4);
//         while (temp)
//         {
//             del = temp;
//             temp = del->next;
//             free(del);
//         }
//         temp->next = NULL;
//     }
//     return head4;
// }

Linklist* MultiplyPolynomial(Linklist *head1, Linklist *head2)
{
    // 创建结果多项式
    Linklist *result = (Linklist*)malloc(sizeof(Linklist));
    result->next = NULL;
    
    // 如果任一多项式为空，返回空多项式
    if (head1->next == NULL || head2->next == NULL) {
        return result;
    }
    
    // 遍历第一个多项式的每一项
    Linklist *p1 = head1->next;
    while (p1 != NULL)
    {
        // 遍历第二个多项式的每一项
        Linklist *p2 = head2->next;
        while (p2 != NULL)
        {
            // 计算两项相乘的结果
            int newCons = p1->cons * p2->cons;
            int newExp = p1->exp + p2->exp;
            
            // 创建新节点
            Linklist *current = result;
            int found = 0;
            
            // 查找是否存在相同指数的项
            while (current->next != NULL)
            {
                if (current->next->exp == newExp)
                {
                    current->next->cons += newCons;
                    found = 1;
                    // 如果系数和为0，删除该项
                    if (current->next->cons == 0)
                    {
                        Linklist *temp = current->next;
                        current->next = temp->next;
                        free(temp);
                    }
                    break;
                }
                current = current->next;
            }
            
            // 如果没有找到相同指数的项且系数不为0，添加新项
            if (!found && newCons != 0)
            {
                Linklist *newNode = (Linklist*)malloc(sizeof(Linklist));
                newNode->cons = newCons;
                newNode->exp = newExp;
                newNode->next = NULL;
                
                // 将新节点插入到结果链表中
                current = result;
                while (current->next != NULL && current->next->exp < newExp)
                {
                    current = current->next;
                }
                newNode->next = current->next;
                current->next = newNode;
            }
            
            p2 = p2->next;
        }
        p1 = p1->next;
    }
    
    // 对结果进行排序（按指数从小到大）
    return SortPolynomial(result);
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