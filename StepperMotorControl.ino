// ESP-12F(WeMos D1 mini)
#define IN1 14 //GPIO 14 / D5
#define IN2 12 //GPIO 12 / D6
#define IN3 13 //GPIO 13 / D7
#define IN4 15 //GPIO 15 / D8


void initStepper() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

int stepsMatrix[8][4] = {
  {LOW, LOW, LOW, HIGH},
  {LOW, LOW, HIGH, HIGH},
  {LOW, LOW, HIGH, LOW},
  {LOW, HIGH, HIGH, LOW},
  {LOW, HIGH, LOW, LOW},
  {HIGH, HIGH, LOW, LOW},
  {HIGH, LOW, LOW, LOW},
  {HIGH, LOW, LOW, HIGH},
};

const int STEPS_PER_REVOLUTION = 4095;
int NEXT_STEP_POSITION = 0;

double rotateToPercent(double targetPercent){
  double rotationAngle = (targetPercent * MAX_ANGLE) - CURRENT_ANGLE;

  CURRENT_ANGLE = CURRENT_ANGLE + rotationAngle;

  rotate(-rotationAngle);
  writeCurrentAngleToFile();
  return rotationAngle;
}

void rotate(double angle){
  int total_steps = calculateSteps(angle);  
  while (total_steps > 0){
    total_steps--;
    performStep(stepsMatrix[NEXT_STEP_POSITION]);
    setNextStepperPositionValueDependingOn(angle);
    delay(1); // 3 if cpu is 80MHz
  }
  initStepper();
}
void setNextStepperPositionValueDependingOn(double angle){
  if (angle < 0){
    NEXT_STEP_POSITION = (NEXT_STEP_POSITION + 8 - 1) % 8;
  } else {
    NEXT_STEP_POSITION = (NEXT_STEP_POSITION + 1) % 8;
  } 
}


int calculateSteps(double angle){
  double factor = angle / (double) 360.0;
  int steps = factor * (double) STEPS_PER_REVOLUTION;
  if (steps < 0){
    steps = steps * -1;
  }
  return steps;
}

void performStep(int outArray[4]) {
  digitalWrite(IN1, outArray[0]);
  digitalWrite(IN2, outArray[1]);
  digitalWrite(IN3, outArray[2]);
  digitalWrite(IN4, outArray[3]);
}
