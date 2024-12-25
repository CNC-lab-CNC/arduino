
#include <LiquidCrystal.h>

float current;

int termPin = 0;   // The analog pin to which the thermistor is connected is A0

int termNom = 100000; // Thermistor reference resistance

int refTemp = 25;   // Temperature for reference resistance

int beta = 3950;   // Beta factor

int resistance = 110000; // value of resistance in series in the circuit


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Temperature thresholds
float targetTemperature = 50.0; // Initial target temperature in °C
const float tolerance= 0.5;

const int buttonupPin = 9; // Button to increase target temperature
const int buttonDownPin = 10; // Button to decrease target temperature



 
void setup() {


pinMode (8, OUTPUT);


Serial.begin(9600); 

 // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

 Serial.begin(9600);

 analogReference(EXTERNAL);

 lcd.print("Heat bed");

 lcd.display();
  delay(200);

 lcd.setCursor(2, 1);
 lcd.display();

pinMode(buttonupPin,INPUT_PULLUP);
pinMode(buttonDownPin,INPUT_PULLUP);

}



void loop() {

//button state
  int buttonupState = digitalRead(buttonupPin);
  int buttonDownState = digitalRead(buttonDownPin);
  // Check button states
  if (buttonupState ==LOW){
    targetTemperature += 1;
    delay(0);
  }
 if (buttonDownState ==LOW){
    targetTemperature -= 1;
    delay(0);
 }
  
 //measuring the voltage on the thermistor

 current = analogRead(termPin);

  

 // Convert the measured value to the thermistor resistance

 current = 1023 / current - 1;

 current = resistance / current;



 //Calculation of temperature according to the relation for the beta factor

 float temperature;

 temperature = current / termNom;     // (R/Ro)

 temperature = log(temperature);       // ln(R/Ro)

 temperature /= beta;          // 1/B * ln(R/Ro)

 temperature += 1.0 / (refTemp + 273.15); // + (1/To)

 temperature = 1.0 / temperature;      // The inverted value

 temperature -= 273.15;         // Convert from Kelvin to degrees Celsius







 lcd.setCursor(1,2);

 lcd.print("TEMP control");

 lcd.setCursor(0,1);

  

  

 lcd.setCursor(1,1);

 lcd.print("Temp:");

 lcd.setCursor(6,1);

 lcd.print(temperature,1);

 lcd.print("C");

 lcd.print("   ");

 //delay of LCD print
delay(10);

lcd.print(targetTemperature);

if (temperature < targetTemperature + tolerance ){ //cold
    digitalWrite(8, HIGH);
   
    lcd.print(" It's cold. ON ");
  }
else if  (temperature > targetTemperature - tolerance )//cold
   {digitalWrite(8, LOW);
   
    lcd.print(" It's hot.  OFF");
}
  delay(100);
}
