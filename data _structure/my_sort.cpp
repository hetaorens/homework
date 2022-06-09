#include <stdio.h>
#include <iostream>
#include <time.h>
#include <sys/time.h>
using namespace std;

// 1、直接插入排序
void InsertSort(int key[], int n)
{
    int i, j;
    for (i = 1; i < n; i++)
    { //遍历第 2~n-1 个元素
        int insert = key[i];
        for (j = i - 1; j >= 0; j--)
        {
            if (insert < key[j])
            {
                key[j + 1] = key[j];
            }
            else
                break;
        }
        key[j + 1] = insert;
    }
}

// 2、简单选择排序
void SelectSort(int key[], int n)
{
    int small, i, j;
    for (i = 0; i < n - 1; i++)
    { //遍历第 1~n-1 个元素
        small = i;
        for (j = i + 1; j < n; j++)
        { ////遍历第 i+1~n 个元素
            if (key[j] < key[small])
            {
                small = j;
            }
        }
        if (small != i)
            swap(key[i], key[small]);
    }
}

// 3、冒泡排序
void BubbleSort(int key[], int n)
{
    int i, j;
    for (i = n - 1; i > 0; i--)
    { //遍历第 2~n 个元素
        bool isSwap = false;
        for (j = 0; j < i; j++)
        { //遍历第 1~i 个元素
            if (key[j] > key[j + 1])
            {
                swap(key[j], key[j + 1]);
                isSwap = true;
            }
        }
        if (!isSwap)
            break;
    }
}

// 4、快速排序
int Partition(int key[], int low, int high)
{
    int i = low, j = high + 1;
    int flag = key[low]; //当前分割元素
    do
    {
        do
            i++;
        while (key[i] < flag);
        do
            j--;
        while (key[j] > flag);
        if (i < j)
            swap(key[i], key[j]);

    } while (i < j);
    swap(key[low], key[j]);
    return j; //下一个分割元素
}

void QuickSort(int key[], int low, int high)
{
    int k;
    if (low < high)
    {
        k = Partition(key, low, high);
        QuickSort(key, low, k - 1);
        QuickSort(key, k + 1, high);
    }
}

void QuickSort(int key[], int n)
{
    QuickSort(key, 0, n - 1);
}


// 5、产生随机序列
void Init(int key[], int n)
{
    // cout << "\t随机序列：";
    for (int i = 0; i < n; i++)
    {
        key[i] = rand() % 1000;
        // cout << key[i] << " ";
    }
    cout << " -> ";
}

// 6、输出有序序列
void output(int key[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << key[i] << " ";
    }
    cout << " -> ";
}

int main()
{
    int key[500000], n;
    cout << "\n\t输入随机序列长度：";
    cin >> n;
    cout << endl;
    srand((int)time(NULL)); //随机发生器
    timeval start, end;     //计时器

    Init(key, n);
    gettimeofday(&start, 0);
    InsertSort(key, n);
    gettimeofday(&end, 0);
    cout << "\t直接插入排序：";
 
    double time = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    time /= 1000;
    cout << "\t排序时长:" << time << "ms\n\n";

    Init(key, n);
    gettimeofday(&start, 0);
    SelectSort(key, n);
    gettimeofday(&end, 0);
    cout << "\t简单选择排序：";
 
    double time2 = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    time2 /= 1000;
    cout << "\t排序时长:" << time2 << "ms\n\n";

    Init(key, n);
    gettimeofday(&start, 0);
    BubbleSort(key, n);
    gettimeofday(&end, 0);
    cout << "\t冒泡排序：";
   
    double time3 = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    time3 /= 1000;
    cout << "\t排序时长:" << time3 << "ms\n\n";

    Init(key, n);
    gettimeofday(&start, 0);
    QuickSort(key, n);
    gettimeofday(&end, 0);
    cout << "\t快速排序：";
   
    double time4 = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    time4 /= 1000;
    cout << "\t排序时长:" << time4 << "ms\n\n";

 

    return 0;
}
