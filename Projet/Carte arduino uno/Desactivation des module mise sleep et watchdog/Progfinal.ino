#include <avr/sleep.h>
#include <avr/wdt.h>

void setup() {
  // Configuration du Watchdog
  cli();  // Désactiver les interruptions globales pendant la configuration
  MCUSR = 0;  // Réinitialiser le registre de réinitialisation
  WDTCSR |= (1 << WDCE) | (1 << WDE);  // Activer le changement de configuration du Watchdog
  WDTCSR = (1 << WDIE) | (1 << WDP3) | (1 << WDP0);  // Activer l'interruption Watchdog, définir une période (8 secondes)
  sei();  // Réactiver les interruptions globales

  // Initialisations nécessaires
}

void loop() {
  // Code principal
  
  // Désactiver tous les modules inutilisés
  
  // Désactiver le convertisseur analogique-numérique
  ADCSRA &= ~(1 << ADEN);

  // Désactiver le contrôleur série (UART)
  UCSR0B = 0;

  // Désactiver le contrôleur TWI (I2C)
  PRR |= (1 << PRTWI);

  // Désactiver le contrôleur SPI
  PRR |= (1 << PRSPI);

  // Désactiver les Timers
  PRR |= (1 << PRTIM0);
  PRR |= (1 << PRTIM1);
  PRR |= (1 << PRTIM2);

  // Désactiver les E/S numériques
  for (int i = 0; i < 20; i++) {
    pinMode(i, INPUT);
    digitalWrite(i, LOW);
  }

  // Mettre le microcontrôleur en mode veille totale
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
}

ISR(WDT_vect) {
  // Routine d'interruption du Watchdog
  // Cette fonction sera appelée toutes les 8 secondes
  // Ajouter ici les actions nécessaires pendant le sommeil
}
