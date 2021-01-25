int lightsArr[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int playerArr[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

int redLedPin = 2;
int greenLedPin = 4;
int blueLedPin = 7;
int yellowLedPin = 8;

int redSwitchPin = 9;
int greenSwitchPin = 10;
int blueSwitchPin = 11;
int yellowSwitchPin = 12;

int redSwitchState;
int greenSwitchState;
int blueSwitchState;
int yellowSwitchState;

int redLedNumber = 1;
int greenLedNumber = 2;
int blueLedNumber = 3;
int yellowLedNumber = 4;

int playerCount = 0;
int lightCount = 0;

int delayTime = 500;
int lightDelay = 500;

byte redLedOn = false;
byte greenLedOn = false;
byte blueLedOn = false;
byte yellowLedOn = false;

byte lightsShown = false;
byte buttonHit = false;
byte gameOver = false;
int buttonPressed(byte ledOn, int ledPin, int switchState, int ledNumber) {
  
  if(switchState == 0 && !ledOn) {
     
     ledOn= true;
     digitalWrite(ledPin,HIGH);
     playerArr[playerCount] = ledNumber;
     playerCount++;
     
  } else if(switchState == 1 && ledOn) {
     digitalWrite(ledPin,LOW);
     ledOn = false;
  }
  
  
  return ledOn;
}

void showLights(int arr[]) {
  int lightNumber;
  buttonHit = true;
  for(int k = 0; k < lightCount; k++) {
    
    if(arr[k] == redLedNumber) {
      lightNumber = redLedPin;
    } else if(arr[k] == greenLedNumber) {
      lightNumber = greenLedPin;
    } else if(arr[k] == blueLedNumber) {
      lightNumber = blueLedPin;
    } else if(arr[k] == yellowLedNumber) {
      lightNumber = yellowLedPin;
    }
   
      digitalWrite(lightNumber,HIGH);
      delay(lightDelay);
      digitalWrite(lightNumber,LOW);
      delay(lightDelay);
  }
}
void setup() {
  // put your setup code here, to run once:
  pinMode(redLedPin,OUTPUT);
  pinMode(greenLedPin,OUTPUT);
  pinMode(blueLedPin,OUTPUT);
  pinMode(yellowLedPin,OUTPUT);
  
  pinMode(redSwitchPin,INPUT);
  pinMode(greenSwitchPin,INPUT);
  pinMode(blueSwitchPin,INPUT);
  pinMode(yellowSwitchPin,INPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  redSwitchState = digitalRead(redSwitchPin);
  greenSwitchState = digitalRead(greenSwitchPin);
  blueSwitchState = digitalRead(blueSwitchPin);
  yellowSwitchState = digitalRead(yellowSwitchPin);

  
  if(lightsShown) {
    
    if(!buttonHit) {
      if(redSwitchState == 0) {
         redLedOn = buttonPressed(redLedOn,redLedPin,redSwitchState,redLedNumber);
      } else if(greenSwitchState == 0) {
         greenLedOn = buttonPressed(greenLedOn,greenLedPin,greenSwitchState,greenLedNumber);
      } else if(blueSwitchState == 0) {
         blueLedOn = buttonPressed(blueLedOn,blueLedPin,blueSwitchState,blueLedNumber);
      } else if(yellowSwitchState == 0) {
         yellowLedOn = buttonPressed(yellowLedOn,yellowLedPin,yellowSwitchState,yellowLedNumber);
      }
    } 
      redLedOn = buttonPressed(redLedOn,redLedPin,redSwitchState,redLedNumber);
      greenLedOn = buttonPressed(greenLedOn,greenLedPin,greenSwitchState,greenLedNumber);
      blueLedOn = buttonPressed(blueLedOn,blueLedPin,blueSwitchState,blueLedNumber);
      yellowLedOn = buttonPressed(yellowLedOn,yellowLedPin,yellowSwitchState,yellowLedNumber);
        
    
    if(playerCount == lightCount) {
      delay(delayTime/2);
      digitalWrite(redLedPin,LOW);
      digitalWrite(greenLedPin,LOW);
      digitalWrite(blueLedPin,LOW);
      digitalWrite(yellowLedPin,LOW);
      delay(delayTime/2);
      
      for(int j = 0; j < lightCount; j++) {
        if(playerArr[j] != lightsArr[j]) {
          for(int p = 0; p < 3; p++) {
            digitalWrite(redLedPin,HIGH);
            digitalWrite(greenLedPin,HIGH);
            digitalWrite(blueLedPin,HIGH);
            digitalWrite(yellowLedPin,HIGH);
            
            delay(lightDelay);

            digitalWrite(redLedPin,LOW);
            digitalWrite(greenLedPin,LOW);
            digitalWrite(blueLedPin,LOW);
            digitalWrite(yellowLedPin,LOW);

            delay(lightDelay);
            
          }
          lightCount = 0;
          for(int b = 0; b < 15; b++) {
            lightsArr[b] = -1;
          }
          gameOver = true;
        }
      }
      
      playerCount = 0;
      if(!gameOver) {
        lightCount++;
      } else {
        lightCount = 0;
        gameOver = false;
      }
      
      lightsShown = false;
      
      for(int b = 0; b < 15; b++) {
        playerArr[b] = -1;
      }
    }
  } else {
    
    for(int i = lightCount; i < 15; i++) {
      if(lightsArr[i] == -1) {
        lightsArr[i] = round(random(4)) + 1;
        break;
      }
    }
    showLights(lightsArr);
    lightsShown = true;
  
  }
}
