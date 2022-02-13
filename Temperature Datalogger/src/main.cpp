#include <Arduino.h>
#include <Keyboard.h>
#include <math.h>

//Function Prototypes
boolean debounce(boolean last);
double Thermistor(int RawADC);

const int TEMP = A0;
const int LIGHT = A1;
const int LED = 3;
const int BUTTON = 2;

boolean lastButton = LOW;
boolean currentButton = LOW;
boolean running = false;
int counter = 1;

void setup() {
  pinMode (LED, OUTPUT);
  Keyboard.begin();
}

void loop() {
  currentButton = debounce(lastButton);

  if (lastButton == LOW && currentButton == HIGH)
  running = !running;

  lastButton = currentButton;

  if (running)
  {
    digitalWrite(LED, HIGH);
   if (millis() % 1000 == 0)
  {
    int temperature = analogRead(TEMP);
    double celcius = Thermistor(temperature);
    int brightness = analogRead(LIGHT);
    Keyboard.print(counter);
    Keyboard.print(",");
    Keyboard.print(celcius);
    Keyboard.print(",");
    Keyboard.println(brightness);
    counter++;
  }
}
else
{
  digitalWrite(LED, LOW);
}
}

boolean debounce(boolean last)
{
  boolean current = digitalRead(BUTTON);
  if (last != current)
  {
    delay(5);
    current = digitalRead(BUTTON);
  }
  return current;
}

/*double Thermistor(int RawADC) 
{
  float R1 = 10000;
  float logR2, R2, T;
  float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741;
  int Vo = RawADC;
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = ((1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)) * (5/3.3));
  T = T - 273.15;
  return T;
}*/

/*double Thermistor(int RawADC)
{
double Temp;
Temp = log(((10240000/RawADC) - 10000));
Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
Temp = Temp (3.3/5);
Temp = Temp - 273.15;           
return Temp;
}*/

double Thermistor(int RawADC)
{
  double Temp;
  Temp = log(10000.0 * ((1024.0/RawADC - 1)));
  Temp = 1/(0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp))*Temp);
  Temp = Temp * (3.3/5);
  Temp = Temp - 273.15;
  return Temp;
}
