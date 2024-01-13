// initialize our variables
int whitePort;
int redPort;
int yellowPort;
int greenPort;
int bluePort;
double timeDelay;
int counter;

void setup() {
  // put your setup code here, to run once:

  // set which port our positive wire is connected to
  whitePort = 0;
  redPort = 1;
  yellowPort = 2;
  greenPort = 3;
  bluePort = 4;

  // "pinMode" sets the port to what we want, in this case "OUTPUT"
  pinMode(whitePort, OUTPUT);
  pinMode(redPort, OUTPUT);
  pinMode(yellowPort, OUTPUT);
  pinMode(greenPort, OUTPUT);
  pinMode(bluePort, OUTPUT);

  // define time delay
  timeDelay = 500; // half a second

  // initialize the counter
  counter = 0;

}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(whitePort, HIGH);

  if (counter % 2 == 0) {
    digitalWrite(redPort, HIGH);
  }
  if (counter % 3 == 0) {
    digitalWrite(yellowPort, HIGH);
  }
  if (counter % 5 == 0) {
    digitalWrite(greenPort, HIGH);
  }
  if (counter % 7 == 0) {
    digitalWrite(bluePort, HIGH);
  }

  delay(timeDelay);


  digitalWrite(whitePort, LOW);
  digitalWrite(redPort, LOW);
  digitalWrite(yellowPort, LOW);
  digitalWrite(greenPort, LOW);
  digitalWrite(bluePort, LOW);

  delay(timeDelay);

  counter ++;
}
