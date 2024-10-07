#include <SPI.h>
#include <DMD2.h>
#include <DMD.h>
#include <Wire.h>

SoftDMD dmd(2, 1);

int entity = 0; // 0:nothing, 1:cow(|), 2:human(-), 3:raptor(/),
int slash = 0; // 0:nothing, 1:vertical(|), 2:horizontal(-), 3:backslash(/), 4:forwardslash(\), 5:thrust(.)
int posX = 22;
int posY = 0;
int interval = 200;
long time; // current time
long start; // time since last move
int Xpin = 5;
int Ypin = 4;
int Zpin = 3;

int getSlash(){
  int x = analogRead(A0);
  bool y = analogRead(A1);
  bool z = analogRead(A2);

  digitalWrite(43, x);
  digitalWrite(45, y);
  digitalWrite(47, z); 
  Serial.println(x);
  delay(100);
   
}

void birth(){
  if(entity == 1){
    birthCow();
  }
  if(entity == 2){
    birthHuman();
  }
  if(entity == 3){
    birthCow();
  }
}

void move(){
  if(entity == 1){
    moveCow();
  }
  if(entity == 2){
    moveHuman();
  }
  if(entity == 3){
    moveCow();
  }
  start = millis();
}

void kill(){
  if(entity == 1){
    killCow();
  }
  if(entity == 2){
    killHuman();
  }
  if(entity == 3){
    killCow();
  }

  entity = 0;
  posX = 22;
  posY = 0;
}

void birthCow(){
  for(int x = posX; x < posX + 8; x+=2){
    for(int y = posY; y < posY + 5; y++){
      dmd.setPixel(x,y,GRAPHICS_ON);  
   }
  }
  for(int x = posX + 1; x < posX + 7; x+=2){
    for(int y = posY + 2; y < posY + 5; y++){
      dmd.setPixel(x,y,GRAPHICS_ON);  
   }  
  }
  for(int x = posX + 7; x < posX + 9; x++){
    for(int y = posY + 3; y < posY + 5; y++){
      dmd.setPixel(x,y,GRAPHICS_ON);  
   }
  }
}

void moveCow(){
  /*for(int y = posY + 3; y < posY + 5; y++){ //Head shift
      dmd.setPixel(posX + 8,y,GRAPHICS_ON);  
   }
  for(int x = posX; x < posX + 8; x+=2){ //Leg shift
    for(int y = posY; y < posY + 3; y++){
      dmd.setPixel(x,y,GRAPHICS_ON);  
   }   
  }
  for(int y = posY; y < posY + 5; y++){ // Back delete
      dmd.setPixel(posX - 1,y,GRAPHICS_OFF);  
   }
  for(int x = posX = 1; x < posX + 8; x+=2){ //Leg shift
    for(int y = posY; y < posY + 2; y++){
      dmd.setPixel(x,y,GRAPHICS_OFF);  
   }   
  }
  */
  dmd.drawFilledBox(posX, posY, posX + 9, posY + 5, GRAPHICS_OFF);
  posX++;
  birthCow();




}

void killCow(){
  for(int y = posY + 2; y < posY + 5; y++){
    dmd.setPixel(posX + 3,y,GRAPHICS_OFF);  
  }
  delay(350);
  dmd.drawFilledBox(posX, posY, posX + 9, posY + 5, GRAPHICS_OFF);
  delay(100);
  birthCow();
  for(int y = posY + 2; y < posY + 5; y++){
    dmd.setPixel(posX + 3,y,GRAPHICS_OFF);  
  }
  delay(100);
  dmd.drawFilledBox(posX, posY, posX + 9, posY + 5, GRAPHICS_OFF);
  delay(100);
  birthCow();
  for(int y = posY + 2; y < posY + 5; y++){
    dmd.setPixel(posX + 3,y,GRAPHICS_OFF);  
  }
  delay(100);
  dmd.drawFilledBox(posX, posY, posX + 9, posY + 5, GRAPHICS_OFF);
  delay(100);
  birthCow();
  for(int y = posY + 2; y < posY + 5; y++){
    dmd.setPixel(posX + 3,y,GRAPHICS_OFF);  
  }
  delay(100);
}

void birthHuman(){
  for(int x = posX + 1; x < posX + 4; x+=2){ // Legs
    for(int y = posY; y < posY + 3; y++){
      dmd.setPixel(x,y,GRAPHICS_ON);  
    }
  }
  for(int x = posX; x < posX + 5; x+=4){ // Arms
    for(int y = posY + 4; y < posY + 7; y++){
      dmd.setPixel(x,y,GRAPHICS_ON);  
    }
  }
  for(int x = posX + 1; x < posX + 4; x++){ // Head
    for(int y = posY + 8; y < posY + 11; y++){
      dmd.setPixel(x,y,GRAPHICS_ON);  
    }
  }
  for(int y = posY + 3; y < posY + 7; y++){ // Body
      dmd.setPixel(posX + 2,y,GRAPHICS_ON);  
    }
  dmd.setPixel(posX + 1,posY + 6,GRAPHICS_ON); // Shoulders
  dmd.setPixel(posX + 3,posY + 6,GRAPHICS_ON);

}

void moveHuman(){
  dmd.drawFilledBox(posX, posY, posX + 5, posY + 11, GRAPHICS_OFF);
  posX++;
  birthHuman();
}

void killHuman(){
  for(int x = posX + 1; x < posX + 4; x++){ // Head
      dmd.setPixel(x,posY + 8,GRAPHICS_OFF);  
  }
  for(int x = posX + 1; x < posX + 4; x++){ // Head
      dmd.setPixel(x,posY + 11,GRAPHICS_ON);  
  }
  delay(350);
  dmd.drawFilledBox(posX, posY, posX + 5, posY + 11, GRAPHICS_OFF);
  delay(100);
  birthHuman();
  for(int x = posX + 1; x < posX + 4; x++){ // Neck cut
      dmd.setPixel(x,posY + 8,GRAPHICS_OFF);  
  }
  for(int x = posX + 1; x < posX + 4; x++){ // Head offset
      dmd.setPixel(x,posY + 11,GRAPHICS_ON);  
  }
  delay(100);
  birthHuman();
  for(int x = posX + 1; x < posX + 4; x++){ // Neck cut
      dmd.setPixel(x,posY + 8,GRAPHICS_OFF);  
  }
  for(int x = posX + 1; x < posX + 4; x++){ // Head offset
      dmd.setPixel(x,posY + 11,GRAPHICS_ON);  
  }
  delay(100);
  birthHuman();
  for(int x = posX + 1; x < posX + 4; x++){ // Neck cut
      dmd.setPixel(x,posY + 8,GRAPHICS_OFF);  
  }
  for(int x = posX + 1; x < posX + 4; x++){ // Head offset
      dmd.setPixel(x,posY + 11,GRAPHICS_ON);  
  }
  delay(100);
}

void setup() {
  //LED
  Serial.begin(9600);
  dmd.setBrightness(127);
  dmd.begin();
  entity = 1;
  birth();
  start = millis();
  //wire
  Wire.begin();
  Wire.beginTransmission(104);
  Wire.write(107);
  Wire.write(0);
  byte rc=Wire.endTransmission(true);
  pinMode (Xpin , OUTPUT );
  pinMode (Ypin , OUTPUT );
  pinMode (Zpin , OUTPUT );
  digitalWrite(Xpin, LOW);
  digitalWrite(Ypin, LOW);
  digitalWrite(Zpin, LOW);
}

void loop(){
  time = millis();
  if(time >= interval + start){
    move();
    start = millis();
  }
  slash = getSlash();
  if(slash){
    kill();
  }

  

}
