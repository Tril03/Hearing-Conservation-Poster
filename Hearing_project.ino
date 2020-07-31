#include <FastLED.h>

#define NUM_LEDS 12

#define DATA_PIN 2

CRGB leds[NUM_LEDS];

void setup() 
{

  adc_init();
  FastLED.addLeds<WS2812B, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  FastLED.setBrightness(100);
  analogReference(EXTERNAL);
  Serial.begin(9600);
} 
 
void loop() 
{
  int lights = get_samples();
  if (lights){
    Serial.println("triggered"); //this is triggered
    conditional_lighting(110.0);
    delay(3000); //how long should this be
  }
  else{
//    Serial.println(root_mean_square());
    double dB_SPL = pascal_to_dBSPL(root_mean_square());
//    Serial.println(dB_SPL);
    conditional_lighting(dB_SPL);
  }

//  Serial.println(get_samples());
  
//  double dB_SPL = pascal_to_dBSPL(root_mean_square());
//
//  conditional_lighting(dB_SPL);
//  root_mean_square();
//  Serial.print(root_mean_square(), 8);
//  Serial.print("Time: ");
//  Serial.print(get_samples());
//  Serial.print("\n");
//  double dB = dB_SPL();
//  double f = main_f();
//  Serial.print("dB: " + dB);
//  Serial.print("\n");
//  double dBA = dBA_weighting(dB, f);
//  double weighing = (dBA-dB);
//  Serial.print("Weighing amount: ");
//  Serial.print(weighing);
//  Serial.print("\n");
//  conditional_lighting(dBA);
}
