#define RST 2
#define MISO 4
#define CLK 7
#define MOSI 8



unsigned char serialsend(unsigned char PINout,unsigned char PINin, unsigned char clockPin, unsigned char dataout)
{
  int datain = 0;
  for (int i = 0; i < 8; i++)  {
    digitalWrite(PINout, (dataout & (1 << 7 - i)) >> (7 - i));// 1 = msb,0 = lsb
    
    datain |= digitalRead(PINin) << 7-i;
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);  
      
  }
  
  return datain;
}
bool programmingenable(){
    int respond;
    serialsend(MOSI,MISO,CLK,0xAC);
    serialsend(MOSI,MISO,CLK,0x53);
    respond = serialsend(MOSI,MISO,CLK,0x00);
    serialsend(MOSI,MISO,CLK,0x00);
    if(respond==0x53)
        return true;
    else
        return false;
}
void cleanflash()
{
    delay(5);//required    
    serialsend(MOSI,MISO,CLK,0xAC);//chip erase command
    serialsend(MOSI,MISO,CLK,0x80);
    serialsend(MOSI,MISO,CLK,0x00);
    serialsend(MOSI,MISO,CLK,0x00);
    delay(10);//after erasechip command min 9.5ms delay is required!!!!, without it the chip wont be erased (delay is required after every word write)
}

void writeflashwordlow(int page,int offset,int bytee)
{
    
    if(offset>31 || offset<0)
        return; 
    else if(page>127)     
        return; 
    
    //128 pages x 32 words == 4096 words(commands)
    delay(5);//required
    serialsend(MOSI,MISO,CLK,0x40);
    serialsend(MOSI,MISO,CLK,page);
    serialsend(MOSI,MISO,CLK,offset);
    serialsend(MOSI,MISO,CLK,bytee);
    delay(5);//required
  
}

void writeflashwordhigh(int page,int offset,int bytee)
{
    
    if(offset>31 || offset<0)
        return; 
    else if(page>127)     
        return; 
    
    //128 pages x 32 words == 4096 words(commands)
    delay(5);//required
    serialsend(MOSI,MISO,CLK,0x48);
    serialsend(MOSI,MISO,CLK,page);
    serialsend(MOSI,MISO,CLK,offset);
    serialsend(MOSI,MISO,CLK,bytee);
    delay(5);//required
  
}
void buffertoflash(int page){
  
    serialsend(MOSI,MISO,CLK,0x4c);
    serialsend(MOSI,MISO,CLK,page);
    serialsend(MOSI,MISO,CLK,0);
    serialsend(MOSI,MISO,CLK,0);
    delay(5);//required
}

int readflash(int loworhigh,int page,int offset)
{

    int respond;
    if(loworhigh)
    {
        serialsend(MOSI,MISO,CLK,0x20);//low byte
        serialsend(MOSI,MISO,CLK,page);
        serialsend(MOSI,MISO,CLK,offset);
        respond = serialsend(MOSI,MISO,CLK,0);
        delay(5);//required
    }
    else
    {
        serialsend(MOSI,MISO,CLK,0x28);//high byte
        serialsend(MOSI,MISO,CLK,page);
        serialsend(MOSI,MISO,CLK,offset);
        respond = serialsend(MOSI,MISO,CLK,0);
        delay(5);//required
    }
    return respond;
}






void setup() {


    pinMode(MISO,INPUT);
    pinMode(MOSI,OUTPUT);
    pinMode(CLK,OUTPUT);
    pinMode(RST,OUTPUT);
    
    digitalWrite(RST, HIGH);
    
    digitalWrite(CLK, LOW);
    digitalWrite(CLK, HIGH);
    digitalWrite(CLK, LOW);
    digitalWrite(CLK, HIGH);
    digitalWrite(CLK, LOW);
    digitalWrite(CLK, HIGH);
    digitalWrite(CLK, LOW);
    
    digitalWrite(RST, LOW);
    delay(5000);
    if(programmingenable())
        Serial.println("programming enabled");
    else
        Serial.println("ERROR...programming not enabled");
    cleanflash();
    for(int x=0;x<128;x++)
    {
        
        for(int i=0;i<32;i++)
        {
            writeflashwordhigh(0,i,i);
        }
        delay(20);//required
    buffertoflash(x);
    }
    //writeflashword(0,0,0,0);
   /// writeflashword(0,1,31,239);
   /// writeflashword(0,2,47,239);
    for(int x=0;x<128;x++)
    {
        Serial.println(x);
        for(int i=0;i<32;i++)
        {
        delay(10);//required
        Serial.println(readflash(1,x,i));
        }
        delay(10);//required
        Serial.println();
    }
    



}

void loop() {
}
