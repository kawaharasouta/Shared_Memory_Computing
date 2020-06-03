#include <math.h> /* Using numerical fuctions (sqrt, etc.) */
#include "pvm3.h" /* Using pvm functions */

main()
{
  int ptid; /* Master task id */
  int n; /* Number of intercals */
  double s,t; /* Interval of integral */
  int i; /* Variable for loop */
  double h; /* Width of one interval */
  double sum=0; /* Accumulated value of the area. Initial value=0 */
  double x; /* x coordinate used at present */
  
  ptid = pvm_parent(); /* put master task id into ptid */
  pvm_recv(ptid, 1); /* Wating for receiving the data from master task, and put the data into the receiving buffer when received */
  pvm_upkint(&n, 1, 1); /*Put the interval assigned for one task into n */
  pvm_upkdouble(&s, 1 ,1); /*Put the left endpoint of the interval to s*/
  pvm_upkdouble(&t, 1 ,1); /* Put the right endpoint into t */
  
  h=(t-s)/n; /* Width of small intervals */
  for (i=0;i<n;++i){ /* Repeat the loop n times */
    x=(i+0.5)*h+s; /* Midpoint of x coordinate */
    sum+=(4*sqrt(1-x*x))*h;  /* Calculate the area of one small interval and add it to sum. */
  }
  pvm_initsend(0); /* Prepare for sending data */
  pvm_pkdouble(&sum, 1, 1); /* Put sum into the sending buffer */
  pvm_send(ptid, 1); /* Send the content of the sending buffer into the master process */
  pvm_exit(); /* End */
  exit(0);
}
