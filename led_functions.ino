void conditional_lighting (double dB_SPL){
  if (dB_SPL <= 85.0){ //fully safe for up to > ~8 hours
    fill_solid(leds, 15, CRGB(0,0,0));//black
    fill_solid(&leds[15], 5, CRGB(255,0,0));//green
//    Serial.print("Green");
  }
  else if (dB_SPL <= 90.0){ //safe for up to > ~2 hours
    fill_solid(leds, 10, CRGB(0,0,0));//black
    fill_solid(&leds[10], 10, CRGB(150, 255,0));//yellow
//    Serial.print("Yellow");
  }
  else if (dB_SPL <= 95.0){ //safe for up to > ~0.5 hours
    fill_solid(leds, 5, CRGB(0,0,0));//black
    fill_solid(&leds[5], 15, CRGB(50,255,0)); //orange
//    Serial.print("Orange");
  }
  else { //safe for <0.5 hours
    fill_solid(leds, 20, CRGB(0,255,0)); //red
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
