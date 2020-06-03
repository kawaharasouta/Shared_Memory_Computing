#include <stdio.h> /* For standard I/O functions¡ */
#include "pvm3.h" /* For stand pvm functions */

main(argc,argv)
int argc;
char **argv;
{
  int intervals; /* Number of intervals */
  int tasks; /* Number of tasks */
  int ctid[100]; /* task id (subtasks) */
	int num;
  int n; /* Number of intervals for one subtask */
  double s,t; /* Interval of tasks */
	double unit;
  double sum, results[100]; /* Results of subtasks */

  if(argc<=2){ /* Finish if no any parameter */
    printf("Usage:pi_dual intervals tasks\n");
    pvm_exit();
    exit(0);
  }

  sscanf(argv[1],"%d",&intervals); 
  sscanf(argv[2],"%d",&tasks); 
  /* Get the first parameter and put it into intervals */
  if(pvm_spawn("pi_slave",(char **) 0,0,"",2,ctid)!=2){
  /* Start two subtasks for executing slave program  
     pi_slave¡ Save the subtask ids into arry ctid */
    printf("an't start pi_slave\n"); /* Fail in starting the subtasks */
    pvm_exit();
    exit(0);
  }
	n=intervals/tasks; /* Interval for one subtask */
	unit=(double)1/tasks;
	num = 0;
	for (s=0;t=unit;s<=1.0;s+=unit,t+=unit) {
		pvm_initsend(0); /* Prepare for data sending */
  	pvm_pkint(&n, 1 ,1); /* Put the interval into the sending buffer */
  	pvm_pkdouble(&s, 1, 1); /* Put the value of s into the sending buffer */
  	pvm_pkdouble(&t, 1 ,1); /* Put the value of t into the sending buffer */
  	pvm_send(ctid[num], 1); 
		num++;
	}

	for (int i = 0; i <= num; i++) {
		pvm_recv(-1, 1); /* Waiting for receiving the data from the subtasks, 
 		        and put the data into the receiving buffer when received */
 		pvm_upkdouble(&result[i],1,1);  /* Put the received value 
 		                     (the result from the first subtask) into result1*/
	}

	sum = 0;
	for (int i = 0; i <= num; i++) {
		sum += results[i];
	}
  
  printf("Intervals=%d, PI=%1.15f",intervals,sum);
    /* Show the result */
  pvm_exit();  /* End */
  exit(0);
}

