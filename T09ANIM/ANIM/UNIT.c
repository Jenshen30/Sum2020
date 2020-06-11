/* FILE NAME: UNIT.C
 * PROGRAMMER: EK6
 * DATE: 09.06.2020
 * PURPOSE: 3D animation project.
*/
#include "anim.h"
/* Unit initialization function.
* ARGUMENTS:
*   - self-pointer to unit object:
*       ek6UNIT *Uni;
*   - animation context:
*       ek6ANIM *Ani;
* RETURNS: None.
*/
static VOID EK6_UnitInit( ek6UNIT *Uni, ek6ANIM *Ani )
{
} /* End of 'EK6_UnitInit' function */
/* Unit deinitialization function.
* ARGUMENTS:
*   - self-pointer to unit object:
*       ek6UNIT *Uni;
*   - animation context:
*       ek6ANIM *Ani;
* RETURNS: None.
*/
static VOID EK6_UnitClose( ek6UNIT *Uni, ek6ANIM *Ani )
{
} /* End of 'EK6_UnitClose' function */

/* Unit inter frame events handle function.
* ARGUMENTS:
*   - self-pointer to unit object:
*       ek6UNIT *Uni;
*   - animation context:
*       ek6ANIM *Ani;
* RETURNS: None.
*/
static VOID EK6_UnitResponse( ek6UNIT *Uni, ek6ANIM *Ani )
{
} /* End of 'EK6_UnitResponse' function */

/* Unit render function.
* ARGUMENTS:
*   - self-pointer to unit object:
*       ek6UNIT *Uni;
*   - animation context:
*       ek6ANIM *Ani;
* RETURNS: None.
*/
static VOID EK6_UnitRender( ek6UNIT *Uni, ek6ANIM *Ani )
{
} /* End of 'EK6_UnitRender' function */
	

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (ek6UNIT *) pointer to created unit.
 */
ek6UNIT * EK6_AnimUnitCreate( INT Size )
{
  ek6UNIT *Uni;

  /* Memory allocation */
  if (Size < sizeof(ek6UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);

  /* Setup unit methods */
  Uni->Init = EK6_UnitInit;
  Uni->Close = EK6_UnitClose;
  Uni->Response = EK6_UnitResponse;
  Uni->Render = EK6_UnitRender;

  return Uni;
} /* End of 'EK6_AnimUnitCreate' function */
                 
/*END OF 'UNITS.C' file*/