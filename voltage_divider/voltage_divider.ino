// Calculates total voltage using a voltage divider
// This is a work-around to register higher than 5 v.

int analogInput = 0;

// vmin is the voltage per step for our arduino
float vMin = .0049;

// variable for our raw adc value
// and then the voltage we will convert it into
int ADCValue = 0;
float voltage = 0.0;
float totalVoltage = 0.0;

// define our resistences
float R1 = 220;
float R2 = 220;

void setup() {
  // put your setup code here, to run once:

  // begin our serial connection with bandwidth of 9600
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  // set our value by reading our analog input
  ADCValue = analogRead(analogInput);

  // print adc value
  //Serial.print(" A2D ");
  //Serial.print(ADCValue);

  // calculate voltage
  totalVoltage = ADCValue * vMin * (R1+R2)/R1;
  voltage = ADCValue * vMin;

  //Serial.print(" voltage: ");
  Serial.print(" voltage read by arduino ");
  Serial.print(voltage,4); // second arg is for sig figs
  Serial.print(" total voltage ");
  Serial.println(totalVoltage,4); // second arg is for sig figs
}
