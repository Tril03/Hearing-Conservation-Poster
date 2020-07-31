void conditional_lighting (double dB_SPL){
  if (dB_SPL <= 80.0){
    fill_solid(leds, NUM_LEDS, CRGB(255,0,0));//green
//    Serial.print("Green");
  }
  else if (dB_SPL <= 85.0){
    fill_solid( leds, NUM_LEDS, CRGB(150, 255,0));//yellow
//    Serial.print("Yellow");
  }
  else if (dB_SPL <= 95.0){
    fill_solid( leds, NUM_LEDS, CRGB(50,255,0)); //orange
//    Serial.print("Orange");
  }
  else if (dB_SPL > 100.0) {
    fill_solid(leds, NUM_LEDS, CRGB(0,255,0)); //red
//    Serial.print("Red");
  }
  FastLED.show();
}

//void set_color (CRGB color){
//  for (int i = 0; i <NUM_LEDS; i++){
//    leds[i] = color;
//  }
//  FastLED.show();
//  Serial.print(color);
//}

void reset(){
  
}
