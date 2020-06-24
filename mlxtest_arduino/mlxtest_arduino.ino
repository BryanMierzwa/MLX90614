/*************************************************** 
  This is a library example for the MLX90614 Temp Sensor

  Designed specifically to work with the MLX90614 sensors in the
  adafruit shop
  ----> https://www.adafruit.com/products/1747 3V version
  ----> https://www.adafruit.com/products/1748 5V version

  These sensors use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_MLX90614.h>
char *typeName[]={"Odczyt temperatury","temperatura czujnika"};

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);

// TIMER 1 for interrupt frequency 2 Hz:
cli(); // stop interrupts
TCCR1A = 0; // set entire TCCR1A register to 0
TCCR1B = 0; // same for TCCR1B
TCNT1  = 0; // initialize counter value to 0
// set compare match register for 2 Hz increments
OCR1A = 31249; // = 16000000 / (256 * 2) - 1 (must be <65536)
// turn on CTC mode
TCCR1B |= (1 << WGM12);
// Set CS12, CS11 and CS10 bits for 256 prescaler
TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
// enable timer compare interrupt
TIMSK1 |= (1 << OCIE1A);
sei(); // allow interrupts
  

  Serial.println("Adafruit MLX90614 test");  

  mlx.begin();  
}

void loop() {
  /*delay(500);*/
}




ISR(TIMER1_COMPA_vect){

  Serial.print("temperatura czujnika = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tOdczyt temperatury = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");


  Serial.println();}
