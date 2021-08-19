#define R 10
#define G 9
#define B 11

int rVal=0, gVal=0, bVal=0, prevR=0, prevG=0, prevB=0;
bool test = false;

void testMode(){
  //init color cycle
  digitalWrite(R, HIGH);
  delay(1000);
  digitalWrite(R, LOW);
  digitalWrite(G, HIGH);
  delay(1000);
  digitalWrite(G, LOW);
  digitalWrite(B, HIGH);
  delay(1000);
  digitalWrite(B, LOW);
  delay(1000);
}

void generateColor(){
  randomSeed(analogRead(A0));
  rVal = random(256);
  randomSeed(analogRead(A0));
  gVal = random(256);
  randomSeed(analogRead(A0));
  bVal = random(256);
  if(rVal>150){
    gVal = random(100);
    bVal = random(100);
  } else if(gVal>150){
    rVal = random(100);
    bVal = random(100);
  } else if(bVal>150){
    rVal = random(100);
    gVal = random(100);
  } else {
    switch(random(100)%3){
      case 0:
        rVal = random(150, 256);
        gVal = random(100);
        bVal = random(100);
        break;
      case 1:
        rVal = random(100);
        gVal = random(150, 256);
        bVal = random(100);
        break;
      case 2:
        rVal = random(100);
        gVal = random(100);
        bVal = random(150, 256);
        break;
    }
  }
}

void renderLed(){
  for(int i=0; i<255; i++){
    if(rVal!=prevR){
      if(rVal<prevR){
        prevR--;
      } else {
        prevR++;
      }          
    }
    if(gVal!=prevG){
      if(gVal<prevG){
        prevG--;
      } else {
        prevG++;
      }          
    }
    if(bVal!=prevB){
      if(bVal<prevB){
        prevB--;
      } else {
        prevB++;
      }          
    }
    analogWrite(R, prevR);
    analogWrite(G, prevG);
    analogWrite(B, prevB);
    delay(10);
  }
}

void printData(){
  //Serial output
  Serial.print("R: ");
  Serial.print(rVal);
  Serial.print(", G: ");
  Serial.print(gVal);
  Serial.print(", B: ");
  Serial.print(bVal);
  Serial.println();
}

void setup()
{
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  randomSeed(analogRead(A0));
  Serial.begin(9600);
  testMode();
}

void loop()
{
  if(test){
    testMode();
  } else {
    generateColor();
    renderLed();
    printData();
    delay(10000);
  }
}
