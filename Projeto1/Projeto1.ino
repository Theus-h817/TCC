#include <Wire.h>
#include <MPU6050.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;
MPU6050 mpu;

TaskHandle_t Tarefa_Principal;
TaskHandle_t Tarefa_Secundaria;


int16_t ax, ay, az;  // Variáveis para os valores do acelerômetro
int16_t gx, gy, gz;  // Variáveis para os valores do giroscópio

float filteredAx = 0.0;
float alpha = 0.1; // Fator de suavização (ajuste conforme necessário)

float Dispara_INT = 0.0;  // Variável para a média ponderada do giroscópio

// Limiar de parada para o giroscópio
const int limiarParada = 100;

// Limiar para detecção de queda
float limiarQueda = 12000;

void setup() {

  xTaskCreatePinnedToCore(
                    Tarefa1,
                    "Tarefa_Principal",
                    10000,
                    NULL,
                    1,
                    &Tarefa_Principal,
                    0);                  

  xTaskCreatePinnedToCore(
                    Tarefa2,
                    "Tarefa_Secundaria",
                    10000,
                    NULL,
                    1,
                    &Tarefa_Secundaria,
                    1); 
   
   
  Wire.begin(22, 21); // Inicializa a comunicação I2C com SDA no D22 e SCL no D21
  Serial.begin(9600);
  SerialBT.begin("ESP32_BT"); // Inicia a conexão Bluetooth
  
  mpu.initialize();
  
  // Configura o sensor para interrupção ativa no pino D19
  pinMode(19, INPUT);
  digitalWrite(19, HIGH);
  
  // Verifica se o sensor está conectado corretamente
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 não encontrado. Verifique a conexão.");
    while (1);


    
  }
}

void loop() 
{
}
