bool **aaa;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
 // pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  
**aaa = new bool*[10];
aaa[0] = new bool[7]{true,true,true,true,true,true,false}; 
aaa[1] = new bool[7]{false,true,true,false,false,false,false}; 
aaa[2] = new bool[7]{true,true,false,true,true,false,false}; 
aaa[3] = new bool[7]{true,true,true,true,false,false,true}; 
aaa[4] = new bool[7]{false,true,true,false,false,true,true}; 
aaa[5] = new bool[7]{true,false,true,true,false,true,true}; 
aaa[6] = new bool[7]{true,false,true,true,true,true,false}; 
aaa[7] = new bool[7]{true,true,true,false,false,false,true}; 
aaa[8] = new bool[7]{true,true,true,true,true,true,true}; 
aaa[9] = new bool[7]{true,true,true,true,false,true,true}; 

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
analogWrite(A5,1023);
analogWrite(A4,1023);
}
long c = 0;

void set(int a)
{ 
}

void table(bool *abc){}


/*
delay(analogRead(A5));
 */
int abc = 0;
void loop() {

digitalWrite(2,false);
}
