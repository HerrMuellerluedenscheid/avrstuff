void setup_PWM(){
    //DDRD |= 0xFF;
    DDRD |= (1<<PIND5);
    TCCR1A |= 1<<WGM11 | 1<<COM1A1 | 1<<COM1A0;
    TCCR1B |= 1<<WGM12 | 1<<WGM13 | 1<<CS10;
    ICR1 = 19999;
}

void set_PWM_range(float factor, float max_left, float max_right){
    OCR1A = ICR1 - (max_left+(max_right-max_left)*factor); //18000
}

void set_PWM_percent(float factor){
    OCR1A = ICR1-ICR1*factor; //18000
}

