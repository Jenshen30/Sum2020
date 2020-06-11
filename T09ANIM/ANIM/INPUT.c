/* FILE NAME: INPUT.C
 * PROGRAMMER: EK6
 * DATE: 09.06.2020
 * PURPOSE: 3D animation project.
 *          Functions about input system.
*/
#include "anim.h"

INT EK6_MouseWheel;
static BYTE KeysOld[256];

static VOID EK6_AnimKeyboardInit( VOID )
{
  GetKeyboardState(EK6_Anim.Keys);
} /* End of 'EK6_AnimKeyboardInit' function */


static VOID EK6_AnimKeyboardResponse( VOID )
{
  INT i;

  GetKeyboardState(EK6_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    EK6_Anim.Keys[i] >>= 7;
    EK6_Anim.KeysClick[i] = EK6_Anim.Keys[i] && !EK6_Anim.KeysOld[i];
  }
  memcpy(EK6_Anim.KeysOld, EK6_Anim.Keys, 256);
}


/* Initilizate mouse function */
static VOID EK6_AnimMouseInit( VOID )
{
  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(EK6_Anim.hWnd, &pt);

  /* приращение координат на экране */
  EK6_Anim.Mdx = 0;
  EK6_Anim.Mdy = 0;
  EK6_Anim.Mdz = 0;
  /* абсолютные значения */
  EK6_Anim.Mx = pt.x;
  EK6_Anim.My = pt.y;
  EK6_Anim.Mz = 0;
  EK6_MouseWheel = 0;
} /* End of 'EK6_AnimMouseInit' function */


static VOID EK6_AnimMouseResponse( VOID )
{
  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(EK6_Anim.hWnd, &pt);
  EK6_Anim.Mdx = pt.x - EK6_Anim.Mx;
  EK6_Anim.Mdy = pt.y - EK6_Anim.My;
  EK6_Anim.Mx = pt.x;
  EK6_Anim.My = pt.y;
  EK6_Anim.Mz += EK6_MouseWheel;
  EK6_MouseWheel = 0;
}

VOID EK6_AnimInputInit( VOID )
{
  EK6_AnimKeyboardInit();
  EK6_AnimMouseInit();
}
VOID EK6_AnimInputResponse( VOID )
{
  EK6_AnimKeyboardResponse();
  EK6_AnimMouseResponse();
}