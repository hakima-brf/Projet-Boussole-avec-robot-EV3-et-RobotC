/*
On d�marre le moteur dans un sens sur appui sur le capteur de contact. 
Ensuite on change  de  sens  � chaque  appui  sur  le  capteur  de  contact.
Deux  appuis  rapproch�s signifiant l'arr�t du moteur.
*/
task main()
{
//pour deux appuis rapproch�s le moteur s'arrete
long t1,t2;
int sens = 1;
t1 = nSysTime - 1000;
t2 = nSysTime - 500;

while (t2-t1>300){ //on fait la diffrence de t1 et  t2 pour determiner quand on a pas deux appuis rapproch�s
   while (getTouchValue(S1)==0){}
   t1=t2;
   t2 = nSysTime;
   sens = - sens;
   setMotorSpeed(motorA,sens*20);
   while (getTouchValue(S1)==1){}
}
setMotorSpeed(motorA,0); // on arrete le moteur quand on a  deux appuis rapproch�s cad t2-t1<300
delay(500);
}

