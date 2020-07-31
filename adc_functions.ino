// initialize adc
void adc_init()
{
    // External AREF, right-adjusted (to left-adjust (1<<ADLAR));
    // ADMUX = (0<<REFS1)|(0<<REFS0)|(0<<ADLAR); //uncomment if all zeros is not default
 
    // ADC Enable and prescaler of 128
    // 16000000/128 = 125000
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}
