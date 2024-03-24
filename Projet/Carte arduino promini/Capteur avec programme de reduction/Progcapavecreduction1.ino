#include <avr/sleep.h>
#include <avr/power.h>
const int ledPin = 13;
const int pinCapteurTactile = 2;
volatile bool capteurActive = false;
void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
// test modul
  power_usart0_disable();
  power_spi_disable();
  power_twi_disable();
  power_timer1_disable();
  power_timer0_disable();
  power_adc_disable();
  // Configuration de la minuterie pour une interruption toutes les 8 secondes
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 1249;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
  // Activation de l'interruption sur le capteur tactile
  attachInterrupt(digitalPinToInterrupt(pinCapteurTactile), capteurTouche, RISING);
}
void loop() {
  if (capteurActive) {
    int valeurCapteur = digitalRead(pinCapteurTactile);
      power_usart0_enable();
      power_spi_enable();
      power_twi_enable();
      power_timer1_enable();
      power_timer0_enable();
      power_adc_enable();
      if (valeurCapteur == HIGH) {
        digitalWrite(ledPin, HIGH);
        Serial.print("Valeur du capteur tactile : ");
        Serial.println(valeurCapteur);
        delay(1000);
        digitalWrite(ledPin, LOW);
    }
    capteurActive = false;
  }
  // Mettre le microcontrôleur en veille profonde
  sleepNow();
}
ISR(TIMER1_COMPA_vect) {
  capteurActive = true;
}
void capteurTouche() {
  capteurActive = true;
}
void sleepNow() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable();
}