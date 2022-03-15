 #pragma config(Sensor, in1, sensorRight, sensorAnalog)
 #pragma config(Sensor, in2, sensorLeft, sensorAnalog)
 #pragma config(Sensor, in3, reflectfrontleft, sensorAnalog)
 #pragma config(Sensor, in4, reflectfrontright, sensorAnalog)
 #pragma config(Sensor, in5, reflectbackleft, sensorAnalog)
 #pragma config(Sensor, in6, reflectbackright, sensorAnalog)
 #pragma config(Sensor, in7, sensorMiddleHigh, sensorAnalog)
 #pragma config(Sensor, in8, sensorMiddleLow, sensorAnalog)
 #pragma config(Sensor, dgtl2, Encoder1, sensorQuadEncoder)
 #pragma config(Sensor, dgtl4, sensor1, sensorDigitalIn)
 #pragma config(Sensor, dgtl5, sensor2, sensorDigitalIn)
 #pragma config(Sensor, dgtl6, sensor3, sensorDigitalIn)
 #pragma config(Sensor, dgtl7, sensor4, sensorDigitalIn)
 #pragma config(Sensor, dgtl9, limitright, sensorDigitalIn)
 #pragma config(Sensor, dgtl10, limitleft, sensorDigitalIn)
 #pragma config(Sensor, dgtl11, limitretrieve, sensorDigitalIn)
 #pragma config(Motor, port2, retrieval_motor,
tmotorServoContinuousRotation, openLoop)
 #pragma config(Motor, port3, rightmotor, tmotorVex393_MC29,
openLoop, reversed, driveRight)
 #pragma config(Motor, port4, leftmotor, tmotorVex393_MC29,
openLoop, driveLeft)
 //*!!Code automatically generated by 'ROBOTC' configuration
wizard !!*//


 #pragma DebuggerWindows("Globals")
 #pragma DebuggerWindows("systemParameters")
 #pragma DebuggerWindows("Sensors")


 int loopArray[10];
 int loopCount = 0;
 int previousLoopNumber = 0;



 /*
 a checker to show which area in the code is currently running
 */
 void recordThisLoop(int loopNumber){
 if (loopNumber == previousLoopNumber) return;
 else{
 loopArray[loopCount] = loopNumber;
 previousLoopNumber = loopNumber;
 loopCount++;
 }
 }

 // Declaration for sensors
 int valueLeft=0, valueRight=0,valueMiddleHigh=0, valueMiddleLow=0;
 int valueReflectBackRight=0, valueReflectBackLeft=0, valueReflectFrontLeft=0,
valueReflectFrontRight=0;
 int ballstate=0, ballcount=0;
 int capturemode =0;

 int LEFT = 1;
 int RIGHT = 2;
 int turnstate = 0;

 // Declaration for compass
 int value1=0, value2=0, value3=0, value4=0;
 int sum=0;
 int reading=0;

 int compass_value[8] = {14,12,13,9,11,3,7,6};
 int compass_calibrated[8];
 int compass_time[8];
 int old = 0, actualreading=0, calibratedpos =0;
 int actualpos =0, readpos2=0;
 int timer=0;


 // Compass mapping
 /*
 N
 W E
 S
 Direction I/O Read(value1,value2,value3,value4) Decimal Form
 North 1110

 North-East 1100

 East 1101

 South-East 1001

 South 1011

 South-West 0011

 West 0111

 North-West 0110

 */

 //Vehicle boundary and forward direction constants
 int NORTH_BOUNDARY = 1;
 int WEST_BOUNDARY = 2;
 int EAST_BOUNDARY = 3;
 int SOUTH_AS_FORWARD = 0;
 int NORTH_AS_FORWARD = 1;
 int vehicleForwardDirection = 1;

 // Declaration for battery level check
 int batterylevel =0;

 int retrieve_grab_ball();

 // ************* BASIC FUNCTION *******************
 // Move forward for a period of time then stop
 void motion_move_forward(int time)
 {
 // 45,50 (33,40)
 clearTimer(T2);
 //timer=time1[T2];
 while (time1[T2]< time)
 {
 motor[rightmotor]=50;
 motor[leftmotor]=60;
 }
 motor[rightmotor]=0;
 motor[leftmotor]=0;
 }

 void motion_move_forward_fast(int time)
 {
 // 45,50 (33,40)
 clearTimer(T2);
 //timer=time1[T2];
 while (time1[T2]< time)
 {

 motor
[rightmotor]=80
;
 motor
[leftmotor]=127
;

}
 motor
[rightmotor]=

;
 motor
[leftmotor]=

;

}

 void motion_move_backward
(int time
)

{
 // 45,50 (33,40)
 clearTimer
(T2);
 //timer=time1[T2];
 while
(time1
[T2]< time
)

{
 motor
[rightmotor]=
-45
;
 motor
[leftmotor]=
-60
;

}
 motor
[rightmotor]=

;
 motor
[leftmotor]=

;

}

 void motion_move_backward_fast
(int
time
)

{
 // 45,50 (33,40)
 clearTimer
(T2);
 //timer=time1[T2];
 while
(time1
[T2]< time
)

{
 motor
[rightmotor]=
-80
;
 motor
[leftmotor]=
-127
;

}
 motor
[rightmotor]=

;
 motor
[leftmotor]=

;

}

 // Turn left on the spot
 void motion_turn_left
(int time
)

{
 // 45,50 (33,40)
 clearTimer
(T2);
 //timer=time1[T2];
 while
(time1
[T2]< time
)

{
 motor
[rightmotor]=40
;
 motor
[leftmotor]=
-50
;

}
 motor
[rightmotor]=

;
 motor
[leftmotor]=

;

}

 // Turn left on the spot
 void motion_turn_left_fast
(int time
)

{
 // 45,50 (33,40)
 clearTimer
(T2);
 //timer=time1[T2];
 while
(time1
[T2]< time
)

{
 motor
[rightmotor]=80
;
 motor
[leftmotor]=
-80
;

}
 motor
[rightmotor]=

;
 motor
[leftmotor]=

;

}

 // Turn left on the spot more faster
 void motion_turn_right
(int time
)

