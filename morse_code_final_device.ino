//Morse Code Device (Encoder/Decoder)

unsigned long previousTime = 0;
unsigned long previous_off_time = 0;
boolean button_on = false;
long t;
boolean solve = false;
int wpm = 20;
int t_dit = 1200 / wpm;
int t_dah = 3 * t_dit;
String phrase = "";
String new_phrase = "";
unsigned long time_off;
int x = 0;
int y = 0;
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
boolean first = true;
int note = 500;
boolean decoder = true;

void setup() {

lcd.begin(16,2);
lcd.print("Morse Code");
lcd.setCursor(0,1);
lcd.print("Device v1.0");
Serial.begin(9600);
Serial.print("Dot Length: ");
Serial.println(t_dit);
Serial.print("Dash Length: ");
Serial.println(t_dah);
pinMode(9,INPUT);
pinMode(13,INPUT);
pinMode(6,INPUT);
pinMode(8, OUTPUT);
delay(1000);
lcd.clear();

}

void loop() {

decoder: 
if (decoder == true){

if (button_on == false){
  if (digitalRead(9) == HIGH){
    tone(7, 500);
    button_on = true; 
    previousTime = millis();
  }
}

if (button_on == true){
  while (digitalRead(9) == HIGH){
    //Serial.println("Button pressed");
  }
  noTone(7);
  t = millis() - previousTime; //duration of button being pressed
  previous_off_time = millis();
  Serial.print("Time On: ");
  Serial.println(t);
  button_on = false;
  solve = true;
  delay(5);
}

// solves for either a dot or dash using t
if (solve == true){
  if (t >= (t_dit - 40) && t <= (t_dit + 70)){
    phrase = phrase + ".";
  }
  if (t >= (t_dah - 40) && t <= (t_dah + 180)){
    phrase = phrase + "-";
  }
  Serial.print("Phrase: ");
  Serial.println(phrase);
  solve = false;
}

while (digitalRead(9) == LOW){   //button is off
  
  time_off = millis() - previous_off_time;

  if(digitalRead(6) == HIGH){   //switches device mode
    lcd.clear();
    lcd.print("Switching to");
    lcd.setCursor(0,1);
    lcd.print("Encoding mode");
    decoder = false;
    phrase = "";
    delay(2000);
    lcd.clear();
    goto encoder;
  }
    
  if ((time_off >= 1000) && y == 0 && first == false){
    new_phrase = new_phrase + " ";
    y = 1;
    Serial.print("Decoded Phrase: ");
    Serial.println(new_phrase);
    lcd.clear();
    lcd.print(new_phrase);
    lcd.setCursor(0,1);
    lcd.print(new_phrase.substring(16));
  }
  
  if ((time_off >= 300) && x == 0){
    //solves for character
    if (phrase == ".-"){
      new_phrase = new_phrase + "A";
    }
    if (phrase == "-..."){
      new_phrase = new_phrase + "B";
    }
    if (phrase == "-.-."){
      new_phrase = new_phrase + "C";
    }
    if (phrase == "-.."){
      new_phrase = new_phrase + "D";
    }
    if (phrase == "."){
      new_phrase = new_phrase + "E";
    }
    if (phrase == "..-."){
      new_phrase = new_phrase + "F";
    }
    if (phrase == "--."){
      new_phrase = new_phrase + "G";
    }
    if (phrase == "...."){
      new_phrase = new_phrase + "H";
    }
    if (phrase == ".."){
      new_phrase = new_phrase + "I";
    }
    if (phrase == ".---"){
      new_phrase = new_phrase + "J";
    }
    if (phrase == "-.-"){
      new_phrase = new_phrase + "K";
    }
    if (phrase == ".-.."){
      new_phrase = new_phrase + "L";
    }
    if (phrase == "--"){
      new_phrase = new_phrase + "M";
    }
    if (phrase == "-."){
      new_phrase = new_phrase + "N";
    }
    if (phrase == "---"){
      new_phrase = new_phrase + "O";
    }
    if (phrase == ".--."){
      new_phrase = new_phrase + "P";
    }
    if (phrase == "--.-"){
      new_phrase = new_phrase + "Q";
    }
    if (phrase == ".-."){
      new_phrase = new_phrase + "R";
    }
    if (phrase == "..."){
      new_phrase = new_phrase + "S";
    }
    if (phrase == "-"){
      new_phrase = new_phrase + "T";
    }
    if (phrase == "..-"){
      new_phrase = new_phrase + "U";
    }
    if (phrase == "...-"){
      new_phrase = new_phrase + "V";
    }
    if (phrase == ".--"){
      new_phrase = new_phrase + "W";
    }
    if (phrase == "-..-"){
      new_phrase = new_phrase + "X";
    }
    if (phrase == "-.--"){
      new_phrase = new_phrase + "Y";
    }
    if (phrase == "--.."){
      new_phrase = new_phrase + "Z";
    }
  Serial.print("Decoded Phrase: ");
  Serial.println(new_phrase);
  lcd.clear();
  lcd.print(new_phrase);
  lcd.setCursor(0,1);
  lcd.print(new_phrase.substring(16));
  phrase = "";
  x = 1;
  }

  if (digitalRead(13) == HIGH){   //reset device
  phrase = "";
  new_phrase = "";
  first = true;
  Serial.println("Device Reset");
  lcd.clear();
  lcd.print("Resetting Device");
  delay(1000);
  lcd.clear();
  return;
  }
  
}

first = false;
tone(7, 500);
x = 0;
y = 0;
previousTime = millis();
Serial.print("Time Off: ");
Serial.println(time_off);
button_on = true; 
} 
// end of decoder




encoder:
if (decoder == false){

Serial.println("Enter the phrase:");
lcd.clear();
lcd.print("Enter the phrase");

while (Serial.available() == 0){ 
  if (digitalRead(6) == HIGH){  //switches device mode
    lcd.clear();
    lcd.print("Switching to");
    lcd.setCursor(0,1);
    lcd.print("Decoding mode");
    decoder = true;
    phrase = "";
    new_phrase = "";
    delay(2000);
    lcd.clear();
    goto decoder;
  }
}
  
phrase = Serial.readString();
lcd.clear();
lcd.print("Encoding message");

for (int i = 0; i <= phrase.length(); i++) {
  if (phrase[i] == 'a') {
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 'b') {
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 'c') {
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 'd'){
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 'e'){
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 'f'){
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 'g'){
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 'h'){
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 'i'){
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 'j'){
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 'k'){
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 'l'){
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 'm'){
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 'n'){
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 'o'){
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 'p'){
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 'q'){
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 'r'){
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 's'){
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 't'){
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 'u'){
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 'v'){
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 'w'){
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 'x'){
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 'y'){
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
  }
  else if (phrase[i] == 'z'){
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dah);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
    delay(t_dit);
    digitalWrite(8, HIGH); tone(7, note);
    delay(t_dit);
    digitalWrite(8, LOW); noTone(7);
  }
  
delay(t_dah);
} // end of for loop

} // end of encoder



}
