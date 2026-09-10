#define SW 33
#define CLK 26
#define DT 27

#define SEND_BUTTON 25

int letterIndex = 0;
int lastCLK;

// Store the word being created
String currentWord = "";

// Maximum number of characters
const int MAX_WORD_LENGTH = 20;


void setup() {

  Serial.begin(115200);

  // Rotary encoder pins
  pinMode(SW, INPUT_PULLUP);
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);

  // Send button
  pinMode(SEND_BUTTON, INPUT_PULLUP);

  // Get initial CLK state
  lastCLK = digitalRead(CLK);

  Serial.println();
  Serial.println("==============================");
  Serial.println(" Rotary Encoder Word Builder");
  Serial.println("==============================");

  Serial.println("Selected: A");
  Serial.println("Current word: ");
}


void loop() {

  // ==========================================
  // ROTARY ENCODER
  // ==========================================

  int currentCLK = digitalRead(CLK);

  if (currentCLK != lastCLK) {

    // Determine direction
    if (digitalRead(DT) != currentCLK) {
      letterIndex++;
    }
    else {
      letterIndex--;
    }

    // Limit A-Z
    if (letterIndex > 25) {
      letterIndex = 25;
    }

    if (letterIndex < 0) {
      letterIndex = 0;
    }

    // Convert index to character
    char selectedCharacter = 'A' + letterIndex;

    Serial.print("Selected character: ");
    Serial.print(selectedCharacter);

    Serial.print("    Index: ");
    Serial.println(letterIndex);
  }

  // Save CLK state
  lastCLK = currentCLK;


  // ==========================================
  // ENCODER PUSH BUTTON - GPIO 33
  // ==========================================

  if (digitalRead(SW) == LOW) {

    char selectedCharacter = 'A' + letterIndex;

    // Check word length
    if (currentWord.length() < MAX_WORD_LENGTH) {

      // Add selected character
      currentWord += selectedCharacter;

      Serial.print("Added character: ");
      Serial.println(selectedCharacter);

      Serial.print("Current word: ");
      Serial.println(currentWord);

    }
    else {

      Serial.println("Maximum word length reached!");

    }

    // Wait until button is released
    while (digitalRead(SW) == LOW) {
      delay(10);
    }

    delay(50);
  }


  // ==========================================
  // SEND BUTTON - GPIO 25
  // ==========================================

  if (digitalRead(SEND_BUTTON) == LOW) {

    if (currentWord.length() > 0) {

      Serial.println();
      Serial.println("==============================");
      Serial.print("SENDING WORD: ");
      Serial.println(currentWord);
      Serial.println("==============================");
      Serial.println();

      // Clear word after sending
      currentWord = "";

      Serial.println("Word cleared.");
      Serial.println("Ready for next word.");

    }
    else {

      Serial.println("No word to send!");

    }

    // Wait until send button is released
    while (digitalRead(SEND_BUTTON) == LOW) {
      delay(10);
    }

    delay(50);
  }
}
