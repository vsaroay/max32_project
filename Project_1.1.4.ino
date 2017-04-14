
#include <Keypad.h>
#include <LiquidCrystal.h>
//#include <SPI.h>
//#include <SD.h>
//#include <MusicPlayer.h>
#include "pitches.h"
#include <String.h>

//MusicPlayer player;
// LCD pins
LiquidCrystal lcd(78, 79, 80, 81, 82, 83);//lcd pins

// Security Code init
char* ourCode = "1234";
int currentPosition = 0;


// key_char pad
const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns

//define the keymap
char keys [ROWS] [COLS] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'X', '0', '=', '/'}
};
byte rowPins[ROWS] = {70, 71, 72, 73}; //connect keypad ROW1, ROW2, ROW3, ROW4 to these arduino pins
byte colPins[COLS] = {74, 75, 76, 77}; //connect keypad COL1, COL2, COL3, COL4 to these arduino pins

//create the keypad
Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//variables declaration
boolean valOnePresent = false;
boolean next = false;
boolean final = false;
String num1, num2;
float ans;
char op;
int secure = -1;
//---------------------------------------------------------------------------------------
//Music Declaration
const int buzzer = 13;
//Hard Coded Music
int melody1[] = {
  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_DS4,
  NOTE_AS4, NOTE_G4, NOTE_DS4, NOTE_AS4,
  NOTE_G4, NOTE_D5, NOTE_D5, NOTE_D5,
  NOTE_DS5, NOTE_AS4, NOTE_FS4, NOTE_DS4,
  NOTE_AS4, NOTE_G4, NOTE_G5, NOTE_G4, NOTE_G4,
  NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_E5, NOTE_DS5,
  NOTE_E5, 0, NOTE_GS4, NOTE_CS5, NOTE_C5,
  NOTE_B4, NOTE_AS4, NOTE_A4, NOTE_AS4, 0,
  NOTE_DS4, NOTE_FS4, NOTE_DS4, NOTE_FS4,
  NOTE_AS4, NOTE_G4, NOTE_AS4, NOTE_D5, NOTE_G5,
  NOTE_G4, NOTE_G4, NOTE_G5, NOTE_FS5, NOTE_F5,
  NOTE_E5, NOTE_DS5, NOTE_E5, 0, NOTE_GS4,
  NOTE_CS5, NOTE_C5, NOTE_B4, NOTE_AS4, NOTE_A4,
  NOTE_AS4, 0, NOTE_DS4, NOTE_FS4, NOTE_DS4,
  NOTE_AS4, NOTE_G4, NOTE_DS4, NOTE_AS4, NOTE_G4
};

// note durations for Darth Vader's Theme Song: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations1[] = {
  4, 4, 4, 6, 16, 4, 6, 16, 2, 4, 4, 4,
  6, 16, 4, 6, 16, 2, 4, 6, 16, 4, 6, 16,
  16, 16, 8, 8, 8, 4, 6, 16, 16, 16, 8,
  8, 8, 4, 6, 16, 4, 6, 16, 2, 4, 6, 16,
  4, 6, 16, 16, 16, 8, 8, 8, 4, 6, 16, 16,
  16, 8, 8, 8, 4, 6, 16, 4, 6, 16, 2,
};

// Notes in the melody Cantina Band
int melody2[] = {
  NOTE_A4, 0, NOTE_D5, 0, NOTE_A4, 0,
  NOTE_D5, 0, NOTE_A4, NOTE_D5, 0,
  NOTE_A4, 0, 0, NOTE_GS4, NOTE_A4,
  0, NOTE_A4, NOTE_GS4, NOTE_A4, NOTE_G4,
  0, NOTE_FS4, NOTE_G4, NOTE_FS4, NOTE_F4,
  NOTE_D4, NOTE_A4, 0, NOTE_D5, 0,
  NOTE_A4, 0, NOTE_D5, 0, NOTE_A4,
  NOTE_D5, 0, NOTE_A4, 0, 0, NOTE_GS4,
  NOTE_A4, 0, NOTE_G4, 0, NOTE_G4,
  NOTE_FS4, NOTE_G4, 0, NOTE_C5, NOTE_AS4,
  NOTE_A4, NOTE_G4, NOTE_A4, 0, NOTE_D5,
  0, NOTE_A4, 0, NOTE_D5, 0, NOTE_A4,
  NOTE_D5, 0, NOTE_A4, 0, 0, NOTE_GS4,
  NOTE_A4, 0, NOTE_C5, 0, 0, NOTE_C5,
  NOTE_A4, NOTE_G4, 0, NOTE_F4, NOTE_D4,
  NOTE_D4, NOTE_F4, NOTE_A4, NOTE_C5, NOTE_DS5,
  NOTE_D5, NOTE_GS4, NOTE_A4, 0, NOTE_F4, 0
  
};

