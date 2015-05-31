void setup(){
Serial.println("Reading beegan");
Serial.begin(19200);
}

void loop(){
Serial.write(Serial.read());
}
