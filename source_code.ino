#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 


#define DHTPIN 2 
#define DHTTYPE DHT22

float prevTempC = 0.0;
float prevHumi = 0.0;

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); 
DHT dht(DHTPIN, DHTTYPE);

String displayString;

void setup() {
  Serial.begin(9600);
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  delay(2000);         
  oled.clearDisplay(); 

  oled.setTextSize(4);      
  oled.setTextColor(WHITE); 
  oled.setCursor(0, 15);    

  dht.begin();              

  displayString.reserve(10); 
}

void loop() {
    float humi = dht.readHumidity();    
    float tempC = dht.readTemperature(); 
    float tempF = tempC * 9.0 / 5.0 + 32; 

    if (isnan(humi) || isnan(tempC)) {
        oled.clearDisplay();
        oledDisplay("Error", 0, "", -16, 2); 
    } else {
        
        oledDisplay("Temperature", tempF, "F", -16, 1.2); 
        oledDisplay("Humidity", humi, "%", 0, 1.2);    
    }
}

void oledDisplay(String label, float value, String unit, int yOffset, int textSize) {
    oled.setTextSize(textSize);  
    oled.setTextColor(SSD1306_WHITE); 
    int y = (SCREEN_HEIGHT / 2) + yOffset;
    oled.fillRect(0, y, SCREEN_WIDTH, textSize * 8, SSD1306_BLACK); 
    String text = label + ": " + String(value, 1) + " " + unit;
    oled.setCursor(0, y);
    oled.println(text);
    oled.display();
}