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

// Aucune difference avec le 1 ???

TASK(Task0)
{
	TaskType taskID;
	GetTaskID(&taskID);
    printf("Tache %d Bonjour ! \n", taskID);
    printf("Avant Activate \n");
	ActivateTask(Task1);
	printf("Après Activate \n");
	TerminateTask();
}
