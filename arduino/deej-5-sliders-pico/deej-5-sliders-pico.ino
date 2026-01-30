// Using example code from the SparkFun Multiplexer Hookup Guide
// https://learn.sparkfun.com/tutorials/multiplexer-breakout-hookup-guide
const int selectPins[3] = { 0, 1, 2 };
const int inputPin = A0;

const int NUM_SLIDERS = 5;
int analogSliderValues[NUM_SLIDERS];

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(selectPins[i], OUTPUT);
    digitalWrite(selectPins[i], HIGH);
  }
  pinMode(inputPin, INPUT);
  Serial.begin(9600);
}

void selectMuxPin(byte pin) {
  for (int i = 0; i < 3; i++) {
    if (pin & (1 << i))
      digitalWrite(selectPins[i], HIGH);
    else
      digitalWrite(selectPins[i], LOW);
  }
}

void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    selectMuxPin(i);
    analogSliderValues[i] = analogRead(inputPin);
  }
}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogSliderValues[i]);

    if (i < NUM_SLIDERS - 1) {
      builtString += String("|");
    }
  }

  Serial.println(builtString);
}

void printSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}

void loop() {
  updateSliderValues();
  sendSliderValues();  // Actually send data (all the time)
  // printSliderValues(); // For debug
  delay(10);
}
