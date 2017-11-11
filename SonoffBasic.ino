#include <ESP8266WiFi.h>
#include <Ticker.h>

#define LED_GPIO 13
#define GPIO_EXTRA 14

unsigned long lasttime = -1;

Ticker ticks;

void tick()
{
  ticks.detach(); 
  bool val = digitalRead(GPIO_EXTRA);
  Serial.print("Timeout, button is ");
  Serial.println(val);

  digitalWrite(LED_GPIO,val);
}

void edge(bool pinLevel, unsigned long time)
{

  
  Serial.print("state ");
  Serial.print(pinLevel);
  Serial.print(" time ");
  Serial.print(time);

  if( (time - lasttime) > 100 )
  {
    Serial.println("   New button press");
  }
  else
  {
    Serial.println("");
    ticks.detach();
  }
  
  lasttime = time;

  ticks.attach(0.1,tick);
}

void isr()
{
  Serial.print("ISR ");
  edge(digitalRead(GPIO_EXTRA),millis());
}

void setup() 
{  
  Serial.begin(115200);
  
  pinMode(LED_GPIO, OUTPUT);
  digitalWrite(LED_GPIO,LOW);
  
  pinMode(GPIO_EXTRA, INPUT_PULLUP);
  attachInterrupt(GPIO_EXTRA, isr, CHANGE);
}

void loop() 
{
  delay(1000);
}
