/* FILE NAME: RNDDATA.C
 * PROGRAMMER: EK6
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 *          All constants and glodal arguments here.
*/
#include "rnd.h"

HWND EK6_hRndWnd;/* Work window handle */     
HDC EK6_hRndDC;/* Work window memory device context  */
HGLRC EK6_hRndGLRC; /* OpenGL rendering context*/
INT EK6_RndFrameW, EK6_RndFrameH; /* Work window size */


DBL
  EK6_RndProjSize,  /* Project plane fit square */
  EK6_RndProjDist,  /* Distance to project plane from viewer (near) */
  EK6_RndProjFarClip;  /* Distance to project far clip plane (far) */


MATR
  EK6_RndMatrView, /* View coordinate system matrix */
  EK6_RndMatrProj, /* Projection coordinate system matrix */
  EK6_RndMatrVP;   /* Stored (View * Proj) matrix */

/* END OF 'RNDDATA.C' FILE */