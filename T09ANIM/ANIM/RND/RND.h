/* FILE NAME: RND.H
 * PROGRAMMER: EK6
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 *          Render system declaration module.
 */


#ifndef __RND_H_
#define __RND_H_

#define GLEW_STATIC

#include "glew.h"
#include <gl/gl.h>

#include "../../def.h"


extern HWND EK6_hRndWnd;        /* Work window handle */
extern HDC EK6_hRndDC;     /* Work window memory device context  */
extern HGLRC EK6_hRndGLRC;
extern INT EK6_RndFrameW, EK6_RndFrameH;/* Work window size */

extern DBL
  EK6_RndProjSize,  /* Project plane fit square */
  EK6_RndProjDist,  /* Distance to project plane from viewer (near) */
  EK6_RndProjFarClip;  /* Distance to project far clip plane (far) */

MATR
  EK6_RndMatrView, /* View coordinate system matrix */
  EK6_RndMatrProj, /* Projection coordinate system matrix */
  EK6_RndMatrVP;   /* Stored (View * Proj) matrix */

VOID EK6_RndInit( HWND hWnd );
VOID EK6_RndClose( VOID );
VOID EK6_RndResize( INT W, INT H );
VOID EK6_RndCopyFrame( VOID );
VOID EK6_RndStart( VOID );
VOID EK6_RndProjSet( VOID );
VOID EK6_RndCamSet( VEC Loc, VEC At, VEC Up );
VOID EK6_RndEnd( VOID );

typedef struct tagek6VERTEX
{
  VEC P;  /* Vertex position */
} ek6VERTEX;

typedef struct tagek6PRIM
{
  ek6VERTEX *V; /* Vertex attributes array */
  INT NumOfV;   /* Number of vertices */

  INT *I;       /* Index array (for trimesh – by 3 ones) */
  INT NumOfI;   /* Number of indices */

  MATR Trans;   /* Additional transformation matrix */
} ek6PRIM;

BOOL EK6_RndPrimCreate( ek6PRIM *Pr, INT NoofV, INT NoofI );
VOID EK6_RndPrimFree( ek6PRIM *Pr );
VOID EK6_RndPrimDraw( ek6PRIM *Pr, MATR World );
VOID EK6_RndPrimCreateSphere( ek6PRIM *Pr, VEC C, DBL R, INT SplitW, INT SplitH );
BOOL EK6_RndPrimLoad( ek6PRIM *Pr, CHAR *FileName, FLT k, FLT delta );
//VOID EK6_RndEnd( VOID );
#endif /* __RND_H_ */

/* END OF 'RND.H' FILE */