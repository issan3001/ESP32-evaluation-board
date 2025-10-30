#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LED_R       0
#define LED_G       2
#define LED_B       4
#define switch_1   12
#define switch_2   14
#define switch_3   26
#define switch_4   27
#define buzzer     15
#define VR         25

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define PWM_FREQ 5000
#define PWM_RES 8   // 0~255

int colorMode = 0; // 0=OFF, 1=RED, 2=GREEN, 3=BLUE

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(switch_1, INPUT_PULLUP);
  pinMode(switch_2, INPUT_PULLUP);
  pinMode(switch_3, INPUT_PULLUP);
  pinMode(switch_4, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

  // 新しいESP32用PWM初期化（チャンネル自動割当）
  if (!ledcAttach(LED_R, PWM_FREQ, PWM_RES)) Serial.println("LED_R attach failed");
  if (!ledcAttach(LED_G, PWM_FREQ, PWM_RES)) Serial.println("LED_G attach failed");
  if (!ledcAttach(LED_B, PWM_FREQ, PWM_RES)) Serial.println("LED_B attach failed");

  // OLED初期化
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("RGB Controller Ready!"));
  display.display();
}

void loop() {
  int vrValue = analogRead(VR);
  int brightness = map(vrValue, 0, 4095, 0, 255); // ESP32 ADCは12bit

  // スイッチで色モード切替
  if (digitalRead(switch_1) == LOW) colorMode = 1;
  if (digitalRead(switch_2) == LOW) colorMode = 2;
  if (digitalRead(switch_3) == LOW) colorMode = 3;
  if (digitalRead(switch_4) == LOW) colorMode = 0; // switch4でOFF

  // LED出力（新しいledcWrite）
  switch (colorMode) {
    case 1: // 赤
      ledcWrite(LED_R, brightness);
      ledcWrite(LED_G, 0);
      ledcWrite(LED_B, 0);
      break;
    case 2: // 緑
      ledcWrite(LED_R, 0);
      ledcWrite(LED_G, brightness);
      ledcWrite(LED_B, 0);
      break;
    case 3: // 青
      ledcWrite(LED_R, 0);
      ledcWrite(LED_G, 0);
      ledcWrite(LED_B, brightness);
      break;
    default: // 消灯
      ledcWrite(LED_R, 0);
      ledcWrite(LED_G, 0);
      ledcWrite(LED_B, 0);
      break;
  }

  // OLED表示更新
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.print("Mode: ");
  switch (colorMode) {
    case 1: display.println("RED"); break;
    case 2: display.println("GREEN"); break;
    case 3: display.println("BLUE"); break;
    default: display.println("OFF");
  }
  display.print("Brightness: ");
  display.println(brightness);
  display.display();

  delay(100);
}
