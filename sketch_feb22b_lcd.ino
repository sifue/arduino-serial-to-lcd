#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // run ic2_scanner sketch and get the IC2 address, which is 0x3f in my case,it could be 0x3f in many cases

int recieveByte = 0;
String bufferStr = "";

void setup()
{
  lcd.init(); // initialize the lcd
  Serial.begin(9600);
}

void loop()
{
  // データが存在したらバッファを初期化
  if (Serial.available() > 0) {
    bufferStr = "";
  }

  // バッファに読み出し
  while (Serial.available() > 0) {
    recieveByte = Serial.read();
    if (recieveByte == (int)'\n') break;
    bufferStr.concat((char)recieveByte);
    delay(100);
  }

  // set cursor to first line
  lcd.setCursor(0, 0);

  // Print a message to the LCD.
  lcd.backlight();
  lcd.print("N-YOBI MONTH KPI");

  // 受け取ったデータがあるなら表示
  if (bufferStr.length() > 0 && Serial.available() == 0) {
    // デバッグ用 送り返すのは重いのでやらない
//    Serial.print("I received: ");
//    Serial.println(bufferStr);
    
    lcd.setCursor(0, 1);
    lcd.print(bufferStr);
  }
}
