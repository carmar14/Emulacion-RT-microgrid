#include <FreeRTOS_ARM.h>

#define SERIAL_BUFFER_SIZE 24

int loadVolt = 0;
int loadVoltA = 0;
int Bio = 0, Dies = 0, EnAlt = 0,EnAltA = 0;;

void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  Serial.begin(115200);               // Velocidad de comunicación serial
  Serial1.begin(115200);
  Serial2.begin(115200);

  analogWriteResolution(12);
  SerialUSB.flush();

  loadVolt = 0;
  loadVoltA = 0;
  Bio = 0;
  Dies = 0;
  EnAlt = 0;
  EnAltA = 0;
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  xTaskCreate(commIN_Rasp, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  xTaskCreate(commOut_Rasp, NULL, configMINIMAL_STACK_SIZE , NULL, 2, NULL);
  xTaskCreate(commIN_1, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  xTaskCreate(commIN_2, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  xTaskCreate(commOut_all, NULL, configMINIMAL_STACK_SIZE , NULL, 1, NULL);
  vTaskStartScheduler();
}

static void commIN_Rasp(void* arg) {

  bool stringComplete = false;  // whether the string is complete
  //String inputString = "";
  bool conti = true;
  char inputCharArray[125];
  char delim[] = ",";
  char *ptr;
  int j = 0;
  String vload_CA, reno_CA;
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  while (1) {
    if (SerialUSB.available()) {
      //digitalWrite(LED_BUILTIN, HIGH);
      stringComplete = false;
      conti = true;
      //inputString = "";
      memset(inputCharArray, 0, sizeof(inputCharArray));
      while (conti) {
        char inChar = (char)SerialUSB.read();
        if (inChar == 's') {
          j = 0;
          while (!stringComplete) {
            while (SerialUSB.available() && conti) {
              char inChar = (char)SerialUSB.read();
              if (inChar == 'e') {
                stringComplete = true;
                conti = false;
              } else {
                inputCharArray[j] = inChar;
                j++;
              }
            }
          }
        }

      }
      //SerialUSB.flush();
      ptr = strtok(inputCharArray, delim);
      vload_CA = ptr;
      loadVolt = vload_CA.toFloat();
      ptr = strtok(NULL, delim);
      reno_CA = ptr;
      EnAlt = reno_CA.toFloat();
    }
    //digitalWrite(LED_BUILTIN, LOW);
    loadVoltA = map(loadVolt, -6000, 6000, 0, 4095);
    analogWrite(DAC0, loadVoltA);
    EnAltA = map(loadVolt, -4800, 4800, 0, 4095);
    analogWrite(DAC1, EnAltA);
    //analogWrite(DAC1, 0);
    //analogWrite(DAC0, 0);

    vTaskDelayUntil(&xLastWakeTime, (2 / portTICK_PERIOD_MS));
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
    //    SerialUSB.print(EnAlt);
    //    SerialUSB.print(',');
    SerialUSB.println('e');
    vTaskDelayUntil(&xLastWakeTime, (2 / portTICK_PERIOD_MS));
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

    vTaskDelayUntil(&xLastWakeTime, (2 / portTICK_PERIOD_MS));
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

    vTaskDelayUntil(&xLastWakeTime, (2 / portTICK_PERIOD_MS));
  }
}


static void commOut_all(void* arg) {
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  while (1) {
    Serial.println(loadVolt);
    vTaskDelayUntil(&xLastWakeTime, (2 / portTICK_PERIOD_MS));
  }
}


void loop() {}
