#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_BMP280.h>

// --- ピン定義 ---
#define LED_R     15
#define LED_G     2
#define LED_B     4
#define SWITCH_1  12
#define SWITCH_2  14
#define SWITCH_3  26
#define SWITCH_4  27
#define VR        25

// --- OLED設定 ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- センサー設定 ---
Adafruit_AHTX0 aht;
Adafruit_BMP280 bmp;  // I2Cアドレス 0x77

// --- PWM設定 ---
#define PWM_FREQ 5000
#define PWM_RES 8  // 0~255

int colorMode = 0; // 0=OFF, 1=RED, 2=GREEN, 3=BLUE

void setup() {
  Wire.begin(21, 22); // SDA=21, SCL=22（ESP32標準ピン）

  pinMode(SWITCH_1, INPUT_PULLUP);
  pinMode(SWITCH_2, INPUT_PULLUP);
  pinMode(SWITCH_3, INPUT_PULLUP);
  pinMode(SWITCH_4, INPUT_PULLUP);

  ledcAttach(LED_R, PWM_FREQ, PWM_RES);
  ledcAttach(LED_G, PWM_FREQ, PWM_RES);
  ledcAttach(LED_B, PWM_FREQ, PWM_RES);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Init..."));
  display.display();

  if (!aht.begin()) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(F("AHT20 not found"));
    display.display();
    while (1);
  }

  if (!bmp.begin(0x77)) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(F("BMP280 not found"));
    display.display();
    while (1);
  }

  delay(1000);
}

void loop() {
  int vrValue = analogRead(VR);
  int brightness = map(vrValue, 0, 4095, 0, 255);

  if (digitalRead(SWITCH_1) == LOW) colorMode = 1;
  if (digitalRead(SWITCH_2) == LOW) colorMode = 2;
  if (digitalRead(SWITCH_3) == LOW) colorMode = 3;
  if (digitalRead(SWITCH_4) == LOW) colorMode = 0;

  switch (colorMode) {
    case 1:
      ledcWrite(LED_R, brightness);
      ledcWrite(LED_G, 0);
      ledcWrite(LED_B, 0);
      break;
    case 2:
      ledcWrite(LED_R, 0);
      ledcWrite(LED_G, brightness);
      ledcWrite(LED_B, 0);
      break;
    case 3:
      ledcWrite(LED_R, 0);
      ledcWrite(LED_G, 0);
      ledcWrite(LED_B, brightness);
      break;
    default:
      ledcWrite(LED_R, 0);
      ledcWrite(LED_G, 0);
      ledcWrite(LED_B, 0);
      break;
  }

  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  float pressure = bmp.readPressure() / 100.0F; // hPa

  display.clearDisplay();

  // 温度（大きく中央表示）
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.printf("%.1f C", temp.temperature);

  // 湿度・気圧
  display.setTextSize(1);
  display.setCursor(0, 30);
  display.printf("Hum: %.1f %%", humidity.relative_humidity);
  display.setCursor(0, 42);
  display.printf("Pre: %.1f hPa", pressure);

  // LED色・明るさ
  display.setCursor(0, 54);
  display.print("LED: ");
  switch (colorMode) {
    case 1: display.print("RED"); break;
    case 2: display.print("GREEN"); break;
    case 3: display.print("BLUE"); break;
    default: display.print("OFF"); break;
  }
  display.printf("  %3d", brightness);

  display.display();
  delay(500);
}
