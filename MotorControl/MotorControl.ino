#include "Defines.h"
#include "MotorStructure.h"
#include <Arduino.h>

using namespace std;

///////////////////////   Arduino ///////////////////////

//******* POT to control a stepper speed and direction ******//

String readString;
String Echo;
String OneTwo;
String ThreeFourFiveSix;

//char strValue[MAX_LEN - 1];
int index = 0;
int intThreeFourFiveSix = 0;

String strValue = "";

int position_X1 = 0;
int position_Y1 = 0;
int position_Z1 = 0;
int position_Z2 = 0;
int position_Z3 = 0;

int actual_position_X1 = 0;
int actual_position_Y1 = 0;
int actual_position_Z1 = 0;
int actual_position_Z2 = 0;
int actual_position_Z3 = 0;

//declare values
int Homing_Speed_X1 = 80;       //step speed (delay between steps)
int Homing_Speed_Y1 = 80;       //step speed (delay between steps)  
int Homing_Speed_Z1 = 80;       //step speed (delay between steps)  
int Homing_Speed_Z2 = 80;       //step speed (delay between steps)  
int Homing_Speed_Z3 = 80;       //step speed (delay between steps)  

int Speed_X1 = 5000;
int Speed_Y1 = 10000;
int Speed_Z1 = 1500;
int Speed_Z2 = 1500;
int Speed_Z3 = 1500;

int val = 0;
int j = 0;

// Initializing motors
Motor Motor_X(PIN_STEP_X, PIN_DIR_X, PIN_ENABLE_X, PIN_LMSWITCH_X, MAX_POSITION_X, MM_PER_STEP_X, SUB_STEP_NUMBER_X, MAX_SPEED_X, HOMING_DELAY_X, false);
Motor Motor_Y(PIN_STEP_Y, PIN_DIR_Y, PIN_ENABLE_Y, PIN_LMSWITCH_Y, MAX_POSITION_Y, MM_PER_STEP_Y, SUB_STEP_NUMBER_Y, MAX_SPEED_Y, HOMING_DELAY_Y, false);
Motor Motor_Z1(PIN_STEP_Z1, PIN_DIR_Z1, PIN_ENABLE_Z1, PIN_LMSWITCH_Z1, MAX_POSITION_Z1, MM_PER_STEP_Z1, SUB_STEP_NUMBER_Z1, MAX_SPEED_Z1, HOMING_DELAY_Z1, true);
Motor Motor_Z2(PIN_STEP_Z2, PIN_DIR_Z2, PIN_ENABLE_Z2, PIN_LMSWITCH_Z2, MAX_POSITION_Z2, MM_PER_STEP_Z2, SUB_STEP_NUMBER_Z2, MAX_SPEED_Z2, HOMING_DELAY_Z2, true);
Motor Motor_Z3(PIN_STEP_Z3, PIN_DIR_Z3, PIN_ENABLE_Z3, PIN_LMSWITCH_Z3, MAX_POSITION_Z3, MM_PER_STEP_Z3, SUB_STEP_NUMBER_Z3, MAX_SPEED_Z3, HOMING_DELAY_Z3, true);

