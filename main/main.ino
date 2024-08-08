#include <LiquidCrystal_I2C.h>
#include <Wire.h>

int scrollUp = A0;
int scrollDown = A1;
int enter = A2;

LiquidCrystal_I2C lcd(0x27,  16, 2);
void setup() {
  lcd.init();
  lcd.backlight();
  delay(250);
  pinMode(scrollUp, INPUT);
  pinMode(scrollDown, INPUT);
  pinMode(enter, INPUT);
}

void loop() {
  int ics[] = {7400,7402,7404,7407,7408,7432}; 
  int total = sizeof(ics)/sizeof(ics[0]);
  int currentIndex = 0;
  bool selected = false;
  void (*tester[total])() {
    nand7400,
    nor7402,
    not7404,
    buffer7407,
    aand7408,
    or7432,
  };
  print(4,0,"WELCOME!");
  delay(2000);
  lcd.clear();

  while(!selected){
    lcd.clear();
    print(0,0,"IC: " + String(ics[currentIndex]));
    if(digitalRead(scrollUp) && currentIndex<total-1){
      delay(500);
      if(digitalRead(scrollUp) && currentIndex<total-1)
      currentIndex++;

    }
    if(digitalRead(scrollDown) && currentIndex > 0){
      delay(500);
      if(digitalRead(scrollDown) && currentIndex > 0)
      currentIndex--;
    }
    if(digitalRead(enter)){
      delay(500);
      if(digitalRead(enter)){
        lcd.clear();
        print(0,0,"TESTING: " + String(ics[currentIndex]));
        delay(500);
        print(1, 1, "Testing...");
        tester[currentIndex]();

        delay(5000);

      }
    }
  }
}

void print(int c,int r,String s){

  lcd.setCursor(c,r);
  lcd.print(s);
  delay(250);


}


bool not7404() {
  int ip[] = {1, 3, 5, 9, 11, 13};
  int op[] = {2, 4, 6, 8, 10, 12};
  int a = 0, b = 0, p = 0;
  for (int i = 0; i < 6; i++) {
    pinMode(ip[i], INPUT);
    pinMode(op[i], OUTPUT);
  }
  for (int i = 0; i < 6; i++) {
    digitalWrite(ip[i], HIGH);
    a = digitalRead(op[i]);
    delay(500);
    digitalWrite(ip[i], LOW);
    b = digitalRead(op[i]);
    delay(500);
    if (a == 0 && b == 1) {
      p++;
      continue;
    } else {
      break;
    }
  }
  if(p == 6){
    lcd.clear();
    print(0, 1,"IC: 7404");
    print(1, 1,"Working");
  }
  else{
    lcd.clear();
    print(0, 1,"IC: 7404");
    print(1,1,"Not Working");
  }
}

bool buffer7407() {
  int ip[] = {1, 3, 5, 9, 11, 13};
  int op[] = {2, 4, 6, 8, 10, 12};
  int a = 0, b = 0, p = 0;
  for (int i = 0; i < 6; i++) {
    pinMode(ip[i], INPUT);
    pinMode(op[i], OUTPUT);
  }
  for (int i = 0; i < 6; i++) {
    digitalWrite(ip[i], HIGH);
    delay(500);
    a = digitalRead(op[i]);
    delay(500);
    digitalWrite(ip[i], LOW);
    delay(500);
    b = digitalRead(op[i]);
    delay(500);
    if (a == 1 && b == 0) {
      p++;
      continue;
    } else {
      break;
    }
  }
  return (p == 6);
}

