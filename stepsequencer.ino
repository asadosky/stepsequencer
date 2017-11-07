//new comment 1
int analogPin = A14;
int led_pin = 2;
int foto_r = 0;
int currentStep = 0;
unsigned long lastStepTime = 0;
int tempo = 100;
boolean tog_last_state = LOW;
boolean tog_button_state = LOW;
boolean tog_step_state = LOW;
boolean tog_last_state2 = LOW;
boolean tog_button_state2 = LOW;
boolean tog_step_state2 = LOW;
int count = 0;
int dark = 700;
int light = 800;

boolean last_state = false;

void setup() {
 Serial.begin(9600);
  pinMode(23, INPUT); 
  pinMode(22, INPUT); 
  pinMode(analogPin, INPUT); 
   pinMode(led_pin, OUTPUT);
}

void loop() {
  play_note();
 print_okay();
  calibrate_light();
    calibrate_dark();
}
void print_okay(){
   if (millis() > lastStepTime + tempo) {   
    lastStepTime = millis();//increment to the next step
foto_r = analogRead(analogPin);
Serial.print("sensorVal ");
Serial.println(foto_r);
   }
}
void play_note(){
   if (foto_r > (light - 200) && last_state == false)  { //if light
    usbMIDI.sendNoteOff(52, 0, 0);
    digitalWrite(led_pin, LOW);
   // Serial.println("OFF_DARK_OFF");
    last_state = true;
        
   }
   else if (foto_r < (dark + 200) && last_state == true){ //if dark. //left button
   usbMIDI.sendNoteOn(52, 127, 0);
   digitalWrite(led_pin, HIGH);
   Serial.println("ON_LIGHT_ON");
   last_state = false;
}
}

void calibrate_dark(){
    tog_last_state = tog_button_state;
    tog_button_state = digitalRead(23);
    if (tog_button_state == HIGH && tog_last_state == LOW)  
    { dark = foto_r; Serial.print("dark "); Serial.println(dark);}
}
    void calibrate_light(){
    tog_last_state2 = tog_button_state2;
    tog_button_state2 = digitalRead(22);
    if (tog_button_state2 == HIGH && tog_last_state2 == LOW)  
    { light = foto_r;  
      Serial.print("light "); Serial.println(light);} 
    }

//860 high
//450 low

