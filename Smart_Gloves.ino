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

        int data1 = analogRead(pinkyXaxis_pin);
        int data2 = analogRead(ringXaxis_pin);
        int data3 = analogRead(middleXaxis_pin);
        int data4 = analogRead(indexXaxis_pin);
        int data5 = analogRead(thumbXaxis_pin);

        int state1 = detState(data1);
        int state2 = detState(data2);
        int state3 = detState(data3);
        int state4 = detState(data4);
        int state5 = detState(data5);

        int stateArray[6] = {state1, state2, state3, state4, state5};

        String finalState = convertState(stateArray, 5);

        if(nflag){
            finalState = '1' + finalState;
            Serial.println("Number_Mode");
            Serial.println(finalState);
            bluetooth.print(finalState);
        }
        
        else if(aflag){
            finalState = '2' + finalState;
            Serial.println("Alphabet_Mode");
            Serial.println(finalState);
            bluetooth.print(finalState);
        }
        else if(wflag){
            finalState = '3' + finalState;
            Serial.println("Word_Mode");
            Serial.println(finalState);
            bluetooth.print(finalState);
            
        }
        nprev = numswitch;
        aprev = alpswitch;
        wprev = worswitch;
  }
  prev = switch1;
  delay(3000);
}

int detState (int data) {
    int state = 1;
    if(data > 650) {
        state = 0;
    } else {
        state = 1;
    }
    return state;
}

String convertState (int stateArray[], int size) {
    String result;

    for (int i=0;i<size;i++) {
      result += (stateArray[i] == 0) ? '0' : '1';
    }
    
    return result;
}

