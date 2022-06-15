#include <Arduino.h>
#include <Ultrasonic.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
//-------------- Minhas Classes --------------//
#include "led.h"
#include "infra.h"
//-------------- WiFi Arguments --------------//
#define WIFI_SSID "****"
#define WIFI_PASSWORD "****"
//-------------- Firebase Arguments --------------//
#define API_KEY "****"
#define DATABASE_URL "****"
#define USER_EMAIL "****"
#define USER_PASSWORD "****"
//-------------- Firebase Objects --------------//
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
//-------------- Project Objects --------------//
Ultrasonic sensorUltra(18, 19);
Led ledRed(27), ledGreen(26);
Infra sensorInfra1(4), sensorInfra2(5);
//-------------- Variaveis --------------//
int contPass, contYes, contNo;
bool flagInfra = true, flagUltra = false;
unsigned long wait_roller = 0;
//-------------- Tasks --------------//
void Sensors(void *pvParameters)
{
  String taskMessage = "Tarefa executando no núcleo: ";
  taskMessage = taskMessage + xPortGetCoreID();
  Serial.println(taskMessage);
  while (true)
  {
    int long_time = 4000;
    
    if (sensorUltra.read() <= 100 and (millis() > wait_roller))
    {
      int init_time = 0;
      flagUltra = true;
      init_time = millis();

      while ((millis() - init_time < long_time) and (sensorUltra.read() <= 100))
        ;
      if (millis() - init_time >= long_time)
      {
        Serial.println("Ultra: Avaliação iniciada.");

        while (flagInfra and sensorUltra.read() <= 100)
        {
          // Condicional Infra1
          if (sensorInfra1.checkStatus() == true and flagInfra)
          {
            ledGreen.on_status(sensorInfra1.checkStatus());
            contYes++;
            Serial.println("Infra1: Avaliação POSITIVA recebida.");
            flagInfra = false;
            ledGreen.reset();
          }
          // Condicional Infra2
          if (sensorInfra2.checkStatus() and flagInfra)
          {
            ledRed.on_status(sensorInfra2.checkStatus());
            contNo++;
            Serial.println("Infra2: Avaliação NEGATIVA recebida.");
            flagInfra = false;
            ledRed.reset();
          }

          vTaskDelay(5);
        }
        Serial.println("Ultra: avaliação concluída");
      }
    }
    else if (flagUltra)
    {
      String passagem = "Contador Passagem: ";
      passagem = passagem + contPass++;
      Serial.println(passagem);
      flagInfra = true;
      flagUltra = false;
    }
    vTaskDelay(5);
  }
}

void Database(void *pvParameters)
{
  String taskMessage = "Tarefa executando no núcleo: ";
  taskMessage = taskMessage + xPortGetCoreID();
  Serial.println(taskMessage);
  while (true)
  {
    Firebase.setInt(fbdo, "/flow", contPass);
    Firebase.setInt(fbdo, "/votes/yes", contYes);
    Firebase.setInt(fbdo, "/votes/no", contNo);

    vTaskDelay(5000);
  }
}

//-------------- Setup --------------//
void setup()
{
  Serial.begin(9600);

  // Conectando WiFi
  Serial.println();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando ao wifi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println("");
  Serial.println("Conectado com sucesso a rede.");

  // Conectando Firebase
  Firebase.begin(DATABASE_URL, API_KEY);
  Firebase.reconnectWiFi(true);

  // Construindo as tasks blink LED...
  xTaskCreatePinnedToCore(Sensors, "Sensors", 10000, NULL, 1, NULL, 0);
  delay(500);
  xTaskCreatePinnedToCore(Database, "Firebase", 10000, NULL, 2, NULL, 1);
  delay(500);
}

//-------------- Loop --------------//
void loop()
{
  
}
