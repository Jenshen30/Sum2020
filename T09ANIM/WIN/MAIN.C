/* FILE NAME: MAIN.C
 * PROGRAMMER: EK6
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 *          WinAPI start module.
 */

#include <stdio.h>
//#include <time.h>

//#include "../def.h"
//#include "../anim/rnd/rnd.h"
#include "../units.h"

/* Window class name */
#define WND_CLASS_NAME "My Window Class Name"

/*Forward declaration*/
LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT CmdShow )
{
  HWND hWnd;
  MSG msg;
  WNDCLASS wc;
  INT i;

  /* Fill window class structure */
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.hInstance = hInstance;
  wc.lpszClassName = WND_CLASS_NAME;
  wc.lpszMenuName = NULL;
  wc.lpfnWndProc = WinFunc;

  /* Register window class */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error regoister window class", "Error", MB_OK | MB_ICONERROR);
    return 0;
  }

  /* Window creation */
  hWnd = CreateWindow(WND_CLASS_NAME, "CGSG Primary Practice Group Window",
    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
    NULL, NULL, hInstance, NULL);

  /*Add unit samples*/

  ShowWindow(hWnd, CmdShow);
  EK6_AnimAddUnit(EK6_UnitCreateBall());

  ///for (i = 0; i < 2; i++)
    EK6_AnimAddUnit(EK6_UnitCreateBall());
  EK6_AnimAddUnit(EK6_UnitCreateControl());

  /* Message loop */
  while (TRUE)
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      DispatchMessage(&msg);
    }
    else
      SendMessage(hWnd, WM_TIMER, 47, 0);

  return 30;
} /* End of 'WinMain' function */

LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  PAINTSTRUCT ps;
  HDC hDC;
  static ek6PRIM wf, Pr, Lm;

  switch (Msg)
  {
  case WM_GETMINMAXINFO:
     ((MINMAXINFO *)lParam)->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) + GetSystemMetrics(SM_CYCAPTION) + 2 * GetSystemMetrics(SM_CYBORDER);
    return 0;
  case WM_CREATE:
    EK6_AnimInit(hWnd);
    //EK6_RndPrimCreateSphere(&Pr, VecSet(0.2, 0.5, 0.2), 1.3, 50, 50);
    EK6_RndPrimLoad(&wf, "WOLF.obj", 0.01, -0.5);
    //EK6_RndPrimLoad(&Lm, "LEGO_Man.obj", 0.1, 2);//
    SetTimer(hWnd, 30, 0, NULL);
    return 0;
  case WM_MOUSEWHEEL:
    EK6_MouseWheel += (SHORT)HIWORD(wParam);
    return 0;
  ///case WM_LBUTTONDOWN:
    ///SetCapture(hWnd);
    ///return 0;
/// case WM_LBUTTONUP:
   /// ReleaseCapture();
    ///return 0;
  case WM_SIZE:
    EK6_AnimResize(LOWORD(lParam), HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 47, 0);
    EK6_AnimCopyFrame();
    return 0;
  case WM_TIMER:
    /*painting stage*/
     EK6_AnimRender();
     //EK6_RndPrimDraw(&Pr, MatrRotateY(clock() / 200.0));
     EK6_RndPrimDraw(&wf, MatrRotateY(- sin(EK6_Anim.GlobalTime) / 200.0));
     //EK6_RndPrimDraw(&Lm, MatrRotateX(clock() / 300.0));//
     //EK6_RndEnd();
     ///InvalidateRect(hWnd, NULL, FALSE);
     hDC = GetDC(hWnd);
     EK6_AnimCopyFrame();
     /*InvalidateRect(hWnd, NULL, FALSE);*/
     return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps); 
    EK6_AnimCopyFrame();   
    EndPaint(hWnd, &ps);  
    return 0;
  case WM_DESTROY:
    //EK6_RndPrimFree(&Pr);
    EK6_RndPrimFree(&wf);
    //EK6_RndPrimFree(&Lm);
    //EK6_RndClose();

    EK6_AnimClose();
    KillTimer(hWnd, 47);
    PostQuitMessage(30);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'WinFunc' function */

/*End of 'MAIN.C' file*/