/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 11;
int LED_PIN = 10;

const long volUp = 0x481;
const long volDown = 0xC81;
const long power = 0xA81;

const long red = 0x1000E0F;
const long green = 0x1008E8F;
const long blue =  0x100CECF;

IRrecv irrecv(RECV_PIN);
IRsend irsend;

decode_results results;

void setup()
{
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Started the receiver");
}

void led(uint8_t val) {
  digitalWrite(LED_PIN, val);
  delay(200);
}

void transmit(int value) {
  Serial.print("transmit(): ");
  Serial.println(results.value, HEX);
  
  for (int i = 0; i < 3; i++) {
    irsend.sendSony(value, 12); // Sony TV power code
    delay(40);
  }
  irrecv.enableIRIn(); // Re-enable receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.print("Received: ");
    Serial.println(results.value, HEX);

    if (results.value == red) {
      transmit(volDown);
    } 
    else if (results.value == green) {
      transmit(volUp);
    }
    else if (results.value == blue) {
      transmit(power);
    } 

    irrecv.resume(); // Receive the next value
  }
}
