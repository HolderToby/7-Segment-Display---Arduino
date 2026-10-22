/* Development Notes - these are only here to help write the learning journal

logic bug when calculating second digit
i did digit2 = num - digit1 instead of digit1 *10
i then fixed it to digit 2= num - (10*digit1)
after that i moved to using modulo : digit 2 = num % 10

then i added floating point numbers (limited to 1 unit and 1 decimal place)
*/

// declare the pins that will be used for the display
                  //a,b,c,d,e,f,g,dp
int pins[2][8] = {{2, 3, 4, 5, 6, 7, 8, 9 },
                   {22, 23, 24, 25, 26, 27, 28, 29}};

int dpPins[] = {9, 29};

int layouts[10][7] = {
  // create a list of all the powerstates each pin should use for each number
  { 1, 1, 1, 1, 1, 1, 0},  // 0
  { 0, 1, 1, 0, 0, 0, 0},  // 1
  { 1, 1, 0, 1, 1, 0, 1},  // 2
  { 1, 1, 1, 1, 0, 0, 1},  // 3
  { 0, 1, 1, 0, 0, 1, 1},  // 4
  { 1, 0, 1, 1, 0, 1, 1},  // 5
  { 1, 0, 1, 1, 1, 1, 1},  // 6
  { 1, 1, 1, 0, 0, 0, 0},  // 7
  { 1, 1, 1, 1, 1, 1, 1},  // 8
  { 1, 1, 1, 1, 0, 1, 1}   // 9
};

int num = 0;  // start the number count at 0 - this is the number this display is showing

void setup() {
  // Set all the pins to output
  for (int i = 0; i < 8; i++) {
    pinMode(pins[0][i], OUTPUT); // set pins for first digit
    pinMode(pins[1][i], OUTPUT); // set pins for second digit
  }

  pinMode(dpPins[0], OUTPUT);
  pinMode(dpPins[1], OUTPUT);

  Serial.begin(9600); // begin the serial communication at 9600 bps
}

void writeDigit(int n, int digit) {

  // iterate through each of the pins
  for (int i = 0; i < 7; i++) {

    // write its state on / off according to the array
    digitalWrite(pins[digit][i], layouts[n][i]);
  }
}

void displayInt(int num){

  digitalWrite(dpPins[0], 0);  // sets the decimal place of the first digit to low
  digitalWrite(dpPins[1], 1);  // sets the decimal place of the second digit to high


  int tens = num / 10; // floor division - results in just the first digit (tens) of the number
  int units = num % 10; // Modulo division - gets the remainder of the number divised by 10 - the units

  writeDigit(tens, 0); // draws the first digit - tens
  writeDigit(units, 1); // draws the second digit - units
}

void displayDecimal(float num){

  digitalWrite(dpPins[0], 1);  // sets the decimal place of the first digit to high
  digitalWrite(dpPins[1], 0);  // sets the decimal place of the second digit to low

  int units = (int)num % 10; // modulo division
  int firstDecimal = (int)(num * 10) % 10; // modulo of the number * 10

  writeDigit(units, 0);  //draws the first digit - units
  writeDigit(firstDecimal, 1);  // draws the second digit - first decimal place

}



void loop() {

  displayInt(num);  // draws the current number as a whole number
  //displayDecimal((float)num / 10); // draws the current number as a decimal (divides by 10)

  Serial.println(num); // print the current number to serial monitor

  num++;                     // increase to the next number e.g. 3 -> 4
  if (num > 99) { num = 0; }  // reset to 0 once 99 is exceeded
  delay(500);               // wait a moment before moving on to the next number
}
