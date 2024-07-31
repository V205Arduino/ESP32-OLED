#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_SDA 21
#define OLED_SCL 22
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
    Serial.begin(115200);
    Wire.begin(OLED_SDA, OLED_SCL); // Initialize I2C bus

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;); // Loop forever if allocation fails
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("Hello, world!"));
    display.display();
    Serial.println("done setup...");

  pinMode(32, OUTPUT);
  digitalWrite(32, HIGH);
   pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);

}

void loop() {
    // Your loop code here
}