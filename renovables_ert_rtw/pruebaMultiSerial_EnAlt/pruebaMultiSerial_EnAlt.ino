#include <FreeRTOS_ARM.h>

#define SERIAL_BUFFER_SIZE 10

int loadVolt = 0;
int EnAlt = 0;
int EnAltA = 0;

void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  Serial.begin(115200);
  Serial3.begin(115200);

  analogWriteResolution(12);

  xTaskCreate(commIN_Rasp, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  xTaskCreate(commOut_Rasp, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  xTaskCreate(commIN_Load, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  xTaskCreate(commOut_Load, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  vTaskStartScheduler();
}

static void commIN_Rasp(void* arg) {

  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  while (1) {

    if (SerialUSB.available())
    {
      EnAlt = SerialUSB.parseInt();
      SerialUSB.flush();

    }
    EnAltA = map(EnAlt, -6000, 6000, 0, 4095);
    analogWrite(DAC1, EnAltA);

    vTaskDelayUntil(&xLastWakeTime, (10 / portTICK_PERIOD_MS));
  }

}


static void commOut_Rasp(void* arg) {
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  while (1) {

    SerialUSB.print('s');
    SerialUSB.print(loadVolt);
    SerialUSB.println('e');
    vTaskDelayUntil(&xLastWakeTime, (10 / portTICK_PERIOD_MS));
  }
}

static void commIN_Load(void* arg) {

  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  while (1) {
    if (Serial.available()) {
      loadVolt = Serial.parseInt();
      Serial.flush();
    }

    vTaskDelayUntil(&xLastWakeTime, (10 / portTICK_PERIOD_MS));
  }
}

static void commOut_Load(void* arg) {
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  while (1) {
    Serial3.println(EnAlt);
    vTaskDelayUntil(&xLastWakeTime, (10 / portTICK_PERIOD_MS));
  }
}

void loop() {}
