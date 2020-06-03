/*FILE NAME: T05DET.C
* PROGRAMER: EK6
* DATE: 03.06.2020
*/

#include <windows.h>

#include <stdio.h>

#define MAX 3

DOUBLE A[MAX][MAX];
INT N;

INT P[MAX];
BOOL IsParity = 1;
DOUBLE Determinant;

VOID Store( VOID )
{
  DOUBLE prod = 1;
  INT i;

  for(i = 0; i < N; i++)
      prod *= A[i][P[i]];
  Determinant += (IsParity ? 1 : -1) * prod;
}
/*fnPermutation for i elements*/
VOID Swap( INT *P, INT *P1 )
{
  INT i;

  i = *P;
  *P = *P1;
  *P1 = i;
}

VOID Go( INT Pos )
{
  INT i, x;
  BOOL SaveParity;

  if (Pos == MAX)
    Store();
  else
  {
    SaveParity = IsParity; 
    Go(Pos + 1);
    for (i = Pos + 1; i < MAX; i++)
    {
      /* ставим на позицию Pos по очереди каждый i-й элемент */
      Swap(&P[Pos], &P[i]);
      IsParity = !IsParity;
      Go(Pos + 1); 
    }
    x = P[Pos];
    for(i = Pos + 1; i < MAX; i++)
    {
      P[i - 1] = P[i];
    }
    P[MAX - 1] = x;
    IsParity = SaveParity;
  }
}

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
  INT i;

  if (LoadMatrix("m.txt"))
  {
    for(i = 0; i < N; i++)
      P[i] = i;
  
    Go(0);
    printf("%lf", Determinant);
    getchar();
    getchar();
  }
}

