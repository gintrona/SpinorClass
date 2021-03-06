#include"class_spinor.h"

//****************************************
//	Implementation			//
//****************************************

//CONSTRUCTORS
//by default
complex_spinor::complex_spinor(){

	this->_numSites = 1;
	this->dimension = 2;
	this->priv_pVector = gsl_vector_complex_alloc(dimension);

}

//with number of sites
complex_spinor::complex_spinor(const int & numSites){

	this->priv_pVector = gsl_vector_complex_alloc(2*numSites);
	this->_numSites = numSites;
	this->dimension = 2*numSites;

}		
//copy
complex_spinor::complex_spinor(const complex_spinor & another){
	
	this->_numSites = another._numSites;
	this->dimension = another.dimension;
	this->priv_pVector = gsl_vector_complex_alloc(this->dimension);
	gsl_vector_complex_memcpy(this->priv_pVector, another.priv_pVector);

}
// a simple spinor with two components
complex_spinor::complex_spinor(const gsl_complex & component_UP, const gsl_complex & component_DOWN){

	this->priv_pVector = gsl_vector_complex_alloc(2);
	this->dimension = 2;
	this->_numSites = 1;
	this->complex_spinor_set(UP, component_UP );
	this->complex_spinor_set(DOWN, component_DOWN );
}
//Destructor
complex_spinor::~complex_spinor(){
	gsl_vector_complex_free(this->priv_pVector);
}

gsl_vector_complex * complex_spinor::pVector()const {
	return this->priv_pVector;
}

//GET AND SET

const gsl_complex complex_spinor::complex_spinor_get(SPIN spin_i) const{
	return gsl_vector_complex_get(this->priv_pVector , spin_i);
}	

const gsl_complex complex_spinor::complex_spinor_get(const int & nSitio , SPIN spin_i) const{
	return gsl_vector_complex_get(this->priv_pVector ,2*nSitio + spin_i);
}

void complex_spinor::complex_spinor_set(const int & nSitio,  SPIN spin_i, const gsl_complex &  value ){
	gsl_vector_complex_set( this->priv_pVector ,2* nSitio + spin_i, value);
}

void complex_spinor::complex_spinor_set( SPIN spin_i, const gsl_complex &  value ){
	gsl_vector_complex_set( this->priv_pVector , spin_i, value);
}

int complex_spinor::numSites() const{
	return this->_numSites;
}

//WRITE AND READ

void complex_spinor::complex_spinor_fprintf(FILE * pFile) const{
	gsl_vector_complex_fprintf( pFile, this->priv_pVector ,"%f");
}

void complex_spinor::complex_spinor_fwrite(FILE * pFile) const{
	gsl_vector_complex_fwrite( pFile, this->priv_pVector );
}


//OPERATIONS ON SPINORS

void complex_spinor::complex_spinor_set_zero() {
	
	int i;
	int numSites = this->_numSites;
	gsl_complex zero;

	GSL_SET_COMPLEX(&zero, 0, 0);

	for(i=0;i<numSites;i++){
		this->complex_spinor_set(i,UP, zero);
		this->complex_spinor_set(i,DOWN, zero);
	}

}

complex_spinor complex_spinor::op(OPERATOR_SPIN spinOperator) const{
	
	int i;
	double result;
	//Spin Parameters
	int new_numSites = this->_numSites;

	complex_spinor complex_spinor_resu(new_numSites);
	


if(spinOperator == S_X ){

	for(i=0 ; i<new_numSites ; i++){
	gsl_complex oldUP = this->complex_spinor_get(i, UP);
	gsl_complex oldDOWN = this->complex_spinor_get(i, DOWN);
	
	complex_spinor_resu.complex_spinor_set(i, UP, gsl_complex_mul_real(oldDOWN, 0.5));
	complex_spinor_resu.complex_spinor_set(i, DOWN, gsl_complex_mul_real(oldUP, 0.5));	
	}
}

else if(spinOperator == S_Y){

	for(i=0 ; i<new_numSites ; i++){
	gsl_complex oldUP = this->complex_spinor_get(i, UP);
	gsl_complex oldDOWN = this->complex_spinor_get(i, DOWN);

	complex_spinor_resu.complex_spinor_set(i, UP, gsl_complex_mul_imag(oldDOWN, 0.5));
	complex_spinor_resu.complex_spinor_set(i, DOWN, gsl_complex_mul_imag(oldUP, -0.5));	
	}

}

else{ //S_Z

	for(i=0 ; i<new_numSites ; i++){
	gsl_complex oldUP = this->complex_spinor_get(i, UP);
	gsl_complex oldDOWN = this->complex_spinor_get(i, DOWN);

	complex_spinor_resu.complex_spinor_set(i, UP, gsl_complex_mul_real(oldUP, 0.5));
	complex_spinor_resu.complex_spinor_set(i, DOWN, gsl_complex_mul_real(oldDOWN, -0.5));	
	}

}
	return complex_spinor_resu;

}

