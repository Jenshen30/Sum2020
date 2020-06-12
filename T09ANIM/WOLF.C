/* FILE NAME: WOLF.C
 * PROGRAMMER: EK6
 * DATE: 12.06.2020
 * PURPOSE: 3D animation project.
 *                 - Wolf unit.
*/
#include <math.h>

#include "units.h"

typedef struct
{
  EK6_BASE_UNIT_FIELDS;
  ek6PRIM WOLF;
} ek6UNIT_WOLF; 

/* Wolf unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ek6UNIT_BALL *Uni;
 *   - animation context:
 *       ek6ANIM *Ani;
 * RETURNS: None.
 */
static VOID EK6_UnitInit( ek6UNIT_WOLF *Uni, ek6ANIM *Ani )
{
  ///Uni->Pos = VecSet(0, 1, 0);
  EK6_RndPrimLoad(&Uni->WOLF, "WOLF.obj", 0.01, 0.9);
} /* End of 'EK6_UnitInit' function */


static VOID EK6_UnitClose( ek6UNIT_WOLF *Uni, ek6ANIM *Ani )
{
  EK6_RndPrimFree(&Uni->WOLF);
}/*End of 'EK6_UnitClose' fn*/
/* WOLF unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ek6UNIT_BALL *Uni;
 *   - animation context:
 *       ek6ANIM *Ani;
 * RETURNS: None.
 */
static VOID EK6_UnitResponse( ek6UNIT_WOLF *Uni, ek6ANIM *Ani )
{
 ///Uni->Pos.X += Ani->DeltaTime * 2.5;//fixme
} /* End of 'EK6_UnitResponse' function */

/* Bounce ball unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ek6UNIT_WOLF *Uni;
 *   - animation context:
 *       ek6ANIM *Ani;
 * RETURNS: None.
 */
static VOID EK6_UnitRender( ek6UNIT_WOLF *Uni, ek6ANIM *Ani )
{
  EK6_RndPrimDraw(&Uni->WOLF, MatrRotate(Ani->Time * 30, VecSet(1, 2, 3)));
} /* End of 'EK6_UnitRender' function */

/* Unit WOLF creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ek6UNIT *) pointer to created unit.
 */
ek6UNIT * EK6_UnitCreateWolf( VOID )
{
  ek6UNIT *Uni;

  if ((Uni = EK6_AnimUnitCreate(sizeof(ek6UNIT_WOLF))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)EK6_UnitInit;
  Uni->Response = (VOID *)EK6_UnitResponse;
  Uni->Render = (VOID *)EK6_UnitRender;

  return Uni;
} /* End of 'EK6_UnitCreateWolf' function */

/*END OF 'U_BALL.C' file*/