{

 // 45,50 (33,40)
 clearTimer(T2);
 //timer=time1[T2];
 while (time1[T2]< time)
 {
 motor[rightmotor]=-45;
 motor[leftmotor]=50;
 }
 motor[rightmotor]=0;
 motor[leftmotor]=0;
 }
 // Turn right on the spot
 void motion_turn_right_fast(int time)
 {
 // 45,50 (33,40)
 clearTimer(T2);
 //timer=time1[T2];
 while (time1[T2]< time)
 {
 motor[rightmotor]=-80;
 motor[leftmotor]=80;
 }
 motor[rightmotor]=0;
 motor[leftmotor]=0;
 }

 int leftMapping (int value){
 int distance = 3.05+(150.4-3.05)/(1+pow((value/218),1.27));
 if (distance<= 80 && distance >=10)
 return distance;
 else
 return 80;
 }
 int rightMapping (int value){
 int distance = 6.05+(92.6-6.05)/(1+pow((value/358.1),1.68));
 if (distance<= 80 && distance >=10)
 return distance;
 else
 return 80;
 }
 int middleHighMapping (int value){
 int distance = -0.50+(9600905-0.50)/(1+pow((value/0.00224),0.9845));
 if (distance<= 80 && distance >=10)
 return distance;
 else
 return 80;
 }
 int middleLowMapping (int value){
 int distance = 8.47+(40.08-8.47)/(1+pow((value/408.02),2.149));
 if (distance<= 30 && distance >=4)
 return distance;
 else
 return 30;
 }



 // Read compass absolute decimal value
 int read_compass ()
 {
 value1 = SensorValue(sensor1);
 value2 = SensorValue(sensor2);
 value3 = SensorValue(sensor3);
 value4 = SensorValue(sensor4);
 sum = value1*8 + value2*4 + value3*2 + value4*1;
 return sum;
 }


 // Read position based on calibrated array
 int read_calibrated()
 {
 int pos =0;
 reading=read_compass();
 for (int i=0;i<8;i++)
 {
 if (reading == compass_calibrated[i])
 {
 pos = i;
 }
 if (reading == compass_value[i])
 {
 actualpos = i;
 }
 }

 return pos;
 }

 // Calibrate compass to create array with calibrated with position 0 starting
