#include <avr/sleep.h>
#include <avr/wdt.h>

void setup() {
  // Configuration du Watchdog
  cli();  // Désactiver les interruptions globales pendant la configuration
  MCUSR = 0;  // Réinitialiser le registre de réinitialisation
  WDTCSR |= (1 << WDCE) | (1 << WDE);  // Activer le changement de configuration du Watchdog
  WDTCSR = (1 << WDIE) | (1 << WDP3) | (1 << WDP0);  // Activer l'interruption Watchdog, définir une période (8 secondes)
  sei();  // Réactiver les interruptions globales

  // Mise en sommeil
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void loop() {
  sleep_mode();  // Entrer en mode sommeil
}

ISR(WDT_vect) {
  // Routine d'interruption du Watchdog
  // Cette fonction sera appelée toutes les 8 secondes

  // Ajouter ici les actions nécessaires pendant le sommeil
  // Notez que vous pouvez réveiller le microcontrôleur à intervalles réguliers
  // pour effectuer des tâches spécifiques avant de retourner en sommeil
}
