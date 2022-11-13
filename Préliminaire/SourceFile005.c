/* 
Un  peu  de  programmation  multitâche.  On fixe  le  gyromètre  à la  brique  EV3.  
On écrit une tâche qui observe à 10 Hz la vitesse de rotation et garde en mémoire le min et le max. 
On écrit une deuxième tâche qui stocke dans un fichier la vitesse observée toutes les minutes. 
Enfin on écrit une troisième tâche qui observe le capteur de contact pour interrompre le programme
lorsqu’on appuie dessus. 
Le min et le max devront être sauvegardés à la fin du fichier des vitesses observées avant de quitter le programme.

*/
int min, max, val;
string s_min,s_max,s_val;
long fileHandle;
TSemaphore mutexMinMax;

// tache watch qui va observer le gyrometre at va garde en mémoire le min et le max.
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
//tache qui  observe le capteur de contact pour interromprele programme lorsqu’on appuie dessus.
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

