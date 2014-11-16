const int pirsensorPin = 2;
const int tempsensorPin = A1;
const float warningTemp = 28.01;
const float arefVoltage = 3.3;
unsigned long seconds = 1000L;
unsigned long minutes = seconds * 60;
#include <Bridge.h>
#include <Temboo.h>
#include "TembooAccount.h"
const String GMAIL_USER_NAME = "xxxxxxx@gmail.com"; ////
const String GMAIL_PASSWORD = "xxxxxxxx";
const String TO_EMAIL_ADDRESS = "xxxxx@email.domain";

void setup() {
  Serial.begin(9600);
  Bridge.begin();
  pinMode(pirsensorPin, INPUT);
  pinMode(tempsensorPin, INPUT);
  analogReference(EXTERNAL);
}

void loop() {
  int sensorVal = analogRead(tempsensorPin);
  Serial.print("Sensor Value: ");
  Serial.print(sensorVal);
  float voltage = sensorVal * arefVoltage;
  voltage /= 1024.0;
  Serial.print(", Volts: ");
  Serial.print(voltage);
  Serial.print(", degrees C: ");
  float temperature = (voltage - .5) * 100;
  Serial.println(temperature);
  delay(200);

  if (digitalRead(pirsensorPin) == HIGH || temperature > warningTemp) {
    Serial.println("Running SendAnEmail...");
    
    TembooChoreo SendEmailChoreo;
    
    SendEmailChoreo.begin();
    SendEmailChoreo.setAccountName(TEMBOO_ACCOUNT);
    SendEmailChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    SendEmailChoreo.setAppKey(TEMBOO_APP_KEY);

    SendEmailChoreo.setChoreo("/Library/Google/Gmail/SendEmail");
    SendEmailChoreo.addInput("Username", GMAIL_USER_NAME);
    SendEmailChoreo.addInput("Password", GMAIL_PASSWORD);
    SendEmailChoreo.addInput("ToAddress", TO_EMAIL_ADDRESS);
    SendEmailChoreo.addInput("Subject", "Subject for the warning");
    SendEmailChoreo.addInput("MessageBody", "Message body for the warning");

    unsigned int returnCode = SendEmailChoreo.run();

    if (returnCode == 0) {
      Serial.println("Success! Email sent!");
      Serial.println("Monitoring continues aprroximately  in 15 minutes");
      delay(15 * minutes);

    } else {
      while (SendEmailChoreo.available()) {
        char c = SendEmailChoreo.read();
        Serial.print(c);
      }

      delay(20 * seconds);
    }

    SendEmailChoreo.close();

  }
}