// note duration for Cantina Band
int noteDurations2[] = {
  4, 64, 4, 64, 4, 64, 4, 64, 8, 4,
  64, 8, 64, 8, 8, 4, 64, 8, 8, 8, 8,
  8, 8, 8, 8, 2.666, 1.99, 4, 64, 4, 64,
  4, 64, 4, 64, 8, 4, 64, 8, 64, 8, 8,
  4, 64, 8, 8, 2.666, 8, 4, 64, 8, 4, 4,
  2.666, 4, 64, 4, 64, 4, 64, 4, 64, 8, 4,
  64, 8, 64, 8, 8, 4, 64, 8, 64, 8, 2.666,
  8, 4, 64, 2.666, 1.99, 2, 2, 2, 2, 4, 4,
  8, 4, 64, 4, 2
};

// Notes in the melody Love Theme: Anakin and Padme
int melody3[] = {
  NOTE_A4, NOTE_F5, NOTE_D5, NOTE_G5,
  NOTE_F5, NOTE_E5, NOTE_F5, NOTE_D5,
  NOTE_F5, NOTE_E5, NOTE_D5, NOTE_E5,
  NOTE_C5, NOTE_D5, NOTE_C5, NOTE_A4,
  NOTE_A4, NOTE_F5, NOTE_D5, NOTE_D5,
  NOTE_E5, NOTE_F5, NOTE_G5, NOTE_E5,
  NOTE_A5, NOTE_G5, NOTE_A5, NOTE_A5,
  NOTE_C6, NOTE_AS5, NOTE_A5, NOTE_G5,
  NOTE_G5, NOTE_A5, NOTE_AS5, NOTE_AS5,
  NOTE_G5, NOTE_C6, NOTE_AS5, NOTE_A5,
  NOTE_G5, NOTE_FS5, NOTE_A5, NOTE_D6,
  NOTE_D4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4,
  NOTE_E4, NOTE_C4, NOTE_F4, NOTE_E4,
  NOTE_D4, NOTE_C4, NOTE_B3, NOTE_D4, NOTE_G4
};

// note duration for Love Theme
int noteDurations3[] = {
  2, 1.3, 2, 3, 3, 3, 2, 2, 3, 3, 3, 2,
  2, 1, 2, 1, 2, 1, 2, 3, 3, 3, 2, 2, 2,
  1, 1, 2, 1.6, 4, 4, 4, 3, 3, 3, 2, 2, 1.6,
  4, 4, 4, 4, 4, 2, 2, 1.6, 4, 4, 4, 3, 3, 3,
  2, 2, 1.6, 4, 4, 4, 4, 4, 1
};

// notes in the melody Duel of the Fates
int melody4[] = {
  NOTE_F3, NOTE_G3, NOTE_F3, NOTE_DS3, NOTE_D3,
  NOTE_F3, NOTE_G3, NOTE_F3, NOTE_DS3, NOTE_D3,
  NOTE_F3, NOTE_G3, NOTE_F3, NOTE_DS3, NOTE_D3,
  NOTE_F3, NOTE_G3, NOTE_F3, NOTE_DS3, NOTE_D3,
  NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_B3,
  NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_E4, 0, NOTE_E4,
  NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_B3, NOTE_A4,
  NOTE_G4, NOTE_FS4, NOTE_E4, 0, NOTE_DS4, NOTE_E4,
  NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_A4,
  NOTE_G4, NOTE_FS4, 0, NOTE_DS4, NOTE_E4, NOTE_FS4,
  NOTE_G4, NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_DS4
};

// note duration for Duel of the Fates
int noteDurations4[] = {
  8, 8, 16, 16, 8, 8, 8, 16, 16, 8, 8, 8, 16,
  16, 8, 8, 8, 16, 16, 8, 8, 8, 4, 4, 4, 4,
  8, 8, 4, 4, 8, 8, 4, 4, 4, 4, 8, 8, 4, 4,
  8, 8, 4, 4, 4, 4, 8, 8, 4, 4, 8, 8, 4, 4,
  4, 4, 8, 8, 1
};

