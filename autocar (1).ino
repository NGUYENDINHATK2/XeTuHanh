 

int trig1 = 13;
int echo1 = 12;
int trig2 = 10;
int echo2 = 9;
int trig3 = 8;
int echo3 = 7;

int in1 = 2;
int in2 = 3;
int in3 = 4;
int in4 = 5;
int ENA = 6;
int ENB = 11;
int LeftSpeed = 150;
int RightSpeed = 150;
long khoang_cach_trai = 0, khoang_cach_giua = 0, khoang_cach_phai = 0;
long pingTime, distance;
float speedSound = 0.0343;
int DIS = 20;
#define led1 A3
#define led2 A4
#define led3 A5
#define COI A0
long line_trai()
{
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  pingTime = pulseIn(echo1, HIGH);
  distance = (pingTime / 2) * speedSound;
  if (distance > 2000) distance = 0;
  return (distance);
}

long line_giua()
{
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  pingTime = pulseIn(echo2, HIGH);
  distance = (pingTime / 2) * speedSound;
  if (distance > 2000) distance = 0;
  return (distance);
}

long line_phai()
{
  digitalWrite(trig3, LOW);
  delayMicroseconds(2);
  digitalWrite(trig3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig3, LOW);
  pingTime = pulseIn(echo3, HIGH);
  distance = (pingTime / 2) * speedSound;
  if (distance > 2000) distance = 0;
  return (distance);
}

void setup()
{
  Serial.begin(9600);
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(echo3, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(COI, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(COI, LOW);
  moveStop();
  //tesst ban ddaauf
  //while(1)
  // {
  //  moveForward(LeftSpeed);delay(5000);
  //  moveBackward(LeftSpeed);delay(5000);
  //  turnLeft(LeftSpeed);delay(5000);
  //  turnRight(LeftSpeed);delay(5000);
  //  moveStop();delay(5000);
  //  }

  //  while (1)
  //  {
  //    // khoang_cach_trai = line_trai();
  //    // khoang_cach_trai = line_giua();
  //    // khoang_cach_trai = line_phai();
  //    Serial.println(khoang_cach_trai);
  //    delay(500);
  //  }

}

void loop()
{
  khoang_cach_trai = line_trai();
  delay(10);
  khoang_cach_giua = line_giua();
  delay(10);
  khoang_cach_phai = line_phai();
  delay(10);
  Serial.print("khoang_cach_trai = ");
  Serial.print(khoang_cach_trai);
  Serial.println("cm /");
  Serial.print("khoang_cach_giua = ");
  Serial.print(khoang_cach_giua);
  Serial.println("cm /");
  Serial.print("khoang_cach_phai = ");
  Serial.print(khoang_cach_phai);
  Serial.println("cm");
  if ((khoang_cach_trai > 40 || khoang_cach_giua > 40 || khoang_cach_phai > 40))
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(COI, LOW);
  }
  if ((khoang_cach_trai < 40 && khoang_cach_trai > 15) || (khoang_cach_giua < 40 && khoang_cach_giua > 15) || (khoang_cach_phai < 40 && khoang_cach_phai > 15))
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(COI, LOW);
  }
  if ((khoang_cach_trai < 15 || khoang_cach_giua < 15 || khoang_cach_phai < 15))
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(COI, HIGH);
  }
  //  Obstacle on left side
  if (khoang_cach_trai < DIS && khoang_cach_giua > DIS && khoang_cach_phai > DIS)
  {
    turnRight(LeftSpeed);
    delay(25);  //  turn lightly right
  }
  //  Obstacle on front
  else if (khoang_cach_trai > DIS && khoang_cach_giua < DIS && khoang_cach_phai > DIS)
  {
    if (khoang_cach_trai > khoang_cach_phai)
    {
      turnLeft(LeftSpeed);
      delay(400);  //  turn 90 degree left
    }
    if (khoang_cach_trai < khoang_cach_phai)
    {
      turnRight(LeftSpeed);
      delay(400);  //  turn 90 degree right
    }
  }
  //  Obstacle on right side
  else if (khoang_cach_trai > DIS && khoang_cach_giua > DIS && khoang_cach_phai < DIS)
  {
    turnLeft(LeftSpeed);
    delay(25);  //turn lightly left
  }
  //  Obstacle on front & left side
  else if (khoang_cach_trai < DIS && khoang_cach_giua < DIS && khoang_cach_phai > DIS)
  {
    turnRight(LeftSpeed);
    delay(400);  //  turnRight 90 degree
  }
  //  Obstacle on front & right side
  else if (khoang_cach_trai > DIS && khoang_cach_giua < DIS && khoang_cach_phai < DIS)
  {
    turnLeft(LeftSpeed);
    delay(400);  //  turnLeft 90 degree
  }
  //  Obstacle on left & right side
  else if (khoang_cach_trai < DIS && khoang_cach_giua > DIS && khoang_cach_phai < DIS)
  {
    if (khoang_cach_trai > khoang_cach_phai)
    {
      turnLeft(LeftSpeed);
      delay(50);  //  shift left
    }
    if (khoang_cach_trai < khoang_cach_phai)
    {
      turnRight(LeftSpeed);
      delay(50);  //  shift right
    }
  }
  //  Obstacle on all 3 side
  else if (khoang_cach_trai < DIS && khoang_cach_giua < DIS && khoang_cach_phai < DIS)
  {
    moveStop();
    delay(1000);
    moveBackward(LeftSpeed);
    delay(1000);
    turnLeft(LeftSpeed);
    delay(800);  //turn 180 degrees
  }
  else
  {
    moveForward(LeftSpeed);
  }
}

void moveForward(int Speed)
{
  Serial.println("Move Forward");
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveBackward(int Speed)
{
  Serial.println("Move Backward");
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnRight(int Speed)
{
  Serial.println("Turn Right");
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnLeft(int Speed)
{
  Serial.println("Turn Left");
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveStop()
{
  Serial.println("Move Stop");
  analogWrite(ENA, LOW);
  analogWrite(ENB, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
