#include <arduinoFFT.h>

const int sample_period_micros = 150;

const int true_period_micros = 160; // extra time for parsing through while loop (constant relationship between sample_period and true_period)

const int SAMPLE_SIZE = 780; //~125 ms measuring period
const int IMPULSE_SIZE = SAMPLE_SIZE/4; //31.25 ms
const float SAMPLING_FREQUENCY = 1000000 * 1 / true_period_micros;

int16_t fast_samples[SAMPLE_SIZE];
static int impulse_sample_count = 0;
//initial methodology
int get_samples() { //returns true if impulse is bad, false if it isn't; regardless of fast sampling rms, if impulse is bad, then red light goes up. Return char w/ diff vals to process for distinguishing different levels of impulses
  long t0 = micros();
  long long initial;
  analogRead(A0); //first read takes longer
  for (int i = 0; i < SAMPLE_SIZE; i++) {
    initial = micros();
    fast_samples[i] = analogRead(A0);
    while (micros() - initial <= sample_period_micros); //this takes 10 us to parse through
  }
  Serial.println(micros() - t0);
}

float greatest_rms(){
  float great_rms = 0;
  for (int i = 0; i < 4; i++){
    great_rms = max(great_rms, root_mean_square(&fast_samples[i*IMPULSE_SIZE], IMPULSE_SIZE));
  }
//  Serial.print("largest impulse: ");
//  Serial.println(pascal_to_dBSPL(great_rms));
  float fast_rms = root_mean_square(fast_samples, SAMPLE_SIZE);
//  Serial.print("fast samples: ");
//  Serial.println(pascal_to_dBSPL(smaller_rms));
  if (great_rms > 1.12){
    great_rms = great_rms * -1;
    return great_rms;
  }
  else{
    return fast_rms;
  }
//  great_rms = max(great_rms, smaller_rms);
}
////came up with better way
//int get_samples() { //Return int w/ diff vals to process for distinguishing different levels of impulses
//  unsigned long long initial;
//  int16_t analog;
//  analogRead(A0); //first read takes longer
//  for (int i = 0; i < SAMPLE_SIZE; i++) {
//    analog = analogRead(A0);
//    fast_samples[i] = analog;
//    
//    if (impulse_sample_count < IMPULSE_SIZE)  {
//      impulse_samples[impulse_sample_count++] = analog;
//      
//    }
//    else { //not doing lighting here bc that would cause delay always
////      long t0 = micros();
//      float impulse = pascal_to_dBSPL(impulse_rms());//11.6 ms (don't know how to avoid currently) dBSPL function add 200 us
//      impulse_samples[0] = analogRead(A0);
//      impulse_sample_count = 1; //reset impulse_sample_count when array is filled
//      
//      if (impulse > 95.0) return 1;
////      else if (impulse > 90.0) return 2;
////      else if (impulse > 85.0) return 3;
////      Serial.println(micros() - t0);
////      impulse_samples[0] = analogRead(A0);
////      impulse_sample_count = 1; //reset impulse_sample_count when array is filled
//    }
//    while (micros() - initial <= sample_period_micros) {}; //ensures a constant sampling rate 
//  }
//  
//  return 0;
//}

//float impulse_rms() {
//  float mean_square = 0.0;
//  for (int i = 0; i < IMPULSE_SIZE; i++) {
//    //    Serial.println(fast_samples[i],8);
//    mean_square += pow(sound_pressure(mic_voltage(op_amp_voltage(impulse_samples[i] - 509))), 2);
//  }
//  mean_square /= IMPULSE_SIZE;
//  float rms = sqrt(mean_square);
//  return rms;
//}

float root_mean_square(int16_t data[], int count) { 
  float mean_square = 0.0;
  for (int i = 0; i < count; i++) {
    mean_square += pow(sound_pressure(mic_voltage(op_amp_voltage(data[i] - 509))), 2);
  }
  mean_square /= count;
  float rms = sqrt(mean_square);
  return rms;
}

void top_frequencies() {
  double vImag[SAMPLE_SIZE];
  double vReal[SAMPLE_SIZE];
  for (int i = 0; i < SAMPLE_SIZE; i++) {
    vReal[i] = fast_samples[i];
    vImag[i] = 0;
  }
  arduinoFFT FFT = arduinoFFT();

  FFT.Windowing(vReal, SAMPLE_SIZE, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLE_SIZE, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLE_SIZE);

  for (int i = 2; i < (SAMPLE_SIZE / 2); i++)
  {
    //    i * SAMPLING_FREQUENCY) / SAMPLE_SIZE; //frequency
    //    Serial.print(" ");
    //    Serial.println(vReal[i], 1);    //amplitude for each frequency
  }
}
