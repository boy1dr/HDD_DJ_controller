
/*///////////////////////////////////
Chris Mitchell 14/11/2013

Motor Inputs D2, D3, D4

*////////////////////////////////////

int j1 = 2;
int j2 = 3;
int j3 = 4;

int p=0;
int b=0;
int y=0;

int old_p = 0;
int old_b = 0;
int old_y = 0;

int state_p = 0;
int state_b = 0;
int state_y = 0;

int countr = 0;
int myInts[6];


void setup(){
  Serial.begin(9600);
  delay(1000);
}

void loop(){
  p = digitalRead(j1);
  b = digitalRead(j2);
  y = digitalRead(j3);
  
  if( (p == 1)&&( old_p == 1)&&(state_p==0) ){
    //coil #1 rising edge
    state_p = 1;
    set_latest(1);
    if( get_last()==3 ) { goLeft(); }
    if( get_last()==2 ) { goRight(); }
  }
  if( (p == 0)&&( old_p == 0)&&(state_p==1) ){
    //coil #1 FALLING edge
    state_p = 0;
  }
  
  
  
  if( (b == 1)&&( old_b == 1)&&(state_b==0) ){
    //coil #2 rising edge
    state_b = 1;
    set_latest(2);
    if( get_last()==0 ) { goLeft(); }
    if( get_last()==3 ) { goRight(); }
  }
  if( (b == 0)&&( old_b == 0)&&(state_b==1) ){
    //coil #2 FALLING edge
    state_b = 0;
  }
  
   if( (y == 1)&&( old_y == 1)&&(state_y==0) ){
    //coil #3 rising edge
    state_y = 1;
    set_latest(3);
    if( get_last()==2 ) { goLeft(); }
    if( get_last()==1 ) { goRight(); }
  }
  if( (y == 0)&&( old_y == 0)&&(state_y==1) ){
    //coil #3 FALLING edge
    state_y = 0;
  }
  
  old_p = p;
  old_b = b;
  old_y = y;
}

void set_latest(int inCoil){
  countr++;
  if(countr>2){countr=0;}
  myInts[countr] = inCoil;
}

int get_last(){
  int local_countr = 0;
  if(countr==0){local_countr = 2;}
  if(countr==1){local_countr = 0;}
  if(countr==2){local_countr = 1;}
  return myInts[local_countr];
}

void goLeft(){
  Serial.write(176);       // Control Change
  Serial.write(63);        // note byte. 18
  Serial.write(127);       // velocity (not used at the moment);
}

void goRight(){
  Serial.write(176);
  Serial.write(65);    //19
  Serial.write(127);
}





