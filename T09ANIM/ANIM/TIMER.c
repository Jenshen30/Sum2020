/* FILE NAME: TIMER.C
 * PROGRAMMER: EK6
 * DATE: 09.06.2020
 * PURPOSE: 3D animation project.
 *          Timer implementation.
*/

#include "anim.h"

/* Local timer data*/

static UINT64
    StartTime,    /* Start program time */
    OldTime,      /* Previous frame time */
    OldTimeFPS,   /* Old time FPS measurement */
    PauseTime,    /* Time during pause period */
    TimePerSec,   /* Timer resolution */
    FrameCounter; /* Frames counter */

/*Timer initialization function.
* ARGUMENTS: None.
* RETURNS None
*/
VOID EK6_TimerInit( VOID )
{
  LARGE_INTEGER t;	

  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  FrameCounter = 0;
  EK6_Anim.IsPause = FALSE;
  EK6_Anim.FPS = 30.0;
  PauseTime = 0;
}/*End of 'EK6_TimerInit' function*/


/*Timer initrframe response function.
* ARGUMENTS: None.
* RETURNS None
*/
VOID EK6_TimerResponse( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);
  /* Global time */
  EK6_Anim.GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
  EK6_Anim.GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;

  /* Time with pause */
  if (EK6_Anim.IsPause)
  {
    EK6_Anim.DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
  else
  {
    EK6_Anim.DeltaTime = EK6_Anim.GlobalDeltaTime;
    EK6_Anim.Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
  }
  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > TimePerSec)
  {
    EK6_Anim.FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
}/*End of 'EK6_TimerResponse' function*/

/*END OF 'TIMER.C' FILE*/