//from original reading
 void calibrate_compass()
 {
 int pos = 0;
 reading=read_compass();
 for (int i=0;i<8;i++)
 {
 if (reading == compass_value[i])
 {
 pos = i;
 }
 }
 for (int i=0;i<8;i++)
 {
 compass_calibrated[i]=compass_value[pos];
 pos++;
 if (pos>7)
 {
 pos=pos-8;
 }
 }
 }


 // Orientate to north
 void motion_move_calibrated_north()
 {
 int pos = read_calibrated();
 clearTimer(timer4);
 if (pos>4)
 {
 do {
 motion_turn_right_fast(20);
 pos = read_calibrated();
 if (pos == 0)
 {
 delay(50);
 pos =read_calibrated();
 }
 if (pos ==1 || pos ==2){
 motion_turn_left(200);
 return;
 }
 read_compass();
 }while(pos!=0 && time1[timer4]<3000);
 motion_turn_right_fast(100);


 }
 else if (pos!=0)
 {
 do{
 motion_turn_left_fast(20);
 pos = read_calibrated();
 if (pos == 0)
 {
 delay(50);
 pos =read_calibrated();
 }
 if (pos == 6 || pos ==7){
 motion_turn_right(200);
 return;
 }
 read_compass();
 }while(pos!=0 && time1[timer4]<3000);
 motion_turn_left_fast(100);
 }

 }

 void motion_move_calibrated_south()
 {
 clearTimer(timer4);
 int pos=read_calibrated();
 if (pos<4)
 {
 do{
 motion_turn_right_fast(20);
 pos=read_calibrated();
 if (pos == 4)
 {
 delay(50);
 pos =read_calibrated();
 }
 if (pos ==5 || pos ==6){
 motion_turn_left(200);
 return;
 }
 }while(pos!=4 && time1[timer4]<3000);
 motion_turn_right_fast(100);
 }
 else if (pos != 4 )
 {
 do{
 motion_turn_left_fast(20);
 pos=read_calibrated();
 if (pos == 4)
 {
 delay(50);
 pos =read_calibrated();
 }
 if (pos ==3 || pos ==2){
 motion_turn_right(200);
 return;
 }
 }while(pos!=4 && time1[timer4]<3000);
 motion_turn_left_fast(100);
 }
 }

 void motion_swerve(int dir, int leftSpeed, int rightSpeed, int time){
 // 45,50 (33,40)
 clearTimer(T2);
 //timer=time1[T2];
 while (time1[T2]< time)
 {

 motor[rightmotor]=dir*rightSpeed;
 motor[leftmotor]=dir*leftSpeed;
 }
 motor[rightmotor]=0;
 motor[leftmotor]=0;
 }


 //**********************NEW CODE***********************//
 const int leftSensor = 1;
 const int rightSensor = 2;
 const int topSensor = 3;
 const int middleSensor =4;
 const int reflectfrontleftSensor =5;
 const int reflectfrontrightSensor =6;
 const int reflectbackleftSensor =7;
 const int reflectbackrightSensor =8;


 /*
 this function turns the sensors to boolean
 */
 int sensorDetectedObject(int whichSensor){
 switch (whichSensor){
 case leftSensor:
 if (leftMapping(SensorValue(sensorLeft)) < 50) {
 delay(35);
 if (leftMapping(SensorValue(sensorLeft)) < 50) return 1;
 else return 0;
 }
 else return 0;
 break;
 case rightSensor:
 if (rightMapping(SensorValue(sensorRight)) < 50){
 delay(35);
 if (rightMapping(SensorValue(sensorRight)) < 50) return 1;
 else return 0;
 }
 else return 0;
 break;
 case topSensor:
 if (SensorValue(sensorMiddleHigh) > 300){
 delay(35);
 if (SensorValue(sensorMiddleHigh) > 300) return 1;
 else return 0;
 }
 else return 0;
 break;
 case middleSensor:
 if (middleLowMapping(SensorValue(sensorMiddleLow)) < 28){
 delay(35);
 if (middleLowMapping(SensorValue(sensorMiddleLow)) < 28) return
;
 else return 0;
 }
 else return 0;
 break;
 case reflectfrontleftSensor:
 if (SensorValue(reflectfrontleft) <37 &&
SensorValue(reflectfrontleft) >10) return 1;
 else return 0;
 break;
 case reflectfrontrightSensor:
 if (SensorValue(reflectfrontright) <41&&
SensorValue(reflectfrontright) >10) return 1;
 else return 0;
 break;
 case reflectbackleftSensor:

 if (SensorValue(reflectbackleft) <45 &&
SensorValue(reflectbackleft) >10) return 1;
 else return 0;
 break;
 case reflectbackrightSensor:
 if (SensorValue(reflectbackright) <40 &&
SensorValue(reflectbackright) >10) return 1;
 else return 0;
 break;
 default:
 return 0;
 break;
 }
 return 0;
 }

 int check_which_boundary(){
 int pos = read_calibrated();
 switch (pos){
 case 0: //north
 if (sensorDetectedObject(reflectfrontleftSensor) == 1 &&
sensorDetectedObject(reflectfrontrightSensor)==1) return NORTH_BOUNDARY;
 if (sensorDetectedObject(reflectfrontleftSensor) == 1){
 clearTimer(timer4);
 do{
 motion_move_forward(5);
 if (sensorDetectedObject(reflectfrontrightSensor) == 1) return
NORTH_BOUNDARY;
 }while (time1[timer4] < 200);
 return WEST_BOUNDARY;
 }
 if (sensorDetectedObject(reflectfrontrightSensor)==1){
 clearTimer(timer4);
 do{
 motion_move_forward(5);
 if (sensorDetectedObject(reflectfrontleftSensor)==1) return
NORTH_BOUNDARY;
 }while (time1[timer4] < 200);
 return EAST_BOUNDARY;
 }
 break;
 case 1:
 if (sensorDetectedObject(reflectfrontleftSensor)==1) return
NORTH_BOUNDARY;
 if (sensorDetectedObject(reflectfrontrightSensor)==1) return
EAST_BOUNDARY;
 break;
 case 2:
 if ( sensorDetectedObject(reflectfrontleftSensor)==1 &&
sensorDetectedObject(reflectfrontrightSensor)==1) return EAST_BOUNDARY;
 if (sensorDetectedObject(reflectfrontleftSensor)==1){
 clearTimer(timer4);
 do{
 motion_move_forward(5);
 if (sensorDetectedObject(reflectfrontrightSensor)==1) return
EAST_BOUNDARY;
 }while (time1[timer4] < 200);
 return NORTH_BOUNDARY;
 }
 break;
 case 6:
 if ( sensorDetectedObject(reflectfrontleftSensor)==1 &&
sensorDetectedObject(reflectfrontrightSensor)==1) return WEST_BOUNDARY;
 if (sensorDetectedObject(reflectfrontrightSensor)==1){
 clearTimer(timer4);
 do{
 motion_move_forward(5);

 if (sensorDetectedObject(reflectfrontleftSensor)==1) return
WEST_BOUNDARY;
 }while (time1[timer4] < 200);
 return NORTH_BOUNDARY;
 }
 break;
 case 7:
 if (sensorDetectedObject(reflectfrontrightSensor)==1) return
NORTH_BOUNDARY;
 if (sensorDetectedObject(reflectfrontleftSensor)==1) return
WEST_BOUNDARY;
 break;

 }
 return 0;
 }

 task linesensor()
 {
 int boundary = 0;
 while(1)
 {
 //// check for enemy
 //if (enemy_detection() == 1){
 // enemypresent=1;
 //}
 //else
 // enemypresent=0;

 // Recovery case for different case
 // front left detected
 if (sensorDetectedObject(reflectfrontleftSensor)==1 ) //front left hit
 {
 hogCPU();
 if (check_which_boundary() == NORTH_BOUNDARY)
 {
 vehicleForwardDirection = SOUTH_AS_FORWARD;
 motion_move_backward(500);
 motion_move_calibrated_south();
 }
 else
 {
 motor[rightmotor]=0;
 motor[leftmotor]=0;
 // motion_move_backward(1000);
 for(int i = 0; i<=50; i++){
 motion_move_backward(20);
 if (sensorDetectedObject(reflectbackleftSensor) ==1)
 {
 motion_turn_right(1600);
 motion_move_forward(500);
 break;
 }
 if (i == 50) motion_turn_right_fast(300);
 }
 }
 releaseCPU();
 }
 // front right detected
 if (sensorDetectedObject(reflectfrontrightSensor)==1) //front right hit
 {
 hogCPU();

 if (check_which_boundary() == NORTH_BOUNDARY)
 {
 vehicleForwardDirection = SOUTH_AS_FORWARD;
 motion_move_backward(500);
 motion_move_calibrated_south();

 }

 else
 {
 motor[rightmotor]=0;
 motor[leftmotor]=0;
 // motion_move_backward(1000);
 for(int i = 0; i<=50; i++){
 motion_move_backward(20);
 if (sensorDetectedObject(reflectbackrightSensor) ==1)
 {
 motion_turn_left(1600);
 motion_move_forward(500);
 break;
 }
 if (i == 50) motion_turn_left_fast(300);
 }
 }
 releaseCPU();
 }
 // backleft detected
 if ( sensorDetectedObject(reflectbackleftSensor)==1) //back left hit
and no ball
 {
 hogCPU();
 //NEWCODE
 motor[rightmotor]=0;
 motor[leftmotor]=0;
 // motion_move_backward(1000);
 for(int i = 0; i<=50; i++){
 motion_move_forward(20);
 if (sensorDetectedObject(reflectfrontleftSensor) ==1)
 {
 motion_turn_right(1600);
 motion_move_forward(500);
 break;
 }
 if (i == 50) motion_turn_right_fast(300);
 }
 //OLD CODE
 //motor[rightmotor]=0;
 //motor[leftmotor]=0;
 //motion_move_forward(1000);
 releaseCPU();
 }
 // backright detected
 if (sensorDetectedObject(reflectbackrightSensor)==1) //back right hit
and no ball
 {
 hogCPU();
 //NEW CODE
 motor[rightmotor]=0;
 motor[leftmotor]=0;
 // motion_move_backward(1000);
 for(int i = 0; i<=50; i++){
 motion_move_forward(20);
 if (sensorDetectedObject(reflectfrontrightSensor) ==1)
 {
 motion_turn_left(1600);
 motion_move_forward(500);
 break;
 }
 if (i == 50) motion_turn_left_fast(300);
 }
 //OLD CODE
 //motor[rightmotor]=0;
 //motor[leftmotor]=0;
 ////motion_turn_left(500);

 //motion_move_forward(1000);
 releaseCPU();
 }

 // Add detection for base wall
 //if (sensorDetectedObject(leftSensor) == 1 &&
sensorDetectedObject(rightSensor) == 1 && enemy_detection() ==0)
 //{
 // hogCPU();
 // motor[rightmotor]=0;
 // motor[leftmotor]=0;
 // motion_turn_left_fast(1600);
 // vehicleForwardDirection = NORTH_AS_FORWARD;
 // motion_move_forward(1000);
 // releaseCPU();
 //}

 }
 }

 int cornerBallDetected(){
 if (sensorDetectedObject(reflectfrontleftSensor) ==1 ||
sensorDetectedObject(reflectfrontrightSensor) ==1){
 motor[leftmotor] = 0;
 motor[rightmotor]=0;
 return 1;
 }
 else return 0;
 }

 void cornerBallRecovery(){
 if (middleLowMapping(SensorValue[sensorMiddleLow]) <= 17 ){
 retrieve_grab_ball();
 //ballstate = 1;
 }
 //else if (sensorDetectedObject(leftSensor) ||
sensorDetectedObject(rightSensor) || sensorDetectedObject(middleSensor)){
 // if (sensorDetectedObject(reflectfrontrightSensor))
 // {
 // // OLD CODE
 // ////motion_move_forward(100);
 // //motion_turn_left(2400);
 // ////motion_move_forward(200);
 // motion_move_backward(500);
 // clearTimer(timer1);
 // do
 // {
 // motion_swerve(1,40,120,20);
 // if (middleLowMapping(SensorValue[sensorMiddleLow]) <= 11 )
 // {
 // if (retrieve_grab_ball())
 // {
 // motion_turn_left(1600);
 // motion_move_forward(500);
 // return;
 // }
 // }
 // if (sensorDetectedObject(reflectfrontrightSensor))
 // {
 // motion_move_backward(1000);
 // return ;
 // }
 // if (sensorDetectedObject(reflectbackrightSensor))
 // {
 // clearTimer(timer1);
 // do {
 // motion_move_forward(20);

 // if (middleLowMapping(SensorValue[sensorMiddleLow]) <=
 )
 // {
 // if (retrieve_grab_ball()){
 // motion_turn_right(1600);
 // motion_move_forward(500);
 // return;
 // }
 // }
 // }while (time1[timer1]<300);
 // return;
 // }
 // }
 // while (time1[timer1]<3000);
 // }
 // else if (sensorDetectedObject(reflectfrontleftSensor))
 // {
 // // OLD CODE
 // ////motion_move_forward(100);
 // //motion_turn_right(2400);
 // ////motion_move_forward(200);
 // motion_move_backward(500);
 // clearTimer(timer1);
 // do
 // {
 // motion_swerve(1,120,40,20);
 // if (middleLowMapping(SensorValue[sensorMiddleLow]) <= 11 )
 // {
 // if (retrieve_grab_ball())
 // {
 // motion_turn_right(1600);
 // motion_move_forward(500);
 // return;
 // }
 // }
 // if (sensorDetectedObject(reflectfrontleftSensor))
 // {
 // motion_move_backward(1000);
 // return ;
 // }
 // if (sensorDetectedObject(reflectbackleftSensor))
 // {
 // clearTimer(timer1);
 // do {
 // motion_move_forward(20);
 // if (middleLowMapping(SensorValue[sensorMiddleLow]) <=
 )
 // {
 // if (retrieve_grab_ball()){
 // motion_turn_right(1600);
 // motion_move_forward(500);
 // return;
 // }
 // }
 // }while (time1[timer1]<300);
 // return;
 // }
 // }
 // while (time1[timer1]<3000);
 // }
 // else {
 // clearTimer(timer1);
 // do{
 // motion_move_backward(5);
 // } while ( ( sensorDetectedObject(reflectfrontleftSensor) == 0 ||
