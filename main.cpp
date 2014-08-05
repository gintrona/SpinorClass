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
	
	gsl_complex complexVar1;
	GSL_SET_COMPLEX(&complexVar1,1.0,0.0);
	
	gsl_complex complexVar2;
	GSL_SET_COMPLEX(&complexVar2,1.0,2.0);
	
	gsl_complex complexVar3;
	GSL_SET_COMPLEX(&complexVar3, 3.0,4.0);
	
	gsl_complex complexVar4;
	GSL_SET_COMPLEX(&complexVar4,0.0,0.0);

	gsl_complex complexVariable3;
	GSL_SET_COMPLEX(&complexVariable3, 0.0, 0.0);
	
	gsl_complex complexVariable4;
	GSL_SET_COMPLEX(&complexVariable4, 0.0, 0.0);


	gsl_complex c_value1;	
	gsl_complex c_zero;
	GSL_SET_COMPLEX(&c_zero, 0.0, 0.0);
	
		
	//******************
	// 2· CLASS SPINOR *
	//******************

	//CONSTRUCTORS
	
		// default
		complex_spinor Spinor1;
		complex_spinor * spinor = &Spinor1;

		// with arguments
		complex_spinor Spinor2(complexVar1,complexVar2);

		// copy 
		complex_spinor Spinor3(Spinor2);

		if(displayOption == CONSTR){
		cout<<"\nSpinor1 (default)\n"<< Spinor1 <<endl;
		cout<<"\nSpinor2 (arguments) \n"<< Spinor2<<endl;
		cout<<"\nSpinor3 (copy of Spinor2) \n"<< Spinor3 <<endl;
		}

	//GET AND SET

		complexVar3 = Spinor2.complex_spinor_get(UP);   //return complexVar1
		complexVar4 = Spinor2.complex_spinor_get(DOWN); //return complexVar2
		
		Spinor3.complex_spinor_set(UP, complexVariable3 ); //modify Spinor3; initalized before
		Spinor3.complex_spinor_set(DOWN,complexVariable4 );


		if(displayOption==GETANDSET){
		cout<<"\nSpinor2 = "<< GSL_REAL(complexVariable3)<<" +i "<<GSL_IMAG(complexVariable3) <<endl;
		cout<<"\nSpinor3 (with new components)  \n"<<Spinor3<<endl;
		cout<<"\nDimension of the spinor = "<<	Spinor3.numSites() <<endl;	
		}
		
	// OPERATIONS

		// Operator on a spinor
		complex_spinor Spinor4(Spinor2.op(S_Z)); 	//apply the S_Z operator on Spinor2 and use it to 
								// contruct another Spinor4 
		// Set all components to zero 							     
		//Spinor2.complex_spinor_set_zero();
	
		// compute the Norm of a Spinor
		double my_norm = Spinor4.norm();

		//get the mean Value of the operator S_Z
		double my_meanValue = Spinor4.meanValue(S_Z);
	
		complexVar4 = Spinor3*Spinor4;

		// perform the sum
		complex_spinor Spinor5(Spinor4+Spinor2);

		if(displayOption==OPER){
			cout<<"\nSpinor2 = "<< Spinor2 <<endl;
			cout<<"\nSpinor4 = "<< Spinor4 <<endl;
			cout<<"\nNorm of Spinor4 = "<< my_norm <<endl; 
			my_norm>1.0 ? cout<<" Not normalized !! "<<endl : cout<<endl;		
			cout<<"\nMeanValue = "<< my_meanValue <<endl;
			cout<<"\nMultiplication (Spinor3*Spinor4) = "<< GSL_REAL(complexVar4)
			<<" +i "<<GSL_IMAG(complexVar4) <<endl;
			cout<<"\nSpinor5 = Spinor2 + Spinor4  =  \n"<< Spinor5 <<endl;		
		}


	//***************
	// CLASS MATRIX *
	//***************

	spin_matrix_complex MatrixHami(numOfSites,numOfSites);							
	spin_matrix_complex * matrixHami = &MatrixHami;
				
	// set amatrix element
 	MatrixHami.spin_matrix_complex_set(1 , UP, 2, UP, complexVar1);
 	MatrixHami.spin_matrix_complex_set(1 , UP, 2, DOWN, complexVar1);
 	MatrixHami.spin_matrix_complex_set(1 , DOWN, 2, UP, complexVar1);
 	MatrixHami.spin_matrix_complex_set(1 , DOWN, 2, DOWN, complexVar1);
	
 	c_value1 = MatrixHami.spin_matrix_complex_get(1 , UP, 2, DOWN);
	
	cout<<"\n####################################################"<<endl;
	cout<< "Real part	"<<GSL_REAL(c_value1) <<endl;
	cout<< "Imaginary part	"<<GSL_IMAG(c_value1) <<endl;

	//access the underlying gsl_matrix_complex by accesing the complex matrix directly     
	
	gsl_matrix_complex_set_zero(matrixHami->pMatriz()); //matrixHami is a pointer

	c_value1 = MatrixHami.spin_matrix_complex_get(1 , UP, 2, DOWN);

	cout<<"\n ####################################################"<<endl;
	cout<< "After setting all matrix elements to zero..."<<endl;
	cout<< "Real part	"<<GSL_REAL(c_value1) <<endl;
	cout<< "Imaginary part	"<<GSL_IMAG(c_value1) <<endl;

	
return 0;

}
