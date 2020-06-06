/* FILE NAME: MTH.H
 * PROGRAMMER: EK6
 * DATE: 05.06.2020
 * PURPOSE: 3D math implementation module.
 */

#ifndef __MTH_H_
#define __MTH_H_

#include <math.h>
#include <windows.h>

/* Pi math constant */
#define PI 3.14159265358979323846

/* Degrees to radians conversion */
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)

/* Base float point types */
typedef double DBL;
typedef double FLT;

/* Space vector/point representation type */
typedef struct tagVEC
{
  DBL X, Y, Z; /* Vector coordinates */
} VEC;

typedef struct tagMATR
{
  DBL A[4][4];/*Matrix elements*/
} MATR;         

/* Add two vectors function.
 * ARGUMENTS:
 *   - vectors to be add:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */

/* VEC creation function.
 * ARGUMENTS:
 *   - coordinates of vector:
 *       DBL X, DBL Y, DBL Z;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecSet( DBL X, DBL Y, DBL Z )
{
  VEC v = {X, Y, Z};

  return v;
} /* End of 'VecSet' function */


__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
} /* End of 'VecAddVec' function */


/*  Subsract two vectors function.
 * ARGUMENTS:
 *   - vectors to be subsract:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z );
}/*End of 'VecSubVec' fn*/


/*  Multiplly vector and nubmer function.
 * ARGUMENTS:
 *   - vector to be multipllied with number:
 *       VEC V1, DBL N;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecMulVec( VEC V1, DBL N )
{
  return VecSet(V1.X * N, V1.Y * N, V1.Z * N);
} /*End of 'VecMulVec' fn*/


/*  Divide vector and nubmer function.
 * ARGUMENTS:
 *   - vector to be divided with number:
 *       VEC V1, DBL N;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecDivNum( VEC V1, DBL N )
{
  return VecSet(V1.X / N, V1.Y / N, V1.Z / N );
}/*End of 'VecDivNum' fn*/


/* Negate vector function.
 * ARGUMENTS:
 *   - vector to be Negate :
 *       VEC V1;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecNeg( VEC V )               
{
  return VecSet(-V.X, -V.Y, -V.Z);
}/*End of 'VecNeg' fn*/


/*  Dot product two vectors function.
 * ARGUMENTS:
 *   - vectors to be dot producted:
 *       VEC V1, V2;
 * RETURNS:
 *   (INT) result value.
 */
__inline DBL VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
}/*End of 'VecDotVec' fn*/


/*  Cross product two vectors function.
  * ARGUMENTS:
  *   - vectors to be cross producted:
  *       VEC V1, V2;
  * RETURNS:
  *   (VEC) result vector.
*/
__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z  - V1.Z * V2.Y,
                V1.Z * V2.X  - V1.X * V2.Z,
                V1.X * V2.Y  - V1.Y * V2.X);
}/*End of 'VecCrossVec' fn*/


/*  Vector len in square function.
  * ARGUMENTS:
  *   - vector to find out the len in square:
  *       VEC V;
  * RETURNS:
  *   (INT) result value.
*/
__inline DBL VecLen2( VEC V )
{
  return VecDotVec(V, V);  
}/*End of 'VecLen2' fn*/


/*  Vector len function.
  * ARGUMENTS:
  *   - vector to find out the len:
  *       VEC V;
  * RETURNS:
  *   (INT) result value.
*/
__inline DBL VecLen( VEC V )
{
  DBL len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return len;
  return sqrt(len);
}/*End of 'VecLen' fn*/


/*  Vector normalize function.
  * ARGUMENTS:
  *   - vector to normalize:
  *       VEC V;
  * RETURNS:
  *   (VEC) result vector.
*/
__inline VEC VecNormalize( VEC V )
{
  DBL len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return V;
  len = sqrt(len);
  return VecDivNum(V, len);
}/*End of 'VecNormalize' fn*/


