//////////////////////////////////////////////////////////////
// joystick() - Reads and returns joystick value
// Joystick is a Parallax 2-Axis joystick from Radio Shack.
// Returns a byte value representing zone
//
//   FWD_LEFT    FWD     FWD_RIGHT
//     STOP      STOP       STOP
//   BK_LEFT      BK     BK_RIGHT
//
//////////////////////////////////////////////////////////////

ROBOT_DIR joystick(void)
{
  int UD = 0;
  int LR = 0;
  int moveDir;
  moveDir = STOP;
  UD = analogRead(A0);
  LR = analogRead(A1);
#ifdef SERIAL_DEBUG_JOYSTICK
  Serial.print("UD = ");
  Serial.print(UD, DEC);
  Serial.print(", LR = ");
  Serial.println(LR, DEC);
#endif
  if (UD > 562)
  {
    if  (LR > 562)
      moveDir = FWD_RIGHT;
    else if (LR < 462)
      moveDir = FWD_LEFT;
    else
      moveDir = FWD;
  }
  else if (UD < 462)
  {
    if  (LR > 562)
      moveDir = BK_RIGHT;
    else if (LR < 462)
      moveDir = BK_LEFT;
    else
      moveDir = BK;
  }
  else
    moveDir = STOP;
#ifdef SERIAL_DEBUG_JOYSTICK
  switch (moveDir)
  {
    case STOP:
      Serial.println("Stop");
      break;
    case FWD_RIGHT:
      Serial.println("Forward Right");
      break;
    case FWD_LEFT:
      Serial.println("Forward Left");
      break;
    case FWD:
      Serial.println("Forward");
      break;
    case BK_RIGHT:
      Serial.println("Back Right");
      break;
    case BK_LEFT:
      Serial.println("Back Left");
      break;
    case BK:
      Serial.println("Back");
      break;
 }
 #endif
  return(moveDir);
}

