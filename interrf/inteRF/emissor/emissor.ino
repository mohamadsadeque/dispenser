//importa a biblioteca RCSwitch
#include <RCSwitch.h>
#include <Keypad.h>

int valor = 0;
int operador;
const byte numRows = 4;
const byte numCols = 4;
char keymap[numRows][numCols] = {
  {'1', '2', '3', 'A'},

  {'4', '5', '6', 'B'},

  {'7', '8', '9', 'C'},

  {'*', '0', '#', 'D'}
};

byte rowPins[numRows] = {9, 8, 7, 6}; //linhas 0 a 3

byte colPins[numCols] = {5, 4, 3, 2}; //Colunas 0 a 3

//inicializar uma instancia da classe keypad

Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

//Instacia a Biblioteca RF
RCSwitch mySwitch = RCSwitch();



void setup() {
  Serial.begin(9600);
  // Seta como habilitado para enviar dados RF o pino 10
  mySwitch.enableTransmit(10);
  delay(50);

}


void loop() {

    valor = valorLido().toInt();
    Serial.println(valor);
    mySwitch.send(valor, 24);
    
  
}



String valorLido() {
  String valorDigitado = "";
  char teclaPressionada = myKeypad.getKey();
  while (teclaPressionada != '#') {
    teclaPressionada = myKeypad.getKey();
    if ((teclaPressionada != NO_KEY) && (teclaPressionada != '#')) {
      valorDigitado.concat(teclaPressionada);// concatena os valores que recebe com os já recebidos anteriormente
    }
  }
  return (valorDigitado); // retorna o valor digitado para a função anterior
}

int operacao() {
  char teclaPressionada = myKeypad.getKey();
  while (teclaPressionada != '#') {
    teclaPressionada = myKeypad.getKey();
    if (teclaPressionada == 'A') {
      return 1;
    }
    else if (teclaPressionada == 'B') {
      return -1;
    }
    else if (teclaPressionada == 'C') {
      return 0;
    }

  }
}

