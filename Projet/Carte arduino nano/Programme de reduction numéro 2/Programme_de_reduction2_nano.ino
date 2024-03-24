#include <avr/sleep.h>
#include <avr/power.h>

// Définition des constantes pour les broches utilisées
const int boutonPoussoir = 2;

// Variable pour stocker l'état du bouton poussoir
int etatBouton = 0;

void setup() {
  // Initialisation du Watchdog
  MCUSR = 0; // Réinitialise le registre de contrôle des interruptions
  WDTCSR = bit(WDCE) | bit(WDE); // Autorise les modifications du Watchdog
  WDTCSR = bit(WDIE) | bit(WDP2) | bit(WDP1) | bit(WDP0); // Configuration du Watchdog : interruption après 1 seconde de veille

  // Configuration du bouton poussoir en entrée
  pinMode(boutonPoussoir, INPUT);

  // Désactivation des modules non utilisés
  power_adc_disable(); // Désactive le module ADC
  power_timer1_disable(); // Désactive le timer 1
  power_timer2_disable(); // Désactive le timer 2

  // Mise en haute impédance des sorties non utilisées
  for (int i = 3; i < 21; i++) {
    pinMode(i, INPUT);
    digitalWrite(i, LOW);

  }

  // Configuration du mode de sommeil
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Mode de sommeil profond
  sleep_enable(); // Active le mode de sommeil

  // Initialisation de l'interruption Watchdog
  attachInterrupt(digitalPinToInterrupt(boutonPoussoir), wakeUp, CHANGE); // Active l'interruption lors d'un changement d'état du bouton
}

void loop() {
  // Entrée en mode sommeil
  sleep_cpu();
}

// Procédure d'interruption pour le réveil du microcontrôleur
void wakeUp() {
  // Désactive le mode de sommeil
  sleep_disable();

  // Attente de la relâche du bouton poussoir
  while (digitalRead(boutonPoussoir) == HIGH);

  sleep_enable();
}

// Procédure d'interruption relative au Watchdog
ISR(WDT_vect) {
  // Pas d'action nécessaire dans cette interruption
}