/* FILE NAME: GLOBE.C
* PROGRAMMER: EK6
* DATE: 04.06.2020
*/
 #include <windows.h>
#include <math.h>
#include "globe.h"

#define M (25 * 3)
#define N (12 * 3)

static VEC Geom[N][M];
                                                       
VOID GlobeSet( INT Xc, INT Yc, DBL R )
{
  INT i, j;
  DBL theta, phi;

  for (i = 0, theta = 0; i < N; i++, theta += PI / (N - 1))
    for (j = 0, phi = 0; j < M; j++, phi += 2 * PI / (M - 1))
    {
      Geom[i][j].X = Xc + R * sin(theta) * sin(phi);
      Geom[i][j].Y = Yc - R * cos(theta);
      Geom[i][j].Z = R * sin(theta) * cos(phi);
    }
}

VOID GlobeDraw( HDC hDC )
{
  INT i, j, s = 3;

  SelectObject(hDC, GetStockObject(NULL_PEN));
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SetDCBrushColor(hDC, RGB(55, 55, 55));

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
    {
      INT
        X = (INT)Geom[i][j].X,
        Y = (INT)Geom[i][j].Y;

      Ellipse(hDC, X - s, Y - s, X + s, Y + s);
    }

}