#pragma config(Sensor, S3,     ,               sensorEV3_Gyro)
#pragma config(Motor,  motorA,          motoraa,       tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
task IHM1;
task watchbuttons;
task watchbuttons2;
task IHM;
task IHM2;
task IHM3;
task choixRobot;
task keepheadingPD;
task keepheadingPD2;

bool a;
bool b ;
bool c ;
//interface

int consignefixe=0 ;
int consigne, consigne2;
TSemaphore mutexCons;
int capGyro,capMotor;
int vitesseAngulaireGyro,vitesseAngulaireMotor,speed;
int p =1;
int d =-0.01;

//interface explicative du choix du rebot
task IHM1(){
	while(1){
	displayTextLine(1, "robot fixe :boutton gauche");
	displayTextLine(2, "robot mobile:boutton droit");
	displayTextLine(3, "           ");
}}

// robot fixe avec consigne à préciser

void launchMotor(int s){
	if(abs(s)>880){
		setMotorSpeed(motorA, 880/9.56);
	}
	else{
		setMotorSpeed(motorA, s);
	}
}


task keepheadingPD{
	while(b){
	vitesseAngulaireMotor=getMotorRPM(motorA)*6;
	capMotor = getMotorEncoder(motorA);
 semaphoreLock(mutexCons);
 consigne2=consigne;
 semaphoreUnlock(mutexCons);
 speed = p*(consigne - capMotor)+vitesseAngulaireMotor*d;
	if (fabs(consigne-capMotor)>1){
		launchMotor(speed);
	}
	else{
			setMotorSpeed(motorA, 0);
		}


	}
	delay(500);
}

task IHM(){
while(1){
	stopTask(IHM3);
	capMotor = getMotorEncoder(motorA);
	displayTextLine(1, "pour quitter:boutton centrale");
	semaphoreLock(mutexCons);
	displayTextLine(2, "consigne=%d", consigne);
	semaphoreUnlock(mutexCons);
	displayTextLine(3, "cap =%d", capMotor);
  displayTextLine(4, "                   ");

}}

task watchbuttons(){
	b=True;
	while(b){
if(getButtonPress(buttonEnter)==1){
	b=false;
	startTask(IHM1);
	while(getButtonPress(buttonEnter)==1){}
}
  if(getButtonPress(buttonRight)==1){
  	semaphoreLock(mutexCons);
	  consigne+=10;
  	semaphoreUnlock(mutexCons);
	  while(getButtonPress(buttonRight)==1){}

  	}

  if(getButtonPress(buttonLeft)==1){
  	semaphoreLock(mutexCons);
	  consigne-=10;
  	semaphoreUnlock(mutexCons);
while(getButtonPress(buttonLeft)==1){}
  	}
  if(getButtonPress(buttonUp)==1){
  	semaphoreLock(mutexCons);
	  consigne+=90;
  	semaphoreUnlock(mutexCons);
	   while(getButtonPress(buttonUp)==1){}
  	}

 if(getButtonPress(buttonDown)==1){
  	semaphoreLock(mutexCons);
	  consigne-=90;
  	semaphoreUnlock(mutexCons);
	   while(getButtonPress(buttonDown)==1){}
  	}
}
}






// rebot mobile à consigne fixe =0
void launchMotorSpeed2(int s){
	if(abs(s)>500){
		setMotorSpeed(motorA, 500/11.11);
	}
	else{
		setMotorSpeed(motorA, s);
	}}

task keepheadingPD2(){
	while(c){
	vitesseAngulaireGyro=getGyroRate(S3)*6;
	capGyro =getGyroDegrees(S3) ;
 speed = p*(consigne-capGyro)+vitesseAngulaireGyro*d;
	if (fabs(consigne-capGyro)>1){
		launchMotorSpeed2(speed);
	}
	else{
			setMotorSpeed(motorA, 0);
		}
	}
}




task IHM2(){
while(c){
	stopTask(IHM3);
	capGyro =getGyroDegrees(S3) ;


	displayTextLine(1, "pour quitter:boutton centrale");

	displayTextLine(2, "consigne=%d", consigne);

	displayTextLine(3, "cap =%d", capGyro);
	displayTextLine(4, "                   ");


}}


task watchbuttons2(){
	c=true;
	while(c){
if(getButtonPress(buttonEnter)==1){
	c=False;
	startTask(IHM1);
	while(getButtonPress(buttonEnter)==1){}

}}}





task IHM3(){
	// explication de signification des bouttons pour la fonction initialize()
	displayTextLine(1, "pisitionement du rebot");
	displayTextLine(2, "pour quitter:boutton centrale");
	displayTextLine(3, "turn left:boutton gauche");
	displayTextLine(4, "turn right: boutton droit");
}
void initialize(){
	a = True;
	while(a){

	//arret du programme sur appui du boutton centrale
	if(getButtonPress(buttonEnter)==1){
		a=False;
		setMotorSpeed(motorA,0);
	}
	//tourner le moteur de 20° vers la droite quend on appui sur le boutton droit
    if(getButtonPress(buttonRight)==1){
  		setMotorSpeed(motorA,20);
	 	while(getButtonPress(buttonRight)==1){}
  	}
  	//tourner le moteur de 20° vers la droite quend on appui sur le boutton droit
    if(getButtonPress(buttonLeft)==1){
  		setMotorSpeed(motorA,-20);
     while(getButtonPress(buttonLeft)==1){}
  	}
}}

task choixRobot(){
	while(1){
//declancher les demarches du rebot mobile
	if(getButtonPress(buttonRight)==1){
		stopTask(IHM1);
		startTask(IHM3);
		initialize();
		waitForButtonPress() ;
		startTask(watchbuttons2);
    startTask(keepheadingPD2);
    startTask(IHM2);
    while(getButtonPress(buttonRight)==1){}
	}
	//declancher les demarches du rebot fixe
	if(getButtonPress(buttonLeft)==1){
	 stopTask(IHM1);
	 startTask(IHM3);
	 initialize();
	 waitForButtonPress() ;
	 startTask(watchbuttons);
   startTask(keepheadingPD);
   startTask(IHM);
		while(getButtonPress(buttonLeft)==1){}

	}

	while (getTouchValue(S1)==0){}
		stopAllTasks();

}}



task main()
{
resetGyro(S3);
resetMotorEncoder(motoraa);
semaphoreInitialize(mutexCons);
startTask(IHM1);
startTask(choixRobot);

while(1){}

}
