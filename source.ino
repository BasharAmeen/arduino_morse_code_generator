#include <ArduinoJson.h>
#define USI unsigned short int
#define USIC USI const
 
USIC PIN = 13;
USIC SHORT = 700;
USIC LONG = 2000;
USIC BREAK = 100;
const char inputText[] = "bashar";
StaticJsonDocument<1047> doc;
USI runing = 1;

void setup() {

  pinMode(PIN, OUTPUT);
  Serial.begin(9600);
  while (!Serial) continue;
  
  const char json[] = "{\"0\":\"----\",\"1\":\".----\",\"2\":\"..---\",\"3\":\"...--\",\"4\":\"....-\",\"5\":\".....\",\"6\":\"-....\",\"7\":\"--...\",\"8\":\"---..\",\"9\":\"----.\",\"a\":\".-\",\"b\":\"-...\",\"c\":\"-.-.\",\"d\":\"-..\",\"e\":\".\",\"f\":\"..-.\",\"g\":\"--.\",\"h\":\"....\",\"i\":\"..\",\"j\":\".---\",\"k\":\"-.-\",\"l\":\".-..\",\"m\":\"--\",\"n\":\"-.\",\"o\":\"---\",\"p\":\".--.\",\"q\":\"--.-\",\"r\":\".-.\",\"s\":\"...\",\"t\":\"-\",\"u\":\"..-\",\"v\":\"...-\",\"w\":\".--\",\"x\":\"-..-\",\"y\":\"-.--\",\"z\":\"--..\",\".\":\".-.-.-\",\",\":\"--..--\",\"?\":\"..--..\",\"!\":\"-.-.--\",\"-\":\"-....-\",\"/\":\"-..-.\",\"@\":\".--.-.\",\"(\":\"-.--.\",\")\":\"-.--.-\"}";
  DeserializationError error = deserializeJson(doc, json);
  
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
}

void loop() {

  if (runing) {
    Serial.println("Start:");
    USIC inputLen = strlen(inputText);
    for (USI inputIndex = 0; inputIndex < inputLen; inputIndex++) {

      const char currentChar = inputText[inputIndex];
      const char* morse_code = doc[&currentChar];

      Serial.print("char is:");
      Serial.println(currentChar);

      USIC morseLen = strlen(morse_code);
      Serial.println("------------------------");
      Serial.println(morseLen);
      Serial.println("^^^^^^^^^^^^^^^^^^^^^^^^^");

      for (USI morseIndex = 0; morseIndex < morseLen; morseIndex++) {

        int morse_part = morse_code[morseIndex];

        digitalWrite(PIN, HIGH);
        if (morse_part == 45) {  // dashe case
          Serial.println("Dashe");
          delay(LONG);
        }

        else {  // dot case
          Serial.println("Dot");
          delay(SHORT);
        }

        digitalWrite(PIN, LOW);
        delay(BREAK);
      }
    }
    digitalWrite(PIN, LOW);
    runing = 0;
  }
}