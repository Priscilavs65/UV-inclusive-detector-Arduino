int buzzer = 8; // Pino digital onde o buzzer está conectado

// Define os pinos dos LEDs

#define pinLedVermelho 5  
// Pino digital 5 conectado ao LED vermelho

#define pinLedAmarelo  7  
// Pino digital 7 conectado ao LED amarelo

#define pinLedVerde    9  
// Pino digital 9 conectado ao LED verde


// Define o pino do sensor UV

#define pinSensorUV    A5 
// Pino analógico A5 conectado ao sensor UV


// Define constantes para ligar e desligar os LEDs

#define liga    HIGH     
// Nível lógico alto (5V)

#define desliga LOW      
// Nível lógico baixo (0V)


// Habilita a saída de depuração pela serial (opcional)

#define DEBUG         
  

int leituraUV = 0;                // Variável para armazenar a leitura do sensor UV

byte indiceUV = 0;             // Variável para armazenar o índice UV calculado

byte indiceUVAnterior = 0;        // Armazena o índice UV da leitura anterior

unsigned long tempoAnterior = 0;  // Variável para controlar o tempo de atualização da leitura


int contadorBuzzer = 0; // Variável para contar o número de toques do buzzer


const int maxToquesBuzzer = 5; // Define o limite máximo de toques para o buzzer  // Alterar este valor para definir o limite de toques

void setup() {

  Serial.begin(9600);                // Inicia a comunicação serial a 9600
  
  pinMode(buzzer, OUTPUT);         // Define o pino do buzzer como saída
  
  pinMode(pinLedVerde, OUTPUT);      // Define o pino do LED verde como saída
 
  pinMode(pinLedAmarelo, OUTPUT);    // Define o pino do LED amarelo como saída
 
  pinMode(pinLedVermelho, OUTPUT);   // Define o pino do LED vermelho como saída
  
  pinMode(pinSensorUV, INPUT);       // Define o pino do sensor UV como entrada

 
 #ifdef DEBUG
    
Serial.println("Fim Setup");     // Imprime mensagem de depuração na serial
 
 #endif  
}


void loop() {
  leituraUV = analogRead(pinSensorUV);       // Lê o valor analógico do sensor UV
  
   indiceUV = map(leituraUV, 0, 203, 0, 10);  // Mapeia a leitura do sensor para o índice UV
 
 #ifdef DEBUG
   
 Serial.print("Indice UV: ");             // Imprime o índice UV na serial
    
  Serial.println(indiceUV);
  
#endif

  
if (indiceUV != indiceUVAnterior)               // Verifica se o índice UV mudou
{
    contadorBuzzer = 0;                      // Reseta o contador de toques do buzzer ao detectar mudança
   
 indiceUVAnterior = indiceUV;             // Atualiza o índice UV anterior para o atual
  }

 
 if (indiceUV >= 6) {                       // Índice UV alto (>= 6)
    
   acendeLed(pinLedVermelho);               // Acende o LED vermelho
    
      tocaBuzzer(440);                         // Toca o buzzer com frequência de 440 Hz
  
} 
else if (indiceUV >= 3) {                // Índice UV moderado (>= 3)
    
acendeLed(pinLedAmarelo);                // Acende o LED amarelo
    
tocaBuzzer(880);                         // Toca o buzzer com frequência de 880 Hz
}
 
else {                                   // Índice UV baixo (< 3)
   
 acendeLed(pinLedVerde);                  // Acende o LED verde
    
  tocaBuzzer(1760);                        // Toca o buzzer com frequência de 1760 Hz
  }

  // Controla o tempo de atualização da leitura do sensor (500ms)
  unsigned long tempoAtual = millis();       // Obtém o tempo atual em milissegundos
  if (tempoAtual - tempoAnterior >= 500) {   // Verifica se passou 500ms desde a última leitura
    tempoAnterior = tempoAtual;              // Atualiza o tempo da última leitura
    // Código para ler o sensor e atualizar o índice UV (pode ser adicionado aqui)
  }
}

// Função para acender um LED específico e apagar os outros
void acendeLed(int pinoLed) {
  digitalWrite(pinLedVermelho, desliga);  // Desliga o LED vermelho
  digitalWrite(pinLedAmarelo, desliga);   // Desliga o LED amarelo
  digitalWrite(pinLedVerde, desliga);     // Desliga o LED verde
  digitalWrite(pinoLed, liga);            // Liga o LED especificado
}

// Função para tocar o buzzer com uma frequência específica
void tocaBuzzer(int frequencia) {
  // Toca o buzzer apenas se o número de toques estiver abaixo do limite
  if (contadorBuzzer < maxToquesBuzzer) {
    tone(buzzer, frequencia);         // Liga o buzzer com a frequência especificada
    
delay(500);                       // Aguarda 500 milissegundos
    noTone(buzzer);                   // Desliga o buzzer
    delay(500);                       // Aguarda 500 milissegundos
    contadorBuzzer++;                 // Incrementa o contador de toques
  }
}

