/* FILE NAME: ANIM.C
 * PROGRAMMER: EK6
 * DATE: 09.06.2020
 * PURPOSE: 3D animation project.
 *          All general anim funtions here.
*/
#include "anim.h"
/*Gloable animation context*/
ek6ANIM EK6_Anim;
INT EK6_MouseWheel;

/* Destroying animation function.
 * ARGUMENTS:
 *         VOID;
 * RETURNS:
 *   (VOID) None.
*/

VOID EK6_AnimClose( VOID )
{
  INT i;

  /*Kill all units*/
  for (i = 0; i < EK6_Anim.NumOfUnits; i++)
  {
    EK6_Anim.Units[i]->Close(EK6_Anim.Units[i], &EK6_Anim);
    free(EK6_Anim.Units[i]);
    EK6_Anim.Units[i] = NULL;  
  }
  EK6_Anim.NumOfUnits = 0;

  EK6_RndClose();
  memset(&EK6_Anim, 0, sizeof(ek6ANIM));
}/*End of 'EK6_AnimClose' fn*/


/* Animation rendering function.
 * ARGUMENTS:
 *         VOID;
 * RETURNS:
 *   (VOID) None.
*/
VOID EK6_AnimRender( VOID )
{
  INT i;

  //some space for. . . timer, keyboard, mouse, joystick . .

  /*Timer Response*/
  EK6_AnimInputResponse();
  EK6_TimerResponse();

  /*Send response to all units*/
  for (i = 0; i < EK6_Anim.NumOfUnits; i++)
    EK6_Anim.Units[i]->Response(EK6_Anim.Units[i], &EK6_Anim);

  EK6_RndStart();

  for (i = 0; i < EK6_Anim.NumOfUnits; i++)
    EK6_Anim.Units[i]->Render(EK6_Anim.Units[i], &EK6_Anim);
  EK6_RndEnd();
}/*End of 'EK6_AnimRender' fn*/


/* Add the element to Anim function.
 * ARGUMENTS:
 *         VOID;
 * RETURNS:
 *   (VOID) None.
*/
VOID EK6_AnimAddUnit( ek6UNIT *Uni )
{
  if (EK6_Anim.NumOfUnits < EK6_MAX_UNITS)
  {
    EK6_Anim.Units[EK6_Anim.NumOfUnits] = Uni;
    EK6_Anim.Units[EK6_Anim.NumOfUnits]->Init(EK6_Anim.Units[EK6_Anim.NumOfUnits], &EK6_Anim);
    EK6_Anim.NumOfUnits++;
  }
}/*End of 'EK6_AnimAddUnit' fn*/


/* Animation initialization function.
 * ARGUMENTS:
 *         VOID;
 * RETURNS:
 *   (VOID) None.
*/
VOID EK6_AnimInit( HWND hWnd )
{
  memset(&EK6_Anim, 0, sizeof(ek6ANIM));

  EK6_Anim.hWnd = hWnd;
  EK6_RndInit(hWnd);
  EK6_Anim.hDC = EK6_hRndDC;
  
  /*Timer Initialization*/
  EK6_AnimInputInit();
  EK6_TimerInit();
}/*End of 'EK6_AnimInit' fn*/


/* Animation resizing function.
 * ARGUMENTS:
 *         VOID;
 * RETURNS:
 *   (VOID) None.
*/
VOID EK6_AnimResize( INT W, INT H )
{
  EK6_Anim.W = W;
  EK6_Anim.H = H;

  EK6_RndResize(W, H);
}/*End of 'EK6_AnimResize' fn*/


/* Animation double bufferization function.
 * ARGUMENTS:
 *         VOID;
 * RETURNS:
 *   (VOID) None.
*/
VOID EK6_AnimCopyFrame( VOID )
{
  EK6_RndCopyFrame();
}/*End of 'EK6_AnimCopyFrame' fn*/

VOID EK6_AnimExit( VOID )
{
  static BOOL IsExit = FALSE;

  if (IsExit)
    return;
  IsExit = TRUE;
  PostMessage(EK6_Anim.hWnd, WM_CLOSE, 0, 0);
}

/* END OF 'ANIM.C' FILE */