#include <avr/sleep.h>

void setup() {
  // Initialisations nécessaires
}

void loop() {
  // Code principal
  
  // Désactiver tous les modules inutilisés
  
  // Désactiver le convertisseur analogique-numérique
  ADCSRA &= ~(1 << ADEN);

  // Désactiver le contrôleur série (UART)
  power_usart0_disable();

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

void power_usart0_disable() {
  UCSR0B = 0;
}
