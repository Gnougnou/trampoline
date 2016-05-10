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

TASK(task_hello)
{
	TaskType taskID;
	GetTaskID(&taskID);
    printf("Tache %d Bonjour ! \n", taskID);
	TerminateTask();
}