/*  Vector by marix multiplication (only orientation) function.
  * ARGUMENTS:
  *   - source vector:
  *       VEC V;
  *   - multiplied matrix
  *       MATR M;
  * RETURNS:
  *   (VEC) result vector.
*/
__inline VEC VectorTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0],
                V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1],
                V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2]);
}/*End of 'VectorTransform' fn*/


/*  Vector by marix multiplication and divizion by last string of matrix function.
  * ARGUMENTS:
  *   - source vector:
  *       VEC V;
  *   - multiplied matrix
  *       MATR M;
  * RETURNS:
  *   (VEC) result vector.
*/
__inline VEC VecMulMatr( VEC V, MATR M )
{                                              
  DBL w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3];

  return VecSet((V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0]) / w,
                (V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1]) / w,
                (V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]) / w);
}/*End of 'VecMulMatr' fn*/

/*Init of UnitMatrix*/
static MATR UnitMatrix = 
{                                     
  {                
    {1, 0, 0, 0},  
    {0, 1, 0, 0},  
    {0, 0, 1, 0},  
    {0, 0, 0, 1}   
  }                
};


/* fn return UnitMatrix.   
  * ARGUMENTS:
  *   - none
  * RETURNS:
  *   (MATR) result UnitMatrix.
*/
__inline MATR MatrIdentity( VOID )
{
  return UnitMatrix;
}/*End of 'MatrIdentity' fn*/


