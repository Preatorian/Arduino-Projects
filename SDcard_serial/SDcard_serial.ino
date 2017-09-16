#define CS 2
#define MOSI 4
#define CLK 7
#define MISO 8


unsigned char serialsend(unsigned char PINout,unsigned char PINin, unsigned char clockPin, unsigned char dataout)
{
  int datain = 0;
  for (int i = 0; i < 8; i++)  {
    digitalWrite(PINout, (dataout & (1 << 7 - i)) >> (7 - i));
    
    datain |= digitalRead(PINin) << 7-i;
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);  
  }
  
  return datain;
}

/*
 * between every command, a byte has to be send!!!:
 * 
 * serialsend(MOSI,MISO,CLK,0xFF);
 * 
 * NOTE:
 * IT wasn't working without that byte
 * 
 */
void readblock(unsigned long blocknr){
    //read single block cmd17
    blocknr <<= 2;
    /*
     * 1. address must be a multiple of 512 
     * 2. first logical sector begins at: 137 -> 0x89
     */
    serialsend(MOSI,MISO,CLK,0xFF);//one byte between commands to be sure that the messege is fully sent
    
    serialsend(MOSI,MISO,CLK,0x51);
    serialsend(MOSI,MISO,CLK,(unsigned char)((blocknr & 16711680) >> 16));
    serialsend(MOSI,MISO,CLK,(unsigned char)((blocknr & 65280) >> 8));
    serialsend(MOSI,MISO,CLK,(unsigned char)(blocknr & 254));
    serialsend(MOSI,MISO,CLK,0x00);
    serialsend(MOSI,MISO,CLK,0x00);
    
    digitalWrite(MOSI,HIGH);
    
    while(digitalRead(MISO))
    {
        digitalWrite(CLK,LOW);
        digitalWrite(CLK,HIGH);
    }
    
    serialsend(MOSI,MISO,CLK,0xFF);
    while(digitalRead(MISO))
    {
        digitalWrite(CLK,LOW);
        digitalWrite(CLK,HIGH);
    }
    
    digitalWrite(CLK,LOW);
    digitalWrite(CLK,HIGH);
    for(int i=0;i<512;i++)
    {
    Serial.print(serialsend(MOSI,MISO,CLK,0xFF),HEX); 
    Serial.print(" "); 
    if((i+1)%16==0)
    Serial.println(); 
    }
    serialsend(MOSI,MISO,CLK,0xFF);//crc
}





int response=0;
void setup() {
    
    
    pinMode(CS,OUTPUT);
    pinMode(MOSI,OUTPUT);
    pinMode(CLK,OUTPUT);
    pinMode(MISO,INPUT);
    delay(6000);
    digitalWrite(MOSI,HIGH);



    do
    {
    digitalWrite(CS,HIGH);
    
    for(int i=0;i<80;i++)
    {
        digitalWrite(CLK,LOW);
        digitalWrite(CLK,HIGH);
    }
    
    
    digitalWrite(CLK,LOW);
    digitalWrite(CS,LOW);
    
    //RESET command
    
    serialsend(MOSI,MISO,CLK,0x40);
    serialsend(MOSI,MISO,CLK,0x00);
    serialsend(MOSI,MISO,CLK,0x00);
    serialsend(MOSI,MISO,CLK,0x00);
    serialsend(MOSI,MISO,CLK,0x00);
    serialsend(MOSI,MISO,CLK,0x95);
    
    while(digitalRead(MISO))
    {
        digitalWrite(CLK,LOW);
        digitalWrite(CLK,HIGH);
    }
        response = serialsend(MOSI,MISO,CLK,0xFF);
    }
    while(response!=0x01);
    
    
    Serial.println("reset ok");
    
    //CMD58 
    
    serialsend(MOSI,MISO,CLK,0xFF);//one byte between commands to be sure that the messege is fully sent
    
    serialsend(MOSI,MISO,CLK,0x7A);
    serialsend(MOSI,MISO,CLK,0x00);
    serialsend(MOSI,MISO,CLK,0x00);
    serialsend(MOSI,MISO,CLK,0x00);
    serialsend(MOSI,MISO,CLK,0x00);
    serialsend(MOSI,MISO,CLK,0x75);
    
    while(digitalRead(MISO))
    {
        digitalWrite(CLK,LOW);
        digitalWrite(CLK,HIGH);
    }
    for(int i=0;i<40;i++)
    {
        Serial.print(digitalRead(MISO));
        digitalWrite(CLK,LOW);
        digitalWrite(CLK,HIGH);  
    }
    do
    {
        
        serialsend(MOSI,MISO,CLK,0xFF);//one byte between commands to be sure that the messege is fully sent
        
        //CMD55 turns off idle mode, and informs that the next command is an aplication specific command
        serialsend(MOSI,MISO,CLK,0x77);
        serialsend(MOSI,MISO,CLK,0x00);
        serialsend(MOSI,MISO,CLK,0x00);
        serialsend(MOSI,MISO,CLK,0x00);
        serialsend(MOSI,MISO,CLK,0x00);
        serialsend(MOSI,MISO,CLK,0x95);
        
        
        digitalWrite(MOSI,HIGH);
        
        while(digitalRead(MISO))
        {
            digitalWrite(CLK,LOW);
            digitalWrite(CLK,HIGH);
        }
        
        serialsend(MOSI,MISO,CLK,0xFF);//this is only for cmd55 respond
        
        
        
        serialsend(MOSI,MISO,CLK,0xFF);//one byte between commands to be sure that the messege is fully sent
        
        //acmd14 turns off idle mode
        serialsend(MOSI,MISO,CLK,0x69);
        serialsend(MOSI,MISO,CLK,0x00);
        serialsend(MOSI,MISO,CLK,0x10);
        serialsend(MOSI,MISO,CLK,0x00);
        serialsend(MOSI,MISO,CLK,0x00);
        serialsend(MOSI,MISO,CLK,0x6F);
        digitalWrite(MOSI,HIGH);
        
        while(digitalRead(MISO))
        {
            digitalWrite(CLK,LOW);
            digitalWrite(CLK,HIGH);
        }
        
        response = serialsend(MOSI,MISO,CLK,0xFF);
        
 
    }
    while(response!=0x00);
    
    Serial.println("idle mode off");
    Serial.println();
    for(unsigned long i=0;i<10000;i++)
    {
        Serial.println();
        Serial.println(i);
        readblock(i);
         
    }
    
   

}


void loop() {
}