double complex_spinor::norm() const{

	double result=0; 
	int new_numSites = this->_numSites;
	int i;

	for(i=0 ; i<new_numSites ; i++){

		gsl_complex oldUP = this->complex_spinor_get(i, UP);
		gsl_complex oldDOWN = this->complex_spinor_get(i, DOWN);

	result = result + (gsl_complex_abs2(oldUP) + gsl_complex_abs2(oldDOWN));
	}
	return result;
}

double complex_spinor::meanValue(OPERATOR_SPIN operador)const{

	int i;
	double result = 0;
	//Spinor Parameters
	int new_numeroSitios = this->_numSites;

if(operador == S_Z){
	result = 0;
	for(i=0 ; i<new_numeroSitios ; i++){

	gsl_complex oldUP = this->complex_spinor_get(i, UP);
	gsl_complex oldDOWN = this->complex_spinor_get(i, DOWN);

	result = result + (gsl_complex_abs2(oldUP) - gsl_complex_abs2(oldDOWN));
	}
}
	return 0.5*result;
}

gsl_complex complex_spinor::operator* (const complex_spinor & complex_spinor_param) const{
	
	gsl_complex aux_UP;
	gsl_complex aux_DOWN;
	gsl_complex aux;
	
	GSL_SET_COMPLEX(&aux_UP, 0, 0);
	GSL_SET_COMPLEX(&aux_DOWN, 0, 0);
	GSL_SET_COMPLEX(&aux, 0, 0);

	int i;
	int nSitios = this->_numSites;

	for(i=0; i<nSitios ; i++){

	aux_UP = gsl_complex_mul(gsl_complex_conjugate(complex_spinor_param.complex_spinor_get(i,UP)) ,this->complex_spinor_get(i,UP));
	aux_DOWN = gsl_complex_mul(gsl_complex_conjugate(complex_spinor_param.complex_spinor_get(i,DOWN)),this->complex_spinor_get(i,DOWN));
	aux=gsl_complex_add(aux, gsl_complex_add(aux_UP,aux_DOWN));
	}
return aux;
}

complex_spinor complex_spinor::operator+(const complex_spinor & complex_spinor_param)const{

	gsl_complex aux_UP;
	gsl_complex aux_DOWN;

	GSL_SET_COMPLEX(&aux_UP, 0, 0);
	GSL_SET_COMPLEX(&aux_DOWN, 0, 0);
	
	int i;	
	int nSitios = this->_numSites;
	complex_spinor complex_spinor_res(nSitios);
	
	for(i=0; i<nSitios ; i++){
	aux_UP = gsl_complex_add(complex_spinor_param.complex_spinor_get(i, UP) , this->complex_spinor_get(i, UP)); 
  	aux_DOWN = gsl_complex_add(complex_spinor_param.complex_spinor_get(i, DOWN) , this->complex_spinor_get(i,DOWN));
	complex_spinor_res.complex_spinor_set(i, UP, aux_UP);
	complex_spinor_res.complex_spinor_set(i, DOWN, aux_DOWN);
	}
	return complex_spinor_res;
}

std::ostream& operator<<(std::ostream &os, const complex_spinor & c_spinor){

	int i;
	int nSitios = c_spinor._numSites;
	for(i=0;i<nSitios;i++){
	os << "[(" <<  GSL_REAL(c_spinor.complex_spinor_get(i,UP))<<" + i. "<<GSL_IMAG(c_spinor.complex_spinor_get(i,UP))<<")]"<<std::endl;
	os << "[(" <<  GSL_REAL(c_spinor.complex_spinor_get(i,DOWN))<<" + i. "<<GSL_IMAG(c_spinor.complex_spinor_get(i,DOWN))<<")]"<<std::endl;
	}
	return os; 
}
