#include <avr/sleep.h>
#include <avr/power.h>

const int ledPin = 13; // Broche LED intégrée sur la carte Arduino Pro Mini

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  // Configuration de la minuterie pour une interruption toutes les 8 secondes
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 15624;           // 8-secondes avec une horloge de 8 MHz
  TCCR1B |= (1 << WGM12);  // Mode CTC (Clear Timer on Compare Match)
  TCCR1B |= (1 << CS12);   // Prédiviseur de 256
  TIMSK1 |= (1 << OCIE1A); // Activation de l'interruption de comparaison
  interrupts();
}

void loop() {
  // Le code ici sera exécuté entre chaque interruption de la minuterie
}

ISR(TIMER1_COMPA_vect) {
  // Cette fonction sera appelée chaque fois que la minuterie atteindra la valeur définie
  digitalWrite(ledPin, HIGH); // Allumer la LED pour montrer que le microcontrôleur est actif
  delay(1000);                // Attendre pendant 1 seconde
  digitalWrite(ledPin, LOW);  // Éteindre la LED

  // Désactiver le module ADC pour économiser de l'énergie
  ADCSRA &= ~(1 << ADEN); // Désactiver l'ADC

  // Mettre le microcontrôleur en veille profonde pour économiser de l'énergie
  sleepNow();
}

void sleepNow() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Choisir le mode de veille profonde
  sleep_enable();                      // Autoriser la veille
  sleep_mode();                        // Mettre le microcontrôleur en veille
  sleep_disable();                     // Désactiver la veille lorsqu'il est réveillé

  // Réactiver le module ADC après la veille
  ADCSRA |= (1 << ADEN); // Réactiver l'ADC
}
