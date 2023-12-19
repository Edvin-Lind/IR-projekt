#include <IRremote.h>

// Deklarerar variabler som är relevanta till koden.
const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;
boolean ON = (false);
boolean Repeat = (true);

// Setup, startar IR modulen samt Serial-monitorn.
void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  pinMode(2, OUTPUT);
}

// Main loopen som updaterar de olika funktionerna.
void loop() {
  updateReceiver();
  updateLight();
  updateONOFF();
}

// updaterar värdet på "results" samt visar results.value i serial monitor.
void updateReceiver() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    irrecv.resume();
  }
}

// Den här delen gör bara så att det är både en större delay samt värdet på boolean "ON" i serial monitor.
void updateONOFF(){
  Serial.println(ON);
  delay (250);
}

// Uppdaterar lampans status
// De 2 första if-satserna kollar vilket värde som IR-receivern tar emot (results.value) samt om boolean "ON" är true eller false.
// Om rätt värde från IR-receivern (results.value) kommer fram och "ON" är false så tänds lampan, vice versa om lampan är på.
// Den andra delen kollar om IR-värdet(results.value) är en string samt om talet 42 finns i (results.value), om 42 finns blir resultatet större än -1 
// och if-satsen påbörjas.
// I nästa if-sats kollar den om boolean "Repeat" är true eller false och ifall den är false så börjar lampan blinka (Repeat går mellan true och false)
// vilket gör att lampan startas och stängs av.
void updateLight() {
  if (results.value == 65535) {
    if (ON == false){
      digitalWrite(2, HIGH);
      ON = true;
      results.value = 0;
    }
    else{
      digitalWrite(2, LOW);
      ON = false;
      results.value = 0;
    }
  }
  String test = String(results.value);
  if (test.indexOf("42") != -1) {
    if (Repeat == false){
      digitalWrite(2, HIGH);
      Repeat = true;
    }
    else{
      digitalWrite(2, LOW);
      Repeat = false;
    }
  }
}
