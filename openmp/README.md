## OpenMP: Prevailing Shared Memory Programming Approach


A platform for parallel computing in shared memory
- Threads – logical processing units in OpenMP. 
- Cores – physical processing units in the computer


- Model for shared-memory parallel programming
- Portable across shared-memory architectures
- Scalable (on shared-memory platforms)
- Incremental parallelization
  - Parallelize individual computations in a program while leaving the rest of the program sequential
- Compiler based
  - Compiler generates thread program and synchronization
- Extensions to existing programming languages (Fortran, C and C++)
  - mainly by directives
  - a few library routines


http://www.openmp.org
