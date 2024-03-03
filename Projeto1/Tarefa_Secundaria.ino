void Tarefa2(void *pvParameters) 
{
  while (true) 
  {
    if (abs(Dispara_INT) > limiarQueda) 
    {
        possivelQueda = true;
        Serial.println(F("Você sofreu uma queda? Responda 'sim' ou 'não' em 15 segundos."));
        tempoInicial = millis();
    }

    
    if (possivelQueda) 
    {
      if (Serial.available() > 0) 
      {
        String resposta = Serial.readStringUntil('\n');
        resposta.trim();

        if (resposta.equalsIgnoreCase("sim")) 
        {
          Queda();
          // Ação a ser realizada se o usuário responder "sim"
          // Por exemplo, enviar mensagem de alerta
 
        } 

        else if(possivelQueda && millis() - tempoInicial > 15000)
        {
          Queda();
          // Ação a ser realizada se o usuário responder "sim"
          // Por exemplo, enviar mensagem de alerta
        }
   
        else if (resposta.equalsIgnoreCase("não")) 
        {
          Serial.println(F("ALERTA IGNORADO, RETOMANDO MONITORAMENTO"));
          // Ação a ser realizada se o usuário responder "não"
          // Por exemplo, desativar o alerta
          possivelQueda = false;
          tempoInicial = 0;
        }
      }
    }

    vTaskDelay(20); 
  }
}

void Queda()
{
    Serial.println(F("ALERTA DE QUEDA, CONTATANDO RESPONSÁVEL"));
    
    delay(15000);

    possivelQueda = false;
    tempoInicial = 0;
}
