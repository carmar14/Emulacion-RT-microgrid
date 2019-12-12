#include <FreeRTOS_ARM.h>

#define SERIAL_BUFFER_SIZE 10

int loadVolt = 0;
int Bio = 0;
int BioA=0;

void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  Serial.begin(115200);
  Serial1.begin(115200);
  analogWriteResolution(12);

  loadVolt = 0;
  Bio = 0;
  BioA=0;

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
    
    if (SerialUSB.available()) {
      Bio = SerialUSB.parseInt();
      SerialUSB.flush();
    }

    BioA=map(Bio,-8000,8000,0,4095);
    analogWrite(DAC0,BioA);
    
    vTaskDelayUntil(&xLastWakeTime, (2 / portTICK_PERIOD_MS));
  }

}


static void commOut_Rasp(void* arg) {
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  while (1) {

    SerialUSB.print('s');
    SerialUSB.print(loadVolt);
    SerialUSB.println('e');
    vTaskDelayUntil(&xLastWakeTime, (2 / portTICK_PERIOD_MS));
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
    vTaskDelayUntil(&xLastWakeTime, (2 / portTICK_PERIOD_MS));
  }
}

static void commOut_Load(void* arg) {
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  while (1) {
    Serial1.println(Bio);
    vTaskDelayUntil(&xLastWakeTime, (2 / portTICK_PERIOD_MS));
  }
}

void loop() {}
