#include <arduino.h>
#include <HardwareSerial.h>

const int ledPin = LED_BUILTIN;
unsigned long taskFon = 300;     //ms - on
unsigned long taskFoff = 700;    //ms - off
unsigned long taskStime = 1000;  // ms - stop stringi yollandığı zaman yanıp sönme süresi

unsigned long taskFRemember = 0;
unsigned long taskStimePrev = 0;


int ledState = LOW;

int taskRunMode = 1;

String stop_txt = "stop\n";
String start_txt = "start\n";


void setup() {
  Serial.begin(115200, SERIAL_8N1);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  unsigned long currentMillis = millis();


  if (Serial.available()) {

    String ledWork = Serial.readString();
    if (stop_txt.equals(ledWork)) {
      taskRunMode = 2;
    } else if (start_txt.equals(ledWork)) {
      taskRunMode = 1;
    }
    if (!(stop_txt.equals(ledWork)) && !(start_txt.equals(ledWork))) {
      if (ledWork.indexOf('=') == 5) {
        ledWork = ledWork.substring(ledWork.indexOf('=') + 1, ledWork.length());
        taskFon = ledWork.toInt();
        Task1();
      } else if (ledWork.indexOf('=') == 6) {
        ledWork = ledWork.substring(ledWork.indexOf('=') + 1, ledWork.length());
        taskFoff = ledWork.toInt();
        Task1();
      }
    }
  }

  if (taskRunMode == 1) {
    Task1();
  } else if (taskRunMode == 2) {
    Task2();
  }
}



void Task1() {
  if (ledState == LOW) {
    if ((millis() - taskFRemember) >= taskFon) {
      ledState = HIGH;
      taskFRemember = millis();
      digitalWrite(ledPin, ledState);
    }
  } else {
    if ((millis() - taskFRemember) >= taskFoff) {
      ledState = LOW;
      taskFRemember = millis();
      digitalWrite(ledPin, ledState);
    }
  }
}

void Task2() {
  if ((millis() - taskStimePrev) >= taskStime) {
    taskStimePrev = millis();
    if (ledState == LOW) {
      ledState = HIGH;
      digitalWrite(ledPin, ledState);
    } else {
      ledState = LOW;
      digitalWrite(ledPin, ledState);
    }
  }
}