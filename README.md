## 使用技術
<p align="left">
  <img src="https://cdn.simpleicons.org/arduino/00979D" alt="Arduino" width="80" />
  <img src="https://cdn.simpleicons.org/kicad/314CB0" alt="KiCad" width="80" />
</p>

# 🇯🇵 日本語版 README

<br>
<br>

## 🎯開発目的
小学生や中学生といった電子工作未経験者が分かりやすく楽しみながら学習できるボードを開発しました。  
また様々な機能を搭載しブレッドボードを使用せずに様々な実験が行えるようにしている


## ⚠️注意
#### 配布プログラムを使用する場合は必ず下記のライブラリを追加してから書き込まないと動作しません
<Adafruit_GFX.h>
<Adafruit_SSD1306.h>
<Adafruit_AHTX0.h>
<Adafruit_BMP280.h>


## 🧪仕様
#### wather_infOLEDについて
AHT20+BME280が一体になったセンサーボードからI2Cで通信を行い同バス上のOLEDに表示させるプログラムです。  
RGBLEDをボタンで色を選択し可変抵抗でアナログ入力を行い、値と連動してLEDの明るさをPWMで変化させています。

#### wather_wifiAPについて
AHT20+BME280が一体になったセンサーボードからI2Cで通信を行い同バス上のOLEDに表示させるプログラムです。  
RGBLEDをボタンで色を選択し可変抵抗でアナログ入力を行い、値と連動してLEDの明るさをPWMで変化させています。  
本体をAPとして動作させてスマホなどから気象データを閲覧できるようにHTTPサーバーも追加しています。


## 🧩使用部品
#### ESP32 ⇒　https://amzn.to/4sqD3HQ
#### OLED  ⇒　https://amzn.to/3Y9AFHy
#### AHT20+BMP280 ⇒ https://amzn.to/4pKP5Ke


## 📐回路図
回路図は PDF形式で配布しています。
詳細はそちらをご確認ください。

<br>
<br>
<br>
<br>

# 🇬🇧 English README

## 🎯 Purpose
・Easy to understand for beginners  

・Learn sensors, displays, and communication  

・Suitable for classrooms and workshops  

## 🧪 Usage (Sample Programs)
#### ■ wather_infOLED

Reads environmental data via I2C from an AHT20 + BMP280 sensor board

Displays temperature, humidity, and pressure on an OLED display

RGB LED color can be selected using buttons

LED brightness is controlled via PWM, linked to analog input from a potentiometer

#### ■ wather_wifiAP

Includes all features of wather_infOLED

The ESP32 operates as a Wi-Fi Access Point

Users can connect via smartphone or PC

Weather data can be viewed through an HTTP server


## 🧩 Components
#### ESP32 ⇒　https://amzn.to/4sqD3HQ
#### OLED  ⇒　https://amzn.to/3Y9AFHy
#### AHT20+BMP280 ⇒ https://amzn.to/4pKP5Ke


## 📐 Schematic
The circuit schematic is provided as a PDF file.  
Please refer to it for wiring details.
