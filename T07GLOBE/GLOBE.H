/* FILE NAME: GLOBE.H
* PROGRAMMER: EK6
* DATE: 04.06.2020
*/

#include <windows.h>

#define PI 3.14159265358979323846

typedef double DBL;
typedef float FLT;

typedef struct tagVEC 
{
  DBL X, Y, Z; 
} VEC;

extern DBL GLB_Time;       
extern DBL GLB_DeltaTime;  
extern DBL GLB_FPS;
extern BOOL GLB_IsPause;

VOID GLB_TimerInit( VOID );
VOID GLB_TimerResponse( VOID );

VOID GlobeSet( INT Xc, INT Yc, DBL R );
VOID GlobeDraw( HDC hDC);
