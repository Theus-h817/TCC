// Aqui serão aloacadas as tarefas de leitura de dados e comunicação bluetooth do ESP32, estaas serão estabelecidas no core 0 

// Protótipo da função mostrarTela()
void mostrarTela();

void Tarefa1(void *pvParameters) 
{
  
// Variável para controlar o estado da Tarefa1
  int tarefa1_pausada = 0;

  while (true) 
  {
    // Lê os valores do acelerômetro e giroscópio
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    
    // Aplica o filtro de média móvel no acelerômetro
    filteredAx = (1 - alpha) * filteredAx + alpha * ax;

    // Calcula a média ponderada do giroscópio
    Dispara_INT = (gx * 0.33) + (gy * 0.33) + (gz * 0.33);

    // Aplica o limiar de parada
    if (abs(Dispara_INT) < limiarParada) 
    {
      mostrarTela();
    }
  }
    // Limita o intervalo de valores
    Dispara_INT = constrain(Dispara_INT, -15000, 15000);
}
  void mostrarTela()
  {
      // Exibe as leituras no Serial Plotter em formato CSV
    Serial.print("Acelerometro_X:");
    Serial.print(ax);
    Serial.print(",Acelerometro_Y:");
    Serial.print(ay);
    Serial.print(",Acelerometro_Z:");
    Serial.print(az);
    Serial.print(",Giroscopio_X:");
    Serial.print(gx);
    Serial.print(",Giroscopio_Y:");
    Serial.print(gy);
    Serial.print(",Giroscopio_Z:");
    Serial.print(gz);
    Serial.print(",Dispara_INT:");
    Serial.println(Dispara_INT);
    
    // Envia as leituras via Bluetooth
    SerialBT.print("Acelerometro_X:");
    SerialBT.print(ax);
    SerialBT.print(",Acelerometro_Y:");
    SerialBT.print(ay);
    SerialBT.print(",Acelerometro_Z:");
    SerialBT.print(az);
    SerialBT.print(",Giroscopio_X:");
    SerialBT.print(gx);
    SerialBT.print(",Giroscopio_Y:");
    SerialBT.print(gy);
    SerialBT.print(",Giroscopio_Z:");
    SerialBT.print(gz);
    SerialBT.print(",Dispara_INT:");
    SerialBT.println(Dispara_INT);
    
    // Aguarda um curto período de tempo para que o Serial Plotter atualize
    delay(10); // Você pode ajustar esse valor conforme necessário

    
  }
