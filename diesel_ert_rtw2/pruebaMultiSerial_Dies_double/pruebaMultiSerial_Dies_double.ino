#include <FreeRTOS_ARM.h>

#define SERIAL_BUFFER_SIZE 10

double loadVolt = 0;
double Dies = 0;
int DiesA=0;

void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  Serial.begin(115200);
  Serial2.begin(115200);
  analogWriteResolution(12);
  loadVolt = 0.0;
  Dies = 0.0;
  DiesA=0;

  xTaskCreate(commIN_Rasp, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  xTaskCreate(commOut_Rasp, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  xTaskCreate(commIN_Load, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  xTaskCreate(commOut_Load, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);

  vTaskStartScheduler();
}

static void commIN_Rasp(void* arg) {
  String dieselStr = "";
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  while (1) {

    if (SerialUSB.available()) {
      dieselStr = Serial2.readStringUntil('\n');
      Dies = dieselStr.toDouble();
      SerialUSB.flush();
    }

    DiesA=map((int)Dies,-40000,40000,0,4095);
    //DiesA=map(Dies,-15000,15000,0,4095);
    analogWrite(DAC1,DiesA);
        

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
  String loadStr = "";
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  while (1) {
    
    if (Serial.available()) {
      loadStr = Serial2.readStringUntil('\n');
      loadVolt = loadStr.toDouble();
      Serial.flush();
    }

    vTaskDelayUntil(&xLastWakeTime, (2 / portTICK_PERIOD_MS));
  }
}

static void commOut_Load(void* arg) {
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  while (1) {
    Serial2.println(Dies);
    vTaskDelayUntil(&xLastWakeTime, (2 / portTICK_PERIOD_MS));
  }
}

void loop() {}
