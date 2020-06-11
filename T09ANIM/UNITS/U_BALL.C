/* FILE NAME: U_BALL.C
 * PROGRAMMER: EK6
 * DATE: 09.06.2020
 * PURPOSE: 3D animation project.
 *                 - bounce ball unit.
*/
#include <math.h>

#include "../units.h"

typedef struct
{
  EK6_BASE_UNIT_FIELDS;
  VEC Pos;
  ek6PRIM Ball;
} ek6UNIT_BALL; 

/* Bounce ball unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ek6UNIT_BALL *Uni;
 *   - animation context:
 *       ek6ANIM *Ani;
 * RETURNS: None.
 */
static VOID EK6_UnitInit( ek6UNIT_BALL *Uni, ek6ANIM *Ani )
{
  ///Uni->Pos = VecSet(0, 1, 0);
  EK6_RndPrimCreateSphere(&Uni->Ball, VecSet(0, 0, 0), 1, 20, 10);
} /* End of 'EK6_UnitInit' function */

static VOID EK6_UnitClose( ek6UNIT_BALL *Uni, ek6ANIM *Ani )
{
  EK6_RndPrimFree(&Uni->Ball);
}/*End of 'EK6_UnitClose' fn*/
/* Bounce ball unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ek6UNIT_BALL *Uni;
 *   - animation context:
 *       ek6ANIM *Ani;
 * RETURNS: None.
 */
static VOID EK6_UnitResponse( ek6UNIT_BALL *Uni, ek6ANIM *Ani )
{
 ///Uni->Pos.X += Ani->DeltaTime * 2.5;//fixme
} /* End of 'EK6_UnitResponse' function */

/* Bounce ball unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ek6UNIT_BALL *Uni;
 *   - animation context:
 *       ek6ANIM *Ani;
 * RETURNS: None.
 */
static VOID EK6_UnitRender( ek6UNIT_BALL *Uni, ek6ANIM *Ani )
{
  EK6_RndPrimDraw(&Uni->Ball, MatrRotate(Ani->Time * 30, VecSet(1, 2, 3)));//DrawSphere(Uni->Pos, 3);//fixme
} /* End of 'EK6_UnitRender' function */

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ek6UNIT *) pointer to created unit.
 */
ek6UNIT * EK6_UnitCreateBall( VOID )
{
  ek6UNIT *Uni;

  if ((Uni = EK6_AnimUnitCreate(sizeof(ek6UNIT_BALL))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)EK6_UnitInit;
  Uni->Response = (VOID *)EK6_UnitResponse;
  Uni->Render = (VOID *)EK6_UnitRender;

  return Uni;
} /* End of 'EK6_UnitCreateBall' function */

/*END OF 'U_BALL.C' file*/