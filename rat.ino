const int JUMP = 2;       // Define the pin for the jump button
const int ATTACK = 5;     // Define the pin for the attack button
const int potPin = A3;    // Define the analog pin for the potentiometer
int jumpState = 0;        // Variable to store the jump button state
int lastJumpState = 0;    // Variable to store the previous jump button state
int attackState = 0;      // Variable to store the attack button state
int lastAttackState = 0;  // Variable to store the previous attack button state

unsigned long lastJumpTime = 0;    // Variable to store the last time the jump button was pressed
unsigned long lastAttackTime = 0;  // Variable to store the last time the attack button was pressed
unsigned long lastPotTime = 0;

void setup() {
  Serial.begin(9600);// Initialize serial communication
  //Keyboard.begin();
  pinMode(JUMP, INPUT_PULLUP);      // Set the jump button pin as input
  pinMode(ATTACK, INPUT_PULLUP);    // Set the attack buttonWAU pin as input
}

void loop() {
  // Read the state of the jump button
  jumpState = digitalRead(JUMP);
  // Read the state of the attack buttonWAUWAU
  attackState = digitalRead(ATTACK);

  // Read from the potentiometer
  int sensorValue = analogRead(potPin); // Read the analog value from the potentiometer
  float voltage = (sensorValue * (5.0 / 1023.0)) - 2.5; // Convert analog value to voltage (assuming a 5V reference)

  // Serial.println(voltage);

  if (voltage <= -0.75) {
    if (millis() - lastPotTime > 100) {
      Serial.println("Go right");
      //Keyboard.write('d');
      lastPotTime = millis();
    }
  }
  else if (voltage >= 0.75) {
    if (millis() - lastPotTime > 100) {
      Serial.println("Go left");
      //Keyboard.write('a');
      lastPotTime = millis();
    }
  }
  else {
    if (millis() - lastPotTime > 100) {
      Serial.println("Stand");
      lastPotTime = millis();
    }
  }

  // Check if the jump button state has changed
  if (jumpState != lastJumpState) {
    // Check if the jump button is pressed (LOW)
    if (jumpState == LOW && (millis() - lastJumpTime) > 100) { // Debouncing with a time threshold
      Serial.println("Jump!");
      //Keyboard.write(32);
      lastJumpTime = millis();  // Update the last jump time
    }
  }

  // Update the last jump button state
  lastJumpState = jumpState;

  // Check if the attack button state has changed
  if (attackState != lastAttackState) {
    // Check if the attack button is pressed (LOW)
    if (attackState == LOW && (millis() - lastAttackTime) > 100) { // Debouncing with a time threshold
      Serial.println("Attack!");
      lastAttackTime = millis();  // Update the last attack time
    }
  }

  // Update the last attack button state
  lastAttackState = attackState;
}