//--------------------------------------------------------------------------------------------------------------------------------------
//Whack a mole declarations
#define MOLENUM 5
#define TIMESTAGE_1 10000
#define TIMESTAGE_2 25000
#define TIMESTAGE_3 25000
#define TIMESTAGE_4 60000
#define MOLE_NUM_1 1
#define MOLE_NUM_2 2
#define MOLE_NUM_3 3
#define MOLE_NUM_4 4
#define UPTIME_1 5000
#define UPTIME_2 4000
#define UPTIME_3 3000
#define UPTIME_4 2000
#define DURATION_1 50
#define DURATION_2 100
#define DURATION_3 200
#define FREQ_HIT 165
#define FREQ_FAIL_1 2794
#define FREQ_FAIL_2 3136
int melody[]=  {NOTE_F4,
NOTE_F4, NOTE_C5, NOTE_C5,NOTE_C5};
int thisNote=0;

int noteDuration []= {6
,8,4,4,6};
/*int parseInputKey(char userInput){
  return 0;
};
void reportScore(){
};*/

#define BUZPIN 10
int LPINS [MOLENUM +1] = {0, 2, 3, 4, 5, 6}; 
int FREQPOP [MOLENUM +1] = {0,330,440,554,659,880};

int led1 = 22;
int led2 = 24;
int long starTick;
int long popTick [MOLENUM +1] = {0,0,0,0,0,0};
int counter [MOLENUM +1] = {0,0,0,0,0,0};
int score = 0;
int isScoreShown = 0;
int upTime = UPTIME_1;

//--------------------------------------------------------------------------------------------------------------------------------------

void setup()
{
  lcd.begin(16,2);
  int i;
  Serial.begin(9600);
  for (i =1; i< MOLENUM; i++){
    pinMode(LPINS[i], OUTPUT);
  }  
  randomSeed(analogRead(0));
  //int starTick = millis();
  pinMode(buzzer, OUTPUT);
}

