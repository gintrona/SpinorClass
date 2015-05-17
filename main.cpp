#include<iostream>
#include<vector>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_histogram.h>
#include<gsl/gsl_eigen.h>
#include<gsl/gsl_vector.h>
#include<gsl/gsl_sort_vector.h>
#include<gsl/gsl_rng.h>
#include<gsl/gsl_permutation.h>
#include<gsl/gsl_histogram.h>
#include<gsl/gsl_linalg.h>
#include<gsl/gsl_complex.h>
#include<gsl/gsl_blas.h>
#include<gsl/gsl_complex_math.h>
#include"class_spin_matrix.h"
#include"class_spinor.h"

using namespace std;

/*
 1· DECLARE AND DEFINE SOME COMPLEX VARIABLES
 2· CLASS SPINOR -> meanValue, norm, operator on a spinor, sum, printf
*/

enum SHOW {CONSTR,GETANDSET,OPER};

int main(int argc,char *argv[]){

	SHOW displayOption = OPER;
		
	int numOfSites = 10;

	//**********************************************
	// 1· DECLARE AND DEFINE SOME COMPLEX VARIABLES *
	//**********************************************
	
	gsl_complex complexVar_1;
	GSL_SET_COMPLEX(&complexVar_1,1.0,0.0);
	
	gsl_complex complexVar_2;
	GSL_SET_COMPLEX(&complexVar_2,1.0,2.0);
	
	gsl_complex complexVar_3;
	GSL_SET_COMPLEX(&complexVar_3, 3.0,4.0);
	
	gsl_complex complexVar_4;
	GSL_SET_COMPLEX(&complexVar_4,0.0,0.0);

	gsl_complex complexVar_5;
	GSL_SET_COMPLEX(&complexVar_5, 0.0, 0.0);
	
	gsl_complex complexVar_6;
	GSL_SET_COMPLEX(&complexVar_6, 0.0, 0.0);


	gsl_complex c_value_1;
	gsl_complex c_zero;
	GSL_SET_COMPLEX(&c_zero, 0.0, 0.0);
	
		
	//******************
	// 2· CLASS SPINOR *
	//******************

	//CONSTRUCTORS
	
		// default
		complex_spinor SpinorDef;
		complex_spinor * pSpinor = &SpinorDef;

		// with arguments
		complex_spinor SpinorArg(complexVar_1,complexVar_2);

		// copy
		complex_spinor SpinorCpy(SpinorArg);

		if(displayOption == CONSTR){
			cout<<"\n SpinorDef (default)\n"<< SpinorDef <<endl;
			cout<<"\n SpinorArg (arguments) \n"<< SpinorArg<<endl;
			cout<<"\n SpinorCpy (copy of SpinorArg) \n"<< SpinorCpy <<endl;
		}

	//GET AND SET

		complexVar_3 = SpinorArg.complex_spinor_get(UP);   //return complexVar1
		complexVar_4 = SpinorArg.complex_spinor_get(DOWN); //return complexVar2
		
		SpinorCpy.complex_spinor_set(UP, complexVar_5 ); //modify Spinor3; initalized before
		SpinorCpy.complex_spinor_set(DOWN,complexVar_6 );

		if(displayOption==GETANDSET){
			cout<<"\n SpinorArg - Up Component => "<< GSL_REAL(complexVar_3)<<" +i "<<GSL_IMAG(complexVar_3) <<endl;
			cout<<"\n SpinorCpy (with new components)  \n"<<SpinorCpy<<endl;
			cout<<"\n Dimension of the spinor = "<<	SpinorCpy.numSites() <<endl;	
		}
		
	// OPERATIONS

		// Operator on a spinor
		complex_spinor SpinorResu(SpinorArg.op(S_Z));//apply the S_Z operator on Spinor2 and use it to contruct  another SpinorResu 
		complex_spinor SpinorResu2 = SpinorArg.op(S_Z); //equivalent

		// Set all components to zero 							     
		//SpinorArg.complex_spinor_set_zero();
	
		// compute the Norm of a Spinor
		double my_norm = SpinorResu.norm();

		//get the mean Value of the operator S_Z
		double my_meanValue = SpinorResu.meanValue(S_Z);
	
		complexVar_4 = SpinorCpy*SpinorResu;

		// perform the sum
		complex_spinor SpinorSum(SpinorResu+SpinorArg);

		if(displayOption==OPER){
			cout<<"\n SpinorArg = "<< SpinorArg <<endl;
			cout<<"\n SpinorResu = "<< SpinorResu <<endl;
			cout<<"\n SpinorResu2 = "<< SpinorResu2 <<endl;
			cout<<"\n Norm of SpinorResu = "<< my_norm <<endl; 
			my_norm>1.0 ? cout<<" Not normalized !! "<<endl : cout<<endl;		
			cout<<"\nMeanValue = "<< my_meanValue <<endl;
			cout<<"\nMultiplication (SpinorCpy*SpinorResu) = "<< GSL_REAL(complexVar_4)
			<<" +i "<<GSL_IMAG(complexVar_4) <<endl;
			cout<<"\n SpinorSum = SpinorArg + SpinorResu = \n"<< SpinorSum <<endl;		
		}

	//***************
	// CLASS MATRIX *
	//***************

	int dim = 2;
	spin_matrix_complex MatrixHami(dim,dim);
	spin_matrix_complex * matrixHami = &MatrixHami;
	
	//matrixHami is a pointer, and pMatriz point to a gsl_matrix_complex
	gsl_matrix_complex_set_zero(matrixHami->pMatriz()); 
				
	// set a matrix element (1,2)
 	MatrixHami.spin_matrix_complex_set(0 , UP, 1, UP,complexVar_1);
 	MatrixHami.spin_matrix_complex_set(0 , UP, 1, DOWN, complexVar_1);
 	MatrixHami.spin_matrix_complex_set(0 , DOWN, 1, UP, complexVar_1);
 	MatrixHami.spin_matrix_complex_set(0 , DOWN, 1, DOWN, complexVar_1);
	
 	c_value_1 = MatrixHami.spin_matrix_complex_get(0 , UP, 1, DOWN);
	
	cout<<"\n### MATRIX ELEMENT ###"<<endl;
	cout<< "Real part	"<<GSL_REAL(c_value_1) <<endl;
	cout<< "Imaginary part	"<<GSL_IMAG(c_value_1) <<endl;
	cout<<"#####################"<<endl;

	//workspace needed by the program
	gsl_eigen_herm_workspace * w 	= gsl_eigen_herm_alloc(2*dim); //2 due to spin
	
	//eigenvalues are stored in vector, the values are real, not complex
	gsl_vector * eigenvalues	= gsl_vector_alloc(2*dim);
	
	//make the matrix Hermitian
	MatrixHami.spin_matrix_complex_symmetrize();
	int g 				= gsl_eigen_herm( matrixHami->pMatriz(), eigenvalues, w);
	
	gsl_eigen_herm_free(w);	
	
	cout<<"\n ############### Eigenvalues ####################"<<endl;
	cout<< "Diagonalization of a Hermitian matrix : Eigenvalues are real"<<endl;
	for(int it=0 ; it<2*dim ; it++){
	  cout<< gsl_vector_get(eigenvalues,it) <<endl;
	}
	cout<<"####################################################"<<endl;
	return 0;
}
