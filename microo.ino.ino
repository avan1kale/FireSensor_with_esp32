
#define BLYNK_TEMPLATE_ID           "TMPL3kar-KWIS"
#define BLYNK_TEMPLATE_NAME         "FIRE ALARM"
#define BLYNK_AUTH_TOKEN            "lIVlsBeLI_qjYcgbSkFbyfBx1Nnq_QoK"


#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[]= BLYNK_AUTH_TOKEN;
char ssid[] = "Galaxy M33 5G53A7";
char pass[] = "hakunamatata";
BlynkTimer timer;

const int FIRE_SENSOR_PIN = 15;  
const int buzzerPin = 4;
// Timer for periodic tasks

WidgetLED led(V1);

void setup() {
  
  // Start the serial communication
  Serial.begin(9600);

  // Connect to WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  pinMode(FIRE_SENSOR_PIN, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  
  timer.setInterval(2000L, checkSensor);
  
}

void loop() {
  
  Blynk.run();
  timer.run();
  checkSensor();
}

void checkSensor(){
  int sensorValue = digitalRead(FIRE_SENSOR_PIN);

  if (sensorValue == 0) {
    Blynk.logEvent("fire_event");
    digitalWrite(buzzerPin, HIGH);
    Serial.println(" Fire Detected!");
    Blynk.virtualWrite(V0, 1);  
    led.on();
  } 
  else if (sensorValue == 1) {
    digitalWrite(buzzerPin, LOW);
    Serial.println(" No Fire.");
    Blynk.virtualWrite(V0, 0);
    led.off(); 
  }
  else{
    Serial.println("error");
    led.off();
  }
  delay(1000);
}
