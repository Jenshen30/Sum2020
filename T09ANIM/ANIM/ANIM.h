/* FILE NAME: ANIM.H
 * PROGRAMMER: EK6
 * DATE: 09.06.2020
 * PURPOSE: 3D animation project.
 *          Functions heads, defines, types of animation.
*/

#ifndef __ANIM_H_
#define __ANIM_H_

#include "rnd/rnd.h"

#define EK6_MAX_UNITS 3000

typedef struct tagek6UNIT ek6UNIT;

typedef struct tagek6ANIM
{
  HWND hWnd;                     /*Frame window*/
  HDC hDC;                       /*Descriptor in memory*/
  INT W, H;                      /*Weight and height of window*/

  ek6UNIT *Units[EK6_MAX_UNITS]; /*Massive of animation objects*/
  INT NumOfUnits;                /*Current number of animation objects*/ 
  
  /* Timer specific data */
  DBL
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per second value */
  BOOL
    IsPause;                     /* Pause flag */

  BYTE Keys[256];      //-- состояние клавиш на текущем кадре
  BYTE KeysOld[256];   //-- состояние клавиш на прошлом кадре
  BYTE KeysClick[256]; //-- признаки однократного нажатия клавиш

   INT Mx, My, Mz, Mdx, Mdy, Mdz;

} ek6ANIM;


/*Base unit fields*/
#define EK6_BASE_UNIT_FIELDS                      \
  VOID (*Init)( ek6UNIT *Uni, ek6ANIM *Ani );     \
  VOID (*Close)( ek6UNIT *Uni, ek6ANIM *Ani );    \
  VOID (*Response)( ek6UNIT *Uni, ek6ANIM *Ani ); \
  VOID (*Render)( ek6UNIT *Uni, ek6ANIM *Ani )    \

/* Animation unit representation type*/
struct tagek6UNIT
{
  EK6_BASE_UNIT_FIELDS;
};
/*Global animation context*/
extern ek6ANIM EK6_Anim;
extern INT EK6_MouseWheel;

VOID EK6_AnimInit( HWND hWnd );
VOID EK6_AnimClose( VOID );
VOID EK6_AnimResize( INT W, INT H );
VOID EK6_AnimCopyFrame( VOID );
VOID EK6_AnimRender( VOID );
VOID EK6_AnimAddUnit( ek6UNIT *Uni );
//VOID EK6_AnimFlipFullScreen( VOID );
VOID EK6_AnimExit( VOID );
ek6UNIT * EK6_AnimUnitCreate( INT Size );

VOID EK6_AnimInputInit( VOID );
VOID EK6_AnimInputResponse( VOID );

/***
 * Timer handle
 ***/

/*Timer initialization function.
* ARGUMENTS: None.
* RETURNS None
*/
VOID EK6_TimerInit( VOID );


/*Timer initrframe response function.
* ARGUMENTS: None.
* RETURNS None
*/
VOID EK6_TimerResponse( VOID );

#endif /* __ANIM_H_ */

/* END OF 'ANIM.H' FILE */