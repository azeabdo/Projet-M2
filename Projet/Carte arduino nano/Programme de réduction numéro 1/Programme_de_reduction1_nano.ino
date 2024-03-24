#include <avr/sleep.h>
#include <avr/wdt.h>

ISR(WDT_vect) {
  // Procédure d'interruption du Watchdog
}

void setup() {
  // Initialisation du Watchdog
  MCUSR = 0;
  WDTCSR = (1<<WDCE) | (1<<WDE);
  WDTCSR = (1<<WDIE) | (1<<WDP3) | (1<<WDP0); // 8 secondes de délai

  // Désactiver les modules inutilisés
  PRR |= (1<<PRTWI) | (1<<PRTIM2) | (1<<PRTIM1) | (1<<PRSPI) | (1<<PRADC);

  // Mettre toutes les sorties en haute impédance
  for (int i = 0; i < 20; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
}

void loop() {
  // Mettre en sommeil
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_cpu();

  // Réveiller le microcontrôleur et effectuer les opérations nécessaires

  // ...

  // Répéter le processus de mise en sommeil
}