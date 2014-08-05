#include"class_spin_matrix.h"


//************************************************
//		IMPLEMENTATION			//
//************************************************

//CONSTRUCTORS AND DESTRUCTORS 

spin_matrix_complex::spin_matrix_complex(const int & numRows, const int & numColumns){

	this->pMatrix = gsl_matrix_complex_alloc(2*numRows, 2*numColumns);
	this->_numSites = numColumns;
	this->dimension = 2*numColumns;
	this->numRowsWithSpin = 2*numRows;
	this->numColsWithSpin = 2*numColumns;

}

spin_matrix_complex::spin_matrix_complex(const spin_matrix_complex & another){
	
	this->pMatrix = gsl_matrix_complex_alloc(another.numRowsWithSpin,
						another.numColsWithSpin);
	this->_numSites = another._numSites;
	this->dimension = 2*another._numSites;
	this->numRowsWithSpin = another.numRowsWithSpin;
	this->numColsWithSpin = another.numColsWithSpin;
	gsl_matrix_complex_memcpy( this->pMatrix, another.pMatrix );	

}

spin_matrix_complex::~spin_matrix_complex(){
	gsl_matrix_complex_free(this->pMatrix);
}

//GETTER Y SETTER

const gsl_complex spin_matrix_complex::spin_matrix_complex_get(const int & i ,SPIN spin_i ,
								const int & j, SPIN spin_j) const{
	
	return gsl_matrix_complex_get(this->pMatrix ,2*i + spin_i, 2*j+ spin_j);
}	

void spin_matrix_complex::spin_matrix_complex_set( const int & i ,SPIN spin_i, const int & j,
SPIN spin_j, const gsl_complex &  value ){

	gsl_matrix_complex_set(this->pMatrix , 2*i + spin_i, 2*j+ spin_j, value);

}

gsl_matrix_complex *  spin_matrix_complex::pMatriz() const{

return pMatrix;

}		


//WRITE AND READ

void spin_matrix_complex::spin_matrix_complex_fprintf(FILE * pFile) const{

	int i;
	int j;
	float real;
	float imag;

	for(i=0;i<numRowsWithSpin; i++){
		for(j=0; j<numColsWithSpin; j++){
		
		real = GSL_REAL(gsl_matrix_complex_get(this->pMatrix, i, j));
		imag = GSL_IMAG(gsl_matrix_complex_get(this->pMatrix, i, j)) ;
		fprintf( pFile ,"%f %f ",real , imag);

		}
		fprintf(pFile , "\n ");
	}
}

void spin_matrix_complex::spin_matrix_complex_fwrite(FILE * pFile) const{
	gsl_matrix_complex_fwrite( pFile, this->pMatrix );
}

void spin_matrix_complex::spin_matrix_complex_fscanf(FILE * pFile) const{

	int i;
	int j;
	float aux_real;
	float aux_imag;

	for(i=0;i<numRowsWithSpin; i++){
		for(j=0; j<numColsWithSpin; j++){

		fscanf(pFile, "%f " , &aux_real, &aux_imag);
		gsl_matrix_complex_set(this->pMatrix, i , j, gsl_complex_rect(aux_real, aux_imag));

		}fscanf(pFile , "\n ");
	}
}

void spin_matrix_complex::spin_matrix_complex_fread(FILE * pFile) const{

	gsl_matrix_complex_fread(pFile, this->pMatrix);

}

//OPERATIONS
const int spin_matrix_complex::spin_matrix_complex_numSites()const{
	return this->_numSites;
}


void spin_matrix_complex::spin_matrix_complex_symmetrize(){

	int i;
	int j;

	for(i=1; i<numRowsWithSpin; i++){
		for(j=0; j<i; j++){
			gsl_matrix_complex_set(this->pMatrix, i , j ,
			gsl_matrix_complex_get(this->pMatrix, j , i));
		}
	}
}


