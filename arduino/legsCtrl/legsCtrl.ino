String inputString = "";
bool stringComplete = false;
int motor_left[] = {2, 3};
int motor_right[] = {7, 8};

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 255 bytes for the inputString:
  inputString.reserve(255);
   // Setup motors
  int i;
  for(i = 0; i < 2; i++){
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    if (inputString == "forward") {
      drive_forward();
      Serial.println("Moving forward");
    }
    else if (inputString == "backward") {
      drive_backward();
      Serial.println("Moving backward");
    }
    else if (inputString == "left") {
      turn_left();
      Serial.println("Turning left");
    }
    else if (inputString == "right") {
      turn_right();
      Serial.println("Turning right");
    }
    else if (inputString == "halt") {
      motor_stop();
      Serial.println("Stopping..");
    }
    else {
      Serial.println(inputString);
      Serial.println("Command fail");
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      // if the incoming character is a newline, set a flag so the main loop can
      // do something about it:
      stringComplete = true;
    }
    else if (inChar == '\r') {
      // do nothing  
    }
    else {
      // add it to the inputString:
      inputString += inChar;
    }
  }
}

void motor_stop(){
  digitalWrite(motor_left[0], LOW); 
  digitalWrite(motor_left[1], LOW); 
  
  digitalWrite(motor_right[0], LOW); 
  digitalWrite(motor_right[1], LOW);
  delay(25);
}

void drive_forward(){
  digitalWrite(motor_left[0], HIGH); 
  digitalWrite(motor_left[1], LOW); 
  
  digitalWrite(motor_right[0], HIGH); 
  digitalWrite(motor_right[1], LOW); 
}

void drive_backward(){
  digitalWrite(motor_left[0], LOW); 
  digitalWrite(motor_left[1], HIGH); 
  
  digitalWrite(motor_right[0], LOW); 
  digitalWrite(motor_right[1], HIGH); 
}

void turn_left(){
  digitalWrite(motor_left[0], LOW); 
  digitalWrite(motor_left[1], HIGH); 
  
  digitalWrite(motor_right[0], HIGH); 
  digitalWrite(motor_right[1], LOW);
}

void turn_right(){
  digitalWrite(motor_left[0], HIGH); 
  digitalWrite(motor_left[1], LOW); 
  
  digitalWrite(motor_right[0], LOW); 
  digitalWrite(motor_right[1], HIGH); 
}
