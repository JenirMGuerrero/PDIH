int interruptor=0;

void setup() {
	pinMode(13, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(11, OUTPUT);
  	pinMode(7, INPUT);

}

void loop() {
  interruptor=digitalRead(7);
  
  if(interruptor==HIGH){    
	digitalWrite(13, HIGH);
	digitalWrite(12, LOW);
	digitalWrite(11, LOW);
    
  }else if(interruptor==LOW){
    
    digitalWrite(13, HIGH);
	digitalWrite(12, LOW);
	digitalWrite(11, LOW);
	delay(1500); 

	digitalWrite(13, LOW);
	digitalWrite(12, HIGH);
	digitalWrite(11, LOW);

	delay(1500);

	digitalWrite(13, LOW);
	digitalWrite(12, LOW);
	digitalWrite(11, HIGH);

	delay(1500);
  }

}