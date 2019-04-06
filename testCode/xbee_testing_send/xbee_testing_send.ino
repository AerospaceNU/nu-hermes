void setup() {
  // put your setup code here, to run once:
  Serial3.begin(9600);
  pinMode(13,OUTPUT);  
    
}

void loop() {
  // put your main code here, to run repeatedly:
    
    Serial3.write("Yo B");
    digitalWrite(13,HIGH);
    delay(500);
    digitalWrite(13,LOW);
    delay(500);

}
