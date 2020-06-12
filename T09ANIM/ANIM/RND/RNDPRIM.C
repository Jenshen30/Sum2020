/* FILE NAME: RNDPRIM.C
 * PROGRAMMER: EK6
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 *          All primitives here and so on.
*/
#include <string.h>
#include <stdio.h>

#include "rnd.h"

VOID EK6_RndPrimCreate( ek6PRIM *Pr, ek6VERTEX *V, INT NumOfV, INT *I, INT NumOfI )
{

  memset(Pr, 0, sizeof(ek6PRIM));


  if (V != NULL)
  {
    /*Generate buffers*/
    glGenBuffers(1, &Pr->VBuf);
    glGenVertexArrays(1, &Pr->VA);

    /* Fill array and buf */
    glBindVertexArray(Pr->VA);
    glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ek6VERTEX) * NumOfV, V, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);

    /*                    layout (номер атрибута),
    *                       количество компонент,
    *                          тип,
    *                                   надо ли нормировать,
    *                                       размер в байтах одного элемента буфера (stride),
    *                                                  смещение в байтах до начала данных */
    glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(ek6VERTEX),
                      (VOID *)0); /* pozition */
    glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(ek6VERTEX),
                      (VOID *)sizeof(VEC)); /* texture coords */
    glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(ek6VERTEX),
                      (VOID *)(sizeof(VEC) + sizeof(VEC2))); /* normale */
    glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(ek6VERTEX),
                      (VOID *)(sizeof(VEC) * 2 + sizeof(VEC2))); /* color*/

    /* turn on atributes (layout) */
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    /* turn on vertex massive */
    glBindVertexArray(0);
  }
  if (I != NULL)
  {
    /* doing active buffers*/
    glGenBuffers(1, &Pr->IBuf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf); 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NumOfI, I, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    Pr->NumOfElements = NumOfI;
  }
  else
    Pr->NumOfElements = NumOfV;

  Pr->Trans = MatrIdentity();
}/*End of 'EK6_RndPrimCreate' fn*/


VOID EK6_RndPrimFree( ek6PRIM *Pr )
{
  if (Pr->VA != 0)
  {
    /* Able vertex array */
    glBindVertexArray(Pr->VA);
    /* Distroy buff */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &Pr->VBuf);
    /* Disable vertex array */
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &Pr->VA);
  }
  if (Pr->IBuf != 0)
     glDeleteBuffers(1, &Pr->IBuf);
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
  INT loc;
  
  /* Send matrix to OpenGL /v.1.0 */
  glLoadMatrixf(wvp.A[0]);

  glUseProgram(EK6_RndProgId);
  if ((loc = glGetUniformLocation(EK6_RndProgId, "MatrWVP")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, wvp.A[0]);
  /* Draw triangles */
  if (Pr->IBuf != 0)
  {
    /* doing active vertex mass */
    glBindVertexArray(Pr->VA);
    /* doing active indexes mass */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    /* painting */
    glDrawElements(GL_TRIANGLES, Pr->NumOfElements, GL_UNSIGNED_INT, NULL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    /* turn off vertex mass */
    glBindVertexArray(0);
  }
  else
  {
    glBindVertexArray(Pr->VA);
    glDrawArrays(GL_TRIANGLES, 0, Pr->NumOfElements);
    glBindVertexArray(0);
  }
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
  INT i, j, k, f, noofv, noofi, size;
  DBL theta, phi;
  ek6VERTEX *V;
  INT *Ind;
  
  memset(Pr, 0, sizeof(ek6PRIM));
  noofv = SplitW * SplitH;
  noofi = (SplitH - 1) * (SplitW - 1) * 6;
  size = sizeof(ek6VERTEX) * noofv + sizeof(INT) * noofi;

  ///if ((V = malloc(size)) == NULL)
    ///return FALSE;
  V = malloc(size);
  Ind = (INT *)(V + noofv);

  k = 0;
  for (i = 0, theta = 0; i < SplitH; i++, theta += PI / (SplitH - 1))
    for (j = 0, phi = 0; j < SplitW; j++, phi += 2 * PI / (SplitW - 1))
    {
      V[k].P.X = C.X + R * sin(theta) * sin(phi);
      V[k].P.Y = C.Y + R * cos(theta);
      V[k].P.Z = C.Z + R * sin(theta) * cos(phi);
      k++;
    }
  k = 0;
  for (i = 0; i < SplitH - 1; i++)
    for (j = 0; j < SplitW - 1; j++)
    {
      Ind[k++] = i * SplitW + j;
      Ind[k++] = i * SplitW + j + 1;
      Ind[k++] = (i + 1) * SplitW + j;

      Ind[k++] = (i + 1) * SplitW + j + 1;
      Ind[k++] = (i + 1) * SplitW + j;
      Ind[k++] = i * SplitW + j + 1;

    }

  EK6_RndPrimCreate(Pr, V, noofv, Ind, noofi);
    ///return FALSE;
   /// return TRUE;
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
  INT nv = 0, nf = 0, size;
  ek6VERTEX *V;
  INT *Ind;
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
  size = sizeof(ek6VERTEX) * nv + sizeof(INT) * (nf * 3);

  if ((V = malloc(size)) == NULL)
    return FALSE;
  Ind = (INT *)(V + nv);

  /* Load geometry data */
  rewind(F);
  nv = 0;
  nf = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;

      sscanf(Buf + 2, "%lf %lf %lf", &x, &y, &z);
      V[nv++].P = VecSet(k * x + delta * 0,k * y + delta,k * z + delta * 0);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n1, n2, n3;

      sscanf(Buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d//%*d %d//%*d %d//%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d/%*d %d/%*d %d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d %d %d", &n1, &n2, &n3) == 3;
      Ind[nf++] = n1 - 1;
      Ind[nf++] = n2 - 1;
      Ind[nf++] = n3 - 1;
    }

    EK6_RndPrimCreate(Pr, V, nv, Ind, nf);

    fclose(F);
    return TRUE;
} /* End of 'EK6_RndPrimCreateCone' function */

/* END OF 'RNDPRIM.C' FILE */