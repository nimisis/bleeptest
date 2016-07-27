/* BleepTest
 */
 
#include <PololuLedStrip.h>

// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<12> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
#define LED_COUNT 120
#define STRIP_DIST 20000.0

rgb_color colors[LED_COUNT];

 bool started;
 unsigned long starttime;
 int laps = 0;
 int totlaps = 0;
 int level = 1;
 int levellaps[] = {0,7,
   8,8,
   9,9,
   10,10,
   11,11,11,
   12,12,
   13,13,13,
   14,14,
   15,15,
   16,16};
 double leveldists[] = {0,140000.0,
   160000.0,160000.0,
   180000.0,180000.0,
   200000.0,200000.0,
   220000.0,220000.0,220000.0,
   240000.0,240000.0,
   260000.0,260000.0,260000.0,
   280000.0,280000.0,
   300000.0,300000.0,
   320000.0,320000.0};
  
void setup()
{
  started = true;
  starttime = millis();
  Serial.begin(9600);
}

void loop()
{
  if (started) {
    unsigned long timesofar = millis() - starttime;
    double speed = 8000.0 + level * 500.0;
    double dist = timesofar * speed / 3600.0;
    dist -= laps * STRIP_DIST;
    if (dist >= STRIP_DIST) {
      laps++;
      totlaps++;
      Serial.println("lapup");
      dist -= STRIP_DIST;
      if (laps == levellaps[level]) {
        Serial.print("level ");
        Serial.print(level);
        Serial.println(" complete ");
        Serial.println(timesofar);
        level++;
        starttime += laps * STRIP_DIST * 3600.0 / speed;
        laps = 0;
      } 
    } 
    if (totlaps % 2 == 0) {
      int first = -1;
      for(uint16_t i = 0; i < LED_COUNT; i++) {
        double leddist = i * (STRIP_DIST / LED_COUNT);
        if (leddist >= dist) {
          if (first == -1) {
            first = i;
          }
        }
      }
      for(uint16_t i = 0; i < LED_COUNT; i++) {
        if (i != first) {
          colors[i] = (rgb_color){0,0,0};
        } else {
          colors[i] = (rgb_color){100,0,0};
        }
      }
    } else {
      int last = -1;
      for(uint16_t i = 0; i < LED_COUNT; i++) {
        double leddist = STRIP_DIST - (i * (STRIP_DIST / LED_COUNT));
        if (leddist >= dist) {
          last = i;
        }
      }
      for(uint16_t i = 0; i < LED_COUNT; i++) {
        if (i != last) {
          colors[i] = (rgb_color){0,0,0};
        } else {
          colors[i] = (rgb_color){0,100,0};
        }
      }
    }
    ledStrip.write(colors, LED_COUNT);  
  }
  delay(10);
}