/*Motor Motor_X = { 0, 0, 0, 0, HOMING_SPEED_X, PIN_STEP_X, PIN_DIR_X, PIN_ENABLE_X, PIN_LMSWITCH_X, 0, MAX_POSITION_X, MM_PER_STEP_X, SUB_STEP_NUMBER_X, LOW, HIGH, MAX_DELAY_X, MAX_RAMP_X, CRUISE_SPEED_DELAY_X };
Motor Motor_Y = { 0,0,0,0,HOMING_SPEED_Y,PIN_STEP_Y,PIN_DIR_Y,PIN_ENABLE_Y,PIN_LMSWITCH_Y,0,MAX_POSITION_Y,MM_PER_STEP_Y,SUB_STEP_NUMBER_Y,LOW, HIGH,MAX_DELAY_Y,MAX_RAMP_Y,CRUISE_SPEED_DELAY_Y};
Motor Motor_Z1 = { 0,0,0,0,HOMING_SPEED_Z1,PIN_STEP_Z1,PIN_DIR_Z1,PIN_ENABLE_Z1,PIN_LMSWITCH_Z1,0,MAX_POSITION_Z1,MM_PER_STEP_Z1,SUB_STEP_NUMBER_Z1,HIGH,LOW,MAX_DELAY_Z1,MAX_RAMP_Z1,CRUISE_SPEED_DELAY_Z1 };
Motor Motor_Z2 = { 0,0,0,0,HOMING_SPEED_Z2,PIN_STEP_Z2,PIN_DIR_Z2,PIN_ENABLE_Z2,PIN_LMSWITCH_Z2,0,MAX_POSITION_Z2,MM_PER_STEP_Z2,SUB_STEP_NUMBER_Z2,HIGH,LOW,MAX_DELAY_Z2,MAX_RAMP_Z2,CRUISE_SPEED_DELAY_Z2 };
Motor Motor_Z3 = { 0,0,0,0,HOMING_SPEED_Z3,PIN_STEP_Z3,PIN_DIR_Z3,PIN_ENABLE_Z3,PIN_LMSWITCH_Z3,0,MAX_POSITION_Z3,MM_PER_STEP_Z3,SUB_STEP_NUMBER_Z3,HIGH,LOW,MAX_DELAY_Z3,MAX_RAMP_Z3,CRUISE_SPEED_DELAY_Z3 };
*/

void setup() {

	// Initializing motor maximum positions in substeps
	//Motor_X.setMaxPositionSubsteps((String)MAX_POSITION_X);
	//Motor_Y.setMaxPositionSubsteps((String)MAX_POSITION_Y);
	//Motor_Z1.setMaxPositionSubsteps((String)MAX_POSITION_Z1);
	//Motor_Z2.setMaxPositionSubsteps((String)MAX_POSITION_Z2);
	//Motor_Z3.setMaxPositionSubsteps((String)MAX_POSITION_Z3);

	//Stepper(200,Step_X1,Dir_X1);
	Serial.begin(BAUD_RATE);	

	pinMode(PIN_STEP_X, OUTPUT);
	pinMode(PIN_DIR_X, OUTPUT);
	pinMode(PIN_ENABLE_X, OUTPUT);
	pinMode(PIN_LMSWITCH_X, INPUT);

	pinMode(PIN_STEP_Y, OUTPUT);
	pinMode(PIN_DIR_Y, OUTPUT);
	pinMode(PIN_ENABLE_Y, OUTPUT);
	pinMode(PIN_LMSWITCH_Y, INPUT);

	pinMode(PIN_STEP_Z1, OUTPUT);
	pinMode(PIN_DIR_Z1, OUTPUT);
	pinMode(PIN_ENABLE_Z1, OUTPUT);
	pinMode(PIN_LMSWITCH_Z1, INPUT);

	pinMode(PIN_STEP_Z2, OUTPUT);
	pinMode(PIN_DIR_Z2, OUTPUT);
	pinMode(PIN_ENABLE_Z2, OUTPUT);
	pinMode(PIN_LMSWITCH_Z2, INPUT);

	pinMode(PIN_STEP_Z3, OUTPUT);
	pinMode(PIN_DIR_Z3, OUTPUT);
	pinMode(PIN_ENABLE_Z3, OUTPUT);
	pinMode(PIN_LMSWITCH_Z3, INPUT);
	// Reserving space for string
	strValue.reserve(128);

	// Disables all motor for now:
	Motor_X.stop();
	Motor_Y.stop();
	Motor_Z1.stop();
	Motor_Z2.stop();
	Motor_Z3.stop();
}

void homing_all_5_axis() {

	Motor_Z1.goHome();

	Motor_Z2.goHome();

	Motor_Z3.goHome();

	Motor_X.goHome();

	Motor_Y.goHome();
}


