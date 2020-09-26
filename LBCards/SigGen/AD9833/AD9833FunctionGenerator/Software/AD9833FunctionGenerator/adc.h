#ifndef __ADC_H__
#define __ADC_H__



float rawAdcValue = 0;
volatile int ADCInput = 0;
volatile int ADCInput1 = 0;
volatile int ADCInput2 = 0;
volatile int ADCInput3 = 0;
volatile int ADCInput6 = 0;


///////////////////////////////////////////////////////
////    void setupADC()
///////////////////////////////////////////////////////

void adc_setup() {
  
  ADMUX = 0;                          // AREF used(allows full pot range), ADC0 input enabled
  ADCSRA |= _BV(ADEN);                // Enable ADC
  ADCSRA |= _BV(ADATE);               // Enable ADC Auto-Trigger
  ADCSRA |= _BV(ADIE);                // Enable ADC ISR
  ADCSRA |= _BV(ADPS0);               // Set prescaler to /2
  
  ADCSRB = 0;                         // free running mode
  ADCSRA |= _BV(ADSC);                // Enable ADC conversions (must be done after ADEN)
}


///////////////////////////////////////////////////////
// Interrupt service routine for the ADC completion
///////////////////////////////////////////////////////

ISR(ADC_vect){

  // get the raw ADC completion
  rawAdcValue = ADCL;
  rawAdcValue += ADCH << 8;

   switch(ADMUX) {
    case 0x00:
      
      ADCInput6 = rawAdcValue;
      
      ADMUX = 0x01;
      break;
    
    case 0x01:
      
      ADCInput = rawAdcValue;
      ADMUX = 0x02;
      break;

    case 0x02:
      
      ADCInput1 = rawAdcValue;
      ADMUX = 0x03;
      break;

    case 0x03:
      
      ADCInput2 = rawAdcValue;
      
      ADMUX = 0x06;
      break;
      
    case 0x06:
      ADCInput3 = rawAdcValue;
      ADMUX = 0x00;
      break;
    
  }
  ADCSRA |= _BV(ADSC);

}

#endif
