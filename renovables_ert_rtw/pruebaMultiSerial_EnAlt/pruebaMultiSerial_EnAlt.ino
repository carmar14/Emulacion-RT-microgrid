#include <FreeRTOS_ARM.h>

int loadVolt = 0;
int EnAlt = 0;

void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  Serial.begin(115200);
  Serial3.begin(115200);

  xTaskCreate(commIN_Rasp, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  xTaskCreate(commOut_Rasp, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  xTaskCreate(commIN_Load, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  xTaskCreate(commOut_Load, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  
}

static void commIN_Rasp(void* arg) {

  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  while (1) {
    SerialUSB.flush();
    EnAlt = SerialUSB.parseInt();
    
    vTaskDelayUntil(&xLastWakeTime, (10 / portTICK_PERIOD_MS));
  }

}


static void commOut_Rasp(void* arg) {
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  while (1) {

    //SerialUSB.print('s');
    SerialUSB.println(loadVolt);
    //SerialUSB.println('e');
    vTaskDelayUntil(&xLastWakeTime, (10 / portTICK_PERIOD_MS));
  }
}

static void commIN_Load(void* arg) {
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  while (1) {
    Serial.flush();
    loadVolt = Serial.parseInt();

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
