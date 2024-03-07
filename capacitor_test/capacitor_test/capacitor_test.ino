
unsigned long time;

int AI0 = 0;
int AI1 = 1;

int ADC0 = 0;
int ADC1 = 0;

float delta_v_min = 0.0049;

float voltage = 0.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  ADC0 = analogRead(AI0);
  ADC1 = analogRead(AI1);

  voltage = (ADC1 - ADC0) * delta_v_min;

  time = millis();
  Serial.print(time/1000.0, 6);
  Serial.print(",");
  Serial.println(voltage, 6);
}
