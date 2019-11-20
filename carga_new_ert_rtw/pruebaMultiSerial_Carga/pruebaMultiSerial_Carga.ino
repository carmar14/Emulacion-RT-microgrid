#include <FreeRTOS_ARM.h>

int loadVolt = 0;
int loadVoltA = 0;
int Bio = 0, Dies = 0, EnAlt = 0;

void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  Serial.begin(115200);               // Velocidad de comunicación serial
  Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);

  analogWriteResolution(12);

  xTaskCreate(commIN_Rasp, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  xTaskCreate(commOut_Rasp, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  xTaskCreate(commIN_1, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  xTaskCreate(commIN_2, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  xTaskCreate(commIN_3, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  xTaskCreate(commOut_all, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  vTaskStartScheduler();
}

static void commIN_Rasp(void* arg) {

  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  while (1) {

    if (SerialUSB.available()) {
      loadVolt = SerialUSB.parseInt();
      //loadVolt = loadVolt_Cad.toInt();
      SerialUSB.flush();
    }

    loadVoltA=map(Dies,-4800,4800,0,4095);
    analogWrite(DAC0,loadVoltA);    

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

    if (Serial1.available()) {
      Bio = Serial1.parseInt();
      Serial1.flush();
    }

    vTaskDelayUntil(&xLastWakeTime, (10 / portTICK_PERIOD_MS));
  }
}


static void commIN_2(void* arg) {
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  while (1) {

    if (Serial2.available()) {
      Dies = Serial2.parseInt();
      Serial2.flush();
    }

    vTaskDelayUntil(&xLastWakeTime, (10 / portTICK_PERIOD_MS));
  }
}


static void commIN_3(void* arg) {
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  while (1) {

    if (Serial2.available()) {
      EnAlt = Serial3.parseInt();
      Serial3.flush();
    }

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
