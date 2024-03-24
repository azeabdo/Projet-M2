// Déclaration des broches
const int pinCapteurTactile = 2; // Remplacez par la broche à laquelle est connecté votre capteur tactile

void setup() {
  // Démarre la communication série à une vitesse de 9600 bauds
  Serial.begin(9600);
}

void loop() {
  // Lit la valeur du capteur tactile
  int valeurCapteur = digitalRead(pinCapteurTactile);

  // Imprime la valeur sur le port série

  //if (valeurCapteur ==1){
    
  Serial.print("Valeur du capteur tactile : ");
  Serial.println(valeurCapteur);


  //}



  // Attente de 500 millisecondes
  delay(500);
}