bool nand7400() {
  int ip[] = {1,2,4,5,9,10,12,13};
  int op[] = {3,6,8,11};
  int a = 0, b = 0, c = 0,d=0,p=0;
  int j=0;
  for (int i = 0; i < 8; i++) 
    pinMode(ip[i], INPUT);
    for (int i = 0; i < 4; i++) 
    pinMode(op[i], OUTPUT);
    for(int i=0;i<8;i+=2){
      j=0;
    digitalWrite(ip[i],LOW);
    digitalWrite(ip[i+1],LOW);
    a=digitalRead(op[j]);

      digitalWrite(ip[i],LOW);
    digitalWrite(ip[i+1],HIGH);
    b=digitalRead(op[j]);

      digitalWrite(ip[i],HIGH);
    digitalWrite(ip[i+1],LOW);
    c=digitalRead(op[j]);

      digitalWrite(ip[i],HIGH);
    digitalWrite(ip[i+1],HIGH);
    d=digitalRead(op[j]);
    j=j+1;
    
    if(a==1 && b==1 && c==1 && d==0){
      p++;
      continue;
    }
    
    else
    break;
    }
    if(p == 4){
    lcd.clear();
    print(0, 1,"IC: 7400");
    print(1, 1,"Working");
  }
  else{
    lcd.clear();
    print(0, 1,"IC: 7400");
    print(1,1,"Not Working");
  }
    }

    bool aand7408() {
  int ip[] = {1,2,4,5,9,10,12,13};
  int op[] = {3,6,8,11};
  int a = 0, b = 0, c = 0,d=0,p=0;
  int j=0;
  for (int i = 0; i < 8; i++) 
    pinMode(ip[i], INPUT);
    for (int i = 0; i < 4; i++) 
    pinMode(op[i], OUTPUT);
    for(int i=0;i<8;i+=2){
      j=0;
    digitalWrite(ip[i],LOW);
    digitalWrite(ip[i+1],LOW);
    a=digitalRead(op[j]);

      digitalWrite(ip[i],LOW);
    digitalWrite(ip[i+1],HIGH);
    b=digitalRead(op[j]);

      digitalWrite(ip[i],HIGH);
    digitalWrite(ip[i+1],LOW);
    c=digitalRead(op[j]);

      digitalWrite(ip[i],HIGH);
    digitalWrite(ip[i+1],HIGH);
    d=digitalRead(op[j]);
    j=j+1;
    
    if(a==0 && b==0 && c==0 && d==1){
      p++;
      continue;
    }
    
    else
    break;
    }
    if(p == 4){
    lcd.clear();
    print(0, 1,"IC: 7408");
    print(1, 1,"Working");
  }
  else{
    lcd.clear();
    print(0, 1,"IC: 7408");
    print(1,1,"Not Working");
  }
    }

    bool nor7402() {
  int ip[] = {2,3,5,6,8,9,11,12};
  int op[] = {1,4,10,13};
  int a = 0, b = 0, c = 0,d=0,p=0;
  int j=0;
  for (int i = 0; i < 8; i++) 
    pinMode(ip[i], INPUT);
    for (int i = 0; i < 4; i++) 
    pinMode(op[i], OUTPUT);
    for(int i=0;i<8;i+=2){
      j=0;
    digitalWrite(ip[i],LOW);
    digitalWrite(ip[i+1],LOW);
    a=digitalRead(op[j]);

      digitalWrite(ip[i],LOW);
    digitalWrite(ip[i+1],HIGH);
    b=digitalRead(op[j]);

      digitalWrite(ip[i],HIGH);
    digitalWrite(ip[i+1],LOW);
    c=digitalRead(op[j]);

      digitalWrite(ip[i],HIGH);
    digitalWrite(ip[i+1],HIGH);
    d=digitalRead(op[j]);
    j=j+1;
    
    if(a==1 && b==0 && c==0 && d==0){
      p++;
      continue;
    }
    
    else
    break;
    }
    if(p == 4){
    lcd.clear();
    print(0, 1,"IC: 7402");
    print(1, 1,"Working");
  }
  else{
    lcd.clear();
    print(0, 1,"IC: 7402");
    print(1,1,"Not Working");
  };
    }

    bool or7432() {
  int ip[] = {1,2,4,5,9,10,12,13};
  int op[] = {3,6,8,11};
  int a = 0, b = 0, c = 0,d=0,p=0;
  int j=0;
  for (int i = 0; i < 8; i++) 
    pinMode(ip[i], INPUT);
    for (int i = 0; i < 4; i++) 
    pinMode(op[i], OUTPUT);
    for(int i=0;i<8;i+=2){
      j=0;
    digitalWrite(ip[i],LOW);
    digitalWrite(ip[i+1],LOW);
    a=digitalRead(op[j]);

      digitalWrite(ip[i],LOW);
    digitalWrite(ip[i+1],HIGH);
    b=digitalRead(op[j]);

      digitalWrite(ip[i],HIGH);
    digitalWrite(ip[i+1],LOW);
    c=digitalRead(op[j]);

      digitalWrite(ip[i],HIGH);
    digitalWrite(ip[i+1],HIGH);
    d=digitalRead(op[j]);
    j=j+1;
    
    if(a==0 && b==1 && c==1 && d==1){
      p++;
      continue;
    }
    
    else
    break;
    }
    if(p == 4){
    lcd.clear();
    print(0, 1,"IC: 7432");
    print(1, 1,"Working");
  }
  else{
    lcd.clear();
    print(0, 1,"IC: 7432");
    print(1,1,"Not Working");
  };
    

}


  



