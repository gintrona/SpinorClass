CC = g++ 	
PROG = main
OBJECTS = class_spin_matrix.o class_spinor.o 

$(PROG).x : $(PROG).o $(OBJECTS)
	$(CC) $(PROG).o $(OBJECTS) -I/usr/local/lib -lm -lstdc++  -L/home/intronati/GSL/lib -lgsl -lgslcblas -o $(PROG).x

$(PROG).o : $(PROG).cpp class_spin_matrix.h class_spinor.h
	$(CC) -c $(PROG).cpp

class_spin_matrix.o : class_spin_matrix.cpp
	$(CC) -c class_spin_matrix.cpp  

class_spinor.o : class_spinor.cpp
	$(CC) -c class_spinor.cpp

clean:
	rm $(PROG).o $(OBJECTS) 

