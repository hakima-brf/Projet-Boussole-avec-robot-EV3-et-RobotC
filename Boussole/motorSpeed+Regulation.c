/*
on fixe les valeures de la vitesse maximale et la pente de la droite passant par les points(0,0)
 et (maxPower,maxSpeed)

 */
#define MAXSPEED 880
#define PENTE 9.67


void launchMotorSpeed(int speed){
	//si la vitesse donnée est supérieure à la vitesse maximale on tourne le moteur à la vitesse maximale prédefinie
	if (abs(speed)>MAXSPEED){
		setMotorSpeed(motorD, MAXSPEED/PENTE);
	}else
	    // si la vitesse donnée est inférieur à la vitesse maximale on tourne le moteur à la vitesse donnée
		setMotorSpeed(motorD, speed/PENTE);
		delay(500);
}





//Régulation

TSemaphore mutexCons;
int consigne =0 ;
int consigne2;
int capMotor;
int vitesseAngulaire,speed;
int p =1;
int d =-0.01;




task watchbuttons(){
	while(1){
if(getButtonPress(buttonEnter)==1) stopAllTasks();
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



task keepheadingPD(){
	while(1){
	vitesseAngulaire=getMotorRPM(motorA)*6;

 semaphoreLock(mutexCons);
 consigne2=consigne;
 semaphoreUnlock(mutexCons);
 speed = p*(consigne - capMotor)+vitesseAngulaire*d;
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
	capMotor = getMotorEncoder(motorA);




	semaphoreLock(mutexCons);


	displayTextLine(1, "consigne=%d", consigne);
	semaphoreUnlock(mutexCons);
	displayTextLine(2, "cap =%d", capMotor);


}}












task main()
{


resetMotorEncoder(motorA);
semaphoreInitialize(mutexCons);
startTask(watchbuttons);
startTask(keepheadingPD);
startTask(IHM);
while(1){}


}
