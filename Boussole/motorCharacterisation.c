#pragma config(Motor,  motorA,          motoraa,       tmotorEV3_Medium, PIDControl, encoder)

int tab[101];
long fileHandle;
void motorCharacterisation(){

	resetMotorEncoder(motoraa);
		for(int puissance = 0; puissance<=100; puissance++){


			setMotorSpeed(motoraa, puissance);
			delay(300);
			tab[puissance]= getMotorRPM(motoraa)*360/60;
		}


		string filename = "motorVitesse1.csv";
		fileHandle =fileOpenWrite(filename);
		string viS;
		string puS;
		for(int i=0; i<=100;i++){
			stringFormat(puS, "%d\t%d\n",i,tab[i]);
			fileWriteData (fileHandle,puS, strlen(puS));
		}
		fileClose(fileHandle);
}

task main()
{

motorCharacterisation();


}
