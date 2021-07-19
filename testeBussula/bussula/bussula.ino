#include <Wire.h>
#include <MechaQMC5883.h>

MechaQMC5883 qmc;
const short destino = 350;
const short tolerancia = 3;
short diferenca = 0;
short comando = 0;

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
  Serial.println();
  Serial.println();
  Serial.print("az: ");
  Serial.print(azimuth);
  Serial.println();
  Orientacao(azimuth);
  delay(500);
}

void Orientacao(int rumoAtual){
  bool azPositivo = rumoAtual <= 180;
  bool destinoPositivo = destino <= 180;

  if((azPositivo && destinoPositivo) || (!azPositivo && !destinoPositivo)){
    if(rumoAtual > destino){
      comando = 2;
    }
    else{
      comando = 1;
    }

    diferenca = abs(rumoAtual - destino);
  }

  if(azPositivo != destinoPositivo){
    if(azPositivo){
      if(diferenca < 180){
        comando = 2;
      }
      else{
        comando = 1;
      }
    }
    else{
      if(diferenca > 180){
        comando = 2;
      }
      else{
        comando = 1;
      }
    }
    
    diferenca = 360 - destino + rumoAtual; 
  }

  if(comando == 1 && diferenca > tolerancia ){
    Serial.println("Virar a direita");  
  }else if(comando == 2 && diferenca > tolerancia){
    Serial.println("Virar a esquerda");  
  }else{
    Serial.println("Manter");  
  }

  Serial.print("Diferenca:");
  Serial.print(diferenca); 
}
