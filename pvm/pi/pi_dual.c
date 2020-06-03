#include <stdio.h> /* For standard I/O functions¡ */
#include "pvm3.h" /* For stand pvm functions */

main(argc,argv)
int argc;
char **argv;
{
  int intervals; /* Number of intervals */
  int ctid[2]; /* task id (subtasks) */
  int n; /* Number of intervals for one subtask */
  double s,t; /* Interval of tasks */
  double result1,result2; /* Results of subtasks */

  if(argc<=1){ /* Finish if no any parameter */
    printf("Usage:pi_dual intervals\n");
    pvm_exit();
    exit(0);
  }

  sscanf(argv[1],"%d",&intervals); 
  /* Get the first parameter and put it into intervals */
  if(pvm_spawn("pi_slave",(char **) 0,0,"",2,ctid)!=2){
  /* Start two subtasks for executing slave program  
     pi_slave¡ Save the subtask ids into arry ctid */
    printf("an't start pi_slave\n"); /* Fail in starting the subtasks */
    pvm_exit();
    exit(0);
  }
	n=intervals/2; /* Interval for one subtask */
  s=0;t=0.5; /* First subtask responsible for interval [0,0.5] */
  pvm_initsend(0); /* Prepare for data sending */
  pvm_pkint(&n, 1 ,1); /* Put the interval into the sending buffer */
  pvm_pkdouble(&s, 1, 1); /* Put the value of s into the sending buffer */
  pvm_pkdouble(&t, 1 ,1); /* Put the value of t into the sending buffer */
  pvm_send(ctid[0], 1); 
  /* Send the content of the buffer to the first subtask */

  s=0.5;t=1; /* Secong subtask responsible for interval [0.5,1] */
  pvm_initsend(0); /* Prepare for data sending */
  pvm_pkint(&n, 1 ,1); /* Put the interval into the sending buffer  */
  pvm_pkdouble(&s, 1, 1); /* Put the value of s into the sending buffe  */
  pvm_pkdouble(&t, 1 ,1); /*  Put the value of t into the sending buffe */
  pvm_send(ctid[1], 1); 
   /* Send the content of the buffer to the second subtask  */

  pvm_recv(-1, 1); /* Waiting for receiving the data from the subtasks, 
          and put the data into the receiving buffer when received */
  pvm_upkdouble(&result1,1,1);  /* Put the received value 
                      (the result from the first subtask) into result1*/
  pvm_recv(-1, 1); /* Waiting for receiving the data from the subtasks, 
               and put the data into the receiving buffer when received */
  pvm_upkdouble(&result2,1,1);   /*Put the received value 
                       (the result from the second subtask)into result2*/
  
  printf("Intervals=%d, PI=%1.15f",intervals,result1+result2);
    /* Show the result */
  pvm_exit();  /* End */
  exit(0);
}

