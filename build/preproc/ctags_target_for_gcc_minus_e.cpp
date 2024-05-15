# 1 "C:\\Users\\ace_m\\OneDrive\\Documenti\\quarto_semestre_TSI\\Embedded_IoT\\SIMON_GAME\\SIMON_GAME.ino"



// potrei usare esempio: enum { READ_LED, READ_BUTTON, ecc...} state al posto di fare come o fatto adesso.
// e non dimenticare di definire lo state nel setup().

int ledSeque[6] = {};

int level = 0;
int state = 1;
bool lose = false;
bool win = false;

int btn[4] = {13, 12, 11, 10};
int led[4] = {7, 6, 5, 4};


void setup() {
  Serial.begin(9600);

  for(int i = 0; i < 4; i++)
  {
    pinMode(btn[i], 0x0);
    pinMode(led[i], 0x1);
  }
  randomSeed(analogRead(A0));
}
void loop() {
  if (state == 1)
  {
    showLeds();
  }

  if (state == 2)
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
    digitalWrite(led[ledSeque[i]], 0x1);
    delay(750);
    digitalWrite(led[ledSeque[i]], 0x0);
    delay(750);
  }
  state = 2;
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
      if (digitalRead(btn[i]) == 0x1){
        Serial.println("Bottone premuto:  " + String(btn[i]));
        delay(150);
        waitButton = 1;

        while(digitalRead(btn[i]) == 0x1);
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
    digitalWrite(led[0], 0x1);
    digitalWrite(led[1], 0x1);
    digitalWrite(led[2], 0x1);
    digitalWrite(led[3], 0x1);
    delay(150);
    digitalWrite(led[3], 0x0);
    digitalWrite(led[2], 0x0);
    digitalWrite(led[1], 0x0);
    digitalWrite(led[0], 0x0);
    delay(150);
  }
  lose = false;
  level = 0;
  state = 1;
  restList();
  delay(3000);
}

void winGame(int numBtn) {
  if (numBtn == 6 - 1)
  {
    for (size_t i = 0; i < 7; i++)
    {
      for (int i = 0; i < 4; i++)
      {
        digitalWrite(led[i], 0x1);
        delay(150);
        digitalWrite(led[i], 0x0);
        delay(150);
      }
    }
    lose = false;
    level = 0;
    restList();
    state = 1;
    Serial.println("Hai vinto il gioco");
  }

  if (numBtn == level)
  {
    Serial.println("Next Level");
    win = true;
    level++;
    state = 1;
  }
}

void restList() {
  for (size_t i = 0; i < 6; i++)
  {
    ledSeque[i] = 
# 163 "C:\\Users\\ace_m\\OneDrive\\Documenti\\quarto_semestre_TSI\\Embedded_IoT\\SIMON_GAME\\SIMON_GAME.ino" 3 4
                 __null
# 163 "C:\\Users\\ace_m\\OneDrive\\Documenti\\quarto_semestre_TSI\\Embedded_IoT\\SIMON_GAME\\SIMON_GAME.ino"
                     ;
  }
}