void loop()
{
  loop_code();
  
}
//--------------------------------------------------------------------------------------------------------------------------------------
void loop_code()
{
  lcd.clear();
  displayCodeEntryScreen();
  secure = Security();
  while(secure != 1)
  {
    lcd.setCursor(0,0);
    secure = Security();
  }
  lcd.clear();
  main_menu();
  /*while(1){
    lcd.setCursor(0,0);
    lcd.print("Calc");
    Calc_loop();
  }*/
}
//----------------------------------------------------------------------------------------
void main_menu()
{
  lcd.clear();
  while(1)
  {
  lcd.setCursor(0,0);
  lcd.print("A Calc  B Tune");
  lcd.setCursor(0,1);
  lcd.print("C Pass  D Game");
  char key_char = myKeypad.getKey();
  switch(key_char)
  {
    case '+':
     lcd.clear();
       while(1)
       {
         lcd.setCursor(0,0);
         lcd.print("Calc");
         Calc_loop();
       }
       break;
     case '-':
      lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Music from Star");
        lcd.setCursor(0,1);
        lcd.print("Wars");
        delay(5000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("A - Darth Vader's");
        lcd.setCursor(0,1);
        lcd.print("Theme");
        delay(5000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("B - Cantina");
        lcd.setCursor(0,1);
        lcd.print("Band");
        delay(5000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("C - Love");
        lcd.setCursor(0,1);
        lcd.print("Theme");
        delay(5000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("D - Duel of");
        lcd.setCursor(0,1);
        lcd.print("The Fates");
        delay(5000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("* - Main Menu");
        delay(5000);
        lcd.clear();
      while(1)
      {
        lcd.setCursor(0,0);
        lcd.print("Select Song");
        Music_Selection();
      }
      break;
      case '*':
        lcd.clear();
        password();
        break;
     case 'X':
       loop_code();
       break;
     case '/':
      score = 0;
      starTick = millis();
      lcd.clear();
      while(1)
      {
        lcd.setCursor(0,0);
        lcd.print("Whack a Mole");
         Whack();
      }
      break;
     default:
       break;
    }
  }
}
void Music_Selection()
{
  char selection = myKeypad.getKey();
  switch(selection)
  {
    case '+': //darth vader's theme
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Darth Vader's");
      lcd.setCursor(0,1);
      lcd.print("Theme");
      playSong(1);
      break;
    case '-':
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cantina Band");
      playSong(2);
      break;
    case '*':
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Love Theme");
      playSong(3);
      break;
    case '/':
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Duel of the Fates");
      playSong(4);
      break;
    case 'X':
      main_menu();
      break;
    default:
      break;
  }
}



void playSong(int i)
{
  switch(i)
  {
    case 1:
      for (int thisNote = 0; thisNote < 70; thisNote++) {  // for 70 notes... this is what happens
        int noteDuration1 = 1000/noteDurations1[thisNote];  // sets up note duration for Darth Vader's Theme
        tone(buzzer, melody1[thisNote],noteDuration1);  // tells the buzzer to play Darth Vader's Theme
        int pauseBetweenNotes = noteDuration1 * 1.60;  // sets the tempo for the song
        delay(pauseBetweenNotes);  // pauses the buzzer
        noTone(buzzer);  // stops the buzzer playing
      }
      break;
    case 2:
      for (int thisNote = 0; thisNote < 91; thisNote++) {  // for 91 notes, this is what happens
        int noteDuration2 = 1000/noteDurations2[thisNote];  // defines note duration for cantina band
        tone(buzzer, melody2[thisNote],noteDuration2);  // tells the  buzzer to play the cantina band melody
        int pauseBetweenNotes2 = noteDuration2 * 0.80; // sets the tempo
        delay(pauseBetweenNotes2);  //pauses the buzzer
        noTone(buzzer);  // stops the buzzer playing
      }
      break;
    case 3:
      for (int thisNote = 0; thisNote < 61; thisNote++) {  // for 61 notes this is what happens
        int noteDuration3 = 1000/noteDurations3[thisNote];  // defines note duration for love theme
        tone(buzzer, melody3[thisNote],noteDuration3);  // tells the buzzer to play love theme
        int pauseBetweenNotes3 = noteDuration3 * 1.10;  // sets the tempo
        delay(pauseBetweenNotes3);  // pauses the buzzer
        noTone(buzzer);  // stops the buzzer
      }
      break;
    case 4:
      for (int thisNote = 0; thisNote < 59; thisNote++) {  // for the 59 notes being played... this is what happens
        int noteDuration4 = 1000/noteDurations4[thisNote];  // sets up the note duration for Duel of the Fates
        tone(buzzer, melody4[thisNote],noteDuration4);  // tells the buzzer to play Duel of the Fates
        int pauseBetweenNotes4 = noteDuration4 * 1.40;  // sets the tempo
        delay(pauseBetweenNotes4);  // pauses the buzzer
        noTone(buzzer); // stops the buzzer
      }
      break;
    default:
      
      break;
  }
}
//---------------------------------------------------------------------------------------
void password()
{
  lcd.setCursor(0,0);
  lcd.print("Enter Old");
  lcd.setCursor(0,1);
  lcd.print("Password");
  int old_password = -1;
  while(old_password != 1)
  {
    lcd.setCursor(0,0);
    old_password = Security();
  }
   
  change_password();
  //lcd.clear();
  //lcd.setCursor(0,0);
  //lcd.print(ourCode);
  //delay(5000);  
  main_menu();
}

//char* change_password()
void change_password()
{
  String newPass;
  newPass = "";
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter New Code");
  int k;
  int currPos = 0;  
  while(currPos < 4){
  char key_char = myKeypad.waitForKey();
  if (int(key_char) != 0) {
    lcd.setCursor(12+currPos,1);
    newPass = newPass + key_char;
    lcd.print("*");
    ++currPos;
    }
  }     
    //int tmp = newPass.toInt();
    //int tmp = atoi((const char*)newPass);
    String conf = "";
    int confCount = 0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Confirm Pass");
    while(confCount < 4)
    {
      char key_char = myKeypad.waitForKey();
      if((int)key_char != 0)
      {
        lcd.setCursor(12+confCount, 1);
        conf = conf + key_char;
        lcd.print("*");
        ++confCount;
      }
    }
      if(strcmp(conf.c_str(), newPass.c_str()))
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Error:");
        lcd.setCursor(0,1);
        lcd.print("Incorrect");
        delay(5000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Returning");
        lcd.setCursor(0,1);
        lcd.print("to Main");
        delay(5000);
        main_menu();
      }
    
    lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Password");
        lcd.setCursor(0,1);
        lcd.print("Changed");
        delay(5000);
    lcd.clear();
    //lcd.setCursor(0,0);
    //lcd.print(tmp+"");
    //ourCode = "";
    //ourCode += (int)tmp;
    ourCode = (char*)newPass.c_str();
    //newPass.toCharArray(ourCode,currPos);
    lcd.setCursor(0,1);
    //lcd.print(ourCode);
    delay(5000);
       
  }

//--------------------------------------------------------------------------------------------------------------------------------------
void Calc_loop()
{
  
  char key_char = myKeypad.getKey();
  if (key_char != NO_KEY && (key_char=='1'||key_char=='2'||key_char=='3'||key_char=='4'||key_char=='5'||key_char=='6'||key_char=='7'||key_char=='8'||key_char=='9'||key_char=='0')){
    if (valOnePresent != true){
      num1 = num1 + key_char;
      int numLength = num1.length();
      lcd.clear();
      lcd.setCursor(15 - numLength, 0); //to adjust one whitespace for operator
      lcd.print(num1);
    }
    else {
      num2 = num2 + key_char;
      int numLength = num2.length();
      lcd.setCursor(15 - numLength, 1);
      lcd.print(num2);
      final = true;
    }
  }
  else if(!valOnePresent && num1 == "" && key_char != NO_KEY && key_char == 'X')
  {
    main_menu(); 
  }
  else if (valOnePresent == false && key_char != NO_KEY && (key_char == '/' || key_char == '*' || key_char == '-' || key_char == '+')){
    if (valOnePresent == false){
      valOnePresent = true;
      op = key_char;
      lcd.setCursor(15,0); //operator on right corner
      lcd.print(op);
    }
  }

  else if (final == true && key_char != NO_KEY && key_char == '='){
    if (op == '+'){
      ans = num1.toInt() + num2.toInt();
    }
    else if (op == '-'){
      ans = num1.toInt() - num2.toInt();
    }
    else if (op == '*'){
      ans = (float)(num1.toInt()) * (float)(num2.toInt());
    }
    else if (op == '/'){
      ans = (float)(num1.toInt()) / (float)(num2.toInt());
    }    
      lcd.clear();
      lcd.setCursor(15,0);
      lcd.autoscroll();
      lcd.print(ans);
      lcd.noAutoscroll();
      calc_clear();
  }
  else if (valOnePresent && key_char != NO_KEY && key_char == 'X'){
    calc_clear();
    lcd.clear();
  }
}
//----------------------------------------------------------------------------------------
void calc_clear()
{
  valOnePresent = false;
  final = false;
  num1 = "";
  num2 = "";
  ans = 0;
  op = ' ';
}
//----------------------------------------------------------------------------------------
int Security()
{
  int l;
  char key_char = myKeypad.getKey();
  int access;
  if (int(key_char) != 0) {
    lcd.setCursor(12,1);
    lcd.print("    ");
    lcd.setCursor(12,1);
    
    for (l=0; l<=currentPosition; ++l)
    {
      lcd.print("*");
    }
    if (key_char == ourCode[currentPosition])
    {
      ++currentPosition;
      if (currentPosition == 4)
      {
        unlockDoor();
        currentPosition = 0;
        access = 1;
      }
    } else 
    {
      invalidCode();
      currentPosition = 0;
      access = 0;
    }  
  }
  return access;
}
//----------------------------------------------------------------------------------------
void invalidCode()
{
  clearScreen();
  lcd.setCursor(0,0);
  lcd.print("ACCESS DENIED!");
  
  delay(1000);
  displayCodeEntryScreen();
}
//----------------------------------------------------------------------------------------
void unlockDoor()
{
  clearScreen();
  lcd.setCursor(0,0);
  lcd.print("ACCESS GRANTED");
  
  //add any code to unlock the door here
  delay(1000);
  clearScreen();
}
//----------------------------------------------------------------------------------------
void displayCodeEntryScreen()
{
  clearScreen();
  lcd.setCursor(0,0);
  lcd.print("Enter Code:");
}
//----------------------------------------------------------------------------------------
void clearScreen()
{
  lcd.setCursor(0,0);
  lcd.print("                    ");
  lcd.setCursor(0,1);
  lcd.print("                    ");
}
//----------------------------------------------------------------------------------------
void Whack() {
  // put your setup code here, to run once:
 int long currentTick;
currentTick = millis() - starTick;
//while(currentTick <=60000){
  // put your main code here, to run repeatedly:
int key;
int i;
int currentMoles = 0;
int moreMoles = 0;
int randNum =0;
int keyNum =-1;
int numberOfMoles = 0;


if (currentTick >=TIMESTAGE_4){
  numberOfMoles = 0;
  for (i =1; i>=MOLENUM; i++){
     if (counter[i] !=0){
       digitalWrite(LPINS[i], LOW);
       counter[i] =0;
       popTick[i] =0;
       tone(BUZPIN, FREQ_FAIL_2, DURATION_2 );
       delay(DURATION_3 );  
  }      
  }
    if(isScoreShown ==0)
    {
      playMusic(); 
     reportScore();
     isScoreShown = 1;
    }
  }
  else if(currentTick >= TIMESTAGE_3)
  {
   numberOfMoles = MOLE_NUM_4;
   upTime = UPTIME_4;
  }
  else if (currentTick >= TIMESTAGE_2)
  {
   numberOfMoles = MOLE_NUM_3;
   upTime = UPTIME_3;
  }
  else if (currentTick >= TIMESTAGE_1)
  {
   numberOfMoles = MOLE_NUM_2;
   upTime = UPTIME_2;
  }
   else 
  {
   numberOfMoles = MOLE_NUM_1;
   upTime = UPTIME_1;
  }
  for(i =1; i<=MOLENUM; i++)
  {
   if ((counter[i] !=0)&&((currentTick - popTick[i]) > upTime))
  {
   counter[i]=0;
   popTick[i] =0;
   digitalWrite(LPINS[i], LOW);  
   tone( BUZPIN, FREQ_FAIL_2, DURATION_2);
   delay( DURATION_3);
  }
  currentMoles = currentMoles + counter[i];
}
  moreMoles = numberOfMoles-currentMoles;
  
   for(i=0; i<moreMoles; i++)
  {
   randNum = random(1, MOLENUM+1);
  if (counter[randNum] ==0)
  {
    Serial.println("make a mole");
    counter[randNum ]= 1;
     popTick[randNum ]= currentTick;
      digitalWrite(LPINS[randNum], HIGH);
      tone( BUZPIN,FREQPOP[randNum], DURATION_1);
      delay(DURATION_1);

  }  
  }
  key= myKeypad.getKey();
  if (key!= NO_KEY)
  {
   
    keyNum = parseInputKey(key);
     Serial.println(keyNum);
    if (keyNum == -1)
    {
     tone(BUZPIN, FREQ_FAIL_1, DURATION_1);
     delay(DURATION_1);
    }
    else if(counter[keyNum]>0)
    {
      counter[keyNum]=0;
      popTick[keyNum]=0;
      digitalWrite(LPINS[keyNum],LOW);
      tone(BUZPIN, FREQ_FAIL_1,DURATION_1);
      delay(DURATION_3 );
      score = score + 10;
    }
    else
    {
      tone(BUZPIN, FREQ_FAIL_1,DURATION_1);
      delay(DURATION_3 );
    }
  }
//}

}
 //char userInput; 
 //parseInputKey(userInput);
int parseInputKey(char userInput)
{
  int number= -1;
  switch (userInput)
  {
  case '1':
  number =1;
  break;
 case '3':
  number =2;
 break;
case '5':
 number =3;
 break;
 case '7':
 number =4;
 break;
 case '9':
 number =5;
 break;
 default:
 break;
  }
  return number; 
}
void reportScore()
{
  int points =0;
  int digit1 =0;
  int digit2 =0;
  int i;
  //playMusic();
  delay(1000);
  points=score;
  Serial.println(score);
  lcd.setCursor(0,1);
  lcd.print("Your Score:");
  lcd.print(" ");
  lcd.print(score);
  delay(10000);
  points = 0;
  score = 0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.clear();
      main_menu();
 /* lcd.print("* To go to Menu");
  char key_char = myKeypad.waitForKey();
  switch(key_char)
  {
    case 'X': 
      lcd.clear();
      main_menu();
      break;
    default:
      break;}*/

}


void playMusic() {
  // put your main code here, to run repeatedly:
 digitalWrite(led1, HIGH); 
 digitalWrite(led2, HIGH);
  for (thisNote = 0; thisNote <5; thisNote++) {

   
   int noteDurations = 1000 / noteDuration[thisNote];
    
    tone(8, melody[thisNote], noteDurations);

      
  

    if(thisNote % 2 == 1)
    {
  digitalWrite(led1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(noteDurations);              // wait for a second
  digitalWrite(led2, LOW);    // turn the LED off by making the voltage LOW
        
    }
  else if(thisNote % 2 == 0)
  {
      digitalWrite(led2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(noteDurations);              // wait for a second
  digitalWrite(led1, LOW);    // turn the LED off by making the voltage LOW
      
  }

    int pauseBetweenNotes = noteDurations * 1.30;
    delay(pauseBetweenNotes);
   
}
}
