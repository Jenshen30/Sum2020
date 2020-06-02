/* FILE NAME: T03CLOCK.C
 * PROGRAMMER: EK6
 * DATE: 02.06.2020
 * PURPOSE:
 */
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#define PI 3.14159265358979323846

/* Window class name */
#define WND_CLASS_NAME "My Window Class Name"

/* Forward declaration */
LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

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
    WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    NULL, NULL, hInstance, NULL);

  ShowWindow(hWnd, CmdShow);

  /* Message loop */
  while (GetMessage(&msg, NULL, 0, 0))
    DispatchMessage(&msg);

  return 30;
} /* End of 'WinMain' function */

VOID DrawHand( HDC hDC, INT X0, INT Y0, DOUBLE AngleInRadian, INT L, INT W, COLORREF Color )
{
  INT i;
  HPEN hPenOld;
  HBRUSH hBrOld;
  POINT pnts[] = 
  {
    {0, L}, {W, 0}, {0, -W}, {-W, 0}
  }, pnts1[sizeof(pnts) / sizeof(pnts[0])];

  for (i = 0; i < sizeof(pnts) / sizeof(pnts[0]); i++)
  {
    pnts1[i].x = X0 + pnts[i].x * cos(AngleInRadian) + pnts[i].y * sin(AngleInRadian);
    pnts1[i].y = Y0 - (pnts[i].y * cos(AngleInRadian) - pnts[i].x * sin(AngleInRadian));
  }

  hPenOld = SelectObject(hDC, GetStockObject(NULL_PEN));
  hBrOld = SelectObject(hDC, GetStockObject(DC_BRUSH));

  SetDCPenColor(hDC, RGB(255, 0, 0));
  SetDCBrushColor(hDC, Color);

  Polygon(hDC, pnts1, sizeof(pnts) / sizeof(pnts[0]));

  SelectObject(hDC, hPenOld);
  SelectObject(hDC, hBrOld);

} /*end  DrawHand function*/

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
}

/* Main window handle function */
LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  INT r;
  SYSTEMTIME st;
  HPEN hPen, hPenOld;
  static BITMAP bm;
  static HDC hMemDCFrame, hMemDCClock;
  static HBITMAP hBmFrame, hBmClock;
  static INT w, h;

  switch (Msg)
  {
  case WM_CREATE:
    hBmClock = LoadImage(NULL, "clock.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hBmClock, sizeof(bm), &bm);

    SetTimer(hWnd, 30, 102, NULL);
    hDC = GetDC(hWnd);
    hMemDCFrame = CreateCompatibleDC(hDC);
    hMemDCClock = CreateCompatibleDC(hDC);
    SelectObject(hMemDCClock, hBmClock);
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
    SendMessage(hWnd, WM_TIMER, 0, 0);

    return 0;
  case WM_SYSKEYDOWN:
    if ( wParam == VK_RETURN)
      FlipFullScreen(hWnd);
    return 0;
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    return 0;
  case WM_TIMER:
    InvalidateRect(hWnd, NULL, FALSE);
    /* Clear Background */
    SelectObject(hMemDCFrame, GetStockObject(WHITE_BRUSH));
    SelectObject(hMemDCFrame, GetStockObject(NULL_PEN));
    Rectangle(hMemDCFrame, 0, 0, w + 1, h + 1);
    
    r = (w < h ? w : h); 
    SetStretchBltMode(hMemDCFrame, COLORONCOLOR);
    StretchBlt(hMemDCFrame, w / 2 - r / 2, h /2 - r / 2, r, r, hMemDCClock, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

    /* draw hands */
    GetLocalTime(&st);
    hPen = CreatePen(PS_SOLID, 8, RGB(255, 0, 0));
    hPenOld = SelectObject(hMemDCFrame, hPen);
    
    MoveToEx(hMemDCFrame, w / 2, h / 2, NULL);
    SelectObject(hMemDCFrame, hPenOld);
    DeleteObject(hPen);
  
    DrawHand(hMemDCFrame, w / 2, h/2, (st.wHour % 12 + st.wMinute / 60.0) * 2 * PI / 12.0, r *0.18, 30, RGB(0, 0, 0));
    DrawHand(hMemDCFrame, w / 2, h/2, (st.wMinute + st.wSecond / 60.0) * 2 * PI / 60.0, r *0.30, 18, RGB(140, 0, 211));
    DrawHand(hMemDCFrame, w / 2, h/2, (st.wSecond + st.wMilliseconds / 1000.0) * 2 * PI / 60.0, r *0.47, 13, RGB(255, 0, 0));                                                                                                              


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
    DeleteObject(hBmClock);
    DeleteDC(hMemDCClock);
    KillTimer(hWnd, 30);
    PostMessage(hWnd, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'WinFunc' function */

/* END OF 'T01FWIN.C' FILE */