void loop()
{
	if (commandReceivedFlag == 1)
	{
		commandReceivedFlag = 0;
		
		char cmd = strValue.charAt(0);
	
		switch (cmd)	//strValue[0])
		{
		case 'X':
		{
			String temp = strValue.substring(strValue.indexOf('X') + 1);

			Serial.print("Going to X: ");
			Serial.println(temp);
			
			//Motor_X.moveTrapezoidally(temp, 1, 180);

			Motor_X.moveToWithTriangularSpeedProfile(temp);

			break;
		}
		case 'Y':
		{
			String temp = strValue.substring(strValue.indexOf('Y') + 1);
			Motor_Y.setDesiredPositionSubsteps(temp);
			Serial.print("Going to Y: ");
			Serial.println(temp);
			
			Motor_Y.moveToWithTriangularSpeedProfile(temp);

			break;
		}
		case 'Z':
		{
			char zAxisNumber = strValue[1];

			if (zAxisNumber == '1')
			{
				String temp = strValue.substring(strValue.indexOf('1') + 1);
				Serial.print("Going to Z1: ");
				Serial.println(temp);

				Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			}
			else if (zAxisNumber == '2')
			{
				String temp = strValue.substring(strValue.indexOf('2') + 1);
				Serial.print("Going to Z2: ");
				Serial.println(temp);
				Motor_Z2.moveToWithTriangularSpeedProfile(temp);
			}
			else if (zAxisNumber == '3')
			{
				String temp = strValue.substring(strValue.indexOf('3') + 1);
				Serial.print("Going to Z3: ");
				Serial.println(temp);

				Motor_Z3.moveToWithTriangularSpeedProfile(temp);
			}
			break;
		}
		case 'H':	// Homing
		{
			char homeAxis = strValue[1];

			if (homeAxis == 'X')
			{
				Serial.println(F("Homing X axis: "));
				Motor_X.goHome();
			}
			else if (homeAxis == 'Y')
			{
				Serial.println(F("Homing Y axis: "));
				Motor_Y.goHome();
			}
			else if (homeAxis == 'Z')
			{
				char zAxisNumber = strValue[2];

				if (zAxisNumber == '1')
				{
					Serial.println(F("Homing Z1 axis: "));
					Motor_Z1.goHome();
				}
				else if (zAxisNumber == '2')
				{
					Serial.println(F("Homing Z2 axis: "));
					Motor_Z2.goHome();
				}
				else if (zAxisNumber == '3')
				{
					Serial.println(F("Homing Z3 axis: "));
					Motor_Z3.goHome();
				}
			}
			else
			{
				homing_all_5_axis();
			}
			break;
		}
		case 'M':	// Picking up pipettes (multi), going pick liquid and diluting in 96 well plates
		{
			
			homing_all_5_axis();
			String temp;
			//****************************************
			// Going pick up pipettes tips
			temp = "3035"; 
			Motor_X.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			temp = "6270";
			Motor_Y.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			temp = "3690";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(1000);

			temp = "2500";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			//****************************************
			// Liquid bucket
			temp = "300";
			Motor_X.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			temp = "4500";	// TODO: modify
			Motor_Y.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			temp = "3730";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(5000);

			temp = "3000";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			//****************************************
			// Row 1
			temp = "1500";
			Motor_X.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			temp = "3700";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(6000);

			temp = "3550";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			//****************************************
			// Row 2
			temp = "1589";
			Motor_X.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			temp = "3700";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(6000);

			temp = "3550";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			//****************************************
			// Row 3
			temp = "1678";
			Motor_X.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			temp = "3700";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(6000);

			temp = "3550";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			//****************************************
			// Row 4
			temp = "1767";
			Motor_X.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			temp = "3700";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(6000);

			temp = "3550";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			//****************************************
			// Row 5
			temp = "1856";
			Motor_X.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			temp = "3700";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(6000);

			temp = "3550";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			//****************************************
			// Row 6
			temp = "1945";
			Motor_X.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			temp = "3700";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(6000);

			temp = "3550";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			//****************************************
			// Row 7
			temp = "2034";
			Motor_X.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			temp = "3700";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(6000);

			temp = "3550";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			//****************************************
			// Row 8
			temp = "2123";
			Motor_X.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			temp = "3700";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(6000);

			temp = "3550";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			//****************************************
			// Row 9
			temp = "2212";
			Motor_X.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			temp = "3700";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(6000);

			temp = "3550";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			//****************************************
			// Row 10
			temp = "2301";
			Motor_X.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			temp = "3700";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(6000);

			temp = "3550";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			//****************************************
			// Row 11
			temp = "2390";
			Motor_X.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			temp = "3700";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(6000);

			temp = "3550";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			//****************************************
			// Row 12
			temp = "2479";
			Motor_X.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			temp = "3700";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(6000);

			temp = "1700";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			//****************************************
			// Going to trash
			temp = "0";
			Motor_X.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			temp = "1150";	// TODO: modify
			Motor_Y.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			temp = "2935";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(1000);

			temp = "270";
			Motor_X.moveToWithTriangularSpeedProfile(temp);
			delay(1000);

			temp = "200";
			Motor_Z1.moveToWithTriangularSpeedProfile(temp);
			delay(500);

			homing_all_5_axis();

			break;
		}
		case 'I':	// dilution demo
		{
			homing_all_5_axis();
			String temp;
			//****************************************
			// Go take pipette 1
			temp = "1660"; // Send robot to 95cm from home on the X axis.
			//Motor_X.setDesiredPositionSubsteps(temp);
			Motor_X.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "6610";
			//Motor_Y.setDesiredPositionSubsteps(temp);
			Motor_Y.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "2885";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "400";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			//****************************************
			// Go make dilution for demo purposes
			temp = "4200"; // Send robot to 95cm from home on the X axis.
			//Motor_X.setDesiredPositionSubsteps(temp);
			Motor_X.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			// First hole
			temp = "4000";
			//Motor_Y.setDesiredPositionSubsteps(temp);
			Motor_Y.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "2700";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);
			delay(10000);

			temp = "2400";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);
			delay(200);

			// Second hole
			temp = "3600";
			//Motor_Y.setDesiredPositionSubsteps(temp);
			Motor_Y.moveToWithTriangularSpeedProfile(temp);
			delay(200);

			temp = "2700";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);
			delay(10000);

			temp = "2400";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);
			delay(200);

			// Going back to first hole
			temp = "4000";
			//Motor_Y.setDesiredPositionSubsteps(temp);
			Motor_Y.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "2800";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);
			delay(10000);

			temp = "2400";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);
			delay(200);

			// Third hole
			temp = "3400";
			//Motor_Y.setDesiredPositionSubsteps(temp);
			Motor_Y.moveToWithTriangularSpeedProfile(temp);
			delay(200);

			temp = "2700";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);
			delay(10000);

			temp = "2400";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			// Fourth hole
			temp = "3200";
			//Motor_Y.setDesiredPositionSubsteps(temp);
			Motor_Y.moveToWithTriangularSpeedProfile(temp);
			delay(200);

			temp = "2700";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);
			delay(10000);

			temp = "2400";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			//****************************************
			// Go to trash for pipette 1
			temp = "100";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);

			temp = "2700"; // Send robot to 95cm from home on the X axis.
			//Motor_X.setDesiredPositionSubsteps(temp);
			Motor_X.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "1700";
			//Motor_Y.setDesiredPositionSubsteps(temp);
			Motor_Y.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "2180";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "2915";
			//Motor_X.setDesiredPositionSubsteps(temp);
			Motor_X.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "100";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			homing_all_5_axis();
			break;
		}
		case 'D':	// Grabbing and trashing pipettes demo
		{
			homing_all_5_axis();
			delay(1000);
			String temp = "";

			//****************************************
			// Go take pipette 1
			temp = "1660"; // Send robot to 95cm from home on the X axis.
			//Motor_X.setDesiredPositionSubsteps(temp);
			Motor_X.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "6610";
			//Motor_Y.setDesiredPositionSubsteps(temp);
			Motor_Y.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "2885";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "100";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			//****************************************
			// Go to trash for pipette 1
			temp = "2700"; // Send robot to 95cm from home on the X axis.
			//Motor_X.setDesiredPositionSubsteps(temp);
			Motor_X.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "1700";
			//Motor_Y.setDesiredPositionSubsteps(temp);
			Motor_Y.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "2180";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "2915";
			//Motor_X.setDesiredPositionSubsteps(temp);
			Motor_X.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "100";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			//****************************************
			// Go take pipette 2
			temp = "2860"; // Send robot to 95cm from home on the X axis.
			//Motor_X.setDesiredPositionSubsteps(temp);
			Motor_X.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "6620";
			//Motor_Y.setDesiredPositionSubsteps(temp);
			Motor_Y.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "2980";//"2885";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "100";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			//****************************************
			// Go to trash for pipette 2
			temp = "2700"; // Send robot to trash X level but keeping a safe area to go down
			//Motor_X.setDesiredPositionSubsteps(temp);
			Motor_X.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "1702";	// Getting to Y position of fork to remove pipette
			//Motor_Y.setDesiredPositionSubsteps(temp);
			Motor_Y.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "2090";	// going down to trash fork Z level
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "2955";	// Getting the pipette in the fork
			//Motor_X.setDesiredPositionSubsteps(temp);
			Motor_X.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "100";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			////****************************************
			// Go take pipette 3
			temp = "4075"; // Send robot to 95cm from home on the X axis.
			//Motor_X.setDesiredPositionSubsteps(temp);
			Motor_X.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "6630";
			//Motor_Y.setDesiredPositionSubsteps(temp);
			Motor_Y.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "3120";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "100";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			////****************************************
			// Go to trash for pipette 3
			temp = "2700"; // Send robot to 95cm from home on the X axis.
			//Motor_X.setDesiredPositionSubsteps(temp);
			Motor_X.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "1705";
			//Motor_Y.setDesiredPositionSubsteps(temp);
			Motor_Y.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "2000";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "3020";
			//Motor_X.setDesiredPositionSubsteps(temp);
			Motor_X.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			temp = "100";
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			Motor_Z3.moveToWithTriangularSpeedProfile(temp);

			delay(500);

			//temp = "100"; // Send robot to 95cm from home on the X axis.
			//Motor_Z3.setDesiredPositionSubsteps(temp);
			//Motor_Z3.moveToWithTriangularSpeedProfile();
			
			homing_all_5_axis();
			break;
		}
		default:
			break;
		}
		strValue = "";	// Clearing string content to reset command analysis
	}
}


