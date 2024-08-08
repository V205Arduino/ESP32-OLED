// Now turn this trash into treasure!
#include <TM1637.h>

const int CLK = 4;
const int DIO = 5;

TM1637 tm(CLK, DIO);

const int piezoPin = 27;

void setup() {
  tm.init();
  tm.set(BRIGHT_TYPICAL);
  Serial1.begin(115200);
  Serial1.println("Hello, Raspberry Pi Pico W!");
}

unsigned long startTime = millis();
unsigned long totalMillis = 1000; // kaboom time!
unsigned long remainingMillis = totalMillis;
unsigned long elapsedMillis;
void loop() {
  //relapsedMillis = millis() - startTime;

  //remainingMillis = totalMillis - elapsedMillis;
  /*
  if (remainingMillis <=20) {
  }else{
    elapsedMillis = millis() - startTime;
    remainingMillis = totalMillis - elapsedMillis;
  }
  */
  elapsedMillis = millis() - startTime;
  
  remainingMillis = totalMillis - elapsedMillis;

  if (remainingMillis > totalMillis) {
    remainingMillis  = 0;
  }else{

  }


  if (remainingMillis > 60000) { 
    int minutes = remainingMillis / 60000;
    int seconds = (remainingMillis % 60000) / 1000;
    Serial1.println("seconds:");
     Serial1.println(seconds);
      Serial1.println("minutes:");
      Serial1.println(minutes);
    tm.display(0, minutes / 10);
    tm.display(1, minutes % 10);
    tm.display(2, seconds / 10);
    tm.display(3, seconds % 10);
    
  } else if ((1 < remainingMillis)  &&(remainingMillis< 60)) {
    int seconds = remainingMillis / 1000;
    Serial1.println("seconds:");
    Serial1.println(seconds);
    int decimals = (remainingMillis % 1000) / 10;
    Serial1.println("decimals");
    Serial1.println(decimals);
    tm.display(0, seconds / 10);
    tm.display(1, seconds % 10);
    tm.display(2, decimals / 10);
    tm.display(3, decimals % 10);
    
  } else if (remainingMillis <= 0){
    tm.display(0, 0);
    tm.display(1, 0);
    tm.display(2, 0);
    tm.display(3, 0);
    while(true){
    endCountdownAction();
    }
  }

  delay(1);
  //Serial1.println(remainingMillis);
}

void endCountdownAction(){
  Serial1.println("kaboom");
  tone(piezoPin, 5000);

}
