// Aqui serão aloacadas as tarefas de comunicação com o usuério e demais recursos não cruciais do ESP32, estaas serão estabelecidas no core 0 

void Tarefa2(void *pvParameters) 
{
  bool quedaDetectada = false;
  bool alertaAtivo = false;
  unsigned long tempoInicial = 0;

  while (true) 
  {
    // Verifica se os valores de Dispara_INT ultrapassam o limite
    if (abs(Dispara_INT) > limiarQueda) 
    {
      // Se uma queda for detectada e o alerta não estiver ativo
      if (!quedaDetectada && !alertaAtivo) 
      {
        quedaDetectada = true;
        alertaAtivo = true;
        tempoInicial = millis(); // Inicia contagem de tempo
        // Pergunta ao usuário se houve queda
        Serial.println("Você sofreu uma queda? Responda 'sim' ou 'não' em 15 segundos.");
        delay(1500);
      } else if (quedaDetectada && alertaAtivo && millis() - tempoInicial > 15000) 
      {
        // Se o usuário não responder dentro do tempo limite
        Serial.println("ALERTA DE QUEDA, CONTATANDO RESPONSÁVEL");
        delay(1500);
      }
      
    }

    // Se o alerta estiver ativo, aguarda a resposta do usuário
    if (alertaAtivo == true || quedaDetectada == true) 
    {
      if (Serial.available() > 0) 
      {
        String resposta = Serial.readStringUntil('\n');
        resposta.trim();
        if (resposta.equalsIgnoreCase("sim")) 
        {
          // Resposta do usuário: sim
             Serial.println("ALERTA DE QUEDA, CONTATANDO RESPONSÁVEL");
             
        } else if (resposta.equalsIgnoreCase("não") || resposta.equals("123")) 
        {
          // Resposta do usuário: não ou código 123
          alertaAtivo = false;
          quedaDetectada = true;
        }
      }
    }

    // Aguarda um curto período de tempo para evitar sobrecarga do processador
    vTaskDelay(20); // Ajuste conforme necessário
  }
}
