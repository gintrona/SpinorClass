SpinorClass
===========


What's a spinor?
----------------


<ul>
<li>A spinor is an element of a vector space used to describe the state of an electron (or any another particle having a spin) and its components are complex numbers (or complex functions).
</li>
    
<li>
Accordingly, a physical operator affecting the spin will modify the spinor. In this spinor class the
three S operators (S_x, S_y, S_z) are implemented, and applying any of these on a spinor will return another modified spinor. 
</li>

<li>
Other common operations are implemented: norm of a spinor, cout, addition.
</li>

If you want to see some examples, check the main.cpp file. You'll find the makefile in the directory as well. 

</ul>
<b>
The spinor class is based on GSL. 
</b>

Using the class
---------------

The <b>class_spinor</b> and the <b>class_spin_matrix</b> allow you to write spinors and related matrix elements in an intuitive way by accessing and manipulating the UP and the DOWN components (or matrix elements) directly. The implementation is based on the GSL library, and more precisely on the complex vector and matrix structures.

To declare and initialize a spinor use:

      complex_spinor Spinor_1(complexVar_1,complexVar_2);
      
or equivalently:

      Spinor_1.complex_spinor_set(UP, complexVar_1); 
      Spinor_1.complex_spinor_set(DOWN,complexVar_2);
   
You get the components simply by calling: 

      complexVar_3 = Spinor_1.complex_spinor_get(UP);   //returns complexVar_1
      complexVar_4 = Spinor_1.complex_spinor_get(DOWN); //returns complexVar_2

In order to set the value of a given matrix element:

	MatrixInstance.spin_matrix_complex_set(0 , UP, 1, UP,complexVar_1);
	MatrixInstance.spin_matrix_complex_set(0 , UP, 1, DOWN,complexVar_2);
	MatrixInstance.spin_matrix_complex_set(0 , DOWN, 1, UP,complexVar_3);
	MatrixInstance.spin_matrix_complex_set(0 , DOWN, 1, DOWN,complexVar_4);

We see here that the matrix element a_01 contains 4 values due to the spin degree of freedom.

Now you can diagonalize the matrix (in this case I take a Hermitian matrix)

	gsl_eigen_herm( MatrixInstance->pMatriz(), eigenvalues, w)

where the method "pMatriz" returns a pointer to the underlying gsl_matrix_complex structure and "eigenvalues" is the vector (gsl_vector) storing the resulting eigenvalues.

