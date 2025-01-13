#include <LedControl.h>      
#include <LiquidCrystal.h>   
#include <Arduino.h> 
//Setari Pini
// LCD: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(5, 6, 7, 8, 9, 10);

// MAX7219: DIN, CLK, CS
LedControl lc = LedControl(11, 13, 12, 1);

// Joystick
const int joyXPin = A0;
const int joyYPin = A1;
const int swPin   = 4;  // buton joystick

// Buzzer
const int buzzerPin = 3;

// VARIABILE GLOBALE
bool soundOn = true;  // By defaul sunetul e on 
int  score   = 100;   // Scorul începe la 100 de puncte
int  bet     = 10;    // Miza implicită 

// Simboluri (8x8)
byte star[8] = {
  B00011000,
  B01011010,
  B00111100,
  B11111111,
  B00111100,
  B01011010,
  B00011000,
  B00000000
};

byte diamond[8] = {
  B00011000,
  B00111100,
  B01111110,
  B11111111,
  B01111110,
  B00111100,
  B00011000,
  B00000000
};

byte number7[8] = {
  B11111111,
  B00000011,
  B00000110,
  B00001100,
  B00011000,
  B00110000,
  B01100000,
  B11000000
};

// Vector simboluri selectate
int selectedSymbols[3];
int selectionCount = 0;

// SUNETE (BEEP) 
void beepStartup() {
  if (!soundOn) return;
  // Secvență scurtă de bip-uri
  tone(buzzerPin, 800, 200);  // 800 Hz, 200 ms
  delay(300);
  tone(buzzerPin, 1000, 200); // 1000 Hz, 200 ms
  delay(300);
  noTone(buzzerPin);
}

void beepSpin() {
  if (!soundOn) return;
  tone(buzzerPin, 600, 80);
  delay(80);
  noTone(buzzerPin);
}

void beepWin() {
  if (!soundOn) return;
  // Scurt arpegiu
  tone(buzzerPin, 1200, 150);
  delay(180);
  tone(buzzerPin, 1500, 150);
  delay(180);
  tone(buzzerPin, 1800, 150);
  delay(200);
  noTone(buzzerPin);
}

void beepLose() {
  if (!soundOn) return;
  tone(buzzerPin, 300, 400);
  delay(400);
  noTone(buzzerPin);
}

// Functii
void displaySymbol(byte symbol[8]) {//parcurge si seteaza matricea 
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, symbol[i]);
  }
}

// Rulăm simbolurile pe matrice, cu beep la fiecare
void rotateSymbols() {
  for (int i = 0; i < 3; i++) {
    displaySymbol(star);
    beepSpin();
    delay(200);

    displaySymbol(diamond);
    beepSpin();
    delay(200);

    displaySymbol(number7);
    beepSpin();
    delay(200);
  }
}

