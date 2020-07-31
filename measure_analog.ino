//#include <arduinoFFT.h>
//
//#define SAMPLES 128           //Must be a power of 2
//#define SAMPLING_FREQUENCY 10000 //Hz, must be less than 10000 due to ADC
//
//const int sampling_period_ms = 1000 * 1/SAMPLING_FREQUENCY;
//
//#define MicSamples (1024*2)
//#define MicPin A0
//
//double dB_SPL()
//{
//    double signalAvg = 0.0, signalMax = 0.0, signalMin = 1025, t0 = millis();
//    for (int i = 0; i < MicSamples; i++)
//    {
//        double k = analogRead(MicPin);
//        signalMax = max(signalMax, k);
//        signalAvg += k;
//    }
//    signalAvg /= MicSamples;
//    
//    return adc_to_dBSPL(signalMax - signalAvg);
//}
//
//double main_f(){
//  long milliseconds;
//   
//  double vReal[SAMPLES];
//  double vImag[SAMPLES];
//  
//  arduinoFFT FFT = arduinoFFT();
//  /*SAMPLING*/
//  for(int i=0; i<SAMPLES; i++)
//  {
//   
//      vReal[i] = analogRead(A0);
//      vImag[i] = 0;
//   
//      milliseconds = millis();    //Overflows after around 70 minutes!
//      while(millis() < (milliseconds + sampling_period_ms)){
//      }
//  }
//
//  /*FFT*/
//  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
//  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
//  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
//  double main_f = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY) * 0.82;
//
//  return main_f;
//}
