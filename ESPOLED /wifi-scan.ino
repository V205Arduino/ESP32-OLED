#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_SDA 21
#define OLED_SCL 22
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define  STEP_PIN 13
#define DIR_PIN 12

const int buttonPin = 25;
void setup() {
  Serial.begin(115200);
  Wire.begin(OLED_SDA, OLED_SCL); // Initialize I2C bus // For some reason this line is not needed

  //if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) { 
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { //This line of code was the main issue on why the text was not rendering. I thing that 0x3D and 0x3C are swapped, since that seemed to fix the issue
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Loop forever if allocation fails
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE); // @V205 you could instead just call WHITE rather than SSD1306_WHITE just for simplicity
  display.setCursor(0, 0);
  display.println(F("Gate Status:"));
  display.println(F("Closed"));
  display.display();
  Serial.println("done setup...");
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  digitalWrite(DIR_PIN, LOW);

  pinMode(buttonPin, INPUT_PULLUP);

}

const int stepsPerRotation = 200; // Full rotation in one direction
const int rotationDelay = 5; // Delay between steps in milliseconds
const int directionChangeDelay = 5000; // Delay between direction changes in milliseconds
int currentStep = 0;

bool lastButtonState = false;
bool buttonState = false;
bool gateStatus = false; //Note: false means closed, true means opened
void loop() {


  static unsigned long timer = 0;
  unsigned long interval = 50;

  //Serial.println("looping, I guess");
  if (millis() - timer >= interval) {
    
    //Serial.println("interval");
    timer = millis();
    buttonState = digitalRead(buttonPin);

    if (buttonState != lastButtonState) {
      if (buttonState == false) {

        Serial.println("DDDDD");
        if(gateStatus == true){
          digitalWrite(DIR_PIN, LOW);
          Serial.println("Open Gate!");
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(0, 0);
          display.println(F("Gate Status:"));
          display.println(F("Open"));
          display.display();
           gateStatus = !gateStatus;
          
        }else{
          digitalWrite(DIR_PIN, HIGH);
          Serial.print("Closed Gate!");
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(0, 0);
          display.println(F("Gate Status:"));
          display.println(F("Closed"));
          display.display();
           gateStatus = !gateStatus;
        }

       
        
        for (int i = 0; i < stepsPerRotation/2; i++) {
            digitalWrite(STEP_PIN, HIGH);
            digitalWrite(STEP_PIN, LOW);
            delay(rotationDelay);

        }
        }
    }
  

  }

  lastButtonState = buttonState;
  /*
  // Rotate in one direction
  digitalWrite(DIR_PIN, LOW);
  for (int i = 0; i < stepsPerRotation/2; i++) {
    digitalWrite(STEP_PIN, HIGH);
    digitalWrite(STEP_PIN, LOW);
    delay(rotationDelay);
  }

  // Delay before changing direction
  delay(directionChangeDelay);

  // Rotate in the other direction
  digitalWrite(DIR_PIN, HIGH);
  for (int i = 0; i < stepsPerRotation/2; i++) {
    digitalWrite(STEP_PIN, HIGH);
    digitalWrite(STEP_PIN, LOW);
    delay(rotationDelay);
  }

  // Delay before repeating the cycle
  delay(directionChangeDelay);
  */
}



/*

int cursor;
void showMenu() {
  cursor=0;
  display.clearDisplay();
  // show menu items:
  for (int i = 0; i<MENU_SIZE; i++) {
    display.drawString(2,i,menu[i]);
  }
  display.setCursor(0,0);
  display.print('>');
}
*/

/**
 * Execute the task which matches the chosen menu item.
 */

/*
void executeChoice(int choice) {
  switch(choice) {
      case 0 :
                Serial.print("Execute choice "); Serial.print(choice); Serial.print(" - "); Serial.println(menu[choice]);
                break;
      case 1 :
                Serial.print("Execute choice "); Serial.print(choice); Serial.print(" - "); Serial.println(menu[choice]);
                break;
      case 2 :
                Serial.print("Execute choice "); Serial.print(choice); Serial.print(" - "); Serial.println(menu[choice]);
                break;
      case 3 :
                Serial.print("Execute choice "); Serial.print(choice); Serial.print(" - "); Serial.println(menu[choice]);
                break;
      case 4 :
                Serial.print("Execute choice "); Serial.print(choice); Serial.print(" - "); Serial.println(menu[choice]);
                break;
      default :
                Serial.print("Execute choice "); Serial.print(choice); Serial.print(" - "); Serial.println(menu[choice]);
                break;
  }
  
}
*/
/*
{
  "version": 1,
  "author": "V205",
  "editor": "wokwi",
  "parts": [
    { "type": "board-esp32-devkit-c-v4", "id": "esp", "top": 9.6, "left": -100.76, "attrs": {} },
    { "type": "board-ssd1306", "id": "oled1", "top": 99.14, "left": 57.83, "attrs": {} },
    {
      "type": "wokwi-led",
      "id": "led1",
      "top": 34.8,
      "left": -140.2,
      "attrs": { "color": "red" }
    }
  ],
  "connections": [
    [ "esp:TX", "$serialMonitor:RX", "", [] ],
    [ "esp:RX", "$serialMonitor:TX", "", [] ],
    [ "oled1:SCL", "esp:22", "green", [ "v0" ] ],
    [ "oled1:SDA", "esp:21", "blue", [ "v-19.2", "h-124.73" ] ],
    [ "oled1:GND", "esp:GND.2", "black", [ "v-67.2", "h-96" ] ],
    [ "oled1:VCC", "esp:3V3", "red", [ "v-28.8", "h0.15", "v-76.8", "h-201.75" ] ],
    [ "led1:A", "esp:CMD", "green", [ "v0" ] ],
    [ "led1:C", "esp:32", "green", [ "v0" ] ]
  ],
  "dependencies": {}
}
*/