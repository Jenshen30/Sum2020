/* FILE NAME: GLOBE.C
* PROGRAMMER: EK6
* DATE: 04.06.2020
*/
#define PI 3.14159265358979323846

typedef double DBL;
typedef float FLT;

typedef struct tagVEC 
{
  DBL X, Y, Z; 
} VEC;

VOID GlobeSet( INT Xc, INT Yc, DBL R );
VOID GlobeDraw( HDC hDC);