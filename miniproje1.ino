String readString;
float Speed = 0; int speed_count = 0; float Acceleration = 0;
int Acceleration_count = 0; float Position = 0; int Position_count = 0;
int Write = 0; int button = 0; float CurDelay = 200; float t11 = 0; float Tadd; double Tf;  long NeedStep = 0 ;
float Movemicros; float Tempmicros; int DummyCounter = -1; float DummyTime = 0; long NumberofStep1 = 0; long NumberofStep2 = 0;
float t1, t2, t3; int Counter1 = 0; int Counter2 = 0; int Counter3 = 0; int Counter4 = 0;  int step1; int step2; int step3;
float x1, x2, x3;
int stepPin = 3; int dirPin = 4;
float Add = 1;


void setup() {


  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);






  /*Serial.print("Add:  "); Serial.println (Add);
    //Tadd = (200 - (200/Speed))/NumberofStep;
    Serial.print("step1:  "); Serial.println (step1);
    Serial.print("step2:  "); Serial.println (step2);
    Serial.print("step3:  "); Serial.println (step3);
    //Tadd = (200/t1)/1000;

    Serial.print("Speed:  "); Serial.println (Speed);
    Serial.print("Position:  "); Serial.println (Position);
    Serial.print("Acceleration:  "); Serial.println (Acceleration);
    Serial.print("t1:  "); Serial.println (t1);
    Serial.print("t2:  "); Serial.println (t2);
    Serial.print("t3:  "); Serial.println (t3);
    Serial.print("x1:  "); Serial.println (x1);
    Serial.print("x2:  "); Serial.println (x2);
    Serial.print("x3:  "); Serial.println (x3);

    Serial.print("NEEDSTEP:  "); Serial.println (NeedStep);*/

  // Movemicros = micros();



}



void loop() {





  while (Speed == 0 || Acceleration == 0 ||  Position == 0 )
  {
    if (speed_count == 0)       //if başlar
    {
      if (Write == 0)
      {
        Serial.println ("Lutfen hiz degerini giriniz. 100-500 araliginda olmasi tavsiye edilir.");
        Write += 1;
      }
      while (Serial.available())
      {
        char c = Serial.read();
        readString += c;
        delay(2);
      }
      if (readString.length() > 0)
      {
        Speed = readString.toInt();
        Serial.print("Girilen hiz degeri: "); Serial.println(Speed);
        readString = "";
        Write = 0;
        speed_count += 1;
      }

    }

    else if (Acceleration_count == 0)   //1. else if başlar
    {
      if (Write == 0)
      {
        Serial.print ("Lutfen ivme degerini giriniz. "); Serial.print(Speed / 2); Serial.print (" - "); Serial.print(Speed * 5); Serial.println(" Araliginda olmasi tavsiye edilir.");
        Write += 1;
      }
      while (Serial.available())
      {
        char c = Serial.read();
        readString += c;
        delay(2);
      }
      if (readString.length() > 0)
      {
        Acceleration = readString.toInt();
        Serial.print("Girilen ivme degeri giriniz: "); Serial.println(Acceleration);
        readString = "";
        Write = 0;
        Acceleration_count += 1;
      }

    }
    else if (Position_count == 0)   //2. else if başlar
    {
      if (Write == 0)
      {
        Serial.print("Lutfen konum degerini giriniz. En az "); Serial.print((Speed * Speed) / Acceleration); Serial.println(" giriniz. Bu sayede motordaki gerekli hareketler rahatlıkla görülecektir. ");
        Serial.println("The maximum position length available 210 mm");
        Write += 1;
      }
      while (Serial.available())
      {
        char c = Serial.read();
        readString += c;
        delay(2);
      }
      if (readString.length() > 0)
      {
        Position = readString.toInt();
        Serial.print("Girilen konum degeri giriniz: "); Serial.println(Position);
        readString = "";
        Write = 0;
        Position_count += 1;
      }

    }                 //if biter

  }

  t1 = (Speed / Acceleration); t3 = t1;
  t2 = (Position - Speed * t1) / Speed;
  //Serial.print("t1:  "); Serial.println (t1); Serial.print("acc:  "); Serial.println (Acceleration);
  x1 = (0.5) * (Acceleration) * t1 * t1;
  x3 = x1;
  x2 = Position - 2 * x1;
  NeedStep = (x1 / 0.0125) * 2 + x2 / 0.0125;
  step1 = x1 / 0.0125;
  step2 = x2 / 0.0125;
  step3 = x3 / 0.0125;
  Add = (200 - 12500 / Speed) / step1;

  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);

  digitalWrite(dirPin, LOW);
  delay(100);

  for (int x = 0; x < 40000 && digitalRead(7) <= 0  ; x++) {

    digitalWrite(3 , HIGH);
    delayMicroseconds(50);
    digitalWrite(3 , LOW);
    delayMicroseconds(50);

  }






  digitalWrite(dirPin, HIGH);
  delay(2000);


  for (int x = 0; x <= step1 ; x++) {

    t11 = 200 - Add * x;
    digitalWrite(3 , HIGH);
    delayMicroseconds(t11);
    digitalWrite(3 , LOW);
    delayMicroseconds(t11);
    NumberofStep2 += 1;

  }

  for (int x = 0; x <= step2 ; x++) {
    digitalWrite(3 , HIGH);
    delayMicroseconds(t11);
    digitalWrite(3 , LOW);
    delayMicroseconds(t11);
    NumberofStep2 += 1;

  }

  for (int x = 0; x < step3; x++) {

    t11 += Add ;
    digitalWrite(3 , HIGH);
    delayMicroseconds(t11);
    digitalWrite(3 , LOW);
    delayMicroseconds(t11);
    NumberofStep2 += 1;
  }

  //Serial.print("NumberofStep2:  "); Serial.println (NumberofStep2);
  delay(2000);

  digitalWrite(dirPin, LOW);
  delay(100);
  Acceleration = 0;
  Speed = 0;
  Position = 0;
  Acceleration_count = 0;
  speed_count = 0;
  Position_count = 0;

  for (int x = 0; x < 40000 && digitalRead(7) <= 0  ; x++) {

    digitalWrite(3 , HIGH);
    delayMicroseconds(50);
    digitalWrite(3 , LOW);
    delayMicroseconds(50);

  }

}   