// SETARE Miza
void setBet() {
  // Valorile posibile pentru miza
  int possibleBets[] = {5, 10, 20, 50, 100};
  const int betsCount = sizeof(possibleBets) / sizeof(possibleBets[0]);
  
  // Găsim indexul mizei curente
  int betIndex = 0;
  for (int i = 0; i < betsCount; i++) {
    if (possibleBets[i] == bet) {
      betIndex = i;
      break;
    }
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Setare Miza");

  while (true) {
    lcd.setCursor(0, 1);
    lcd.print("Miza: ");
    lcd.print(possibleBets[betIndex]);
    lcd.print("     ");

    int xValue = analogRead(joyXPin);
    int yValue = analogRead(joyYPin);

    // Joystick sus (alegem miza anterioară)
    if (yValue < 300) {
      if (betIndex > 0) betIndex--;
      delay(300);
    }
    // Joystick jos (alegem miza următoare)
    else if (yValue > 700) {
      if (betIndex < betsCount - 1) betIndex++;
      delay(300);
    }

    // Apasare buton -> confirmare
    if (digitalRead(swPin) == LOW) {
      bet = possibleBets[betIndex];
      break;
    }
  }

  // Afisam miza selectată
  lcd.clear();
  lcd.print("Miza aleasa: ");
  lcd.print(bet);
  delay(1500);
  lcd.clear();
}

// SETARE SUNET ON / OFF 
void toggleSoundMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Setare Sunet");

  // localSound 0 = OFF, 1 = ON
  int localSound = soundOn ? 1 : 0;

  while (true) {
    lcd.setCursor(0, 1);
    lcd.print("Sound: ");
    if (localSound == 1) lcd.print("ON ");
    else                 lcd.print("OFF");
    lcd.print("    ");

    int yValue = analogRead(joyYPin);

    // Sus -> ON
    if (yValue < 300) {
      localSound = 1;
      delay(300);
    }
    // Jos -> OFF
    else if (yValue > 700) {
      localSound = 0;
      delay(300);
    }

    // Apăsare buton -> confirm
    if (digitalRead(swPin) == LOW) {
      soundOn = (localSound == 1);
      break;
    }
  }

  lcd.clear();
  if (soundOn) lcd.print("Sunet: ON");
  else         lcd.print("Sunet: OFF");
  delay(1500);
  lcd.clear();
}

// MENIU CONFIG (Bet + Sound)
void configMenu() {

  int menuIndex = 0;  // 0 => Miza, 1 => Sound

  while (true) {
    lcd.setCursor(0, 0);
    lcd.print("Configurare      ");

    // Afișăm opțiunea selectată pe linia a 2-a
    lcd.setCursor(0, 1);
    if (menuIndex == 0) {
      lcd.print(">Miza   Sound   ");
    } else {
      lcd.print(" Miza  >Sound   ");
    }

    int xValue = analogRead(joyXPin);
    int yValue = analogRead(joyYPin);

    // Stânga
    if (xValue < 300) {
      menuIndex = 0;
      delay(200);
    }
    // Dreapta
    else if (xValue > 700) {
      menuIndex = 1;
      delay(200);
    }

    // Apasare buton -> intram în setBet() sau toggleSound()
    if (digitalRead(swPin) == LOW) {
      if (menuIndex == 0) setBet();        
      else                toggleSoundMenu(); 
    }

    // Dacă joystick-ul e mult în sus -> ieșim din meniu
    if (yValue < 300) {
      delay(300); // antirență
      lcd.clear();
      return; // revenim la joc
    }
  }
}

