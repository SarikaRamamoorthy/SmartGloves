#include <SoftwareSerial.h>

#define pinkyXaxis_pin A0 // Arduino pin connected to the VRx Pin
#define ringXaxis_pin A1 // Arduino pin connected to the VRx Pin
#define middleXaxis_pin A2 // Arduino pin connected to the VRx Pin
#define indexXaxis_pin A3 // Arduino pin connected to the VRx Pin
#define thumbXaxis_pin A4 // Arduino pin connected to the VRx Pin

SoftwareSerial bluetooth (10,11);

#define switch_pin 2
#define num_pin 3
#define alp_pin 4
#define wor_pin 5
int prev = 0;
int nprev = 0;
int aprev = 0;
int wprev = 0;
boolean flag = false;
boolean nflag = false;
boolean aflag = false;
boolean wflag = false;

void setup() {
    Serial.begin(9600);
    bluetooth.begin(9600);
    pinMode(switch_pin,INPUT);
    pinMode(num_pin,INPUT);
    pinMode(alp_pin,INPUT);
    pinMode(wor_pin,INPUT);
    digitalWrite(switch_pin,HIGH);
    digitalWrite(num_pin,HIGH);
    digitalWrite(alp_pin,HIGH);
    digitalWrite(wor_pin,HIGH);
}


