void Tarefa1(void *pvParameters) {
  int tarefa1_pausada = 0;
  
  while (true) 
  {
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    
    filteredAx = (1 - alpha) * filteredAx + alpha * ax;

    Dispara_INT = (gx * 0.33) + (gy * 0.33) + (gz * 0.33);

    if (abs(Dispara_INT) < limiarParada) 
    {
      mostrarTela();
    }
  }
  Dispara_INT = constrain(Dispara_INT, -15000, 15000);
}

void mostrarTela() 
{
  if (wifiConectado && (!possivelQueda)) 
  {
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    
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
  } 
  
  else 
  {
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
  }
   
  delay(10); 
}