/* Vector to translate (Athenian transformation)    
  * ARGUMENTS:
  *   - vector:
  *       VEC V;(coefficients)
  * RETURNS:
  *   (MATR) result matrix.
*/
__inline MATR MatrTranslate( VEC T )
{
  MATR m =
  {
    {
      {1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {T.X, T.Y, T.Z, 1}
    }
  };

  return m;
}/*End of 'MatrTranslate' fn*/


/* Vector to scale (Athenian transformation)    
  * ARGUMENTS:
  *   - vector:
  *       VEC S;(coefficients)
  * RETURNS:
  *   (MATR) result matrix.
*/
__inline MATR MatrScale( VEC S )
{
  MATR m =
  {
    {
      {S.X, 0, 0, 0},
      {0, S.Y, 0, 0},
      {0, 0, S.Z, 0},
      {0, 0, 0, 1}
    }
  };

  return m;
}/*End of 'MatrScale' fn*/


/* Vector to rotate when X = const (Athenian transformation)    
  * ARGUMENTS:
  *   - Angle:
  *       DBL AngleInDegree;
  * RETURNS:
  *   (MATR) result matrix.
*/
__inline MATR MatrRotateX( DBL AngleInDegree )
{
  DBL
    a = D2R(AngleInDegree),
    c = cos(a),
    s = sin(a);
  MATR m =
  {
    {
      {1, 0, 0, 0},
      {0, c, s, 0},
      {0, -s, c, 0},
      {0, 0, 0, 1}
    }
  };

  return m;
}/*End of 'MatrRotateX' fn*/


/* Vector to rotate when Y = const (Athenian transformation)    
  * ARGUMENTS:
  *   - Angle:
  *       DBL AngleInDegree;
  * RETURNS:
  *   (MATR) result matrix.
*/
__inline MATR MatrRotateY( DBL AngleInDegree )
{
  DBL
    a = D2R(AngleInDegree),
    c = cos(a),
    s = sin(a);
  MATR m =
  {
    {
      {c, 0, -s, 0},
      {0, 1, 0, 0},
      {s, 0, c, 0},
      {0, 0, 0, 1}
    }
  };

  return m;
}/*End of 'MatrRotateY' fn*/


/* Vector to rotate when Z = const (Athenian transformation)    
  * ARGUMENTS:
  *   - Angle:
  *       DBL AngleInDegree;
  * RETURNS:
  *   (MATR) result matrix.
*/
__inline MATR MatrRotateZ( DBL AngleInDegree )
{
  DBL
    a = D2R(AngleInDegree),
    c = cos(a),
    s = sin(a);
  MATR m =
  {
    {
      {c, s, 0, 0},
      {-s, c, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
    }
  };

  return m;
}/*End of 'MatrRotateZ' fn*/


/* Vector to rotate when Z = const (Athenian transformation)    
  * ARGUMENTS:
  *   - Angle:
  *       DBL AngleInDegree;
  * RETURNS:
  *   (MATR) result matrix.
*/
__inline MATR MatrRotate( DBL AngleInDegree, VEC V )
{
  DBL a = D2R(AngleInDegree), c = cos(a), s = sin(a);
  VEC A = VecNormalize(V);
  MATR m =
  {
    {
      {c + A.X * A.X * (1 - c), A.X * A.Y * (1 - c) - A.Z * s, A.X * A.Z * (1 - c) + A.Y * s, 0},
      {A.X * A.Y * (1 - c) + A.Z * s, A.Y * A.Y * (1 - c) + c, A.Y * A.Z * (1 - c) - A.X * s, 0},
      {A.X * A.Z * (1 - c) - A.Y * s, A.Y * A.Z * (1 - c) + A.X * s, c + A.Z * A.Z * (1 - c), 0},
      {0, 0, 0, 1}
    }
  };

  return m;
} /*End of 'MatrRotate' fn*/


/* Two matrix multiplication    
  * ARGUMENTS:
  *   - matrixs:
  *       MATR M1,
  *       MATR M2;
  * RETURNS:
  *   (MATR) result matrix.
*/
__inline MATR MatrMulMatr( MATR M1, MATR M2 ) 
{
  MATR r;
  INT i, j, k;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (r.A[i][j] = 0, k = 0; k < 4; k++)
        r.A[i][j] += M1.A[i][k] * M2.A[k][j];
  return r;
}/*End of 'MatrMulMatr' fn*/


/* Matrix determinate 3x3 fn.    
  * ARGUMENTS:
  *   - coords:
  *      DBL A11, DBL A12, DBL A13,
  *      DBL A21, DBL A22, DBL A23,
  *       DBL A31, DBL A32, DBL A33;
  * RETURNS:
  *   (DBL) result value.
*/
__inline DBL MatrDeterm3x3( DBL A11, DBL A12, DBL A13,
                   DBL A21, DBL A22, DBL A23,
                   DBL A31, DBL A32, DBL A33 )
{
  return A11 * A22 * A33 - A11 * A23 * A32 - A12 * A21 * A33 + 
         A12 * A23 * A31 + A13 * A21 * A32 - A13 * A22 * A31;
}/*End of 'MatrDeterm3x3' fn*/


/* Matrix determinate 4x4 fn.    
  * ARGUMENTS:
  *   - coords:
  *      DBL A11, DBL A12, DBL A13,
  *      DBL A21, DBL A22, DBL A23,
  *       DBL A31, DBL A32, DBL A33;
  * RETURNS:
  *   (DBL) result value.
*/
__inline DBL MatrDeterm( MATR M )
{
  return
    M.A[0][0] * MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                              M.A[2][1], M.A[2][2], M.A[2][3],
                              M.A[3][1], M.A[3][2], M.A[3][3]) +
    -M.A[0][1] * MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                               M.A[2][0], M.A[2][2], M.A[2][3],
                               M.A[3][0], M.A[3][2], M.A[3][3]) +
    M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                              M.A[2][0], M.A[2][1], M.A[2][3],
                              M.A[3][0], M.A[3][1], M.A[3][3]) +
    -M.A[0][3] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                               M.A[2][0], M.A[2][1], M.A[2][2],
                               M.A[3][0], M.A[3][1], M.A[3][2]);
}/*End of 'MatrDeterm' fn*/

