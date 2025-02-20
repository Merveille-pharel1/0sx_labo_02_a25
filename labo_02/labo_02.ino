unsigned long currentTime = 0;
const int bouton = 2;
const int ledA = 11;
const int ledB = 10;
const int ledC = 9;
const int ledD = 8;
const int potentiometre = A1;

int estAppuye(unsigned long currentTime, int etatPresent){
  static int etatPrecedent = 0;
  static int dernierChangement = 0;
  int etat = 0;
  const int delay = 50;

  if(currentTime - dernierChangement < delay) return 0;

  dernierChangement = currentTime;

  if(etatPresent != etatPrecedent){
    etat = etatPresent;
  }

  etatPrecedent = etatPresent;
  return etat;
}

void allumerDel(int valeurConverti){
  if (valeurConverti <= 25){
    digitalWrite(ledA, HIGH);
    digitalWrite(ledB, LOW);
    digitalWrite(ledC, LOW);
    digitalWrite(ledD, LOW);
  }
  if (valeurConverti > 25 && valeurConverti <= 50){
    digitalWrite(ledA, LOW);
    digitalWrite(ledB, HIGH);
    digitalWrite(ledC, LOW);
    digitalWrite(ledD, LOW);
    }
    if (valeurConverti > 50 && valeurConverti <= 75){
    digitalWrite(ledA, LOW);
    digitalWrite(ledB, LOW);
    digitalWrite(ledC, HIGH);
    digitalWrite(ledD, LOW);
    }
    if (valeurConverti > 75 && valeurConverti <= 100){
    digitalWrite(ledA, LOW);
    digitalWrite(ledB, LOW);
    digitalWrite(ledC, LOW);
    digitalWrite(ledD, HIGH);
    }
}

void afficherProgression(int progression){
  int valeurMax = 20;
  Serial.print("[");
  for(int i = 1; i <= valeurMax; i++){
    if(i <= progression)
      Serial.print("#");
    else
      Serial.print(".");
  }
  Serial.print("] ");
  Serial.print(progression * 5);
  Serial.println("%");  

}

void setup() {
  Serial.begin(9600);

  // Ton code ici
  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledC, OUTPUT);
  pinMode(ledD, OUTPUT);
  pinMode(bouton, INPUT_PULLUP);
  Serial.println("Setup completed");
  }

void loop() {
  currentTime = millis();
  int valeur = analogRead(potentiometre);
  
  int progression = map(valeur, 0, 1023, 0, 20);
  
  allumerDel(progression * 5);

  int etatBouton = !digitalRead(bouton);
  if(estAppuye(currentTime, etatBouton)){
    afficherProgression(progression);
  }
}
