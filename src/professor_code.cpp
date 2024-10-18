// C++ code
//
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

// Definindo constantes
const int pinoSensor = A0; // Pino analógico A0 conectado ao sensor de umidade
const int LED = 2; // Pino digital 2 conectado ao led vermelho
const int umidadeMinima = 0; // Valor minimo lido pelo sensor de umidade
const int umidadeMaxima = 539; // Valor máximo lido pelo sensor de umidade(3.3v)
const int limiteSoloSeco = 30; // Valor máximo para solo tipo seco
const int limiteSoloUmido = 60; // Valor máximo para solo tipo Umido

LiquidCrystal_I2C lcd(32, 16, 2);

void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  
  // Inicializando o display LCD
  lcd.init();
  lcd.backlight();
  lcd.leftToRight();
  
  // Exibindo mensagem inicial no LCD
  lcd.setCursor(3,0);
  lcd.print("Monitor de");
  lcd.setCursor(0,1);
  lcd.print("Umidade do Solo");
  delay(4000);
}

void loop()
{
  // Limpando o LCD e exibindo cabeçalho
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nivel de Umidade:");

  // Leitura da umidade do solo
  int umidadeSolo = analogRead(pinoSensor);
  
  // Converte a leitura de 0-539 para 0-100%
  umidadeSolo = map(umidadeSolo, umidadeMinima, umidadeMaxima, 0, 100);
  
  // Exibindo a porcentagem de umidade no Serial Monitor
  Serial.print(umidadeSolo);
  Serial.println("%");

  // Atualiza o LED e o display baseado na umidade
  atualizarEstadoUmidade(umidadeSolo);

  delay(2000);    
}

// Função para atualizar o estado do LED e o display com base na umidade
void atualizarEstadoUmidade(int umidade)
{
  lcd.setCursor(6,1); // Definindo o cursor para exibir o estado
  
  if(umidade <= limiteSoloSeco) {
    digitalWrite(LED, HIGH); // Acende o LED se o solo estiver seco
    lcd.print("SECO");
  } 
  else if (umidade > limiteSoloSeco && umidade <= limiteSoloUmido) {
    digitalWrite(LED, LOW); // Desliga o LED quando o solo está úmido
    lcd.print("UMIDO");
  } 
  else {
    digitalWrite(LED, LOW); // Desliga o LED quando o solo está muito úmido
    lcd.setCursor(2,1);
    lcd.print("MUITO UMIDO");
  }
}

