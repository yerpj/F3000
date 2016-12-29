#include "ntc.h"

extern uint16_t ADC1ConvertedValues[2];

void ntc_init(void)
{
  nolcsa_ADC_Init();
}

float ntc_get_temperature(void)
{
  float Vcc=3.3;
  //uint32_t Voutint=0;
  uint16_t Vadc;
  float Vout;                 // output voltage of voltage divider
  uint32_t R1 = 10000;         // nominal thermistor resistance at nominal temperature Tn
  uint32_t R2 = 10000;         // fixed resistor in voltage divider
  float Rth;                  // actual thermistor resistance
  float Tn = 25 + 273.15;     // nominal temperature in degrees Celsius, convert to degrees Kelvin
  uint32_t Bth = 3435;        // device specific constant from datasheet in Kelvin
  float temp;                 // temperature

  // get the voltage divider output and convert it to volts
  
  Vadc = ADC1ConvertedValues[0];
 
  Vout= (float)((Vadc) *Vcc/0xFFF);
  // calculate actual thermistor resistance
  //Rth = ((Vcc * R2) / (Vout)) - R2;
  Rth = R2*((Vcc/Vout)-1);
  //Rth= (Vout * R2) / (Vcc-Vout);
  // use thermistor equation to calculate temperature in Kelvin
  temp = (Bth*Tn) / (Bth + log(Rth / R1) * Tn);
  // convert temperature from Kelvin to Celsius
  temp = temp - 273.15;

  return temp;
}