/*
SerialEvent occurs whenever a new data comes in the
hardware serial RX.  This routine is run between each
time loop() runs, so using delay inside loop can delay
response.  Multiple bytes of data may be available.
*/
void serialEvent() 
{
	while (Serial.available()) {
		// get the new byte:
		char inChar = (char)Serial.read();

		if ((inChar >= 48 && inChar <= 122) || inChar == 10 || inChar == 13)
		{
			// add it to the inputString:
			strValue += inChar;
		}		
		// if the incoming character is a newline, set a flag
		// so the main loop can do something about it:
		if (inChar == '\n') 
		{
			// If the instruction is asking for information, we treat it right away, otherwise we simply buff the instruction.
			char cmd = strValue.charAt(0);

			if (cmd == 'P')
			{
				char pingAxis = strValue[1];

				if (pingAxis == 'X')
				{
					Serial.print(F("Current position of the X axis: "));
					Serial.print(Motor_X.getCurrentPos());
					Serial.println();
				}
				else if (pingAxis == 'Y')
				{
					Serial.print(F("Current position of the Y axis: "));
					Serial.print(Motor_Y.getCurrentPos());
					Serial.println();
				}
				else if (pingAxis == 'Z')
				{
					char zAxisNumber = strValue[2];

					if (zAxisNumber == '1')
					{
						Serial.print(F("Current position of the Z1 axis: "));
						Serial.print(Motor_Z1.getCurrentPos());
						Serial.println();
					}
					else if (zAxisNumber == '2')
					{
						Serial.print(F("Current position of the Z2 axis: "));
						Serial.print(Motor_Z2.getCurrentPos());
						Serial.println();
					}
					else if (zAxisNumber == '3')
					{
						Serial.print(F("Current position of the Z3 axis: "));
						Serial.print(Motor_Z3.getCurrentPos());
						Serial.println();
					}
				}
				strValue = "";
			}
			else
			{
				commandReceivedFlag = true;
			}	
			
			/*if (strValue.indexOf("Stop") != 0)
			{
				String motorToStop = strValue.substring(strValue.indexOf(":"));
			}*/
		}
	}
}
