//created by : Beny Abdurrahman
//@2020
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <FastLED.h>
#define NUM_LEDS 45         //jumlah led
#define LED_PIN 2           //pin d2 on esp8266
#define COLOR_ORDER GRB
#define LED_TYPE    WS2812B   //type led strip
CRGB leds[NUM_LEDS];

//firebase inisialisasi
#include <FirebaseArduino.h>
//setup firebase API
#define FIREBASE_HOST "xxxxxx.firebaseio.com"
#define FIREBASE_AUTH "oNJJ1lLkAG0wUC1mQTTDQr3w51k61qIDvgFqdv7m"
//setup wifi
#define WIFI_SSID "ssid"
#define WIFI_PASSWORD "password"


void setup() {
  //setup fastled
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  int pinNo =0;
  
  Serial.begin(115200);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);    
  delay(2000);
}

void loop() {
  //depends on your structure
  String path = "/LED/";
  FirebaseObject object = Firebase.get(path);
  int r = object.getInt("red");
  int g = object.getInt("green");
  int b = object.getInt("blue");
  int brightness = object.getInt("brightness");

  Serial.print("brightness");
  Serial.print(brightness);
  Serial.print(" warna");
  Serial.print(r);
  Serial.print(", ");
  Serial.print(g);
  Serial.print(", ");
  Serial.println(b);
  FastLED.setBrightness(brightness);
  for (int pinNo = 0; pinNo <= NUM_LEDS-1; pinNo++) {
    leds[pinNo] = CRGB( r, g, b);    
  }
  FastLED.show(); // Update the LEDs
  delay(500);
}
