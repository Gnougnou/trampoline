#include <stdio.h>
#include "tpl_os.h"

int main(void)
{
    StartOS(OSDEFAULTAPPMODE);
    return 0;
}


void PreTaskHook() {
	TaskType taskID;
	GetTaskID(&taskID);
	printf("Tache %d PreTaskHook \n", taskID);
}

void PostTaskHook() {
	TaskType taskID;
	GetTaskID(&taskID);
	printf("Tache %d PostTaskHook \n", taskID);
}



TASK(Task1)
{
	TaskType taskID;
	GetTaskID(&taskID);
    printf("Tache %d Bonjour ! \n", taskID);
	TerminateTask();
}

// Chaintask terminate la task en cours et lance la suivante
// d'où l'absence du "après activate" dans task0
TASK(Task0)
{
	TaskType taskID;
	GetTaskID(&taskID);
    printf("Tache %d Bonjour ! \n", taskID);
    printf("Avant Activate \n");
	ChainTask(Task1);
	printf("Après Activate \n");
	TerminateTask();
}
