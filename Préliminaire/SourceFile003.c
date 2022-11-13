/*
On démarre le moteur dans un sens sur appui sur le capteur de contact. 
Ensuite on change  de  sens  à chaque  appui  sur  le  capteur  de  contact.
Deux  appuis  rapprochés signifiant l'arrêt du moteur.
*/
task main()
{
//pour deux appuis rapprochés le moteur s'arrete
long t1,t2;
int sens = 1;
t1 = nSysTime - 1000;
t2 = nSysTime - 500;

while (t2-t1>300){ //on fait la diffrence de t1 et  t2 pour determiner quand on a pas deux appuis rapprochés
   while (getTouchValue(S1)==0){}
   t1=t2;
   t2 = nSysTime;
   sens = - sens;
   setMotorSpeed(motorA,sens*20);
   while (getTouchValue(S1)==1){}
}
setMotorSpeed(motorA,0); // on arrete le moteur quand on a  deux appuis rapprochés cad t2-t1<300
delay(500);
}