sensorDetectedObject(reflectfrontrightSensor)== 0 ) && time1[timer1]<50 );
 // if ( sensorDetectedObject(reflectfrontleftSensor) ||
sensorDetectedObject(reflectfrontrightSensor) ){

 // cornerBallRecovery();
 // return;
 // }
 // }
 //}
 else motion_move_backward(200);
 startTask(linesensor);
 return;
 }

 int scanLeft(int count){
 turnstate = LEFT;
 for (int i = 0; i<count; i++){
 if (sensorDetectedObject(middleSensor)){
 //recordthisloop(1); //left scan, middle detected
 motion_turn_right(300);
 return 1;
 }
 else if (sensorDetectedObject(leftSensor)){
 //recordthisloop(2); //left detected
 return 1;
 }
 motion_turn_left_fast(20);
 }
 return 0;
 }

 int scanRight(int count){
 turnstate = RIGHT;
 for (int i=0; i<count; i++){
 if (sensorDetectedObject(middleSensor) ){
 //recordThisLoop(3); //right scan, middle detected
 motion_turn_right(300); //hardcode to left sensor
 return scanLeft(40);
 }
 else if (sensorDetectedObject(rightSensor)){
 //recordthisloop(4); //right detected
 motion_turn_right(700); //hardcode to left sensor
 return scanLeft(40);
 }
 motion_turn_right_fast(20);
 }
 return 0;
 }

 // Enemy Detection //
 // return 1 if enemy detected
 int enemy_detection()
 {
 // if ( (middleHighMapping(SensorValue(sensorMiddleHigh)) -
leftMapping(SensorValue(sensorLeft))) < 20 )
 if (SensorValue(sensorMiddleHigh) >300)
 return 1;
 return 0;
 }

 int baseDetection(){
 if (sensorDetectedObject(leftSensor)==1)
 {
 if (sensorDetectedObject(rightSensor)==1)
 {
 return 1;
 }
 }
 return 0;
 }

 int motion_scan_object(){

 /*
 this funciton will scan left and right for object and return if object is
seen
 */
 int detectsObject = 1;
 //if (sensorDetectedObject(leftSensor) &&
sensorDetectedObject(rightSensor)){
 // //delay(5000);
 // clearTimer(timer4);
 // do{
 // motor[leftmotor]=0;
 // motor[rightmotor]=0;
 // if(enemy_detection()) return 1;
 // }while(time1[timer4] < 2000);
 // if (sensorDetectedObject(leftSensor) &&
sensorDetectedObject(rightSensor)){
 // motion_move_backward_fast(500);
 // motion_turn_right_fast(1600);
 // vehicleForwardDirection = NORTH_AS_FORWARD;
 // motion_move_forward_fast(1000);
 // return 0;
 // }
 // return motion_scan_object();
 //}
 if (sensorDetectedObject(rightSensor)){
 if (scanRight(40) == detectsObject) return 1;
 //motion_turn_right(800);//hard code to center
 if (scanLeft(80) == detectsObject) return 1;
 return 0;
 }
 else
 {
 if (scanLeft(40) == detectsObject) return 1;
 //motion_turn_right(800);//hard code to center
 if (scanRight(80) == detectsObject) return 1;
 }

 return 0;
 }


 int averageDistanceOfRearSensors = 0;

 void motion_scan_ball()
 { //start of motion_scan_ball()
 int objectDetected = motion_scan_object();
 //*******************method if bottom sensor detects but not top
sensors*********************//
 if (objectDetected == 1 && enemy_detection() == 0){ //start of method
 //recordthisloop(5); //bottom sensors detects but not top sensors
 motion_turn_left(300); //hardcode to center
 clearTimer(timer4);
 int moveBackTime = 0;
 stopTask(linesensor);
 do { //move forward until middle sensor detects object
 if (cornerBallDetected()){
 motion_move_forward(300);
 cornerBallRecovery();
 startTask(linesensor);
 motion_move_backward(500);

 }
 motion_move_forward(5);
 moveBackTime += 5;
 } while (sensorDetectedObject(middleSensor) == 0 && time1[timer4] <
 );
 startTask(linesensor);
 //delay(2000);

 if (enemy_detection() == 1){
 //recovery
 averageDistanceOfRearSensors =
(middleHighMapping(SensorValue(sensorMiddleHigh))
 +leftMapping(SensorValue(sensorLeft)))/2;
 //delay(2000);
 if (averageDistanceOfRearSensors < 30){ //means its actually enemy
 //recordthisloop(8); //enemy detected and below 30cm, will move
back
 motion_move_backward(moveBackTime);
 return;
 }
 }
 if (baseDetection() == 1){
 motion_move_backward_fast(500);
 motion_turn_right_fast(1600);
 vehicleForwardDirection = NORTH_AS_FORWARD;
 //motion_move_forward_fast(1000);
 return;
 }
 if (sensorDetectedObject(middleSensor) == 0){
 //recordThisLoop(9); //middle sensor lost object, will rescan
 for (int i=0; i<120;i++){
 if(i < 40) motion_turn_left(20);
 else motion_turn_right(20);
 if (sensorDetectedObject(middleSensor) == 1){
 //recordthisloop(3); //middle sensor detected
 break;
 }
 }
 }
 clearTimer(timer4);
 if (sensorDetectedObject(middleSensor) == 1){
 //capturemode =1;
 //delay(1000);
 //clearTimer(timer4);
 stopTask(linesensor);
 do{ //move forward until ball within 11cm
 if (cornerBallDetected()){
 cornerBallRecovery();
 //capturemode=0;
 return;
 }
 motion_move_forward(5);
 }while(middleLowMapping(SensorValue(sensorMiddleLow)) > 11 &&
time1[timer4] < 1200);
 startTask(linesensor);
 }
 //delay(1000);
 if ( middleLowMapping(SensorValue(sensorMiddleLow)) <= 11){ //return if
ball within 11cm
 ballstate = 1;
 return;
 }
 return;
 }//end of method
 //******************end of method if bottom sensor detects but not top
sensors**************//


 //******************method if bottom and top sensors
detects********************************//
 else if (objectDetected == 1 && enemy_detection() == 1){ // start of method
 //recordthisloop(6); //bottom and top sensors detects
 //delay(1000);
 if (sensorDetectedObject(middleSensor) != 1){
 motion_turn_left(300);
 //delay(1000);

 }//hardcode to center if middle sensor does not detect
 clearTimer(timer4);
 do { //move forward until middle sensor detects object
 motion_move_forward(5);
 } while (sensorDetectedObject(middleSensor) == 0 && time1[timer4] <
 );
 //delay(1000);
 if (sensorDetectedObject(leftSensor) != 1 &&
sensorDetectedObject(rightSensor) == 1){ //if right sensor detects, need to shift
to top eye to detect if there is enemy
 motion_turn_right(800); //turn to look at left side
 //delay(1000);
 averageDistanceOfRearSensors =
(middleHighMapping(SensorValue(sensorMiddleHigh))
 +leftMapping(SensorValue(sensorLeft)))/2;
 //delay(1000);
 motion_turn_left(400); //turn back to center
 }
 else{
 averageDistanceOfRearSensors =
(middleHighMapping(SensorValue(sensorMiddleHigh))
 +leftMapping(SensorValue(sensorLeft)))/2;
 //delay(1000);
 }
 if (sensorDetectedObject(middleSensor) == 1){
 if (averageDistanceOfRearSensors > 40){ //detect object but enemy
is more than 40cm away
 clearTimer(timer4);
 do{ //move forward until ball within 11cm
 motion_move_forward(5);
 }while(middleLowMapping(SensorValue(sensorMiddleLow)) > 11 &&
time1[timer4] < 1200);
 if ( middleLowMapping(SensorValue(sensorMiddleLow)) <=
){ //return if ball within 11cm
 ballstate = 1;
 return;
 }
 }
 else{ //detect object but enemy is closer than 10cm, deem as object
is enemy
 clearTimer(timer4);
 do {
 if (enemy_detection() == 0){
 motion_scan_ball();
 return;
 }
 } while (time1[timer4] < 2000);
 motion_move_backward(800);
 motion_turn_left(1200);
 motion_move_forward(1000);
 motion_turn_right(1200);
 return;
 }
 }
 return;
 }//end of method
 return;
}//end of motion_scan_ball