void loop() {
    int switch1 = digitalRead(switch_pin);
    Serial.println(switch1);
    if(switch1 == 0 && prev == 1){
        if(flag == true){
            flag = false;
            nflag = false;
            aflag = false;
        }
        else
        flag = true;
    }
    if(flag){    
        int numswitch = digitalRead(num_pin);
        int alpswitch = digitalRead(alp_pin);
        int worswitch = digitalRead(wor_pin);
        
        Serial.print("Num_switch ");
        Serial.println(numswitch);
        Serial.print("Alp_switch ");
        Serial.println(alpswitch);
        Serial.print("Wor_switch ");
        Serial.println(worswitch);
        
        if(numswitch == 0 && nprev == 1){
            if(nflag == true)
            nflag = false;
            else{
                nflag = true;
                aflag = false;
                wflag = false;
            }
        }
        if(alpswitch == 0 && aprev == 1){
            if(aflag == true)
            aflag = false;
           else{
                nflag = false;
                aflag = true;
                wflag = false;
            }
        }
        if(worswitch == 0 && wprev == 1){
           if(wflag == true)
           wflag = false;
           else{
               nflag = false;
               aflag = false;
               wflag = true;
          }
        }

        if(nflag){
            int data1 = analogRead(pinkyXaxis_pin);
            int data2 = analogRead(ringXaxis_pin);
            int data3 = analogRead(middleXaxis_pin);
            int data4 = analogRead(indexXaxis_pin);
            int data5 = analogRead(thumbXaxis_pin);
            Serial.println("Number_Mode");
            Serial.print("pinkyXaxis_pin: ");
            Serial.println(data1);
            Serial.print("ringXaxis_pin: ");
            Serial.println(data2);
            Serial.print("middleXaxis_pin: ");
            Serial.println(data3);
            Serial.print("indexXaxis_pin: ");
            Serial.println(data4);
            Serial.print("thumbXaxis_pin: ");
            Serial.println(data5);
            Serial.println(" : ");

            int state1 = det_state(data1);
            int state2 = det_state(data2);
            int state3 = det_state(data3);
            int state4 = det_state(data4);
            int state5 = det_state(data5);

            if((state1 == 0) && (state2 == 0) && (state3 == 0) && (state4 == 0) && (state5 == 0)){
                bluetooth.print("0");
            }
            else if((state1 == 0) && (state2 == 0) && (state3 == 0) && (state4 == 1) && (state5 == 0)){
                bluetooth.print("1");
            }
            else if((state1 == 0) && (state2 == 0) && (state3 == 1) && (state4 == 1) && (state5 == 0)){
                bluetooth.print("2");
            }
            else if((state1 == 0) && (state2 == 0) && (state3 == 1) && (state4 == 1) && (state5 == 1)){
                bluetooth.print("3");
            }
            else if((state1 == 1) && (state2 == 1) && (state3 == 1) && (state4 == 1) && (state5 == 0)){
                bluetooth.print("4");
            }
            else if((state1 == 1) && (state2 == 1) && (state3 == 1) && (state4 == 1) && (state5 == 1)){
                bluetooth.print("5");
            }
            else if((state1 == 0) && (state2 == 1) && (state3 == 1) && (state4 == 1) && (state5 == 0)){
                bluetooth.print("6");
            }
            else if((state1 == 1) && (state2 == 0) && (state3 == 1) && (state4 == 1) && (state5 == 0)){
                bluetooth.print("7");
            }
            else if((state1 == 1) && (state2 == 1) && (state3 == 0) && (state4 == 1) && (state5 == 0)){
                bluetooth.print("8");
            }
            else if((state1 == 1) && (state2 == 1) && (state3 == 1) && (state4 == 0) && (state5 == 0)){
                bluetooth.print("9");
            }
            else{
                bluetooth.print("Invalid position");
            }
        }

        else if(aflag){
            int data1 = analogRead(pinkyXaxis_pin);
            int data2 = analogRead(ringXaxis_pin);
            int data3 = analogRead(middleXaxis_pin);
            int data4 = analogRead(indexXaxis_pin);
            int data5 = analogRead(thumbXaxis_pin);
            
            Serial.println("Alphabet_Mode");
            Serial.print("pinkyXaxis_pin: ");
            Serial.println(data1);
            Serial.print("ringXaxis_pin: ");
            Serial.println(data2);
            Serial.print("middleXaxis_pin: ");
            Serial.println(data3);
            Serial.print("indexXaxis_pin: ");
            Serial.println(data4);
            Serial.print("thumbXaxis_pin: ");
            Serial.println(data5);
            Serial.println(" : ");

            int state1 = det_state(data1);
            int state2 = det_state(data2);
            int state3 = det_state(data3);
            int state4 = det_state(data4);
            int state5 = det_state(data5);

            if((state1 == 0) && (state2 == 0) && (state3 == 0) && (state4 == 0) && (state5 == 0)){
                bluetooth.print("A");
            }
            else if((state1 == 0) && (state2 == 0) && (state3 == 0) && (state4 == 0) && (state5 == 1)){
                bluetooth.print("B");
            }
            else if((state1 == 0) && (state2 == 0) && (state3 == 0) && (state4 == 1) && (state5 == 0)){
                bluetooth.print("C");
            }
            else if((state1 == 0) && (state2 == 0) && (state3 == 0) && (state4 == 1) && (state5 == 1)){
                bluetooth.print("D");
            }
            
            else if((state1 == 0) && (state2 == 0) && (state3 == 1) && (state4 == 0) && (state5 == 0)){
                bluetooth.print("E");
            }
            else if((state1 == 0) && (state2 == 0) && (state3 == 1) && (state4 == 0) && (state5 == 1)){
                bluetooth.print("F");
            }
            else if((state1 == 0) && (state2 == 0) && (state3 == 1) && (state4 == 1) && (state5 == 0)){
                bluetooth.print("G");
            }
            else if((state1 == 0) && (state2 == 0) && (state3 == 1) && (state4 == 1) && (state5 == 1)){
                bluetooth.print("H");
            }
            
            else if((state1 == 0) && (state2 == 1) && (state3 == 0) && (state4 == 0) && (state5 == 0)){
                bluetooth.print("I");
            }
            else if((state1 == 0) && (state2 == 1) && (state3 == 0) && (state4 == 0) && (state5 == 1)){
                bluetooth.print("J");
            }
            else if((state1 == 0) && (state2 == 1) && (state3 == 0) && (state4 == 1) && (state5 == 0)){
                bluetooth.print("K");
            }
            else if((state1 == 0) && (state2 == 1) && (state3 == 0) && (state4 == 1) && (state5 == 1)){
                bluetooth.print("L");
            }

            else if((state1 == 0) && (state2 == 1) && (state3 == 1) && (state4 == 0) && (state5 == 0)){
                bluetooth.print("M");
            }
            else if((state1 == 0) && (state2 == 1) && (state3 == 1) && (state4 == 0) && (state5 == 1)){
                bluetooth.print("N");
            }
            else if((state1 == 0) && (state2 == 1) && (state3 == 1) && (state4 == 1) && (state5 == 0)){
                bluetooth.print("O");
            }
            else if((state1 == 0) && (state2 == 1) && (state3 == 1) && (state4 == 1) && (state5 == 1)){
                bluetooth.print("P");
            }

            else if((state1 == 1) && (state2 == 0) && (state3 == 0) && (state4 == 0) && (state5 == 0)){
                bluetooth.print("Q");
            }
            else if((state1 == 1) && (state2 == 0) && (state3 == 0) && (state4 == 0) && (state5 == 1)){
                bluetooth.print("R");
            }
            else if((state1 == 1) && (state2 == 0) && (state3 == 0) && (state4 == 1) && (state5 == 0)){
                bluetooth.print("S");
            }
            else if((state1 == 1) && (state2 == 0) && (state3 == 0) && (state4 == 1) && (state5 == 1)){
                bluetooth.print("T");
            }

            else if((state1 == 1) && (state2 == 0) && (state3 == 1) && (state4 == 0) && (state5 == 0)){
                bluetooth.print("U");
            }
            else if((state1 == 1) && (state2 == 0) && (state3 == 1) && (state4 == 0) && (state5 == 1)){
                bluetooth.print("V");
            }
            else if((state1 == 1) && (state2 == 0) && (state3 == 1) && (state4 == 1) && (state5 == 0)){
                bluetooth.print("W");
            }
            else if((state1 == 1) && (state2 == 0) && (state3 == 1) && (state4 == 1) && (state5 == 1)){
                bluetooth.print("X");
            }

            else if((state1 == 1) && (state2 == 1) && (state3 == 1) && (state4 == 0) && (state5 == 0)){
                bluetooth.print("Y");
            }
            else if((state1 == 1) && (state2 == 1) && (state3 == 1) && (state4 == 0) && (state5 == 1)){
                bluetooth.print("Z");
            }
            
            else{
                bluetooth.print("Invalid position");
            }
        }
        else if(wflag){
            int data1 = analogRead(pinkyXaxis_pin);
            int data2 = analogRead(ringXaxis_pin);
            int data3 = analogRead(middleXaxis_pin);
            int data4 = analogRead(indexXaxis_pin);
            int data5 = analogRead(thumbXaxis_pin);
            
            Serial.println("Word_Mode");
            Serial.print("pinkyXaxis_pin: ");
            Serial.println(data1);
            Serial.print("ringXaxis_pin: ");
            Serial.println(data2);
            Serial.print("middleXaxis_pin: ");
            Serial.println(data3);
            Serial.print("indexXaxis_pin: ");
            Serial.println(data4);
            Serial.print("thumbXaxis_pin: ");
            Serial.println(data5);
            Serial.println(" : ");

            int state1 = det_state(data1);
            int state2 = det_state(data2);
            int state3 = det_state(data3);
            int state4 = det_state(data4);
            int state5 = det_state(data5);

            if(state1 == 0 && state2 == 0 && state3 == 0 && state4 == 0 && state5 == 0){
                bluetooth.print("bye");
            }
            else if(state1 == 0 && state2 == 0 && state3 == 0 && state4 == 0 && state5 == 1){
                bluetooth.print("I'm thirsty");
            }
            else if(state1 == 0 && state2 == 0 && state3 == 0 && state4 == 1 && state5 == 0){
                bluetooth.print("show me the way");
            }
            else if(state1 == 0 && state2 == 0 && state3 == 0 && state4 == 1 && state5 == 1){
                bluetooth.print("hello");
            }
            else if(state1 == 0 && state2 == 0 && state3 == 1 && state4 == 1 && state5 == 0){
                bluetooth.print("Good Morning");
            }
            else if(state1 == 0 && state2 == 1 && state3 == 1 && state4 == 1 && state5 == 0){
                bluetooth.print("May I use the washroom");
            }
            else if(state1 == 1 && state2 == 0 && state3 == 0 && state4 == 1 && state5 == 0){
                bluetooth.print("Good Evening");
            }
            else if(state1 == 1 && state2 == 1 && state3 == 1 && state4 == 0 && state5 == 0){
                bluetooth.print("I'm Hungry");
            }
            else if(state1 == 1 && state2 == 1 && state3 == 1 && state4 == 1 && state5 == 0){
                bluetooth.print("Excuse me");
            }
            else if(state1 == 1 && state2 == 1 && state3 == 1 && state4 == 1 && state5 == 1){
                bluetooth.print("Hi I use gloves to talk");
            }
            else{
                bluetooth.print("Invalid position");
            }
        }
        nprev = numswitch;
        aprev = alpswitch;
        wprev = worswitch;
  }
  prev = switch1;
  delay(2000);
}

int det_state(int data){
    int state = -1;
    if(data < 600)
    state = 1;
    else if(data > 800)
    state = 0;
    else 
    state = -1;
    return state;
}
