// BandSwitch.ino
// Band switch conntrols Ultimate relay-switched LPF card
//  https://qrp-labs.com/ultimatelpf.html
// Relay Driver Card since Arduino Pro Mini drives 3.3V
//  http://land-boards.com/blwiki/index.php?title=6_Channel_Relay_Driver_Card

#define GPIO_BAND10M 5    // Digio 5 = 10M
#define GPIO_BAND15M 6
#define GPIO_BAND20M 7
#define GPIO_BAND40M 8
#define GPIO_BAND80M 9    // Didio 9 = 80M

void initBandSwitch(void)
{
  pinMode(GPIO_BAND10M,OUTPUT);
  digitalWrite(GPIO_BAND10M, LOW);
  pinMode(GPIO_BAND15M,OUTPUT);
  digitalWrite(GPIO_BAND15M, LOW);
  pinMode(GPIO_BAND20M,OUTPUT);
  digitalWrite(GPIO_BAND20M, LOW);
  pinMode(GPIO_BAND40M,OUTPUT);
  digitalWrite(GPIO_BAND40M, LOW);
  pinMode(GPIO_BAND80M,OUTPUT);
  digitalWrite(GPIO_BAND80M, LOW);
  setBandSwitch();
}

void setBandSwitch(void)
{
  if ((bandNumber == BAND_80M_CW) || (bandNumber == BAND_80M_SSB))
  {
    digitalWrite(GPIO_BAND10M, LOW);
    digitalWrite(GPIO_BAND15M, LOW);
    digitalWrite(GPIO_BAND20M, LOW);
    digitalWrite(GPIO_BAND40M, LOW);
    digitalWrite(GPIO_BAND80M, HIGH);
  }
  if ((bandNumber == BAND_40M_CW) || (bandNumber == BAND_40M_SSB))
  {
    digitalWrite(GPIO_BAND10M, LOW);
    digitalWrite(GPIO_BAND15M, LOW);
    digitalWrite(GPIO_BAND20M, LOW);
    digitalWrite(GPIO_BAND40M, HIGH);
    digitalWrite(GPIO_BAND80M, LOW);
  }
  if ((bandNumber == BAND_20M_CW) || (bandNumber == BAND_20M_SSB))
  {
    digitalWrite(GPIO_BAND10M, LOW);
    digitalWrite(GPIO_BAND15M, LOW);
    digitalWrite(GPIO_BAND20M, HIGH);
    digitalWrite(GPIO_BAND40M, LOW);
    digitalWrite(GPIO_BAND80M, LOW);
  }
  if ((bandNumber == BAND_15M_CW) || (bandNumber == BAND_15M_SSB))
  {
    digitalWrite(GPIO_BAND10M, LOW);
    digitalWrite(GPIO_BAND15M, HIGH);
    digitalWrite(GPIO_BAND20M, LOW);
    digitalWrite(GPIO_BAND40M, LOW);
    digitalWrite(GPIO_BAND80M, LOW);
  }
  if ((bandNumber == BAND_10M_CW) || (bandNumber == BAND_10M_SSB))
  {
    digitalWrite(GPIO_BAND10M, HIGH);
    digitalWrite(GPIO_BAND15M, LOW);
    digitalWrite(GPIO_BAND20M, LOW);
    digitalWrite(GPIO_BAND40M, LOW);
    digitalWrite(GPIO_BAND80M, LOW);
  }
}
