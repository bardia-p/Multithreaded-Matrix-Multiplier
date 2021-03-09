
# Matrix Multiplier Program

by Bardia Parmoun

Released on: 16/02/2021

## DESCRIPTION
- This program is used to calculate the result of the multiplication of two matrices. 
- It uses fork() to create a new child process for every row of the matrix. 
- The result of each operation is recorded on the shared memory which is then read as a whole by the parent process. 

## RUNNING THE PROGRAM
- This programs needs to be tested in a Linux environment. 
- Requires a gcc version of 9.3.1 or higher
1. To run the program first run the makefile to compile the executable file by typing:
```shell
$ make
```
2. After that an executable with the name of MMULT has been generated which  can be run using:
```shell
$ ./MMULT
```
 
## USING THE PROGRAM
To run the program first the matrices M and N need to be initliazed in the header file. This can be achieved by openining the header file and editing it.

1. To open the header file type:
```shell
$ vi shm_shared.h
```
2. Locate the following code:
```c
#define MATRIX_SIZE 4
double M_MATRIX[4][4] = {{20,20,50,40},{10,6,70,8},{40,3,2,10},{8,7,6,5}};
double N_MATRIX[4][4] = {{10,30,50,70},{1,3,6,8},{9,5,5,7}, {8,6,4,2}};
```
3. Now the program is ready to run after this
```
Matrix multiplier program starting
Multiplying matrix M:
[     20.00      20.00      50.00      40.00 ]
[     10.00       6.00      70.00       8.00 ]
[     40.00       3.00       2.00      10.00 ]
[      8.00       7.00       6.00       5.00 ]
with matrix N:
[     10.00      30.00      50.00      70.00 ]
[      1.00       3.00       6.00       8.00 ]
[      9.00       5.00       5.00       7.00 ]
[      8.00       6.00       4.00       2.00 ]
Child Process: working with row 1
Child Process: working with row 2
The largest number in row 1 of matrix Q is 1990.00
The largest number in row 2 of matrix Q is 1254.00
Child Process: working with row 3
Child Process: working with row 4
The largest number in row 3 of matrix Q is 2858.00
The largest number in row 4 of matrix Q is 668.00
Final Result
[    990.00    1150.00    1530.00    1990.00 ]
[    800.00     716.00     918.00    1254.00 ]
[    501.00    1279.00    2068.00    2858.00 ]
[    181.00     321.00     492.00     668.00 ]
The largest number in the matrix is 2858.00
The time it took to run the program in micro sec 695
```
This a sample test case

## Testing multiplication with the identity matrix:
```
Matrix multiplier program starting
Multiplying matrix M:
[     20.00      20.00      50.00      40.00 ]
[     10.00       6.00      70.00       8.00 ]
[     40.00       3.00       2.00      10.00 ]
[      8.00       7.00       6.00       5.00 ]
with matrix N:
[     1.00        0.00       0.00       0.00 ]
[     0.00        1.00       0.00       0.00 ]
[     0.00        0.00       1.00       0.00 ]
[     0.00        0.00       0.00       1.00 ]
Child Process: working with row 1
Child Process: working with row 2
The largest number in row 1 of matrix Q is 50.00
The largest number in row 2 of matrix Q is 70.00
Child Process: working with row 3
The largest number in row 3 of matrix Q is 40.00
Child Process: working with row 4
The largest number in row 4 of matrix Q is 8.00
Final Result
[     20.00      20.00      50.00      40.00 ]
[     10.00       6.00      70.00       8.00 ]
[     40.00       3.00       2.00      10.00 ]
[      8.00       7.00       6.00       5.00 ]
The largest number in the matrix is 70.00
The time it took to run the program in micro sec 390
```

## Testing multiplication with the inverse matrix:
```
Matrix multiplier program starting
Multiplying matrix M:
[     20.00      20.00      50.00      40.00 ]
[     10.00       6.00      70.00       8.00 ]
[     40.00       3.00       2.00      10.00 ]
[      8.00       7.00       6.00       5.00 ]
with matrix N:
[     -0.01       0.00       0.03       0.01 ]
[     -0.02      -0.00      -0.03       0.21 ]
[     -0.00       0.02      -0.00      -0.01 ]
[      0.04      -0.02       0.00      -0.10 ]
Child Process: working with row 1
Child Process: working with row 2
The largest number in row 1 of matrix Q is 1.00
The largest number in row 2 of matrix Q is 1.00
Child Process: working with row 3
The largest number in row 3 of matrix Q is 1.00
Child Process: working with row 4
The largest number in row 4 of matrix Q is 1.00
Final Result
[     1.00       0.00       0.00       0.00 ]
[     0.00       1.00       0.00      -0.00 ]
[     0.00       0.00       1.00      -0.00 ]
[     0.00       0.00       0.00       1.00 ]
The largest number in the matrix is 1.00
The time it took to run the program in micro sec 382
```
## CREDITS
Author: Bardia Parmoun

Copyright © 2021 Bardia Parmoun. All rights reserved
