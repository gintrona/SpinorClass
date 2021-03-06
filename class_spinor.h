#ifndef SPINOR
#define SPINOR

#include<iostream>
#include"gsl/gsl_vector.h"
#include"gsl/gsl_complex_math.h"

enum SPIN { UP, DOWN};
enum OPERATOR_SPIN {S_X, S_Y, S_Z};

class complex_spinor{

	public:

	//CONSTRUCTORES

		//default
		complex_spinor();
		//with number of sites
		complex_spinor(const int & numSites );		
		//copy		
		complex_spinor(const complex_spinor & anotherSpinor);	
		//with parameters
		complex_spinor(const gsl_complex & component_UP, const gsl_complex & component_DOWN);	
		//Destructor
		~complex_spinor();
		//Pointer gsl_vector_complex
		gsl_vector_complex * pVector() const ;

	//GET Y SET		

		const gsl_complex complex_spinor_get(SPIN spin_i) const;
		//return the i-th element with a given spin component 	
		const gsl_complex complex_spinor_get(const int & i, SPIN spin_i) const; 
	
		void complex_spinor_set(SPIN spin_i, const gsl_complex &  value );
		void complex_spinor_set(const int & nSitio,  SPIN spin_i, const gsl_complex &  value );

		int numSites() const; //returns the number of sites of del spinor

	//WRITE AND READ		

		void complex_spinor_fwrite(FILE *)const;
		void complex_spinor_fprintf(FILE *) const;

	//OPERATIONS

		//set all components to zero
		void complex_spinor_set_zero();
		//operation on a spinor returns another operator
		complex_spinor op(OPERATOR_SPIN operador) const;
		//return the norm of the spinor		
		double norm() const;
		//returns the mean value of the spin operator
		double meanValue(OPERATOR_SPIN operador) const;	
		//overloading 		
		gsl_complex operator* (const complex_spinor & complex_spinor_param) const;
		complex_spinor operator+ (const complex_spinor & complex_spinor_param) const;
		friend std::ostream& operator<<(std::ostream& os, const complex_spinor & c_spinor);

	private:
		gsl_vector_complex * priv_pVector;
		unsigned int dimension;
		unsigned int _numSites;	
		void copy(const complex_spinor & another);	
	
};

#endif
