#include <LiquidCrystal.h>

#define pGas A5

LiquidCrystal lcd1(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd2(12, 6, 5, 4, 3, 2);
int Pino_umidade=A1;
int SensorTempPino=A0;
int AlertaTempBaixa=9;
int AlertaOK=8;
int AlertaTempAlta=7;
int TempBaixa=0;
int TempAlta=19;

void setup() { 
  	pinMode(AlertaTempBaixa, OUTPUT);
    pinMode(AlertaOK, OUTPUT);
	pinMode(AlertaTempAlta, OUTPUT);
	lcd1.begin(16,2);
	lcd1.print("Temperatura :");
	lcd1.setCursor(0,1);
	lcd1.print("      C        F");
    Serial.begin(9600);     
    lcd2.begin(16,2);
    lcd2.clear();
    lcd2.setCursor(0,0);
    lcd2.print("Gas e Umidade:");
}

void loop() {
	int SensorTempTensao=analogRead(SensorTempPino);
	float Tensao=SensorTempTensao*5;
	Tensao/=1024;
	float TemperaturaC=(Tensao-0.5)*100;
	float TemperaturaF=(TemperaturaC*9/5)+32;
  	lcd1.setCursor(0,1);
	lcd1.print(TemperaturaC);
	lcd1.setCursor(9,1);
   	lcd1.print(TemperaturaF);
    int sinalGas=analogRead(pGas);
    sinalGas=map(sinalGas,300,750,0,100);
    float umidade = analogRead(Pino_umidade);
    umidade = (umidade/1023);
    umidade = umidade*100;  
    lcd2.setCursor(0,1);
    lcd2.print(sinalGas);
    lcd2.print(" %");
    lcd2.setCursor(8,1);
    lcd2.print(umidade);
    lcd2.print(" %   ");           
    lcd2.setCursor(0,0);
       
   
  delay(100);
  {   
	
  	if (TemperaturaC>=TempAlta) {
      	digitalWrite(AlertaOK,LOW);
  		digitalWrite(AlertaTempBaixa, LOW);
  		digitalWrite(AlertaTempAlta, HIGH);
        Serial.print("ALERTA, A TEMPERATURA ESTA ALTA DEMAIS! \n");
    }
  	else if (TemperaturaC<=TempBaixa){
      	digitalWrite(AlertaOK,LOW);
  		digitalWrite(AlertaTempBaixa, HIGH);
  		digitalWrite(AlertaTempAlta, LOW);        
        Serial.print("ALERTA, A TEMPERATURA ESTA BAIXA DEMAIS! \n");
    }
    else{
  		digitalWrite(AlertaTempBaixa, LOW);
  		digitalWrite(AlertaTempAlta, LOW);
        digitalWrite(AlertaOK, HIGH);
        Serial.print("A temperatura esta na faixa recomendada! \n");
        analogRead;
    }
        delay(10000);
}
       
}
 