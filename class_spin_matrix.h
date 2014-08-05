#ifndef SPIN_MATRIX_COMPLEX
#define SPIN_MATRIX_COMPLEX

#include"gsl/gsl_matrix.h"
#include"class_spinor.h"

//to be removed:
//#include<iostream>
//using namespace std;
//#include <cstdlib>
//#include <cstring>
//#include <math.h>
//#include"gsl/gsl_vector.h"
//#include"gsl/gsl_complex.h"
//#include"gsl/gsl_complex_math.h"


class spin_matrix_complex{
	
	public:

	//CONTRUCTORS

		//WITH PARAMETERS	
		spin_matrix_complex(const int & numRows, const int & numColumns);
		//por copia
		spin_matrix_complex(const spin_matrix_complex & anotherMatrix);
		//destructor	
		~spin_matrix_complex();

	//GETTERS y SETTERS

		const gsl_complex spin_matrix_complex_get(const int & i ,SPIN spin_i ,const int & j, SPIN spin_j) const;	
		//set the value of the element (i,j) 	
		void spin_matrix_complex_set( const int & i , SPIN spin_i, const int & j, SPIN spin_j, const gsl_complex & c_value );
		//returns the pointer to the underlying gsl-matrix		
		gsl_matrix_complex * pMatriz() const;
	
	//Write and read

		const int spin_matrix_complex_numSites() const;
		//write the matrix in a file (ascii with floats)		
		void spin_matrix_complex_fprintf(FILE *) const;
		//write the matri in a file (binary format)
		void spin_matrix_complex_fwrite(FILE *) const;
		//read the file (ascii format with floats)
		void spin_matrix_complex_fscanf(FILE *) const;
		//read the file in binary format
		void spin_matrix_complex_fread(FILE *) const;

	//OPERATIONS
		//symmetrize the matrix
		void spin_matrix_complex_symmetrize();
		

	private:

		gsl_matrix_complex * pMatrix;
		unsigned int _numSites; 
		unsigned int dimension;
		unsigned int numRowsWithSpin;
		unsigned int numColsWithSpin;
};
#endif

