/* FILE NAME: GLOBE.C
* PROGRAMMER: EK6
* DATE: 04.06.2020
*/
#include <stdio.h>
#include <windows.h>

#include "globe.h"
#include "mth.h"

/* Window class name */
#define WND_CLASS_NAME "My Window Class Name"

/* Forward declaration */
LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
VOID FlipFullscrean( HWND hWnd );

/* The main program function */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT CmdShow )
{
  HWND hWnd;
  MSG msg;
  WNDCLASS wc;

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
  hWnd = CreateWindow(WND_CLASS_NAME, "CGSG Primary Practice Group First Window",
    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
    NULL, NULL, hInstance, NULL);

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

/* Toggle fullscrean mode function */
VOID FlipFullScreen( HWND hWnd )
{
  static BOOL IsFullScreen = FALSE;
  static RECT SaveRect;

  if (!IsFullScreen)
  {
    HMONITOR hmon;
    MONITORINFO moninfo;
    RECT rc;

    /* Goto fullscreen mode */
    GetWindowRect(hWnd, &SaveRect);

    /* Get nearest monitor */
    hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

    /* Get monitor information */
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, &moninfo);

    rc = moninfo.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);
    SetWindowPos(hWnd, HWND_TOP,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
  }
  else
  {
    /* Restore window size and position */
    SetWindowPos(hWnd, HWND_TOP, SaveRect.left, SaveRect.top, 
      SaveRect.right - SaveRect.left, SaveRect.bottom - SaveRect.top, 
      SWP_NOOWNERZORDER);
  }
  IsFullScreen = !IsFullScreen;
}

/* Main window handle function */
LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  RECT rc;
  static BITMAP bm;
  static HDC hMemDCFrame;
  static HBITMAP hBmFrame;
  static INT w, h;
  static CHAR Buf[100];

  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    ((MINMAXINFO *)lParam)->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) + GetSystemMetrics(SM_CYCAPTION) + 2 * GetSystemMetrics(SM_CYBORDER);
    return 0;
  case WM_CREATE:
    GLB_TimerInit();
    SetTimer(hWnd, 30, 1, NULL);
    hDC = GetDC(hWnd);
    hMemDCFrame = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    hBmFrame = NULL;
    return 0;
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);

    if (hBmFrame != NULL)
      DeleteObject(hBmFrame);
    hDC = GetDC(hWnd);
    hBmFrame = CreateCompatibleBitmap(hDC, w, h);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDCFrame, hBmFrame);

    GlobeSet(w / 2, h / 2, (w < h ? w : h) * 0.8 / 2);
    SendMessage(hWnd, WM_TIMER, 0, 0);

    return 0;
  case WM_SYSKEYDOWN:
    if ( wParam == VK_RETURN)
      FlipFullScreen(hWnd);
    return 0;
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    else if (wParam == 'P')
      GLB_IsPause = !GLB_IsPause; 
    return 0;
  case WM_TIMER:
    rc.left = 0;
    rc.bottom = h; 
    rc.right = w;
    rc.top = 0;

    GLB_TimerResponse();
    InvalidateRect(hWnd, NULL, FALSE);
    /* Clear Background */
    SelectObject(hMemDCFrame, GetStockObject(WHITE_BRUSH));
    SelectObject(hMemDCFrame, GetStockObject(NULL_PEN));
    Rectangle(hMemDCFrame, 0, 0, w + 1, h + 1);

    m = MatrIdentity();
    GlobeDraw(hMemDCFrame);
    DrawText(hMemDCFrame, Buf, sprintf(Buf, "FPS: %.5f", GLB_FPS), &rc, DT_CENTER | DT_TOP);


    InvalidateRect(hWnd, NULL, FALSE);
    
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);

    BitBlt(hDC, 0, 0, w, h, hMemDCFrame, 0, 0, SRCCOPY); 
    EndPaint(hWnd, &ps);
    return 0;
  case WM_CLOSE:
    if (MessageBox(hWnd, "Are you sure you want to close window?", "Close",
          MB_YESNO | MB_DEFBUTTON2 | MB_ICONQUESTION) == IDYES)
      DestroyWindow(hWnd);
    return 0;
  case WM_DESTROY:
    if (hBmFrame != 0)
      DeleteObject(hBmFrame);
    DeleteDC(hMemDCFrame);

    KillTimer(hWnd, 30);
    PostMessage(hWnd, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'WinFunc' function */

/* End of 'T07GLOBE.c' file */