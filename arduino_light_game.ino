//Sequence data.
int lightsArr[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int playerArr[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

//lightpin variables.
int redLedPin = 2;
int greenLedPin = 4;
int blueLedPin = 7;
int yellowLedPin = 8;

//Switchpin variables
int redSwitchPin = 9;
int greenSwitchPin = 10;
int blueSwitchPin = 11;
int yellowSwitchPin = 12;

//switch state variables.
int redSwitchState;
int greenSwitchState;
int blueSwitchState;
int yellowSwitchState;

//Led Id for comparing in the Sequence data.
int redLedNumber = 1;
int greenLedNumber = 2;
int blueLedNumber = 3;
int yellowLedNumber = 4;

//Number of times sequence has repeated.
int playerCount = 0;
int lightCount = 0;

//Speed limit variables
int delayTime = 500;
int lightDelay = 500;

//Led state
byte redLedOn = false;
byte greenLedOn = false;
byte blueLedOn = false;
byte yellowLedOn = false;

//Game states
byte lightsShown = false;
byte buttonHit = false;
byte gameOver = false;

//Saves button press and ledNumber to playerArr.
//Turns off and on light to show player they pressed that lights button.
//Returns led's state.
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

//Shows lights in sequence to press based on lightsArr (arr[]).
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
//pin setup
void setup() {
 
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
  //Checks the switch state.
  //States either return 1 or 0.
  //If 0 switch was pressed.
  redSwitchState = digitalRead(redSwitchPin);
  greenSwitchState = digitalRead(greenSwitchPin);
  blueSwitchState = digitalRead(blueSwitchPin);
  yellowSwitchState = digitalRead(yellowSwitchPin);

  
  if(lightsShown) {
    //After lights are shown, check for player input.
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
        
    //When player count equals light count, compare playerArr to lightArr.
    //If playerArr does not match lightArr gameOver = true.
    //If playerArr matches lightArr, playerArr gets reset to -1 on all values.
    //playerCount resets to 0.
    //lightsArr adds one more to the sequence and reshows light sequence.
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
    //If it's less than 15 than add 1 more to the sequence.
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
