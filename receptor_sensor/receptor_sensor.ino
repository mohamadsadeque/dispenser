#include <RCSwitch.h>
//Instacia a Biblioteca
RCSwitch mySwitch = RCSwitch();
//variavel responsavel em receber os dados do RF
float value = 0.0;
int dado;

float vazao; //Variável para armazenar o valor em L/min
float media = 0; //Variável para fazer a média
int contaPulso; //Variável para a quantidade de pulsos
int i = 0; //Variável para segundos
int Min = 00; //Variável para minutos
int Horas = 0; // Variável para horas
float Litros = 0; //Variável para Quantidade de agua
float MiliLitros = 0; //Variavel para Conversão

void setup() {
  Serial.begin(9600);
  // delay para estabilizacao do Sinal
  delay(3000);
  //Seta como Receptor/ O "0" é para não interromper, deixar continuo
  //O Pino padrão é o 2
  mySwitch.enableReceive(0);
 pinMode(7,OUTPUT);
 pinMode(3, INPUT);
 attachInterrupt(1, incpulso, RISING); //Configura o pino 3 interrupção
}

void loop() {
  //Quado estiver sinal disponivel

while (value > 0.0) {
  sinal();
 digitalWrite(7, LOW);
 contaPulso = 0;//Zera a variável
 sei(); //Habilita interrupção
 delay (1000); //Aguarda 1 segundo
 cli(); //Desabilita interrupção
 vazao = contaPulso / 5.9; //Converte para L/min
 i++;
 MiliLitros = vazao / 60;
 Litros = Litros + MiliLitros;
 Serial.print("Litros: ");
 Serial.println(Litros);
 if (i == 60)
 {
 Min++;  
 if (Min >= 60)
 {
 Min = 0;
 }
 i = 0; //Zera a variável i para uma nova contagem
 }
 if((value - MiliLitros) > 0.0) 
  value-= MiliLitros ; 
  else
  value = 0.0;
  Serial.print("VALOR PEDIDO: ");
  Serial.println(value);
   
  }
 if(value == 0.0){
 digitalWrite(7, HIGH);
 Serial.println("ESPERANDO...");
 while(value == 0.0 ){
  sinal();
  }
 }

} 
//========================================

  
void incpulso ()
{
 contaPulso++; //Incrementa a variável de pulsos
}

void sinal(){
  if (mySwitch.available()) {
    dado =  mySwitch.getReceivedValue();
    //recebe na variavel value o Status
    if ( dado == -9999) {
      value = 0.0;
      delay(250);
      mySwitch.resetAvailable();
    }
    else {
      if ((value + dado) > 0.0 ) {
        value = value + dado;
      }
      else {
        value = 0.0;
      }
      Serial.println(value);
      delay(300);
      mySwitch.resetAvailable();

    }

  }
  }

