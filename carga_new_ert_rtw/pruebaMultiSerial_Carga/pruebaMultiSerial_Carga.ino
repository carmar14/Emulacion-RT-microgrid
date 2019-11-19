#include <FreeRTOS_ARM.h>

int loadVolt = 0;
int Bio = 0, Dies = 0, EnAlt = 0;

void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  Serial.begin(115200);               // Velocidad de comunicación serial
  Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);

  xTaskCreate(commIN_Rasp, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  xTaskCreate(commOut_Rasp, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  xTaskCreate(commIN_1, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  xTaskCreate(commIN_2, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  xTaskCreate(commIN_3, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  xTaskCreate(commOut_all, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
}

static void commIN_Rasp(void* arg) {

  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  while (1) {
    SerialUSB.flush();
    loadVolt = SerialUSB.parseInt();
    //loadVolt = loadVolt_Cad.toInt();

    vTaskDelayUntil(&xLastWakeTime, (10 / portTICK_PERIOD_MS));
  }

}


static void commOut_Rasp(void* arg) {
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  while (1) {

    SerialUSB.print('s');
    SerialUSB.print(Bio);
    SerialUSB.print(',');
    SerialUSB.print(Dies);
    SerialUSB.print(',');
    SerialUSB.print(EnAlt);
    SerialUSB.print(',');
    SerialUSB.println('e');
    vTaskDelayUntil(&xLastWakeTime, (10 / portTICK_PERIOD_MS));
  }
}


static void commIN_1(void* arg) {
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  while (1) {
    Serial1.flush();
    Bio = Serial1.parseInt();

    vTaskDelayUntil(&xLastWakeTime, (10 / portTICK_PERIOD_MS));
  }
}


static void commIN_2(void* arg) {
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  while (1) {
    Serial2.flush();
    Dies = Serial2.parseInt();

    vTaskDelayUntil(&xLastWakeTime, (10 / portTICK_PERIOD_MS));
  }
}


static void commIN_3(void* arg) {
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  while (1) {
    Serial3.flush();
    EnAlt = Serial3.parseInt();

    vTaskDelayUntil(&xLastWakeTime, (10 / portTICK_PERIOD_MS));
  }
}


static void commOut_all(void* arg) {
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  while (1) {
    Serial.println(loadVolt);
    vTaskDelayUntil(&xLastWakeTime, (10 / portTICK_PERIOD_MS));
  }
}


void loop() {}
