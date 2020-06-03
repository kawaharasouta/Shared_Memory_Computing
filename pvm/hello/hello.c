#include "pvm3.h"

main(void) {
	int tid, answer;

	pvm_spawn("hello_other", (char**)0, 0, "", 1, &tid);
	printf("hello, Dr.t%x\n", tid);

	pvm_recv(tid,1);
	pvm_upkint(&answer, 1, 1);
	printf("Fine, thank you, Dr.t%x", answer);

	pvm_exit();
}
