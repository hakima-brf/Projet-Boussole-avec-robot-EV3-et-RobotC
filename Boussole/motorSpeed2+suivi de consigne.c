
int consigne =0 ;
int cap;
int vitesseAngulaire,speed;
int p =1;
int d =-0.01;


void launchMotorSpeed2(int s){
	if(abs(s)>500){
		setMotorSpeed(motorA, 500/11.11);
	}
	else{
		setMotorSpeed(motorA, s);
	}
}




task watchbuttons2(){
	while(1){
if(getButtonPress(buttonEnter)==1) stopAllTasks();

}
}


task keepheadingPD2(){
	while(1){
	vitesseAngulaire=getGyroRate(S3)*6; //la vitesse de rotation delivres par le gyromètre
	cap =getGyroDegrees(S3) ; // le cap 
 speed = p*(consigne-cap)+vitesseAngulaire*d; //regle de régulation
	if (fabs(consigne-cap)>1){ //si la consigne est diffrente du cap actuel on lance le moteur 
		launchMotorSpeed2(speed);
	}
	else{
			setMotorSpeed(motorA, 0);
		}
	}
}




task IHM2(){
while(1){
	cap =getGyroDegrees(S3) ;

	displayTextLine(1, "pour quitter:boutton centrale");

	displayTextLine(3, "consigne=%d", consigne); //affiche la consigne

	displayTextLine(4, "cap =%d", cap);//affiche le cap


}}

void initialize(){
	while(1){
	displayTextLine(5, "pour quitter:boutton centrale");

	displayTextLine(6, "turn left:boutton gauche");

	displayTextLine(7, "turn right: boutton droit");

	if(getButtonPress(buttonEnter)==1) stopAllTasks();
  if(getButtonPress(buttonRight)==1){
  	setMotorSpeed(motorA,20);
	  while(getButtonPress(buttonRight)==1){}

  	}

  if(getButtonPress(buttonLeft)==1){
  	setMotorSpeed(motorA,-20);

while(getButtonPress(buttonLeft)==1){}
  	}
}}



task main()
{
resetGyro(S3);

startTask(watchbuttons2);
startTask(keepheadingPD2);
startTask(IHM2);
initialize();

while(1){}


}
