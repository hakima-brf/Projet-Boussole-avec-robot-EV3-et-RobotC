/*
On va utiliser maintenant les boutons de la brique pour commander le moteur.
Le bouton droit sert à faire tourner le moteur dans le sens des aiguilles d’une montre. 
Le bouton gauche sert à faire tourner le moteur dans l’autre sens. 
Le bouton haut sert à accélérer le mouvement. 
Le bouton bas sert à ralentir le mouvement. 
La puissance moteur va de 0 à 100, la diminution ou l’augmentation se fera par pas de 10.

*/
task main()
{

int puissance = 20; //on ititialise la puissance à 20
int sens;

while(getButtonPress(buttonEnter)==0){
	
  //si on clique sur le bouton droit le moteur tourne dans le sens des aiguilles d’une montre
  
  if(getButtonPress(buttonRight)==1){
  	sens =1;
  	setMotorSpeed(motorA,sens*puissance);
  	while(getButtonPress(buttonRight)==1){}
  	}
  	
  //si on clique sur le bouton gauche le moteur tourne dans le sens inverse des aiguilles d’une montre

  if(getButtonPress(buttonLeft)==1){
  	sens=-1; //on change le sens de rotation de moteur
  	setMotorSpeed(motorA,sens*puissance);
  	while(getButtonPress(buttonLeft)==1){}
  	}
  	
  //si on clique sur Le bouton haut le mouvement du moteur accélére d'un pas de 10 sans dépasser 100
  	
  if(getButtonPress(buttonUp)==1){
  	puissance=(puissance+10)%100;
  	setMotorSpeed(motorA,sens*puissance);
  	while(getButtonPress(buttonUp)==1){}
  	}
  	
  //si on clique sur Le bouton bas le mouvement du moteur diminue d'un pas de 10 sans dépasser 0
  	
  if(getButtonPress(buttonDown)==1){
  	puissance=(puissance-10)%100;
  	if(puissance<0) puissance=0;
  	setMotorSpeed(motorA,sens*puissance);
  	while(getButtonPress(buttonDown)==1){}
  	}

}
 	setMotorSpeed(motorA,0);
 	delay(500);


}