/*  Matrix inverse fn   
  * ARGUMENTS:
  *   - matrixs:
  *       MATR M1,
  * RETURNS:
  *   (MATR) result matrix.
*/
__inline MATR MatrInverse( MATR M )
{
  MATR r;
  DBL det = MatrDeterm(M);

  if (det == 0)
    return UnitMatrix;

 /* build adjoint matrix */
  r.A[0][0] =
    MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                  M.A[2][1], M.A[2][2], M.A[2][3],
                  M.A[3][1], M.A[3][2], M.A[3][3]);
  r.A[1][0] =
    -MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                   M.A[2][0], M.A[2][2], M.A[2][3],
                   M.A[3][0], M.A[3][2], M.A[3][3]);
  r.A[2][0] =
    MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                  M.A[2][0], M.A[2][1], M.A[2][3],
                  M.A[3][0], M.A[3][1], M.A[3][3]);
  r.A[3][0] =
    -MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                   M.A[2][0], M.A[2][1], M.A[2][2],
                   M.A[3][0], M.A[3][1], M.A[3][2]);

  r.A[0][1] =
    MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                  M.A[2][1], M.A[2][2], M.A[2][3],
                  M.A[3][1], M.A[3][2], M.A[3][3]);
  r.A[1][1] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                   M.A[2][0], M.A[2][2], M.A[2][3],
                   M.A[3][0], M.A[3][2], M.A[3][3]);
  r.A[2][1] =
    MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                  M.A[2][0], M.A[2][1], M.A[2][3],
                  M.A[3][0], M.A[3][1], M.A[3][3]);
  r.A[3][1] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                   M.A[2][0], M.A[2][1], M.A[2][2],
                   M.A[3][0], M.A[3][1], M.A[3][2]);


  r.A[0][2] =
    MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                  M.A[1][1], M.A[1][2], M.A[1][3],
                  M.A[3][1], M.A[3][2], M.A[3][3]);
  r.A[1][2] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                   M.A[1][0], M.A[1][2], M.A[1][3],
                   M.A[3][0], M.A[3][2], M.A[3][3]);
  r.A[2][2] =
    MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                  M.A[1][0], M.A[1][1], M.A[1][3],
                  M.A[3][0], M.A[3][1], M.A[3][3]);
  r.A[3][2] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                   M.A[1][0], M.A[1][1], M.A[1][2],
                   M.A[3][0], M.A[3][1], M.A[3][2]);

  r.A[0][3] =
    MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                  M.A[1][1], M.A[1][2], M.A[1][3],
                  M.A[2][1], M.A[2][2], M.A[2][3]);
  r.A[1][3] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                   M.A[1][0], M.A[1][2], M.A[1][3],
                   M.A[2][0], M.A[2][2], M.A[2][3]);
  r.A[2][3] =
    MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                  M.A[1][0], M.A[1][1], M.A[1][3],
                  M.A[2][0], M.A[2][1], M.A[2][3]);
  r.A[3][3] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                   M.A[1][0], M.A[1][1], M.A[1][2],
                   M.A[2][0], M.A[2][1], M.A[2][2]);

  /* divizion by det */
  r.A[0][0] /= det;
  r.A[1][0] /= det;
  r.A[2][0] /= det;
  r.A[3][0] /= det;
  r.A[0][1] /= det;
  r.A[1][1] /= det;
  r.A[2][1] /= det;
  r.A[3][1] /= det;
  r.A[0][2] /= det;
  r.A[1][2] /= det;
  r.A[2][2] /= det;
  r.A[3][2] /= det;
  r.A[0][3] /= det;
  r.A[1][3] /= det;
  r.A[2][3] /= det;
  r.A[3][3] /= det;

  return r;
}/*End of 'MatrInverse' fn*/


/* Matrix look-at viewer setup function.
 * ARGUMENTS:
 *   - viewer position, look-at point, approximate up direction:
 *       VEC Loc, At, Up1;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC
    Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecCrossVec(Dir, Up1)),
    Up = VecNormalize(VecCrossVec(Right, Dir));
  MATR m =
  {
    {
      {Right.X, Up.X, -Dir.X, 0},
      {Right.Y, Up.Y, -Dir.Y, 0},
      {Right.Z, Up.Z, -Dir.Z, 0},
      {-VecDotVec(Loc, Right), -VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1}
    }
  };

  return m;
} /* End of 'MatrView' function */

#endif /* __MTH_H_ */

/* END OF 'MATH.H' FILE */
