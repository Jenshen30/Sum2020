/* FILE NAME: U_CTRL.C
 * PROGRAMMER: EK6
 * DATE: 09.06.2020
 * PURPOSE: 3D animation project.
*/

#include <stdio.h>

#include "../units.h"

typedef struct tagek6UNIT_CTRL
{
  EK6_BASE_UNIT_FIELDS;
  DBL
    Distance,
    RotateAngle,
    ElevatorAngle;
} ek6UNIT_CTRL; 

static VOID EK6_UnitInit( ek6UNIT_CTRL *Uni, ek6ANIM *Ani )
{
  Uni->RotateAngle = 30;
  Uni->ElevatorAngle = 47;
  Uni->Distance = 4;

  ///wglUseFrontBitmaps(Ani->hDC, 0, 256, 102);
} /* End of 'EK6_UnitInit' function */

static VOID EK6_UnitClose( ek6UNIT_CTRL *Uni, ek6ANIM *Ani )
{
} /* End of 'EK6_UnitClose' function */

static VOID EK6_UnitResponse( ek6UNIT_CTRL *Uni, ek6ANIM *Ani )
{
  VEC L = VecSet(0, 0, Uni->Distance);
  static CHAR Buf[102]; 

  if (Ani->KeysClick['P'])
    Ani->IsPause = !Ani->IsPause;
  if (Ani->KeysClick['W'])
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  if (Ani->KeysClick['S'])
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  //if (Ani->KeysClick[VK_RETURN] && Ani->Keys[VK_MENU])
    //EK6_FlipFullScreen();
  if (Ani->KeysClick[VK_ESCAPE])
    EK6_AnimExit();

  if (Ani->Keys[VK_LBUTTON])
  {
    Uni->Distance += Ani->DeltaTime * Ani->Mdz * 0.3;
    Uni->RotateAngle += Ani->DeltaTime * 30 * Ani->Mdx;
    Uni->ElevatorAngle += Ani->DeltaTime * 30 * Ani->Mdy;
  }
  L = PointTransform(L,
  MatrMulMatr3(MatrRotateZ(-Uni->Distance),
  MatrRotateX(-Uni->ElevatorAngle),
  MatrRotateY(-Uni->RotateAngle)));
  EK6_RndCamSet(L, VecSet(0, 0, 0), VecSet(0, 1, 0));

  SetTextColor(Ani->hDC, RGB(0, 255, 0));
  SetBkMode(Ani->hDC, TRANSPARENT);
  TextOut(Ani->hDC, 0, 0, Buf, sprintf(Buf, "FPS: %.3f", Ani->FPS));
} /* End of 'EK6_UnitResponse' function */


static VOID EK6_UnitRender( VOID )//ek6UNIT_CONTROL *Uni, ek6ANIM *Ani )
{
  //INT n;
  //static CHAR Buf[100];

  //glListBase(102);
  //glCallLists(5, GL_UNSIGNED_BYTE, "a");
  //n = sprintf(Buf, "Fps - %.3f", Ani->FPS);
  //SetWindowText(Ani->hWnd, Buf);
}

ek6UNIT * EK6_UnitCreateControl( VOID )
{
  ek6UNIT_CTRL *Uni;

  /* Memory allocation */
  if ((Uni = (ek6UNIT_CTRL *)EK6_AnimUnitCreate(sizeof(ek6UNIT_CTRL))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)EK6_UnitInit;
  Uni->Close = (VOID *)EK6_UnitClose;
  Uni->Response = (VOID *)EK6_UnitResponse;
  Uni->Render = (VOID *)EK6_UnitRender;
return (ek6UNIT *)Uni;
} /* End of 'EK6_UnitCreateControl' function */

/*END OF 'U.CTRL' FN*/