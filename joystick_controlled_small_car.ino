int up = 2;
int left = 3;
int right = 4;
int down = 5;

#define enA 10 //PWM for motor A (Right) 
#define in1 6 
#define in2 7
#define enB 11 //PWM for motor B (Left)
#define in3 8
#define in4 9

void RForward(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
}
void RBackward(){
   digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
}
void LForward(){
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}
void LBackward(){
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}

void R100(){      //Right Motor at speed 100%
  analogWrite(enA, 100);
}
void R50(){      //Right Motor at speed 50%
  analogWrite(enA, 30);
}
void L100(){      //Right Motor at speed 100%
  analogWrite(enB, 100);
}
void L50(){      //Right Motor at speed 50%
  analogWrite(enB, 30);
}
void L0(){      //Right Motor at speed 0%
  analogWrite(enB, 0);
}
void R0(){      //Right Motor at speed 0%
  analogWrite(enA, 0);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(up,INPUT);
  pinMode(down,INPUT); 
  pinMode(right,INPUT);
  pinMode(left,INPUT);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:

  int upstate = digitalRead(up);
  int downstate = digitalRead(down);
  int rightstate = digitalRead(right);
  int leftstate = digitalRead(left);

  Serial.print("up: ");
  Serial.println(upstate);
  Serial.print("down: ");
  Serial.println(downstate);
  Serial.print("right: ");
  Serial.println(rightstate);
  Serial.print("left: ");
  Serial.println(leftstate);

//  delay(50);

    if(downstate == 0 && rightstate == 0){    //Back and right
    RBackward();
    LBackward();
    R50();
    L100();
  }
  else if(upstate == 0 && rightstate == 0){    //Forwards and Right
    RForward();
    LForward();
    R100();
    L50();
  }
  else if(upstate == 0 && leftstate == 0){    //Forwards and Left
    RForward();
    LForward();
    R50();
    L100();
  }
  else if(downstate == 0 && leftstate == 0){    //Back and left
    RBackward();
    LBackward();
    R100();
    L50();
  }
  else if(upstate == 0 && rightstate == 0){    //Forwards and Right
    RForward();
    LForward();
    R100();
    L50();
  }
  else if(upstate == 0 && leftstate == 0){    //Forwards and Left
    RForward();
    LForward();
    R50();
    L100();
  }
  else if(downstate == 0 && leftstate == 0){    //Back and left
    RBackward();
    LBackward();
    R100();
    L50();
  }
  else if(upstate == 0 && leftstate == 1 && rightstate == 1){    //forwards  (the switches are default to HIGH, so if the pin reads LOW then that means the switch is activated. 
    RForward();
    LForward();
    R100();
    L100();
  }
  else if(downstate == 0 && leftstate == 1 && rightstate == 1){    //backwards
    RBackward();
    LBackward();
    R100();
    L100();
  }
  else if(rightstate == 0 && upstate == 1 && downstate == 1){    //Right
    RBackward();
    LForward();
    R100();
    L100();
  }
  else if(leftstate == 0 && upstate == 1 && downstate == 1){    //left
    RForward();
    LBackward();
    R100();
    L100();
  }

  else{
    R0();
    L0();
  }
}
