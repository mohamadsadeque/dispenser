
float vazao; //Variável para armazenar o valor em L/min
float media = 0; //Variável para fazer a média
int contaPulso; //Variável para a quantidade de pulsos
int i = 0; //Variável para segundos
int Min = 00; //Variável para minutos
int Horas = 0; // Variável para horas
float Litros = 0; //Variável para Quantidade de agua
float MiliLitros = 0; //Variavel para Conversão
  
  
  
  
void setup()
{
 Serial.begin(9600);
 delay(3000); 
 pinMode(2, INPUT);
 attachInterrupt(0, incpulso, RISING); //Configura o pino 2(Interrupção 0) interrupção
}
  
  
void loop ()
{
 contaPulso = 0;//Zera a variável
 sei(); //Habilita interrupção
 delay (1000); //Aguarda 1 segundo
 cli(); //Desabilita interrupção
  
 vazao = contaPulso / 5.5; //Converte para L/min
 media = media + vazao; //Soma a vazão para o calculo da media
 i++;
 Serial.print("Vazao");
 Serial.print(vazao); //Escreve no display o valor da vazão
 Serial.print(" L/min "); //Escreve L/min
 Serial.print("Tempo: ");
 Serial.print(Horas);
 Serial.print(":");//Escreve :
 Serial.print(Min);
 Serial.print(":"); //Escreve :
 Serial.println(i); //Escreve a contagem i (segundos)
 MiliLitros = vazao / 60;
 Litros = Litros + MiliLitros;
 Serial.print("Litros: ");
 Serial.print(Litros);
 
  
 // Neste conjunto de linhas fizemos a média das leituras obtidas a cada 1 minuto
 if (i == 60)
 {
 Min++;  
 if (Min >= 60)
 {
 Horas++;
 Min = 0;
 }
 media = 0; //Zera a variável media para uma nova contagem
 i = 0; //Zera a variável i para uma nova contagem
 }
  
}
  
  
void incpulso ()
{
 contaPulso++; //Incrementa a variável de pulsos
}
