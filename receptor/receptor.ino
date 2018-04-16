#include <RCSwitch.h>
//Instacia a Biblioteca
RCSwitch mySwitch = RCSwitch();
//variavel responsavel em receber os dados do RF
int value = 0;
int dado;

void setup() {
  Serial.begin(9600);
  // delay para estabilizacao do Sinal
  delay(500);
  //Seta como Receptor/ O "0" é para não interromper, deixar continuo
  //O Pino padrão é o 2
  mySwitch.enableReceive(0);
}

void loop() {
  //Quado estiver sinal disponivel
  if (mySwitch.available()) {
    dado =  mySwitch.getReceivedValue();
    //recebe na variavel value o Status
    if ( dado == -9999) {
      value = 0;
      delay(250);
      mySwitch.resetAvailable();
    }
    else {
      if ((value + dado) > 0 ) {
        value = value + dado;
      }
      else {
        value = 0;
      }
      Serial.println(value);
      delay(250);
      mySwitch.resetAvailable();

    }

  }

  if (value > 0) {
    value--;
  }
  Serial.println(value);
  delay(250);

}
//========================================
