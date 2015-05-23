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
The complex_spinor and spin_matrix_complex classes are based on GSL. 
</b>

Using the class
---------------

The <b>spinor</b> and the <b>spin_matrix</b> classes allow you to write spinors and related matrix elements in an intuitive way by accessing and manipulating the UP and the DOWN components (or matrix elements) directly. The implementation is based on the GSL library, and more precisely on the complex vector and matrix structures.

To declare and initialize a spinor use:

      complex_spinor Spinor_1(complexVar_1,complexVar_2);
      
or equivalently:

      Spinor_1.complex_spinor_set(UP, complexVar_1); 
      Spinor_1.complex_spinor_set(DOWN,complexVar_2);
   
You get the components simply by calling: 

      complexVar_3 = Spinor_1.complex_spinor_get(UP);   //returns complexVar_1
      complexVar_4 = Spinor_1.complex_spinor_get(DOWN); //returns complexVar_2

In order to use the spin_matrix_complex, you first initialize it:

       spin_matrix_complex MatrixHami(dim,dim);
       spin_matrix_complex * matrixHami = &MatrixHami;

and then you set the matrix elements:

	MatrixInstance.spin_matrix_complex_set(0 , UP, 1, UP,complexVar_1);
	MatrixInstance.spin_matrix_complex_set(0 , UP, 1, DOWN,complexVar_2);
	MatrixInstance.spin_matrix_complex_set(0 , DOWN, 1, UP,complexVar_3);
	MatrixInstance.spin_matrix_complex_set(0 , DOWN, 1, DOWN,complexVar_4);

In a tight-binding model with spin-orbit coupling this matrix element would
correspond to the transition element between sites 1 and 0.  

Now you can diagonalize the matrix (in this case I take a complex Hermitian matrix, hence the eigenvalues are real)

	gsl_eigen_herm( matrixInstance->pMatriz(), eigenvalues, w)

where the method "pMatriz" returns a pointer to the underlying gsl_matrix_complex structure and "eigenvalues" is the vector (gsl_vector) storing the resulting (real) eigenvalues.
