/*

RpiShutTimer

This is free software released under MIT License
Copyright 2021 Giorgio L. Rutigliano
(www.iltecnico.info, www.i8zse.eu, www.giorgiorutigliano.it)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. 

*/
int TimeOut=100; //seconds to wait before poweroff
int REL=6;
int INP=7;
bool LastState=0;
int Tl=TimeOut;

void setup() {
  pinMode(REL, OUTPUT); // 
  pinMode(INP, INPUT);
  digitalWrite(REL, HIGH); 
  Serial.begin(9600);
}

void loop() {
  bool KEY=digitalRead(INP);
  if (KEY && !LastState) {
    LastState=KEY;
    Tl=TimeOut;
    Serial.println("**Powerback**");
  } 
  if (!KEY && LastState) {
    LastState=KEY;
    Serial.println("**Powerfail**");
  } 
  delay(1000); // wait for a second
  Serial.print(KEY);
  Serial.println(LastState);
  if (KEY==0) {
    Tl-=1;
    if (Tl<1) {
      Serial.println("**PowerOff**");
      digitalWrite(REL, LOW);
      exit(0); 
    }  
  }   
}
