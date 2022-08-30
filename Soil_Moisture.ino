const int DEBUG_MODE =  1 ;
const int WATERPUMP = 10; //motor pump connected to pin 10
const int sensor = A1; //sensor digital pin vonnected to pin 9
const int emptyTankLed = 9;

int val; //This variable stores the value received from Soil moisture sensor.

int soilMoistureThreshold;
int temp_sens_val;
int stopMotor = 0 ;
int delay_Start = millis();
const int stopMotorThresholdValue = 2100;
const long EMPTY_TANK_TIMEOUT = 10000 ;// in milli seconds
// Seven Segment

int Value = 0;
const byte PIN[7] = {2, 3, 4, 5, 6, 7, 8};
long beginningPumpTime = 0; 

// 7-segment Drawings for numbers 0 to 9
int bits[10][7] = {{ 1, 1, 1, 1, 1, 1, 0 },  // 0
  { 0, 1, 1, 0, 0, 0, 0 },  // 1
  { 1, 1, 0, 1, 1, 0, 1 },  // 2
  { 1, 1, 1, 1, 0, 0, 1 },  // 3
  { 0, 1, 1, 0, 0, 1, 1 },  // 4
  { 1, 0, 1, 1, 0, 1, 1 },  // 5
  { 1, 0, 1, 1, 1, 1, 1 },  // 6
  { 1, 1, 1, 0, 0, 0, 0 },  // 7
  { 1, 1, 1, 1, 1, 1, 1 },  // 8
  { 1, 1, 1, 1, 0, 1, 1 }  // 9
};

int isEmpty = 0;
void setup() {
  if(DEBUG_MODE == 1){
    Serial.begin(9600);
  }
  for (int i = 0; i < 7; i++) {
    pinMode (PIN[i], OUTPUT);
  }
  pinMode(emptyTankLed, OUTPUT);
  pinMode(WATERPUMP, OUTPUT); //Set pin 10 as OUTPUT pin
  pinMode(sensor, INPUT); //Set pin A1 as input pin, to receive data from Soil moisture sensor.
}

void loop()
{
  //Read Potentiometer Value and update 7-seg accordingly
  updateSevenSegmentAndSoilMoistureThreshold();

  // Read anolog pin and control the pump accordingly
  readSensorValue();
 
  // checks for empty tank or non-responsive sensor
  isEmpty = checkForEmptyTank();

  
}

void readSensorValue(){
  val = analogRead(sensor);
    if(DEBUG_MODE == 1){
      Serial.print("Sensor Value  = ");
      Serial.println(val);
    }
    if ( stopMotor == 1){
          digitalWrite(WATERPUMP, LOW);
      }
      
  if (val > soilMoistureThreshold) {
    if(    beginningPumpTime = 0){
            beginningPumpTime = millis();

      }
    if(stopMotor == 0){
       digitalWrite(WATERPUMP, HIGH);
    }
  }
  else {
    digitalWrite(WATERPUMP, LOW);
    beginningPumpTime = 0;

  }
  }

int checkForEmptyTank(){ 
     delay(50); 
     temp_sens_val = val - analogRead(sensor);

     if(DEBUG_MODE == 1){
        Serial.println("running time = ");
        Serial.println((millis() - beginningPumpTime));
      }
  if ( (  abs(temp_sens_val)  < 40) && (digitalRead(WATERPUMP) == HIGH) && (millis() - beginningPumpTime) > EMPTY_TANK_TIMEOUT ) {
      soilMoistureThreshold = stopMotorThresholdValue;
      stopMotor = 1;
      digitalWrite(emptyTankLed, HIGH);
      return 1;
    }
    else {
      if(stopMotor == 0){
        digitalWrite(emptyTankLed, LOW);
      }
      return 0;
    }
  }

  void updateSevenSegmentAndSoilMoistureThreshold(){
   Value = analogRead(A0);
  // Serial.println(Value);
  for (int j = 0; j < 7; j++) {
    if (Value < 80) {
      digitalWrite(j + 2, bits[0][j]);
      
      soilMoistureThreshold = stopMotorThresholdValue;
    }
    else if (Value > 80 && Value < 177) {
      digitalWrite(j + 2, bits[1][j]);
      soilMoistureThreshold = 912;
    }
    else if (Value > 177 && Value < 265) {
      digitalWrite(j + 2, bits[2][j]);
      soilMoistureThreshold = 824;
    }
    else if (Value > 265 && Value < 353) {
      digitalWrite(j + 2, bits[3][j]);
      soilMoistureThreshold = 736;
    }
    else if (Value > 353 && Value < 441) {
      digitalWrite(j + 2, bits[4][j]);
      soilMoistureThreshold = 648;

    }
    else if (Value > 441 && Value < 529) {
      digitalWrite(j + 2, bits[5][j]);
      soilMoistureThreshold = 560;
    }
    else if (Value > 529 && Value < 617) {
      digitalWrite(j + 2, bits[6][j]);
      soilMoistureThreshold = 472;
    }
    else if (Value > 617 && Value < 705) {
      digitalWrite(j + 2, bits[7][j]);
      soilMoistureThreshold = 384;

    }
    else if (Value > 705 && Value < 793) {
      digitalWrite(j + 2, bits[8][j]);
      soilMoistureThreshold = 296;
    }
    else {
      digitalWrite(j + 2, bits[9][j]);
      soilMoistureThreshold = 240;
    }
  }
  }
