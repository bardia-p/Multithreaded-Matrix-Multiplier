// Bardia Parmoun
// 101143006

#define MATRIX_SIZE 4
double M_MATRIX[4][4] =  {{20,20,50,40},{10,6, 70, 8}, {40,3,2,10}, {8, 7, 6, 5}};
double N_MATRIX[4][4] = {{10,30,50,70},{1,3,6,8},{9,5,5,7}, {8,6,4,2}};

struct shared_use_st {
	int isMemoryFull;
	int rowsVisited;
	double Q_MATRIX[MATRIX_SIZE][MATRIX_SIZE];
	double maxValues[MATRIX_SIZE];
};
