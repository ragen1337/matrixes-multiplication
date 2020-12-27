#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

const short dim = 1000;

void matrix_multiplier( long *matrix, long *vector, long *result_vector );
void matrix_and_vector_rand( long *matrix, long *vector );

int main (void)
{
    srand( (unsigned)time(NULL) );

    const short matrix_amount = 500;
    long *matrixes;
    long *vectors;
    long *res_vectors;

    //memory allocation for vectors and matrices
    matrixes = (long*)malloc(matrix_amount * dim * dim * sizeof(long));
    vectors = (long*)malloc(matrix_amount * dim * sizeof(long));
    res_vectors = (long*)malloc(matrix_amount * dim * dim * sizeof(long));

    //creating random matrixes and vectors
    for( int i = 0; i < matrix_amount; i++ ){
        matrix_and_vector_rand( matrixes + i*dim*dim , vectors + i*dim);
    }

    //timing 
    int start, stop;
    start = clock();

    //matrixes multiplication 
    for( int i = 0; i < matrix_amount; i++ ){
        matrix_multiplier( matrixes + i*dim*dim, vectors + i*dim , res_vectors + i*dim );
    }

    stop = clock();
    double delta = (double)(stop - start)/CLOCKS_PER_SEC;

    printf("start time: %i\n", start);
    printf("stop time: %i\n", stop);
    printf("algorithm duration: %e\n", delta );


    free(matrixes);
    free(vectors);
    free(res_vectors);
}

/*
* this function fill the matrix and vector with random numbers
*/
void matrix_and_vector_rand( long *matrix, long *vector ){
    for (short i = 0; i < dim; i++){
        *(vector + i) = rand();
        
        for (short j = 0; j < dim; j++){
            *(matrix + i*dim + j) = rand();
        }
    }
}

/*
* this function multiplies matrix and vector
*/
void matrix_multiplier( long *matrix, long *vector, long *result_vector )
{
    for (short i = 0; i < dim; i++){
        *(result_vector + i) = 0;

        for (short j = 0; j < dim; j++){
            *(result_vector + i) += *(matrix + i*dim + j) * ( *(vector + j) );
        }
    }
}