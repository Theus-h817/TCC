#include <Wire.h>
#include <MPU6050.h>
#include <BluetoothSerial.h>
#include <WiFi.h>
#include <ArduinoOTA.h>

BluetoothSerial SerialBT;
MPU6050 mpu;

TaskHandle_t Tarefa_Principal;
TaskHandle_t Tarefa_Secundaria;

int16_t ax, ay, az;
int16_t gx, gy, gz; 

float filteredAx = 0.0;
float alpha = 0.1; 

float Dispara_INT = 0.0; 

const int limiarParada = 100;
float limiarQueda = 12000;

bool possivelQueda = false;
unsigned long tempoInicial = 0;

bool wifiConectado = false;
void conectarWiFi();
void Queda();

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

  Wire.begin(22, 21); 
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT"); 
  
  mpu.initialize();
  
  pinMode(19, INPUT);
  digitalWrite(19, HIGH);
  
  if (!mpu.testConnection()) 
  {
    Serial.println(F("MPU6050 não encontrado. Verifique a conexão."));
    while (1);
  }
  else {
    Serial.println(F("MPU6050 encontrado, iniciando a busca Wi-Fi."));
    conectarWiFi(); // Chamada da função para conectar ao Wi-Fi
  }
}

void conectarWiFi() 
{
  WiFi.mode(WIFI_STA);
  int numNetworks = WiFi.scanNetworks();
  Serial.println("Redes disponíveis:");
  
  for (int i = 0; i < numNetworks; i++) 
  {
    Serial.println(WiFi.SSID(i));
  }
  
  String chosenSSID;
  Serial.println(F("Digite o nome da rede desejada (somente redes 2.5G):"));
  
  while (!wifiConectado) {
    while (!Serial.available()) 
    {
      delay(50);
    }
    
    chosenSSID = Serial.readStringUntil('\n'); // Alterado aqui
    chosenSSID.trim();
    Serial.print("Rede escolhida: ");
    Serial.println(chosenSSID);
    bool found = false;
    
    for (int i = 0; i < numNetworks; i++) 
    {
      if (chosenSSID.equals(WiFi.SSID(i))) 
      {
        found = true;
        break;
      }
    }
    
    if (!found) 
    {
      Serial.println(F("Rede não encontrada. Por favor, tente novamente:"));
      chosenSSID = "";
      conectarWiFi();
    } 
    
    else 
    {
      Serial.println(F("Digite a senha:"));
      while (!Serial.available()) 
      {
        delay(100);
      }
      
      String password = Serial.readStringUntil('\n'); // Alterado aqui
      password.trim();
      Serial.println("Conectando a " + chosenSSID);
      WiFi.begin(chosenSSID.c_str(), password.c_str());
      int tentativas = 0;

      
      while (WiFi.waitForConnectResult() != WL_CONNECTED && tentativas < 3) 
      {
        Serial.println("Falha na conexão! Tentando novamente...");
        delay(1000);
        WiFi.begin(chosenSSID.c_str(), password.c_str());
        tentativas++;
      }
      
      if (WiFi.status() == WL_CONNECTED) 
      {
        Serial.println("Conectado a " + chosenSSID);
        Serial.print(F("Endereço IP: "));
        Serial.println(WiFi.localIP());
        wifiConectado = true;
      } 
      
      else 
      {
        Serial.println("Não foi possível conectar ao Wi-Fi após 3 tentativas.");
        chosenSSID = "";
        conectarWiFi();
      }
    }
  }
}

void loop() {
  ArduinoOTA.handle();
}
