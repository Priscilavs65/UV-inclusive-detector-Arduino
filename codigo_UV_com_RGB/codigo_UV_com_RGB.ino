int buzzer = 8; // Pino digital onde o buzzer está conectado

// Define os pinos do LED RGB
#define pinLedVermelho 12 // Pino digital 9 conectado ao LED vermelho do RGB
#define pinLedVerde 10   // Pino digital 10 conectado ao LED verde do RGB
#define pinLedAzul 11    // Pino digital 11 conectado ao LED azul do RGB

// Define o pino do sensor UV
#define pinSensorUV A5 // Pino analógico A5 conectado ao sensor UV

// Define constantes para ligar e desligar os LEDs
#define liga HIGH    // Nível lógico alto (5V)
#define desliga LOW   // Nível lógico baixo (0V)

// Habilita a saída de depuração pela serial (opcional)
#define DEBUG

int leituraUV = 0;          // Variável para armazenar a leitura do sensor UV
byte indiceUV = 0;          // Variável para armazenar o índice UV calculado
byte indiceUVAnterior = 0; // Armazena o índice UV da leitura anterior
unsigned long tempoAnterior = 0; // Variável para controlar o tempo de atualização da leitura

// Variável para contar o número de toques do buzzer
int contadorBuzzer = 0;

// Define o limite máximo de toques para o buzzer
const int maxToquesBuzzer = 5; // Alterar este valor para definir o limite de toques

void setup() {
  Serial.begin(9600);          // Inicia a comunicação serial a 9600 baud
  pinMode(buzzer, OUTPUT);      // Define o pino do buzzer como saída
  pinMode(pinLedVermelho, OUTPUT); // Define o pino do LED vermelho como saída
  pinMode(pinLedVerde, OUTPUT);   // Define o pino do LED verde como saída
  pinMode(pinLedAzul, OUTPUT);    // Define o pino do LED azul como saída
  pinMode(pinSensorUV, INPUT);   // Define o pino do sensor UV como entrada

#ifdef DEBUG
  Serial.println("Fim Setup");  // Imprime mensagem de depuração na serial
#endif
}

void loop() {
  leituraUV = analogRead(pinSensorUV);      // Lê o valor analógico do sensor UV
  indiceUV = map(leituraUV, 0, 203, 0, 10); // Mapeia a leitura do sensor para o índice UV

#ifdef DEBUG
  Serial.print("Indice UV: ");           // Imprime o índice UV na serial
  Serial.println(indiceUV);
#endif

  // Verifica se o índice UV mudou
  if (indiceUV != indiceUVAnterior) {
    contadorBuzzer = 0;                  // Reseta o contador de toques do buzzer ao detectar mudança
    indiceUVAnterior = indiceUV;          // Atualiza o índice UV anterior para o atual
  }

  if (indiceUV >= 6) {                    // Índice UV alto (>= 6)
    acendeLed(255, 0, 0); // Vermelho
    tocaBuzzer(440);                  // Toca o buzzer com frequência de 440 Hz
  } else if (indiceUV >= 3) {           // Índice UV moderado (>= 3)
    acendeLed(255, 255, 0); // Amarelo
    tocaBuzzer(880);                  // Toca o buzzer com frequência de 880 Hz
  } else {                              // Índice UV baixo (< 3)
    acendeLed(0, 255, 0); // Verde
    tocaBuzzer(1760);                 // Toca o buzzer com frequência de 1760 Hz
  }

  // Controla o tempo de atualização da leitura do sensor (500ms)
  unsigned long tempoAtual = millis();    // Obtém o tempo atual em milissegundos
  if (tempoAtual - tempoAnterior >= 500) {  // Verifica se passou 500ms desde a última leitura
    tempoAnterior = tempoAtual;          // Atualiza o tempo da última leitura
    // Código para ler o sensor e atualizar o índice UV (pode ser adicionado aqui)
  }
}

// Função para acender o LED RGB com a cor especificada
void acendeLed(int vermelho, int verde, int azul) {
  analogWrite(pinLedVermelho, vermelho);
  analogWrite(pinLedVerde, verde);
  analogWrite(pinLedAzul, azul);
}

// Função para tocar o buzzer com uma frequência específica
void tocaBuzzer(int frequencia) {
  // Toca o buzzer apenas se o número de toques estiver abaixo do limite
  if (contadorBuzzer < maxToquesBuzzer) {
    tone(buzzer, frequencia);      // Liga o buzzer com a frequência especificada
    delay(500);                    // Aguarda 500 milissegundos
    noTone(buzzer);                // Desliga o buzzer
    delay(500);                    // Aguarda 500 milissegundos
    contadorBuzzer++;              // Incrementa o contador de toques
  }
}