//**********************END OF NEW CODE****************//




void motion_scan_360()
{
 for (int i=0; i<170; i++){

 motion_turn_right_fast(20);
 if ((sensorDetectedObject(middleSensor) == 1 ||
sensorDetectedObject(leftSensor) || sensorDetectedObject(rightSensor)) &&
enemy_detection() == 0) return;
 }
}



// reverse until ensure home is reached
int motion_home()
{
 stopTask(linesensor);
 motion_move_calibrated_north();
 clearTimer(timer4);
 while (time1[timer4] < 10000)
 {

 while (sensorDetectedObject(reflectbackleftSensor)==1) //hit back left
 {
 motion_move_backward(100);
 if (SensorValue(limitleft)==0 && SensorValue(limitright) ==0)
return 1;
 //else if (SensorValue(limitright)==0){
 // motion_swerve(-1,120,0,400);
 // return 1;
 //}
 else if (SensorValue(limitleft) ==0){
 motion_swerve(-1,0,120,400);
 return 1;
 }
 //NEW CODE
 motor[rightmotor]=0;
 motor[leftmotor]=0;
 for(int i = 0; i<=50; i++){
 motion_move_forward(20);
 if (sensorDetectedObject(reflectfrontleftSensor) ==1)
 {
 motion_turn_right(1600);
 motion_move_forward(500);
 break;
 }
 if (i == 50) motion_turn_left_fast(300);
 }
 //OLD CODE
 //motion_move_forward(1000);
 //motion_turn_left(400);
 //motion_move_calibrated_north();
 return -1;
 }

 while (sensorDetectedObject(reflectbackrightSensor)==1)//hit back right
 {
 motion_move_backward(100);
 //NEW CODE
 if (SensorValue(limitleft)==0 && SensorValue(limitright) ==0)
return 1;
 else if (SensorValue(limitright)==0){
 motion_swerve(-1,120,0,800);
 return 1;
 }
 //else if (SensorValue(limitleft) ==0){
 // motion_swerve(-1,0 ,120,800);
 // return 1;
 //}

 //OLD CODE
 //if (SensorValue(limitleft)==0 || SensorValue(limitright)==0)

 //{
 // return 1;
 //}

 //NEW CODE
 motor[rightmotor]=0;
 motor[leftmotor]=0;
 for(int i = 0; i<=50; i++){
 motion_move_forward(20);
 if (sensorDetectedObject(reflectfrontrightSensor) ==1)
 {
 motion_turn_left(1600);
 motion_move_forward(500);
 break;
 }
 if (i == 50) motion_turn_right_fast(300);
 }
 //OLD CODE
 //motion_move_forward(400);
 //motion_turn_right(400);
 //motion_move_calibrated_north();
 return -1;
 }

 motion_move_backward_fast(10);
 }
 if (time1[timer4] > 9500)
 {
 motion_move_forward_fast(500);
 motion_turn_left_fast(800);
 motion_move_forward_fast(500);
 return -1;
 }
 // check if its wall or robot
 // Note: Wrong case/Recovery is not implemented yet
 //for (int i=0; i<1; i++)
 //{
 // motion_move_forward(500);
 // while (SensorValue(limitleft)==1 || SensorValue(limitright)==1)
 // {
 // motion_move_backward_fast(100);
 // }
 //}
 return -1;
}