// ====================== CHECK RESULT ======================
void checkResult() {
  bool isWin = false;
  if (selectedSymbols[0] == 2 && selectedSymbols[1] == 2 && selectedSymbols[2] == 2) {
    // 7-7-7
    score += bet * 10;
    lcd.setCursor(0, 1);
    lcd.print("777! CASTIG X10 ");
    isWin = true;
  }
  else if (selectedSymbols[0] == 0 && selectedSymbols[1] == 0 && selectedSymbols[2] == 0) {
    // STELE-STEA-STEA
    score += bet * 20;
    lcd.setCursor(0, 1);
    lcd.print("STELE! CASTIG X20");
    isWin = true;
  }
  else if (selectedSymbols[0] == 1 && selectedSymbols[1] == 1 && selectedSymbols[2] == 1) {
    // ROMB-ROMB-ROMB
    score += bet * 5;
    lcd.setCursor(0, 1);
    lcd.print("ROMBURI! X5     ");
    isWin = true;
  }
  else if (
    (selectedSymbols[0] == 2 && selectedSymbols[1] == 2 && selectedSymbols[2] == 0) ||
    (selectedSymbols[0] == 2 && selectedSymbols[1] == 0 && selectedSymbols[2] == 2) ||
    (selectedSymbols[0] == 0 && selectedSymbols[1] == 2 && selectedSymbols[2] == 2)
  ) {
    // 777 + STELE
    score += bet * 10;
    lcd.setCursor(0, 1);
    lcd.print("777+STELE! X10  ");
    isWin = true;
  }
  else if (
    (selectedSymbols[0] == 1 && selectedSymbols[1] == 1 && selectedSymbols[2] == 0) ||
    (selectedSymbols[0] == 1 && selectedSymbols[1] == 0 && selectedSymbols[2] == 1) ||
    (selectedSymbols[0] == 0 && selectedSymbols[1] == 1 && selectedSymbols[2] == 1)
  ) {
    // ROMB + STELE
    score += bet * 5;
    lcd.setCursor(0, 1);
    lcd.print("ROMB+STELE! X5  ");
    isWin = true;
  }
  else if (
    (selectedSymbols[0] == 0 && selectedSymbols[1] == 0 && selectedSymbols[2] == 2) ||
    (selectedSymbols[0] == 0 && selectedSymbols[1] == 2 && selectedSymbols[2] == 0) ||
    (selectedSymbols[0] == 2 && selectedSymbols[1] == 0 && selectedSymbols[2] == 0)
  ) {
    // 2 STELE
    score += bet * 2;
    lcd.setCursor(0, 1);
    lcd.print("2 STELE! X2     ");
    isWin = true;
  }
  else {
    // Pierdere
    score -= bet;
    lcd.setCursor(0, 1);
    lcd.print("PIERDERE!       ");
  }

  // Sunet
  if (isWin) beepWin();
  else       beepLose();

  delay(3000);
  lcd.clear();

  // Dacă rămânem fără bani
  if (score <= 0) {
    lcd.setCursor(0, 0);
    lcd.print("Ai pierdut      ");
    lcd.setCursor(0, 1);
    lcd.print("Du-te la Amanet ");
    
    // Sunet "fail" suplimentar
    if (soundOn) {
      tone(buzzerPin, 200, 1000);
      delay(1100);
      noTone(buzzerPin);
    }

    while (1) {
      // Joc blocat
    }
  } else {
    // Mai avem bani -> după fiecare rundă
    // re-selectăm miza și/sau sunetul dacă vrem
    configMenu();
  }
}

// SETUP
void setup() {
  // LCD
  lcd.begin(16, 2);
  lcd.print("Slot Machine!");

  // MAX7219
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  // Joystick buton
  pinMode(swPin, INPUT_PULLUP);

  // Buzzer
  pinMode(buzzerPin, OUTPUT);

  delay(1200);
  lcd.clear();

  // Sunet la pornire
  beepStartup();

  // Meniu initial de configurare (miza + sunet)
  configMenu();
}

// LOOP (JOCUL) 
void loop() {
  // Afisam scorul
  lcd.setCursor(0, 0);
  lcd.print("Scor: ");
  lcd.print(score);
  lcd.print("     ");

  // Daca nu am selectat încă 3 simboluri
  if (selectionCount < 3) {
    // Rulăm animația
    rotateSymbols();

    // Apăsam butonul -> selectăm un simbol random
    if (digitalRead(swPin) == LOW) {
      int randomSymbol = random(0, 3);  // 0=star, 1=diamond, 2=7
      selectedSymbols[selectionCount] = randomSymbol;

      switch (randomSymbol) {
        case 0:
          displaySymbol(star);
          lcd.setCursor(0, 1);
          lcd.print("STELE SELECTAT  ");
          break;
        case 1:
          displaySymbol(diamond);
          lcd.setCursor(0, 1);
          lcd.print("ROMB SELECTAT   ");
          break;
        case 2:
          displaySymbol(number7);
          lcd.setCursor(0, 1);
          lcd.print("777 SELECTAT    ");
          break;
      }
      delay(1500);
      lcd.clear();
      selectionCount++;
    }
  }
  else {
    // Avem 3 simboluri -> verificăm
    checkResult();
    // Resetam pentru următoarea rundă
    selectionCount = 0;
    lcd.clear();
  }
}
