TSemaphore mutexCons; //on initialise une semaphore car la consigne une variable utilisée en écriture par
// watchButtons() et en lecture parkeepHeading().
float consigne =0 ; // on initialise la consigne à 0
int cap=0; //  le cap atteint par le moteur on l'initialise mnt à 0


// tache qui scrute les boutons de la brique pour faire le  suivi  de  consigne
task watchbuttons(){
	while(1){
if(getButtonPress(buttonEnter)==1) stopAllTasks(); //on arrete le programme sur appui du bouton centrale

  //si on appuit sur le bouton droit on ajoute 10 à la consigne afin que le moteur tourne de 10° vers la droite
  if(getButtonPress(buttonRight)==1){
  	//on utilise la semaphore à chaque acces à la consigne car c'est une ressource partagée
  	semaphoreLock(mutexCons);
	  consigne+=10;
  	semaphoreUnlock(mutexCons);
	while(getButtonPress(buttonRight)==1){}
  	}
  	
  //si on appuit sur le bouton gauche on ajoute -10° à la consigne afin que le moteur tourne de 10° vers la gauche
  if(getButtonPress(buttonLeft)==1){
  	semaphoreLock(mutexCons);
	  consigne-=10;
  	semaphoreUnlock(mutexCons);
    while(getButtonPress(buttonLeft)==1){}
  	}
  	
  //si on appuit sur le bouton haut on ajoute 90° à la consigne afin que le moteur tourne de 90° vers la droite
  if(getButtonPress(buttonUp)==1){
  	semaphoreLock(mutexCons);
	  consigne+=90;
  	semaphoreUnlock(mutexCons);
	   while(getButtonPress(buttonUp)==1){}
  	}
  	
  //si on appuit sur le bouton bas on ajoute -90° à la consigne afin que le moteur tourne de 90° vers la gauche
 if(getButtonPress(buttonDown)==1){
  	semaphoreLock(mutexCons);
	  consigne-=90;
  	semaphoreUnlock(mutexCons);
	   while(getButtonPress(buttonDown)==1){}
  	}
}
}

// tache qui effectue en boucle le changement de consigne
task keepheading(){
	bool consignechanged = false; //on initialise un variable pour determiner quand la consigne a changé
	float consigne2;  //consigne2 va prendre la valeur de consigne

	while(1){
 semaphoreLock(mutexCons);
 //si la consigne mémorisé dans consigne2 est diffrente de la consigne actuelle on met a jour la consigne 
 	if(consigne2 != consigne){
		consigne2 = consigne;
		consignechanged = true;
	}else{
	consignechanged = false;
	}
	//si la consigne a changé on envoie la commande au moteur
	if (consignechanged && fabs(consigne2-getMotorEncoder(motorA))>1) 	setMotorTarget(motorA,consigne2,20);
		semaphoreUnlock(mutexCons);

	}
	delay(500);
}

/*
tache qui explique à l'utilisateur à quoi servent les boutons et qui affiche la consigne ainsi que le cap 
atteint par le moteur.
*/
task IHM(){
while(1){
	cap = getMotorEncoder(motorA);
	semaphoreLock(mutexCons);
	displayTextLine(1, "consigne=%d", consigne);
	semaphoreUnlock(mutexCons);
	displayTextLine(2, "cap =%d", cap);
}
}


task main()
{
resetMotorEncoder(motorA);
semaphoreInitialize(mutexCons);
startTask(watchbuttons);
startTask(keepheading);
startTask(IHM);
while(1){}
}

