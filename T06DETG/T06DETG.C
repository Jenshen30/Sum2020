/*FILE NAME: T05DET.C
* PROGRAMER: EK6
* DATE: 03.06.2020
*/

#include <windows.h>

#include<math.h>

#include <stdio.h>

#define MAX 3

DOUBLE A[MAX][MAX];
INT N;

VOID Swap( DOUBLE *P, DOUBLE *P1 )
{
  INT i;

  i = *P;
  *P = *P1;
  *P1 = i;
}

DOUBLE Gaus( VOID )
{
  DOUBLE det;
  INT i, max_row, max_col, y, x, q, mult, k; 

  det = 1.0;
  for (i = 0; i < N; i++)
  {
    /* look for maximum matrix element -> j row k column */
    max_row = max_col = i;
    for (y = i; y < N; y++)
      for (x = i; x < N; x++)
        if (fabs(A[y][x]) > fabs(A[max_row][max_col]))
          max_col = x, max_row = y;
    if (A[max_row][max_col] == 0)
    {
      det = 0.0;
      break;
    }

    if (max_row != i)
    {
      /* Swap max_row row and i row (elements [i..N-1]) */
      for (x = i; x < N; x++)
        Swap(&A[i][x], &A[max_row][x]);
      det = -det;
    }
    if (max_col != i)
    {
      /* Swap max_col column and i column (elements [0..N-1]) */
      for (y = i; y < N; y++)
        Swap(&A[y][i],&A[y][max_col]);
      det = -det;
    }

    /* Subtrack from every row j:[i+1..N-1] i row multiplied by A[j][i] / A[i][i] */  
    for(q = i + 1; q < N; q++)
    {
      mult = A[q][i] / A[i][i];
      for(k = i; k < N; k++)
         A[k][q] -= mult * A[k][i];
    }
    det *= A[i][i];
  }
  return det;
}
/*fnLoadMatrix*/
BOOL LoadMatrix( CHAR *FileName )
{
  FILE *F;
  INT i, j;

  N = 0;
  F = fopen(FileName, "r");
  if (F == NULL)
    return FALSE;

  fscanf(F, "%d", &N);
  if (N > MAX)
    N = MAX;
  else
    if (N < 0)
      N = 0;

  for(i = 0; i < N; i ++)
    for(j = 0; j < N; j++)
      fscanf(F, "%lf", &A[i][j]);

  fclose(F);
  return TRUE;  
}

VOID main( VOID )
{
 if (LoadMatrix("m.txt"))
 {
    printf("%lf", Gaus());  
 }
 getchar();
 getchar();
}