#include<stdio.h>
#include <time.h>
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
void printArray(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
}

int Partition (int A[], int p, int r)
{
    int x = A[r];
    int i = (p - 1);
    int j;
    for (j = p; j <= r; j++)
    {
        if (A[j] <= x)
        {
            i++;
            swap(&A[i], &A[j]);
        }
    }
    if(i<r)
    return i;
    else return i-1;
}
void QuickSort(int A[], int p, int r)
{
    if (p < r)
    {
        int q = Partition(A, p, r);
        QuickSort(A, p, q);
        QuickSort(A, q + 1, r);
    }
}
void bubbleSort(int A[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)
       for (j = 0; j < n-i-1; j++)
           if (A[j] > A[j+1])
              swap(&A[j], &A[j+1]);
}
void bubbleQuickSort(int A[], int p, int r)
{
    if (p < r)
    {
        if(r<=500000000)
        {
            bubbleSort(A,r);
        }
        else
        {
            int q = Partition(A, p, r);
            QuickSort(A, p, q);
            QuickSort(A, q + 1, r);
        }
    }
}

int main()
{
    int i;int ile=10000;
    int A[ile];
    //int A[] = {10, 7, 8, 9, 1, 5,14,33,83,64,55,21,8,0,3,66,77,33,2,1,45,8};
     for(i=0; i<ile; i++)
    {
        A[i] = rand()%10000+1;
    }
    int n = (sizeof(A)/sizeof(A[0])-1);
    time_t start,end;
    double dif;

  time (&start);
  bubbleQuickSort(A,0,n);
  time (&end);
  dif = difftime (end,start);
  printf ("Your calculations took %.2lf seconds to run.\n", dif );
    //printf("Sorted Array: ");
    //printArray(A, n);
    return 0;
}
