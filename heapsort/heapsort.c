#include<stdio.h>
#include <stdlib.h>
#include <math.h>
void Heapify (int *A, int heapSize, int i)
{
  int largest, tmp;
  while (i <= heapSize)
    {
      int l = 2 * i, r = (2 * i) + 1;
      if (l <= heapSize && A[l] > A[i])
	largest = l;
      else
	largest = i;
      if (r <= heapSize && A[r] > A[largest])
	largest = r;
      if (largest != i)
	{
	  tmp = A[largest];
	  A[largest] = A[i];
	  A[i] = tmp;
	  i = largest;
	}
      else
	return;
    }
}

void BuldHeap (int *A, int length)
{
  int heapSize = length;
  int i;
  for (i = floor (length / 2); i >= 0; i--)
    Heapify (A, length, i);
}

void HeapSort (int *A, int length)
{
  int tmp, i;
  BuldHeap (A, length);
  for (i = length; i > 0; i--)
    {
      tmp = A[i];
      A[i] = A[0];
      A[0] = tmp;
      length--;
      Heapify (A, length, 0);
    }
}

int main ()
{
  FILE *fp;
  fp = fopen ("plik.txt", "r");
  char ch;
  int length = 0;
  while (!feof (fp))
    {
      ch = fgetc (fp);
      if (ch == '\n')
	{
	  length++;
	}
    }
  rewind (fp);
  int A[length];
  int j = 0;
  int num;
  while (fscanf (fp, "%d", &num) > 0)
    {
      A[j] = num;
      j++;
    }
  fclose (fp);

  int k;
  HeapSort (A, length);
  FILE *fp2;
  fp2 = fopen ("plik2.txt", "w");
  for (k = 0; k <= length; k++)
    {
      fprintf (fp2, "%d\n", A[k]);
    }
  fclose (fp2);

  return 0;
}
