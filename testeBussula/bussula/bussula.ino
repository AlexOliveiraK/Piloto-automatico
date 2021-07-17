#include <Wire.h>
#include <MechaQMC5883.h>

MechaQMC5883 qmc;
const int destino = 10;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  qmc.init();
  //qmc.setMode(Mode_Continuous,ODR_200Hz,RNG_2G,OSR_256);
}

void loop() {
  int x, y, z;
  int azimuth;
  //float azimuth; //is supporting float too
  qmc.read(&x, &y, &z,&azimuth);
  Serial.print(" a: ");
  Serial.print(azimuth);
  Serial.println();
  Navega(azimuth);
  delay(300);
}

void Navega(int az){
  bool azPositivo = az <= 180;
  bool destinoPositivo = destino <= 180;
  Serial.print("dif:");
  Serial.print(az - destino);
  Serial.println();
  
  if(azPositivo && destinoPositivo){
    if(az > destino){
      Serial.println("ambos positivos esquerda");       
    }
    else{
      Serial.println("ambos positivos direita");
    }
  }

  if(!azPositivo && !destinoPositivo){
    if(az < destino){
      Serial.println("ambos negativos !direita");       
    }
    else{
      Serial.println("ambos negativos !esquerda");
    }
  }

  if(azPositivo != destinoPositivo){
    if(!azPositivo){
      az = az - 180;
      if(az > destino){
        Serial.println("!azPositivo direita");       
      }
      else{
        Serial.println("!azPositivo esquerda");       
      }
    }

    if(!destinoPositivo){
      az = az + 180;
      if(az > destino){
        Serial.println("!azPositivo direita");
      }
      else{
        Serial.println("!azPositivo esquerda");       
      }
    }
  }
}
