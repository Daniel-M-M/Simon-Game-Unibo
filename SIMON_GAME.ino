#define LEVELS 6
#define READ_LED 1
#define READ_BUTTON 2
// potrei usare esempio: enum { READ_LED, READ_BUTTON, ecc...} state al posto di fare come o fatto adesso.
// e non dimenticare di definire lo state nel setup().

int ledSeque[LEVELS] = {};

int level = 0;
int state = READ_LED;
bool lose = false;
bool win = false;

int btn[4] = {13, 12, 11, 10};
int led[4] = {7, 6, 5, 4};


void setup() {
  Serial.begin(9600);

  for(int i = 0; i < 4; i++)
  {
    pinMode(btn[i], INPUT);
    pinMode(led[i], OUTPUT);
  }
  randomSeed(analogRead(A0));
}
void loop() {
  if (state == READ_LED)
  {
    showLeds();
  }
  
  if (state == READ_BUTTON)
  {
    win = false;
    lose = false;
    int btnLetto;
    Serial.println("Fase premi i bottoni");

    for (int i = 0; i <= level && lose == false; i++)
    {
      btnLetto = readButton();
      if (btnLetto == -1)
      {
        Serial.println("non leggo il bottone");
      }

      if (btnLetto != ledSeque[i])
      {
        lose = true;
      } else {
        winGame(i);
        if (win)
        {
          break;
        }
      }
    }

    if(lose)
    {
      loseGame();
    }
  }
}

//ok
void showLeds() {
  randomLedSequence();
  Serial.println("Show Leds");

  for (int i = 0; i <= level; i++) {
    digitalWrite(led[ledSeque[i]], HIGH);
    delay(750);
    digitalWrite(led[ledSeque[i]], LOW);
    delay(750);
  }
  state = READ_BUTTON;
}

//ok
void randomLedSequence() {
  ledSeque[level] = random(4);
}

//ok
int readButton() {
  Serial.println("Sono entrato nella fuc readButton");

  int waitButton = 0;

  while (waitButton == 0)
  {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(btn[i]) == HIGH){
        Serial.println("Bottone premuto:  " + String(btn[i]));
        delay(150);
        waitButton = 1;

        while(digitalRead(btn[i]) == HIGH);
        delay(200);
        return i;
      }
    }
  }
}

void loseGame() {
  Serial.println("Hai perso il gioco");
  for (size_t i = 0; i < 4; i++)
  {
    digitalWrite(led[0], HIGH);
    digitalWrite(led[1], HIGH);
    digitalWrite(led[2], HIGH);
    digitalWrite(led[3], HIGH);
    delay(150);
    digitalWrite(led[3], LOW);
    digitalWrite(led[2], LOW);
    digitalWrite(led[1], LOW);
    digitalWrite(led[0], LOW);
    delay(150);
  }
  lose = false;
  level = 0;
  state = READ_LED;
  restList();
  delay(3000);
}

void winGame(int numBtn) {
  if (numBtn == LEVELS - 1)
  {
    for (size_t i = 0; i < 7; i++)
    {
      for (int i = 0; i < 4; i++)
      {
        digitalWrite(led[i], HIGH);
        delay(150);
        digitalWrite(led[i], LOW);
        delay(150);
      }
    }
    lose = false;
    level = 0;
    restList();
    state = READ_LED;
    Serial.println("Hai vinto il gioco");
  }

  if (numBtn == level)
  {
    Serial.println("Next Level");
    win = true;
    level++;
    state = READ_LED;
  }
}

void restList() {
  for (size_t i = 0; i < LEVELS; i++)
  {
    ledSeque[i] = NULL;
  }
}