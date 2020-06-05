/* FILE NAME: GLOBE.C
* PROGRAMMER: EK6
* DATE: 04.06.2020
*/
 #include <windows.h>

#include <math.h>

#include <time.h>

#include "globe.h"

#define M 50
#define N 36

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
      VEC
        v = VecRotateZ(Geom[i][j], 34 * t),
        v1 = VecRotateX(v, 34 * t);

      pnts[i][j].x = CenterX + (INT)v1.X, 
      pnts[i][j].y = CenterY - (INT)v1.Y;
    }

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