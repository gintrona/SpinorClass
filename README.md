SpinorClass
===========

A spinor class based on GSL. 

The class_spinor and the class_spin_matrix allow you to write spinors and related matrix elements in a transparent way. 

What's a spinor? 

If you've stumbled upon this project,  you probably know what a spinor is and you're already dealing with them. In any case, and as an example, a spinor used to describe the state of an electron is a complex vector with two components, each of them carrying a complex number (actually a complex function).
A physical operator affecting the spin can modify the spinor. 

The class spinor implements the S operators (the three operators): applying the operator on a spinor returns another modified spinor. 

It's also possible to get the norm of a spinor, and the operations TATATATTA are also implemented (overloaded) to deal with spinor.
   
Initializing a spinor is as easy as :


And the matrix element (involving two spinors) is written as: 

 

How's it implemented?
Both the spinor and the spin_matrices are based on the gsl_complex_vector and gsl_complex matrix
GSL complex vectors respectively. These two classes provide an interface to the corresponding gsl classes and their main purpose is to have a fluent code.   
