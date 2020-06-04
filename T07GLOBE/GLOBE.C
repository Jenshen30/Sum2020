/* FILE NAME: GLOBE.C
* PROGRAMMER: EK6
* DATE: 04.06.2020
*/
 #include <windows.h>

#include <math.h>

#include <time.h>

#include "globe.h"

#define M (25 * 3)
#define N (12 * 3)

static VEC Geom[N][M];
static INT CenterX, CenterY;

VEC VecRotateZ( VEC V, DBL Angle)
{
  VEC r;
  
  Angle *= PI / 180;
  r.X = V.X * cos(Angle) - V.Y * sin(Angle);
  r.Y = V.Y * cos(Angle) + V.X * sin(Angle);
  r.Z = V.Z;

  return r;
}
VEC VecRotateX(VEC V, DBL Angle)
{
  VEC r;
  
  Angle *= PI / 180;
  r.X = V.X;
  r.Y = V.Y * cos(Angle) + V.Z * sin(Angle);
  r.Z = V.Z * cos(Angle) - V.Y * sin(Angle);

  return r;
}
/*fill mass Geom*/                                                      
VOID GlobeSet( INT Xc, INT Yc, DBL R )
{
  INT i, j;
  DBL theta, phi;

  CenterX = Xc;
  CenterY = Yc;
  for (i = 0, theta = 0; i < N; i++, theta += PI / (N - 1))
    for (j = 0, phi = 0; j < M; j++, phi += 2 * PI / (M - 1))
    {
      Geom[i][j].X = R * sin(theta) * sin(phi);
      Geom[i][j].Y = R * cos(theta);
      Geom[i][j].Z = R * sin(theta) * cos(phi);
    }
}

VOID GlobeDraw( HDC hDC )
{
  INT i, j, s = 3;
  DBL t = (DBL)clock() / CLOCKS_PER_SEC;
  static POINT pnts[N][M];

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
    {
      VEC v = VecRotateZ(Geom[i][j], 30 * t),
          v1 = VecRotateX(Geom[i][j], 30 * t); 
        pnts[i][j].x = CenterX + (INT)v1.X, 
        pnts[i][j].y = CenterY - (INT)v1.Y;
    }
    /*points*/
  /*
    for (i = 0; i < N; i++)
      for (j = 0; j < M; j++)
        Ellipse(hDC, pnts[i][j].x - s, pnts[i][j].y - s, pnts[i][j].x + s, pnts[i][j].y + s);
    */
    /*horizontal lines*/
  /*
    SelectObject(hDC, GetStockObject(BLACK_PEN));
    SelectObject(hDC, GetStockObject(NULL_BRUSH));
    SetDCBrushColor(hDC, RGB(55, 55, 55));
    for (i = 0; i < N; i++)
    {
      MoveToEx(hDC, pnts[i][0].x, pnts[i][0].y, NULL);
      for (j = 0; j < M; j++)
        LineTo(hDC, pnts[i][j].x, pnts[i][j].y);
    }
    */
    /*vertical lines*/
    /*
    SelectObject(hDC, GetStockObject(BLACK_PEN));
    SelectObject(hDC, GetStockObject(NULL_BRUSH));
    SetDCBrushColor(hDC, RGB(55, 55, 55));
    for (j = 0; j < M; j++)
    {
      MoveToEx(hDC, pnts[0][j].x, pnts[0][j].y, NULL);
      for (i = 0; i < N; i++)
        LineTo(hDC, pnts[i][j].x, pnts[i][j].y);
    }
    */
  SelectObject(hDC, GetStockObject(BLACK_PEN));
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  srand(10);
  for (i = 0; i < N - 1; i++)
      for (j = 0; j < M - 1; j++)
      {
        POINT p[4];

        p[0] = pnts[i][j];
        p[1] = pnts[i][j + 1];
        p[2] = pnts[i + 1][j + 1];
        p[3] = pnts[i + 1][j];
        SetDCBrushColor(hDC, RGB(rand() % 256, 20, rand() % 256, rand() % 256) );
        if ((p[0].x - p[1].x) * (p[0].y + p[1].y) + 
           (p[1].x - p[2].x) * (p[1].y + p[2].y) +
           (p[2].x - p[3].x) * (p[2].y + p[3].y) +
           (p[3].x - p[0].x) * (p[3].y + p[0].y) <= 0)
          Polygon(hDC, p, 4); 
      }
}