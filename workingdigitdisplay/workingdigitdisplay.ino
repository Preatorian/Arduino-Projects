int **aaa;
  void setup() {
    // initialize digital pin LED_BUILTIN as an output.
   // pinMode(LED_BUILTIN, OUTPUT);
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
    pinMode(A4, OUTPUT);
    pinMode(A5, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
  
  aaa = new int*[16];
  aaa[0] = new int[7]{200,200,200,200,200,200,000}; 
  aaa[1] = new int[7]{000,200,200,000,000,000,000}; 
  aaa[2] = new int[7]{200,200,000,200,200,000,200}; 
  aaa[3] = new int[7]{200,200,200,200,000,000,200}; 
  aaa[4] = new int[7]{000,200,200,000,000,200,200}; 
  aaa[5] = new int[7]{200,000,200,200,000,200,200}; 
  aaa[6] = new int[7]{200,000,200,200,200,200,200}; 
  aaa[7] = new int[7]{200,200,200,000,000,000,000}; 
  aaa[8] = new int[7]{200,200,200,200,200,200,200}; 
  aaa[9] = new int[7]{200,200,200,200,000,200,200}; 
  aaa[10] = new int[7]{200,200,200,000,200,200,200}; 
  aaa[11] = new int[7]{000,000,200,200,200,200,200}; 
  aaa[12] = new int[7]{200,000,000,200,200,200,000}; 
  aaa[13] = new int[7]{000,200,200,200,200,000,200}; 
  aaa[14] = new int[7]{200,000,000,200,200,200,200}; 
  aaa[15] = new int[7]{200,000,000,000,200,200,200}; 
  
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
    pinMode(A4, OUTPUT);
    pinMode(A5, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
  analogWrite(A1,200);//czerowny
  
  analogWrite(A4,128);
  digitalWrite(8,LOW);//pomaranczowy 
  }
int volt=0,voltagein=0;

  void set(int a)
  { 
  for(int i=0;i<7;i++)
  {
  volt = 200-aaa[a][i];
  digitalWrite(i+2,volt);
  }
  analogWrite(A5,200-(aaa[a][4]));
  }
  
bool was=false;
int abc = 0,m=0,s=0,h=0;

void loop() 
{
  /*  set(h%10);
  analogWrite(A2,0);
  analogWrite(A3,0);*/
  
  set((m-m%10)/10);
  analogWrite(A0,128);
  delay(1);
  analogWrite(A0,0);
  set(m%10);
  analogWrite(A1,128);
  delay(1);
  analogWrite(A1,0);
  set(h%10);
  analogWrite(A2,128);
  delay(1);
  analogWrite(A2,0);
  set((h-h%10)/10);
  analogWrite(A3,128);
  delay(1);
  analogWrite(A3,0);
  
  if(millis()%1000>500 and millis()%1000<999)
  {
  analogWrite(A4,128);
  was=true;
  }
  else if(millis()%1000<500 and millis()%1000>=0)
  {
  analogWrite(A4,120);
  if(was==true)
    m--;
    if(s<0)
    {
      s=59;
      m--;
    }
    if(m<0)
    {
      m=59;
      h--;
    }
    if(h<0)
    {
      h=59;
    }
    was=false;
    }
  }
