SpinorClass
===========


What's a spinor?
----------------


If you've stumbled upon this project,  you probably know what a spinor is and you're already dealing with them. So let me just specify what I took into account to implement the class.

<ul>
<li>A spinor is used to describe the state of an electron (or another particle bearing a spin)
and its components are complex numbers (or complex functions).
</li>
    
<li>      
A physical operator affecting the spin can modify the spinor, so the class spinor implements the
three S operators: applying the operator on a spinor returns another modified spinor. 
</li>

<li>
It's also possible to get the norm of a spinor, and the operations TATATATTA are also implemented (overloaded) to        deal with spinor.
</li>

</ul>
<b>
A spinor class based on GSL. 
</b>

Using the class
---------------

The <b>class_spinor</b> and the <b>class_spin_matrix</b> allow you to write spinors and related matrix elements in a transparent way. 

Declaring and initializing a spinor is as easy as :

      complex_spinor Spinor1(complexVar1,complexVar2);
      
or equivalently:

      Spinor1.complex_spinor_set(UP, complexVariable1); 
      Spinor1.complex_spinor_set(DOWN,complexVariable2);
   
You get its components simply by calling: 

      complexVar3 = Spinor1.complex_spinor_get(UP);   //returns complexVar1
      complexVar4 = Spinor1.complex_spinor_get(DOWN); //returns complexVar2


The implementation is based on the GSL library, and more precisely on the vector and matrix structures.  

   
Initializing a spinor is as easy as :


And the matrix element (involving two spinors) is written as: 

 

How's it implemented?
Both the spinor and the spin_matrices are based on the gsl_complex_vector and gsl_complex matrix
GSL complex vectors respectively. These two classes provide an interface to the corresponding gsl classes and their main purpose is to have a fluent code.   
