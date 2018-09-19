#include <RCSwitch.h>
//Instacia a Biblioteca
RCSwitch mySwitch = RCSwitch();
//variavel responsavel em receber os dados do RF
const byte interruptPin = 3;
int value = 0;
int dado = 0;
int dadoR;
int estado = 0;
unsigned long tempo1;
unsigned long tempo2=0;
int chave[] = {7, 8, 9, 10};

void interrupt() {
  tempo1 = millis();
  if((tempo1 - tempo2) > 200){
  tempo2 = tempo1;
  Serial.println("entrei");
  estado = !estado;
  digitalWrite(7,estado);
  delay(300);
  }
}
void setup() {
   
  for (int i = 0; i < 4; i++) {
    pinMode(chave[i], INPUT_PULLUP);
  }
  for (int i = 0; i < 4; i++) {
    if (digitalRead(chave[i])) {
      dado += pow(2, i);
    }
  }

  // delay para estabilizacao do Sinal
  delay(500);
  //Seta como Receptor/ O "0" é para não interromper, deixar continuo
  //O Pino padrão é o 2
  mySwitch.enableReceive(0);
  pinMode(7, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), interrupt, CHANGE);

}




void loop() {
  //Quado estiver sinal disponivel
  if (mySwitch.available()) {
    Serial.println(dado);
    //dado =  mySwitch.getReceivedValue();
    //recebe na variavel value o Status
    if ( dadoR == dado) {
      estado = !estado;
    }
    delay(100); 
  digitalWrite(7, estado);
  
  delay(150);
  mySwitch.resetAvailable();
  }
 

}





//========================================
