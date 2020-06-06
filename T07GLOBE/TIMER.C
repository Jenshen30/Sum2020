/* FILE NAME: TIMER.C
* PROGRAMMER: EK6
* DATE: 04.06.2020
*/

#include <time.h>

#include "mth.h"
#include "globe.h"

DBL GLB_Time;       
DBL GLB_DeltaTime;  
DBL GLB_FPS;
BOOL GLB_IsPause;

/* Local timer data */
static LONG
  StartTime,
  PauseTime,
  OldTime,
  OldFPSTime,
  FrameCount;

VOID GLB_TimerInit( VOID )
{
  StartTime = clock();
  OldTime = StartTime; 
  OldFPSTime = StartTime;
  PauseTime = 0;
  FrameCount = 0;
  GLB_IsPause =StartTime;
}

/* Something new */
VOID GLB_TimerResponse( VOID )
{
  LONG t = clock();

  if (!GLB_IsPause)
  {
    GLB_Time = (DOUBLE)(t - PauseTime - StartTime) / CLOCKS_PER_SEC;
    GLB_DeltaTime = (DOUBLE)(t - OldTime) / CLOCKS_PER_SEC;
  }
  else
  {
    PauseTime += t - OldTime;
    GLB_DeltaTime = 0;
  }

  FrameCount++;
  if (t - OldFPSTime > CLOCKS_PER_SEC)
  {
    GLB_FPS = FrameCount / ((DBL)(t - OldFPSTime) / CLOCKS_PER_SEC);
    OldFPSTime = t;
    FrameCount = 0;
  }
  OldTime = t; 
}