/* 
Un  peu  de  programmation  multit�che.  On fixe  le  gyrom�tre  � la  brique  EV3.  
On �crit une t�che qui observe � 10 Hz la vitesse de rotation et garde en m�moire le min et le max. 
On �crit une deuxi�me t�che qui stocke dans un fichier la vitesse observ�e toutes les minutes. 
Enfin on �crit une troisi�me t�che qui observe le capteur de contact pour interrompre le programme
lorsqu�on appuie dessus. 
Le min et le max devront �tre sauvegard�s � la fin du fichier des vitesses observ�es avant de quitter le programme.

*/
int min, max, val;
string s_min,s_max,s_val;
long fileHandle;
TSemaphore mutexMinMax;

// tache watch qui va observer le gyrometre at va garde en m�moire le min et le max.
task watch(){
while(1){
	val=getGyroRate(S2);
	semaphoreLock(mutexMinMax);
	if(val<min) min=val;
	if(val>max) max=val;
	semaphoreUnlock(mutexMinMax);
	delay(100);
}
}
//tache write qui va ecrire qui va ecrire les valeurs du gyrometre dans le fichier toutes les minutes
task write(){
	while(1){
	val=getGyroRate(S2);
	semaphoreLock(mutexMinMax);
	if(val<min) min=val;
	if(val>max) max=val;
	semaphoreUnlock(mutexMinMax);
	stringFormat(s_val, "val = %ld\n", val);
	fileWriteData(fileHandle,s_val, strlen(s_val));
	delay(60000);
}
}
//tache qui  observe le capteur de contact pour interromprele programme lorsqu�on appuie dessus.
task halt(){
	while(getTouchValue(S1)==0){}
	stopTask(write);
	stopTask(watch);
	stringFormat(s_min, "min = %ld\n", min);
	stringFormat(s_max, "max = %ld\n", max);
	fileWriteData(fileHandle,s_min, strlen(s_min));
	fileWriteData(fileHandle,s_max, strlen(s_max));
	fileClose(fileHandle);
	stopAllTasks();
}

task main()
{

min= getGyroRate(S2);
max=min;
fileHandle = fileOpenWrite("GyroData");
semaphoreInitialize(mutexMinMax);
//on lance les taches
startTask(watch);
startTask(write);
startTask(halt);
while(1){}
}