//*******RETIREVAL SYSTEM***********//

#define HOLDING_BALL 1
#define DEFAULT 2

//CONSTANTS by retrieval
int ROUND = 360;
int TIMER_THRESHOLD = 1600;
int BACKTRACK_VAL = 5;
int RETRIEVE_SPEED = 127;
int DEPOSIT_SPEED = 80;
int SLOW_SPEED = 40;
int BALL_IS_CAPTURED_THRESHOLD = 1800;

//Declaration by retrieval
int currentEncoderValue;

int position = 2;
int encoderOffset = 0;

/*
sets the speed for retrieving the ball

*/
int speedToRetrieve(int currentValue, int targetValue){
 int angularDisplacement = abs(targetValue - currentValue);
 if ( angularDisplacement < 60 ) {
 return SLOW_SPEED;
 }
 else return RETRIEVE_SPEED;
}

/*
sets the speed for depositing the ball
tested best with 80, higher will not have enough torque
*/
int speedToDeposit(int currentValue, int targetValue){
 int angularDisplacement = abs(targetValue - currentValue);
 if ( angularDisplacement < 50) {
 return SLOW_SPEED;
 }
 else return DEPOSIT_SPEED;
}


int findEncoderOffset(int currentEncoderValue){
 wait1Msec(1000);
 return SensorValue[Encoder1] - currentEncoderValue;
}


// Function will untangle robot when stucked for TIMER_THRESHOLD period
void retrieve_untangle(){
 /*
 Function will untangle robot when stucked for TIMER_THRESHOLD period
 */
 //NEW CODE FOR UNTANGLE
 motor[retrieval_motor]=0;
 delay(500);
 int backtrackValue = SensorValue[Encoder1] - BACKTRACK_VAL;
 clearTimer(timer2);
 if ( SensorValue[sensorMiddleLow] < 700 ){
 do{
 motor[retrieval_motor] = -RETRIEVE_SPEED;
 }while(SensorValue[Encoder1] > backtrackValue && time1[timer2] < 1000);
 motor[retrieval_motor] = 0;
 motion_move_forward(100);
 }
 else motion_move_forward(200);
 // OLD CODE FOR UNTANGLE
 //motor[retrieval_motor] = 0;
 //delay(500);
 //int backtrack_value = SensorValue(Encoder1)- BACKTRACK_VAL;
 //while (SensorValue[Encoder1]>backtrack_value){
 // motor[retrieval_motor] = -RETRIEVE_SPEED;
 //}
 //motor[retrieval_motor] = 0;
 return;
}

void retrieve_zero_arm(){
 clearTimer(timer1);
 do{
 motor[retrieval_motor] = 60;
 } while ( SensorValue[limitretrieve] == 1 && time1[timer1] < 5000);
 motor[retrieval_motor] = 0;
 SensorValue[Encoder1] = 0;
 encoderOffset = findEncoderOffset(SensorValue[Encoder1]);
}
/*
retrieval functoin to check if capture of ball is sucessful

returns 1 if sucess, -1 if fails
*/
int retrieve_check_for_capture(){
 wait1Msec(1000);
 if (SensorValue[sensorMiddleLow] > BALL_IS_CAPTURED_THRESHOLD ) return 1;
 else return -1;
}

