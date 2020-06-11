/* FILE NAME: RNDBASE.C
 * PROGRAMMER: EK6
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 *          Render system declaration module.
*/

#include "rnd.h"

/*link libraryes*/
#pragma comment(lib, "opengl32")

/* Inicialization of render system function.
 * ARGUMENTS:
 *         - main window handle
 *         HWND hWnd;
 * RETURNS:
 *   (VOID) None.
*/
VOID EK6_RndInit( HWND hWnd )
{
  PIXELFORMATDESCRIPTOR pfd = {0};
  INT i;

  /* Store window handle */
  EK6_hRndWnd = hWnd;
  /* Obtain work window device context */
  EK6_hRndDC = GetDC(hWnd);
  /* OpenGL initialization */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32; 

  i = ChoosePixelFormat(EK6_hRndDC, &pfd);
  DescribePixelFormat(EK6_hRndDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(EK6_hRndDC, i, &pfd);

  /* OpenGL init: setup rendering context */
  EK6_hRndGLRC = wglCreateContext(EK6_hRndDC);
  wglMakeCurrent(EK6_hRndDC, EK6_hRndGLRC);

  if (glewInit() != GLEW_OK ||
        !(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
  {
    MessageBox(NULL, "Error OpenGL initialization", "Error", 
      MB_OK | MB_ICONERROR);
    exit(0);
  }
  glClearColor(0.3, 0.4, 0.5, 1);
  glEnable(GL_DEPTH_TEST);

  /* Set default render parameters*/
  EK6_RndFrameW = 45;
  EK6_RndFrameH = 45;
  EK6_RndProjSize = 0.1;
  EK6_RndProjDist = 0.1;
  EK6_RndProjFarClip = 300;

  EK6_RndProjSet();
  EK6_RndCamSet(VecSet(-4, 1, 1), VecSet(1, 1, -1), VecSet(-1, 1, 1));
}/* End of 'EK6_RndInit' fn*/


/* Killing render system function.
 * ARGUMENTS:
 *         None
 * RETURNS:
 *   (VOID) None.
*/
VOID EK6_RndClose( VOID )
{
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(EK6_hRndGLRC);
  ReleaseDC(EK6_hRndWnd, EK6_hRndDC);  
}/* End of 'EK6_RndClose' fn*/


/* Resizing elements fn.
 * ARGUMENTS:
 *         - coords
 *         INT W, H;
 * RETURNS:
 *   (VOID) None.
*/
VOID EK6_RndResize( INT W, INT H )
{
 /*Set OpenGL viewport*/
  glViewport(0, 0, W, H);
  /* Saving size */
  EK6_RndFrameW = W;
  EK6_RndFrameH = H;

  /* recounting projection*/
  EK6_RndProjSet();
}/* End of 'EK6_RndResize' fn*/


/* Double buffering fn.
 * ARGUMENTS:
 *         - None
 * RETURNS:
 *   (VOID) None.
*/
VOID EK6_RndCopyFrame( VOID )
{
  ///SwapBuffers(EK6_hRndDC);
  wglSwapLayerBuffers(EK6_hRndDC, WGL_SWAP_MAIN_PLANE);
}/* End of 'EK6_RndCopyFrame' fn*/


/* Sterting rendering process fn.
 * ARGUMENTS:
 *         - None
 * RETURNS:
 *   (VOID) None.
*/
VOID EK6_RndStart( VOID )
{

  /* Clear Background */
  glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
  /*Set draw parameters*/
}/* End of 'EK6_RndResize' fn*/


/* Projecting function.
 * ARGUMENTS:
 *         None
 * RETURNS:
 *   (VOID) None.
*/
VOID EK6_RndProjSet( VOID )
{
  DBL rx, ry;

  rx = ry = EK6_RndProjSize;

  /* Correct aspect ration */
  if (EK6_RndFrameW > EK6_RndFrameH)
    rx *= (DBL)EK6_RndFrameW / EK6_RndFrameH;
  else
    ry *= (DBL)EK6_RndFrameH / EK6_RndFrameW;


  EK6_RndMatrProj =
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
      EK6_RndProjDist, EK6_RndProjFarClip);
  EK6_RndMatrVP = MatrMulMatr(EK6_RndMatrView, EK6_RndMatrProj);
}/* End of 'EK6_RndProjSet' fn */


/* Setup camera view fn.
 * ARGUMENTS:
 *         - Vectors
 *         VEC Loc, At, Up; 
 * RETURNS:
 *   (VOID) None.
*/
VOID EK6_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  EK6_RndMatrView = MatrView(Loc, At, Up);
  EK6_RndMatrVP = MatrMulMatr(EK6_RndMatrView, EK6_RndMatrProj);
}/* End of 'EK6_RndCamSet' fn */

VOID EK6_RndEnd( VOID )
{
  glFinish();
}

/* END OF 'RNDBASE.C' FILE */