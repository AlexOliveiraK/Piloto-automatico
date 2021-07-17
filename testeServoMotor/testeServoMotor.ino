#include <Servo.h>

Servo motor;

void setup() {
  motor.attach(7);
  Serial.begin(9600);
  Serial.println("PRONTO");
}

void loop() {

  for(int i = 0; i <= 150; i++){
    motor.write(i);
    delay(50);
  }

    for(int i = 150; i >= 0; i--){
    motor.write(i);
    delay(50);
  }
  
  delay(500);
}