void retrieve_deposit_ball(){
 /*
 Function will deposit ball
 */

 //NEW CODE
 currentEncoderValue = SensorValue[Encoder1];
 clearTimer(timer1);
 clearTimer(timer4);
 if (retrieve_check_for_capture() == 1){
 do {
 motor[retrieval_motor] = speedToDeposit(SensorValue(Encoder1),
(3.3/4.0)*ROUND) ;
 if (time1[timer1] > 3000){
 motor[retrieval_motor] = 0;
 while ( SensorValue[Encoder1] >= (1.0/2.0)*ROUND){
 motor[retrieval_motor] = -
speedToDeposit(SensorValue(Encoder1),(1.0/2.0)*ROUND) ;
 }
 motor[retrieval_motor] = 0;
 clearTimer(timer1);
 }
 }while(SensorValue[Encoder1] <= ((3.1/4.0)*ROUND - encoderOffset) &&
time1[timer4] < 10000);
 motor[retrieval_motor] = 0;
 if (time1[timer4] > 10000){
 while ( SensorValue[Encoder1] >= (1.0/4.0)*ROUND){
 motor[retrieval_motor] = -
speedToDeposit(SensorValue(Encoder1),(1.0/2.0)*ROUND) ;
 }
 motor[retrieval_motor] = 0;
 }
 wait1Msec(1000);
 retrieve_zero_arm();
 }
 else retrieve_zero_arm();
}

//OLD CODE
//currentEncoderValue = SensorValue[Encoder1];
//wait1Msec(1000);
//switch (position){

//case HOLDING_BALL:
// while (SensorValue[Encoder1]<= currentEncoderValue - encoderOffset +
(1.0/4.0)*ROUND){
// motor[retrieval_motor] = speedToDeposit(SensorValue(Encoder1),
currentEncoderValue - encoderOffset + (1.0/4.0)*ROUND) ;
// //motor[retrieval_motor] = 60;
// }
// motor[retrieval_motor] = 0;
// encoderOffset = findEncoderOffset(SensorValue[Encoder1]);
// retrieve_zero_arm();
// position = DEFAULT;
// ballstate = 0;
// break;
//default:
// //empty loop
// break;
//}

//}

int retrieve_grab_ball(){
 /*
 Function will retrieve ball into loading area, if ball is stuck, it will
 automatically untangle itself and try again
 */

 //NEW CODE
 //if (retrieve_check_for_capture() == 1){
 // ballstate = 1;
 // return;
 //}
 clearTimer(timer1);
 clearTimer(timer4);
 currentEncoderValue = SensorValue[Encoder1];
 if ( SensorValue[sensorMiddleLow] < 1800){
 do{
 motor[retrieval_motor] = speedToRetrieve(SensorValue(Encoder1),
(1.0/2.0)*ROUND );
 if (time1[timer1] > TIMER_THRESHOLD){
 if (retrieve_check_for_capture() == -1){
 //NEWround
 retrieve_untangle();
 clearTimer(timer1);
 //OLD CODE
 //if ( SensorValue[sensorMiddleLow] < 700){
 // retrieve_untangle();
 // motion_move_forward(100);
 //}
 //else motion_move_forward(200);
 //clearTimer(timer1);
 }
 }
 }while( SensorValue[Encoder1] <= (1.0/2.0)*ROUND && time1[timer4] <
);
 motor[retrieval_motor] = 0;
 //encoderOffset = findEncoderOffset(SensorValue[Encoder1]);
 if (time1[timer4] > 10000 ){
 delay(1000);
 clearTimer(timer4);
 do {
 motor[retrieval_motor] = -
speedToRetrieve(SensorValue(Encoder1),(1.0/4.0)*ROUND) ;
 }while( SensorValue[Encoder1] >= (1.0/4.0)*ROUND && time1[timer4]
< 2000 );
 motor[retrieval_motor] = 0;
 if (time1[timer4] > 2000) motion_move_backward_fast(400);
 }
 }


 if (retrieve_check_for_capture() == 1){
 ballstate = 1;
 return 1;
 }
 else {
 ballstate = 0;
 retrieve_zero_arm();
 return 0;
 }
}


//OLD CODE
//clearTimer(timer1);
//currentEncoderValue = SensorValue[Encoder1];
//switch (position){

//case HOLDING_BALL:
// while (SensorValue[Encoder1] <= currentEncoderValue - encoderOffset +
ROUND ){
// motor[retrieval_motor] = speedToRetrieve(SensorValue(Encoder1),
currentEncoderValue - encoderOffset + ROUND);
// if (time1[timer1] > TIMER_THRESHOLD){
// retrieve_untangle();
// motion_move_forward(100);
// }
// }
// motor[retrieval_motor] = 0;
// encoderOffset = findEncoderOffset(SensorValue[Encoder1]);
// position = HOLDING_BALL;
// break;
//case DEFAULT:
// while (SensorValue[Encoder1] <= currentEncoderValue - encoderOffset +
(1.0/2.0)*ROUND ){
// motor[retrieval_motor] = speedToRetrieve(SensorValue(Encoder1),
currentEncoderValue - encoderOffset + (1.0/2.0)*ROUND );
// if (time1[timer1] > TIMER_THRESHOLD){
// retrieve_untangle();
// motion_move_forward(100);
// }
// }
// motor[retrieval_motor] = 0;
// encoderOffset = findEncoderOffset(SensorValue[Encoder1]);
// position = HOLDING_BALL;
// break;
//default:
// //empty case
// break;
//}
//if (retrieve_check_for_capture() == -1) {
// retrieve_zero_arm();
// ballstate = 0;
//}
//}

//***********END OF RETRIEVAL**************//



// ************ START OF MAIN PROGRAM ************** //


int motion_goto_base_center(){
 //NEW CODE
 for (int i=0; i<140; i++){
 if (i < 100) motion_move_forward_fast(20);
 else motion_turn_left_fast(20);
 if (middleLowMapping(SensorValue(sensorMiddleLow)) < 11){
 if (retrieve_grab_ball()) return 1;
 }
 if (sensorDetectedObject(reflectfrontleftSensor) ||
sensorDetectedObject(reflectbackleftSensor)){
 motion_turn_right_fast(800);
 motion_move_forward_fast(1200);
 motion_move_calibrated_north();
 startTask(linesensor);
 return 1;
 }
 if ( sensorDetectedObject(reflectfrontrightSensor) ||
sensorDetectedObject(reflectbackrightSensor) ){
 motion_turn_left_fast(800);
 motion_move_forward_fast(1200);
 motion_move_calibrated_north();
 startTask(linesensor);
 return 1;

 }
 }
 stopTask(linesensor);
 clearTimer(timer4);
 do{
 motion_move_forward_fast(5);
 if (middleLowMapping(SensorValue(sensorMiddleLow)) < 11){
 if (retrieve_grab_ball()){
 startTask(linesensor);
 return 1;
 }
 }
 }while( sensorDetectedObject(reflectfrontrightSensor)==0 &&
sensorDetectedObject(reflectfrontleftSensor) == 0 && time1[timer4] < 3000);
 if (sensorDetectedObject(reflectfrontrightSensor) ||
sensorDetectedObject(reflectfrontleftSensor)){
 motion_move_backward_fast(1200);
 motion_move_calibrated_north();
 //delay(1000);
 startTask(linesensor);
 return 1;
 }
 else{
 clearTimer(timer4);
 do{
 motion_move_backward_fast(5);
 }while( sensorDetectedObject(reflectbackrightSensor)==0 &&
sensorDetectedObject(reflectbackleftSensor)==0 && time1[timer4] < 5000);
 if(sensorDetectedObject(reflectbackrightSensor)||
sensorDetectedObject(reflectbackleftSensor) ){
 motion_move_forward_fast(1200);
 motion_move_calibrated_north();
 //delay(1000);
 startTask(linesensor);
 return 1;
 }
 else {
 motion_move_calibrated_north();
 startTask(linesensor);
 return 0;
 }
 }
}

