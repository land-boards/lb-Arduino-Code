// reflowCalcs - calculate desired temp

#define TIME0_LEADFREE 0
#define TIMET1_LEADFREE 120
#define TIMET2_LEADFREE 165
#define TIMET3_LEADFREE 210
#define TIMET4_LEADFREE 218
#define TIMET5_LEADFREE 600
#define TEMPT0_LEADFREE 22.0
#define TEMPT1_LEADFREE 150.0
#define TEMPT2_LEADFREE 200.0
#define TEMPT3_LEADFREE 252.0
#define TEMPT4_LEADFREE 252.0
#define TEMPT5_LEADFREE -40.0

#define TIME0_LEADED 0
#define TIMET1_LEADED 90
#define TIMET2_LEADED 180
#define TIMET3_LEADED 220
#define TIMET4_LEADED 230
#define TIMET5_LEADED 600
#define TEMPT0_LEADED 22.0
#define TEMPT1_LEADED 150.0
#define TEMPT2_LEADED 180.0
#define TEMPT3_LEADED 215.0
#define TEMPT4_LEADED 215.0
#define TEMPT5_LEADED -30.0

double getDesiredTempLeadFree(int currTime)
{
  if (currTime < TIMET1_LEADFREE)
    return (TEMPT0_LEADFREE + ((double)currTime                   * ((TEMPT1_LEADFREE-TEMPT0_LEADFREE)/(float)(TIMET1_LEADFREE-TIME0_LEADFREE))));
  else if (currTime < TIMET2_LEADFREE)
    return (TEMPT1_LEADFREE + ((double)(currTime-TIMET1_LEADFREE) * ((TEMPT2_LEADFREE-TEMPT1_LEADFREE)/(float)(TIMET2_LEADFREE-TIMET1_LEADFREE))));
  else if (currTime < TIMET3_LEADFREE)
    return (TEMPT2_LEADFREE + ((double)(currTime-TIMET2_LEADFREE) * ((TEMPT3_LEADFREE-TEMPT2_LEADFREE)/(float)(TIMET3_LEADFREE-TIMET2_LEADFREE))));
  else if (currTime < TIMET4_LEADFREE)
    return (TEMPT3_LEADFREE);
  return (TEMPT5_LEADFREE); // off
}

double getDesiredTempLeaded(int currTime)
{
  if (currTime < TIMET1_LEADED)
    return (TEMPT0_LEADED + ((double)currTime                   * ((TEMPT1_LEADED-TEMPT0_LEADED)/(float)(TIMET1_LEADED-TIME0_LEADED))));
  else if (currTime < TIMET2_LEADED)
    return (TEMPT1_LEADED + ((double)(currTime-TIMET1_LEADED) * ((TEMPT2_LEADED-TEMPT1_LEADED)/(float)(TIMET2_LEADED-TIMET1_LEADED))));
  else if (currTime < TIMET3_LEADED)
    return (TEMPT2_LEADED + ((double)(currTime-TIMET2_LEADED) * ((TEMPT3_LEADED-TEMPT2_LEADED)/(float)(TIMET3_LEADED-TIMET2_LEADED))));
  else if (currTime < TIMET4_LEADED)
    return (TEMPT3_LEADED);
  return (TEMPT5_LEADED); // off
}

