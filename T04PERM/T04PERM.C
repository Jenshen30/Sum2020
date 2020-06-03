/* FILE NAME: T03CLOCK.C
 * PROGRAMMER: EK6
 * DATE: 02.06.2020
 * PURPOSE:
 */

#include <stdio.h>

#include <windows.h>

/* Permutation array */
#define MAX 5
INT P[MAX];
BOOL IsParity = 1;

/* Store permutation to log file function */
VOID Store( VOID )
{
  FILE *F;
  INT i;

  F = fopen("PERM.TXT", "a");
  if (F == NULL)
    return;

  for (i = 0; i < MAX - 1; i++)
    fprintf(F, "%d, ", P[i]);
  fprintf(F, "%d Ц parity: %s\n", P[MAX - 1], IsParity ? "even" : "odd");

  fclose(F);
} /* End of 'Store' function */

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


  
INT main( VOID )
{
 INT i;

 for(i = 0; i < MAX; i++)
 {
   P[i] = i;
 }
 Go(0);
}