void reset_system(){
 vehicleForwardDirection = NORTH_AS_FORWARD;
 motion_move_forward(200);
 startTask(linesensor);
 ballstate=0;
 SensorValue[sensorRight]=0;
 SensorValue[sensorLeft]=0;
 SensorValue[sensorMiddleHigh]=0;
 SensorValue[sensorMiddleLow]=0;
 SensorValue[reflectbackright]=0;
 SensorValue[reflectbackleft]=0;
 SensorValue[reflectfrontright]=0;
 SensorValue[reflectfrontleft]=0;
 turnstate = 0;
 averageDistanceOfRearSensors = 0;
 clearTimer(timer1);
 clearTimer(timer2);
 clearTimer(timer3);
 clearTimer(timer4);
}

task main()
{ //start of main task
 vehicleForwardDirection = NORTH_AS_FORWARD;

 batterylevel=nAvgBatteryLevel;
 ballstate=0;
 SensorValue[Encoder1]=0;
 SensorValue[sensorRight]=0;
 SensorValue[sensorLeft]=0;
 SensorValue[sensorMiddleHigh]=0;
 SensorValue[sensorMiddleLow]=0;
 SensorValue[reflectbackright]=0;
 SensorValue[reflectbackleft]=0;
 SensorValue[reflectfrontright]=0;
 SensorValue[reflectfrontleft]=0;

 retrieve_zero_arm();

 while (1){
 if (SensorValue(limitleft) == 0){
 retrieve_grab_ball();
 }
 if (SensorValue(limitright) == 0){
 retrieve_deposit_ball();
 }
}

 //while(1){
 // if (SensorValue(limitleft) == 0){
 // motion_scan_object();
 // }
 // if (SensorValue(limitright) == 0){
 // scanRight(40);
 // }
 //}

 while (1)
 {
 if (SensorValue(limitleft)==0){
 // calibrate compass
 calibrate_compass();
 startTask(linesensor);
 break;
 }
 }

 //while(1){
 //}
 //while(1){
 // motion_move_backward(10);
 //}

 /*
 while (1)
 {
 valueLeft = leftMapping(SensorValue(sensorLeft));
 valueRight = rightMapping(SensorValue(sensorRight));
 valueMiddleHigh = middleHighMapping(SensorValue(sensorMiddleHigh));
 valueMiddleLow = middleLowMapping(SensorValue(sensorMiddleLow));
 }
 */

 while(1){
 clearTimer(timer3);
 reset_system();
 //burst forward for ballcount ==0

 if (ballcount ==0)
 {
 for(int i = 0; i<180; i++){
 motion_move_forward_fast(20);

 if (sensorDetectedObject(middleSensor) ||
sensorDetectedObject(leftSensor) || sensorDetectedObject(rightSensor)) break;
 if (i == 99){
 break;
 }
 }
 }
 else // after first ball
 {
 motion_goto_base_center();
 }

 // Detect/Scan Ball
 // Scan for ball, once detected, tune to middle
 int i = 0;
 while (ballstate ==0 && ballcount == 0)
 {
 if (i==2){
 motion_scan_360();
 i = -1;
 if (sensorDetectedObject(middleSensor) ||
sensorDetectedObject(leftSensor) || sensorDetectedObject(rightSensor)){
 motion_scan_ball();
 }
 }
 else motion_scan_ball();
 i++;
 if (ballstate == 1){
 if (retrieve_grab_ball())
 //retrieve_deposit_ball();
 break;
 }
 else{
 //recordthisloop(7); //fail scan, going one bound ahead
 if (time100[timer3] >1200)
 {
 ballstate=1;
 while(motion_home() != 1)
 {
 //infinite loop
 }
 ballcount++;
 continue;
 }

 if (vehicleForwardDirection == NORTH_AS_FORWARD)
motion_move_calibrated_north();
 else motion_move_calibrated_south();
 for(int i = 0; i<100; i++){
 motion_move_forward(20);
 if (sensorDetectedObject(middleSensor) ||
sensorDetectedObject(leftSensor) || sensorDetectedObject(rightSensor)) break;
 if (i == 99){
 break;
 }
 }
 }
 }

 // Collection of second ball onwards
 while (ballstate == 0 && ballcount != 0)
 {
 motion_scan_360();
 if (sensorDetectedObject(middleSensor) ||
sensorDetectedObject(leftSensor) || sensorDetectedObject(rightSensor)){
 motion_scan_ball();
 }
 if (ballstate == 1){

 if (retrieve_grab_ball())
 //retrieve_deposit_ball();
 break;
 }
 else{
 //recordthisloop(7); //fail scan, going one bound ahead
 if (time100[timer3] >1200)
 {
 ballstate=1;
 while(motion_home() != 1)
 {
 //infinite loop
 }
 ballcount++;
 continue;
 }

 if (vehicleForwardDirection == NORTH_AS_FORWARD)
motion_move_calibrated_north();
 else motion_move_calibrated_south();
 //motion_turn_left(100);
 for(int i = 0; i<100; i++){
 motion_move_forward(20);
 if (sensorDetectedObject(middleSensor) ||
sensorDetectedObject(leftSensor) || sensorDetectedObject(rightSensor)) break;
 }
 }
 }

 while(motion_home() != 1)
 {
 //infinite loop
 }
 retrieve_deposit_ball();
 i=0;
 ballcount++;
 }

} //end of main task
