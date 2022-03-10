#pragma config(Sensor, in1,		 sharpRight,		 sensorAnalog)
#pragma config(Sensor, in2,		 sharpShort,		 sensorAnalog)
#pragma config(Sensor, in4,		 sharpTop,			 sensorAnalog)
#pragma config(Sensor, in5,		 sharpLeft,			 sensorAnalog)
#pragma config(Sensor, in7,		 reflective,		 sensorAnalog)
#pragma config(Sensor, dgtl12, limit_power,		 sensorDigitalIn)
#pragma config(Motor,	 port2,						rightWheel,		 tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,	 port3,						leftWheel,		 tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard							 !!*//

//!!Code automatically generated by 'ROBOTC' configuration wizard								!!//

 #pragma DebuggerWindows("Globals")
 #pragma DebuggerWindows("systemParameters")
 #pragma DebuggerWindows("Sensors")
 int distanceR = 0, distanceL = 0, distanceT = 0;
 int shortDistance = 0;
 int detectsLine = 0;

 int sawBall = 0;
 int robot_start;
 int robot_end;
 int count;
 char state[50];

void motor_off(){
motor[rightWheel] = 0;
motor[leftWheel] = 0;
}

task main()
{
while(true){
	SensorValue[sharpRight] = 0;
	SensorValue[sharpLeft] = 0;
	SensorValue[sharpTop] = 0;
	SensorValue[sharpShort] = 0;
	SensorValue[reflective] = 0;
	SensorValue[limit_power] = 1;

	robot_start = 1;
	count =0;

	while (robot_start==1){
		if (SensorValue[limit_power]==0){
			robot_start=0;
			robot_end = 1;}
		}
	while(robot_end==1){
		distanceR = 29.988 * pow(SensorValue[sharpRight],-1.173) *1000 * 5/2;
		distanceL = 29.988 * pow(SensorValue[sharpLeft],-1.173) *1000 * 5/2;
		distanceT = 29.988 * pow(SensorValue[sharpTop],-1.173) *1000 * 5/2;

		if(SensorValue[limit_power]==0 && count>10)
		{robot_end = 0;
		motor_off();
		delay(10000);
		}
		//writeDebugStreamLine("Distance in cm : %i", distance);

		shortDistance = 12.08 * pow(SensorValue[sharpShort], -1.058)*1000 * 5/4;

		if (distanceR>80){
			distanceR = 80;
		}
		if (distanceL > 80){
			distanceL = 80;
		}
		if (distanceT>80){
			distanceT = 80;
		}
		if (shortDistance>10){
			shortDistance = 10;
		}
		if (distanceR<10){
			distanceR = 10;
		}
		if (distanceL < 10){
			distanceL = 10;
		}
		if (distanceT < 10){
			distanceT =10;
		}
		if (shortDistance < 4){
			shortDistance = 4;
		}



		if (((distanceT - distanceL)>20)){
			//keep turning slightly
			motor[leftWheel] = 1270;
			motor[rightWheel] = 1270;
		strcpy(state, "reverse and move");

			delay(5);
			//move straight
			motor[leftWheel] = 1270;
			motor[rightWheel] = -1270;
		delay(100);
			sawBall = 1;
	}
	if (((distanceT - shortDistance)>25)){
		//keep going straight
		strcpy(state, "move straight");
	}

	else if (((distanceT - distanceR)>20)){
		//reverse rotation
		motor[leftWheel] = -1270;
		motor[rightWheel] = -1270;
		delay(15);
		//move straight
		motor[leftWheel] = 1270;
		motor[rightWheel] = -1270;
		strcpy(state, "keep turning and move");
		delay(100);
	}
	else{
		//just keep rotating
		if (sawBall ==0){
			motor[leftWheel] = 1270;
			motor[rightWheel] = 1270;
		strcpy(state, "keep rotating");
		}
	}
	count +=1;
	delay(5);

}
}
}
