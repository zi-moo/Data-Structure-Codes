//1.输入两组整数，一组8个，一组10个，分别他们的均值和方差，并从小到大排序。对排好序的两组有序数组合并之后排序，并计算均值和方差。
//（至少采用两种排序算法来实现排序，计算均值和方差用一个函数，排序采用一个函数）
//输出结果包括以下内容：原始两组数，他们的均值和方差，排好序的两组结果。合并之后排好序的结果，合并之后的均值和方差。两种排序算法各自移动和交换数据的总次数。

//2. 631218, 382053，763315，编程计算这三个数字的最大公约数。

#include <stdio.h>

void calculate(int *a, int n, double *mean, double *var); //calculate mean and variance
void insert_sort(int *a, int n, int *move, int *swap); //insert sort
void bubble_sort(int *a, int n, int *move, int *swap); //bubble sort
void combine(int *a, int *b, int *c, int n, int m); //combine two arrays
int gcd(int a, int b, int c); //greatest common divisor


int main(void)
{
    int arr1[8] = {1, 2, 7, 4, 9, 13, 10, 3},
        arr2[10] = {5, 6, 8, 15, 12, 19, 11, 17, 14, 16},
        arr3[18], arr3_copy[18];
    double mean1, mean2, var1, var2, mean3, var3;
    int move1 = 0, swap1 = 0, move2 = 0, swap2 = 0, move3 = 0, swap3 = 0, move_copy = 0, swap_copy = 0;

    //calculate average and variance
    calculate(arr1, 8, &mean1, &var1);
    calculate(arr2, 10, &mean2, &var2);

    printf("\noriginal array1: [");
    for (int i = 0; i < 8; i++) {
        printf("%d ", arr1[i]);
    }
    printf("]\n");
    printf("array1: average = %.2f, variance = %.2f\n", mean1, var1);
    printf("\noriginal array2: [");
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr2[i]);
    }
    printf("]\n");
    printf("array2: average = %.2f, variance = %.2f\n", mean2, var2);

    //bubble sort
    bubble_sort(arr1, 8, &move1, &swap1);
    printf("\narray1 after bubble sort: [");
    for (int i = 0; i < 8; i++) {
        printf("%d ", arr1[i]);
    }
    printf("]\n");
    printf("array1 with bubble sort: move = %d, swap = %d\n", move1, swap1);

    //insert sort
    insert_sort(arr2, 10, &move2, &swap2);
    printf("\narray2 after insert sort: [");
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr2[i]);
    }
    printf("]\n");
    printf("array2 with insert sort: move = %d, swap = %d\n", move2, swap2);

    //combine two arrays
    combine(arr1, arr2, arr3, 8, 10);
    for (int i = 0; i < 18; i++) {
        arr3_copy[i] = arr3[i];
    }
    bubble_sort(arr3, 18, &move3, &swap3);
    calculate(arr3, 18, &mean3, &var3);
    printf("\narray3 after sort: [");
    for (int i = 0; i < 18; i++) {
        printf("%d ", arr3[i]);
    }
    printf("]\n");
    printf("array3: average = %.2f, variance = %.2f\n", mean3, var3);
    printf("array3 with bubble sort: move = %d, swap = %d\n", move3, swap3);
    insert_sort(arr3_copy, 18, &move_copy, &swap_copy);
    printf("array3 with insert sort: move = %d, swap = %d\n", move_copy, swap_copy);

    //calculate gcd
    printf("\nGCD of 631218, 382053 and 763315 is %d\n", gcd(631218, 382053, 763315));
}

void calculate(int *a, int n, double *mean, double *var)
{
    int i;
    double sum = 0, sum2 = 0;
    for (i = 0; i < n; i++)
    {
        sum += a[i];
        sum2 += a[i] * a[i];
    }
    *mean = sum / n;
    *var = sum2 / n - (*mean) * (*mean);
}

void bubble_sort(int *a, int n, int *move, int *swap)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                *swap += 1;
                *move += 2;
            }

        }
    }
}

void insert_sort(int *a, int n, int *move, int *swap)
{
    int i, j, key;
    for (i = 1; i < n; i++)
    {
        key = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j = j - 1;
            *move += 1;
        }
        a[j + 1] = key;
        *move += 1;
        *swap += 1; 
    }
}

void combine(int *a, int *b, int *c, int n, int m)
{
    int i;
    for (i = 0; i < n; i++)
    {
        c[i] = a[i];
    }
    for (i = 0; i < m; i++)
    {
        c[n + i] = b[i];
    }
}

int gcd(int a, int b, int c)
{
    int i, min, max, gcd = 1;
    min = a < b ? a : b;
    max = a > b ? a : b;
    min = min < c ? min : c;
    max = max > c ? max : c;
    for (i = min; i > 0; i--)
    {
        if (a % i == 0 && b % i == 0 && c % i == 0)
        {
            gcd = i;
            break;
        }
    }
    return gcd;
}

// int gcd(int a, int b, int c)
// {
//     int i, min, max, gcd = 1;
//     min = a < b ? a : b;
//     max = a > b ? a : b;
//     min = min < c ? min : c;
//     max = max > c ? max : c;
//     for (i = 1; i < min; i++)
//     {
//         if (a % i == 0 && b % i == 0 && c % i == 0)
//         {
//             gcd = i;
//         }
//     }
//     return gcd;
// }

// int gcd(int a,int b)
// {
// 	int r;
// 	r = a%b;
// 	while(r!=0)
// 	{
// 		a = b;
// 		b = r;
// 		r = a%b;
// 	}
// 	return b;    
// }
// gcd(a,gcd(b,c))