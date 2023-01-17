#pragma config(Motor,  port2,           leftMotor,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           rightMotor,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           leftLift,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           rightLift,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           centerLift,    tmotorVex393_MC29, openLoop)

//TELEOP TASK
task teleop()
{

	int maxPower = 127;
	int minPower = -127;
	int deadband = 5;

	while(1 == 1){

		//Calculates motor power
		float leftPower = (vexRT[Ch2] + vexRT[Ch1]);
		float rightPower = (vexRT[Ch2] - vexRT[Ch1]);

		// check calculated amount against min/max
		if (rightPower > maxPower) {

			rightPower = maxPower;
		}
		else if (rightPower < minPower){

			rightPower = minPower;

		}
		if (leftPower > maxPower) {

			leftPower = maxPower;

		}
		else if (leftPower < minPower) {

			leftPower = minPower;

		}

		//ignore values within deadband range
		if (abs(leftPower) < deadband ) leftPower = 0;
		if (abs(rightPower) < deadband ) rightPower = 0;

		//sets motor power
		motor[leftMotor]  = leftPower;
		motor[rightMotor] = rightPower;

		//LIFT CONTROL
		//center lift motor up

		if(vexRT[Btn6U] == 1) {

			motor[centerLift] = 55;

		}

		//center lift motor down
		else if(vexRT[Btn6D] == 1) {

			motor[centerLift] = -35;

		}

		else {

			motor[centerLift] = 0;

		}

		//lift main lift up
		if (vexRT[Btn5D] == 1) {

			motor[leftLift] = 65;
			motor[rightLift] = 65;

		}

		//drop main lift
		else if (vexRT[Btn5U] == 1) {

			motor[leftLift] = -40;
			motor[rightLift] = -40;

		}

		//If buttons are not pressed, nothing happens
		else{

			motor[leftLift] = 0;
			motor[rightLift] = 0;

		}

	}

}

//AUTONOMOUS TASK
task auton(){

	int i = 0;

	while(i == 0) {

		wait1Msec(60);

		//Move forward 5 feet
		motor[rightMotor] = 80;
		motor[leftMotor] = 80;
		wait1Msec(850);
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;

		wait1Msec(60);

		//Turn right
		motor[leftMotor] = 50;
		motor[rightMotor] = -50;
		wait1Msec(740);
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;
		wait1Msec(60);

		//Move forward
		motor[rightMotor] = 80;
		motor[leftMotor] = 80;
		wait1Msec(255);
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;

		wait1Msec(60);

		//Turn left
		motor[leftMotor] = -50;
		motor[rightMotor] = 50;
		wait1Msec(740);
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;

		wait1Msec(60);

		//Move forward 5 feet
		motor[rightMotor] = 80;
		motor[leftMotor] = 80;
		wait1Msec(425);
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;

		wait1Msec(60);

		//Turn left
		motor[leftMotor] = -80;
		motor[rightMotor] = 80;
		wait1Msec(740);
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;

		wait1Msec(60);

		//Move forward 
		motor[rightMotor] = 50;
		motor[leftMotor] = 50;
		wait1Msec(255);
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;

		wait1Msec(60);

		//Turn left
		motor[leftMotor] = -80;
		motor[rightMotor] = 80;
		wait1Msec(740);
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;

		wait1Msec(60);

		//Move forward
		motor[rightMotor] = 50;
		motor[leftMotor] = 50;
		wait1Msec(300);
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;

		wait1Msec(60);

		i++;

	}

}

//MAIN METHOD
task main()
{

	while(true){

		//AUTONOMOUS STARTS WHEN BUTTON 7D IS PRESSED
		if(vexRT[Btn7D] == 1) {

			startTask(auton); 

			//Wait for joystick button to be released so we don't start the task multiple times
			while(vexRT[Btn7D] == 1){

				sleep(10);

			}

		}

		//TELE-OP STARTS WHEN BUTTON 7U IS PRESSED
		if(vexRT[Btn7U] == 1){

			startTask(teleop);  //autonomous starts when buton 7U is pressed

			//Wait for joystick button to be released so we don't start the task multiple times
			while(vexRT[Btn7U] == 1){

				sleep(10);

			}

		}

		//EMERGENCY SWITCH TRIGGERS WHEN BUTTON 7L IS PRESSED
		if(vexRT[Btn7L] == 1)
		{
			//Turn off tasks
			stopTask(teleop);
			stopTask(auton);

			//Shut down motors (if needed)
			stopMotor(leftMotor);
			stopMotor(rightMotor);
			stopMotor(leftLift);
			stopMotor(leftMotor);
			stopMotor(centerLift);
			motor[leftMotor] = 0;
			motor[rightMotor] = 0;
			motor[leftLift] = 0;
			motor[rightLift] = 0;
			motor[centerLift] = 0;

		}

		//Repeat the cycle every 25ms - sleeping give processor time to other tasks
		sleep(25);

	}

}
