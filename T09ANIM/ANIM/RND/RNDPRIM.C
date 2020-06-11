/* FILE NAME: RNDPRIM.C
 * PROGRAMMER: EK6
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 *          All primitives here and so on.
*/
#include <string.h>
#include <stdio.h>

#include "rnd.h"

BOOL EK6_RndPrimCreate( ek6PRIM *Pr, INT NoofV, INT NoofI )
{
  INT size;

  memset(Pr, 0, sizeof(ek6PRIM));
  size = sizeof(ek6VERTEX) * NoofV + sizeof(INT) * NoofI;

  if ((Pr->V = malloc(size)) == NULL)
    return FALSE;
  Pr->I = (INT *)(Pr->V + NoofV);
  Pr->NumOfV = NoofV;
  Pr->NumOfI = NoofI;
  Pr->Trans = MatrIdentity();
  memset(Pr->V, 0, size);

  return TRUE;
}/*End of 'EK6_RndPrimCreate' fn*/


VOID EK6_RndPrimFree( ek6PRIM *Pr )
{
  if (Pr->V != NULL)
    free(Pr->V);
  memset(Pr, 0, sizeof(ek6PRIM));
}/*End of 'EK6_RndPrimFree' fn*/


/* Drawing primitives function.
 * ARGUMENTS:
 *   - pointer to primitive to be build:
 *       ek6PRIM *Pr;
 *   - matrix of WORLD:
 *       MATR World;
 * RETURNS:
 *   (VOID) None.
*/
VOID EK6_RndPrimDraw( ek6PRIM *Pr, MATR World )
{
  MATR wvp = MatrMulMatr3(Pr->Trans, World, EK6_RndMatrVP);
  INT i;
  
  /* Send matrix to OpenGL /v.1.0 */
  glLoadMatrixf(wvp.A[0]);

  /* Draw triangles */
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); ///!!!
  glBegin(GL_TRIANGLES);
  for (i = 0; i < Pr->NumOfI; i++)
  {
    glColor3d(100, 30, 100);
    glVertex3fv(&Pr->V[Pr->I[i]].P.X);
  }
  glEnd();
  
}/*End of 'EK6_RndPrimDraw' fn*/


/*  Special function for filling the Sphere_matrix of coords and matrix of Number of Indexes.
 * ARGUMENTS:
 *   - pointer to primitive to be build:
 *       ek6PRIM *Pr;
 *   - the coords of center:
 *       VEC C;
 *   - radius:
 *       DBL R;
 *   - Numbers of vertex
 *       INT SplitW, SplitH;
 * RETURNS:
 *   (VOID) None.
*/
VOID EK6_RndPrimCreateSphere( ek6PRIM *Pr, VEC C, DBL R, INT SplitW, INT SplitH )
{
  INT i, j, k;
  DBL theta, phi;
  
  EK6_RndPrimCreate(Pr, SplitW * SplitH, (SplitH - 1) * (SplitW - 1) * 6);

  k = 0;
  for (i = 0, theta = 0; i < SplitH; i++, theta += PI / (SplitH - 1))
    for (j = 0, phi = 0; j < SplitW; j++, phi += 2 * PI / (SplitW - 1))
    {
      Pr->V[k].P.X = C.X + R * sin(theta) * sin(phi);
      Pr->V[k].P.Y = C.Y + R * cos(theta);
      Pr->V[k].P.Z = C.Z + R * sin(theta) * cos(phi);
      k++;
    }
  k = 0;
  for (i = 0; i < SplitH - 1; i++)
    for (j = 0; j < SplitW - 1; j++)
    {
      Pr->I[k++] = i * SplitW + j;
      Pr->I[k++] = i * SplitW + j + 1;
      Pr->I[k++] = (i + 1) * SplitW + j;

      Pr->I[k++] = (i + 1) * SplitW + j + 1;
      Pr->I[k++] = (i + 1) * SplitW + j;
      Pr->I[k++] = i * SplitW + j + 1;

    }
}/*End of 'EK6_RndPrimCreateSphere' fn*/


/* Load primitive from .OBJ file function.
 * ARGUMENTS:
 *   - pointer to primitive to be build:
 *       ek6PRIM *Pr;
 *   - .OBJ file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE is successful, FALSE otherwise.
 */
BOOL EK6_RndPrimLoad( ek6PRIM *Pr, CHAR *FileName, FLT k, FLT delta ) //FLT param is extra. 
{
  FILE *F;
  INT nv = 0, nf = 0;
  static CHAR Buf[1000];

  memset(Pr, 0, sizeof(ek6PRIM));

  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Vertex and factes count */
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
      nf++;

  if (!EK6_RndPrimCreate(Pr, nv, nf * 3))
  {
    fclose(F);
    return FALSE;
  }

  /* Load geometry data */
  rewind(F);
  nv = 0;
  nf = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;

      sscanf(Buf + 2, "%lf %lf %lf", &x, &y, &z);
      Pr->V[nv++].P = VecSet(k * x + delta * 0,k * y + delta,k * z + delta * 0);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n1, n2, n3;

      sscanf(Buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d//%*d %d//%*d %d//%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d/%*d %d/%*d %d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d %d %d", &n1, &n2, &n3) == 3;
      Pr->I[nf++] = n1 - 1;
      Pr->I[nf++] = n2 - 1;
      Pr->I[nf++] = n3 - 1;
    }


  fclose(F);
  return TRUE;
} /* End of 'EK6_RndPrimCreateCone' function */

/* END OF 'RNDPRIM.C' FILE */