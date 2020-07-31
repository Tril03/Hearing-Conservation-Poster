#include <arduinoFFT.h>

const int sample_period_micros = 150;

const int true_period_micros = 213; // extra time for

const int SAMPLE_SIZE = 586; //125 ms measuring period
const int IMPULSE_SIZE = 164; //35 ms
const float SAMPLING_FREQUENCY = 1000000 * 1 / true_period_micros;

int16_t fast_samples[SAMPLE_SIZE];
int16_t impulse_samples[IMPULSE_SIZE];
static int impulse_sample_count = 0;
//initial methodology
//int get_samples() { //returns true if impulse is bad, false if it isn't; regardless of fast sampling rms, if impulse is bad, then red light goes up. Return char w/ diff vals to process for distinguishing different levels of impulses
//  long t0 = micros();
//  long long initial;
//  analogRead(A0); //first read takes longer
//  for (int i = 0; i < 3; i++) {
//    for (int j = 0; j < IMPULSE_SIZE; j++) {
//      initial = micros();
//      impulse_samples[j] = fast_samples[IMPULSE_SIZE*i + j] = analogRead(A0);
//      while (micros() - initial <= sample_period_micros) {}; //this takes 10 us to parse through
//    }
//
//    if (pascal_to_dBSPL(impulse_rms()) > 105){
//      return 1;//4 us, including print statement time; not going to affect readings
//    }
//
//  }
//  for (int k = IMPULSE_SIZE*3; k < SAMPLE_SIZE; k++){
//    initial = micros();
//    fast_samples[k] = analogRead(A0);
//    while (micros() - initial <= sample_period_micros) {};
//  }
////  Serial.println(micros() - t0);
//  return 0;
//}
//came up with better way
int get_samples() { //Return i wnt/ diff vals to process for distinguishing different levels of impulses
  unsigned long long initial;
  int16_t analog;
  analogRead(A0); //first read takes longer
  for (int i = 0; i < SAMPLE_SIZE; i++) {
    analog = analogRead(A0);
    fast_samples[i] = analog;
    
    if (impulse_sample_count < IMPULSE_SIZE)  {
      impulse_samples[impulse_sample_count++] = analog;
    }
    else {
//      long t0 = micros();
      if (impulse_rms() > 3.55) { //11.4 ms (don't know how to avoid currently)
        impulse_samples[0] = analog;
        impulse_sample_count = 1; //reset impulse_sample_count when array is filled
        return 1;//4 us, including print statement time; not going to affect readings
      }
//      Serial.println(micros() - t0);
      impulse_samples[0] = analog;
      impulse_sample_count = 1; //reset impulse_sample_count when array is filled
    }
    while (micros() - initial <= sample_period_micros) {};
  }
  
  return 0;
}

float impulse_rms() {
  float mean_square = 0.0;
  for (int i = 0; i < IMPULSE_SIZE; i++) {
    //    Serial.println(fast_samples[i],8);
    mean_square += pow(sound_pressure(mic_voltage(op_amp_voltage(impulse_samples[i] - 509))), 2);
  }
  mean_square /= IMPULSE_SIZE;
  float rms = sqrt(mean_square);
  return rms;
}

float root_mean_square() { //will take too much memory to pass by value, so making separate function to pass impulse root_mean_square
  float mean_square = 0.0;
  for (int i = 0; i < SAMPLE_SIZE; i++) {
    mean_square += pow(sound_pressure(mic_voltage(op_amp_voltage(fast_samples[i] - 509))), 2);
  }
  mean_square /= SAMPLE_SIZE;
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
