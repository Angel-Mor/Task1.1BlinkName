const int ledPin = LED_BUILTIN;  // Built in LED
const int buttonPin = 2;         // Button is connected to the digital pin 2

// Timings for Morse code
const int dotDuration = 200;     
const int dashDuration = dotDuration * 3; 
const int letterSpace = dotDuration * 3;  
const int wordSpace = dotDuration * 7;    

String name = ""; // Variable to store the name entered by the user

bool buttonState = LOW;         // Current state of the button
bool lastButtonState = LOW;     // Last state of the button 

void setup() {
  pinMode(ledPin, OUTPUT);        // Set the LED pin as an output
  pinMode(buttonPin, INPUT_PULLUP); // Set the button pin as an input
  Serial.begin(9600);             // Initialize serial communication at 9600 baud rate
  Serial.println("Enter your name in the Serial Monitor and press the button to blink it in Morse code:");
}

void loop() {
  buttonState = digitalRead(buttonPin); // Read the current state of the button
  
  // Check if a new name is entered via the serial monitor
  if (Serial.available() > 0) {  
    name = Serial.readStringUntil('\n'); 
    name.trim();  
    Serial.print("Name entered: ");  
    Serial.println(name);
  }

  // If the button was pressed and a name was entered
  if (buttonState == LOW && lastButtonState == HIGH && name.length() > 0) {
    Serial.print("Morse Code: ");
    String morseCode = convertNameToMorse(name); // Convert the name to Morse code
    Serial.println(morseCode);  // Print the Morse code representation
    
    // Loop through the Morse code and blink the LED accordingly
    for (int i = 0; i < morseCode.length(); i++) {
      if (morseCode[i] == '.') {
        blinkDot();  
      } else if (morseCode[i] == '-') {
        blinkDash(); 
      } else if (morseCode[i] == ' ') {
        delay(letterSpace); 
      }
      
      // Reset the loop if the button is pressed while blinking
      if (digitalRead(buttonPin) == LOW) {
        i = -1;  // Reset the index to -1 so it starts from the beginning
      }
    }
  }

  lastButtonState = buttonState;  
}

// Convert the entered name to Morse code
String convertNameToMorse(String name) {
  String morseCode = "";  
  for (int i = 0; i < name.length(); i++) {
    morseCode += convertToMorse(name[i]);  // Convert each character to Morse code
    morseCode += " ";  
  }
  return morseCode; 
}

// Convert individual characters to their corresponding Morse code
String convertToMorse(char c) {
  switch (toupper(c)) {  
    case 'A': return ".-";
    case 'B': return "-...";
    case 'C': return "-.-.";
    case 'D': return "-..";
    case 'E': return ".";
    case 'F': return "..-.";
    case 'G': return "--.";
    case 'H': return "....";
    case 'I': return "..";
    case 'J': return ".---";
    case 'K': return "-.-";
    case 'L': return ".-..";
    case 'M': return "--";
    case 'N': return "-.";
    case 'O': return "---";
    case 'P': return ".--.";
    case 'Q': return "--.-";
    case 'R': return ".-.";
    case 'S': return "...";
    case 'T': return "-";
    case 'U': return "..-";
    case 'V': return "...-";
    case 'W': return ".--";
    case 'X': return "-..-";
    case 'Y': return "-.--";
    case 'Z': return "--..";
    case ' ': return " ";  
    default: return "";    // If the character is not recognized, return an empty string
  }
}

// Function to blink the LED for a dot
void blinkDot() {
  digitalWrite(ledPin, HIGH);  // Turn on the LED
  delay(dotDuration);          
  digitalWrite(ledPin, LOW);   // Turn off the LED
  delay(dotDuration);         
}

// Function to blink the LED for a dash
void blinkDash() {
  digitalWrite(ledPin, HIGH);  // Turn the LED on
  delay(dashDuration);        
  digitalWrite(ledPin, LOW);   // Turn the LED off
  delay(dotDuration);        
}
