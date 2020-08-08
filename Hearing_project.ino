#include <FastLED.h>

#define NUM_LEDS 20

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
  get_samples();
  float great_rms = greatest_rms();
  if (great_rms < 0) {
    great_rms = great_rms * -1;
    float dB_SPL = pascal_to_dBSPL(great_rms);
    conditional_lighting(dB_SPL);
//    Serial.print(dB_SPL);
    Serial.println("     if statement pass");
    delay(2000);
  }
  else {
    float dB_SPL = pascal_to_dBSPL(great_rms);
//    Serial.println(dB_SPL);    
    conditional_lighting(dB_SPL);
  }
}
//   Serial.println(dB_SPL);
//  if (impulse_sound == 1){
//    Serial.println("triggered"); //this is triggered
//    conditional_lighting(110.0);
//    delay(1000); //how long should this be
//  else if (impulse_sound == 2){
//    Serial.println("triggered"); //this is triggered
//    conditional_lighting(92.5);
//    delay(2000); //how long should this be
//  }
//  else if (impulse_sound == 3){
//    Serial.println("triggered"); //this is triggered
//    conditional_lighting(87.5);
//    delay(2000); //how long should this be
//  }
//    Serial.println(root_mean_square());
//    Serial.println(dB_SPL);

//  }

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
//}
