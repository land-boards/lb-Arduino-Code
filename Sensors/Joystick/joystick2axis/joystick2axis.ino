enum ROBOT_DIR
{
  STOP = 0,
  FWD_RIGHT,
  FWD_LEFT,
  FWD,
  BK_RIGHT,
  BK_LEFT,
  BK, 
};

int UD = 0;
int LR = 0;

void setup() {
  Serial.begin(9600);
}

void loop() 
{
  int moveDir;
  moveDir = STOP;
  UD = analogRead(A0);
  LR = analogRead(A1);
  Serial.print("UD = ");
  Serial.print(UD, DEC);
  Serial.print(", LR = ");
  Serial.println(LR, DEC);
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
  switch (moveDir)
  {
    case STOP:
      Serial.println("Stop");
      break;
    case FWD_RIGHT:
      Serial.println("Forware Right");
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
  delay(200);
}
