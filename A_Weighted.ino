double dBA_weighting(double dB, double f){
  double term1 = 10*log10((1.562339 * pow(f,4))/((pow(f,2) + pow(107.65265,2))*(pow(f,2) + pow(737.86223,2))));
  double term2 = 10*log10((2.242881*pow(10,16)*pow(f,4))/(pow((pow(f,2)+pow(20.598997,2)),2)*pow((pow(f,2)+pow(12194.22,2)),2)));
  return (term1+term2)+dB;
}
