const double feedback_gain = 26; //set by trimmer-pot behind amp
const double atmospheric_pressure = 101325; //changes constantly.


double op_amp_voltage(int adc_output){
  return adc_output * (3.3/1023);
}

double mic_voltage(double op_amp_voltage) {
  return op_amp_voltage/feedback_gain;
}

double sound_pressure(double mic_voltage){
  return mic_voltage * pow(10, 44/20);
}

double pascal_to_dBSPL(long double pascal_amplitude){ //using long double because previously using double processor assumed amplitude was 0 instead of a really small num
  if (pascal_amplitude <= 0) return 55.85;
  long double middle = pascal_amplitude/0.00002;
  return 20 * log10(middle);
}

double adc_to_dBSPL(int adc_output){
  return pascal_to_dBSPL(sound_pressure(mic_voltage(op_amp_voltage(adc_output))));
}
