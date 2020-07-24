CC=g++-10
CFLAGS=-std=c++20 -I $(EIGEN_PATH)
GTEST=-lgtest -lpthread
SRCDIR=../../src
BUILDDIR=../../build
TESTDIR=.

SFML_PATH=/home/artem/Soft/SFML-2.5.1
EIGEN_PATH=/home/artem/Soft/eigen

all: $(BUILDDIR)/rigidbody_test

$(BUILDDIR)/rigidbody_test: $(BUILDDIR)/rigidbody.o $(BUILDDIR)/rigidbody_test.o $(BUILDDIR)/point3d.o $(BUILDDIR)/coordinates.o
	$(CC) $(CFLAGS) -o $(BUILDDIR)/rigidbody_test $(BUILDDIR)/rigidbody.o $(BUILDDIR)/rigidbody_test.o $(BUILDDIR)/point3d.o $(BUILDDIR)/coordinates.o -L$(SFML_PATH)/lib -lsfml-graphics -lsfml-window -lsfml-system $(GTEST)

$(BUILDDIR)/rigidbody.o: $(SRCDIR)/rigidbody/rigidbody.cpp $(SRCDIR)/rigidbody/rigidbody.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/rigidbody/rigidbody.cpp -o $(BUILDDIR)/rigidbody.o $(GTEST)


$(BUILDDIR)/point3d.o: $(SRCDIR)/point/point3d.cpp $(SRCDIR)/point/point3d.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/point/point3d.cpp -o $(BUILDDIR)/point3d.o $(GTEST)

$(BUILDDIR)/coordinates.o: $(SRCDIR)/point/coordinates.cpp $(SRCDIR)/point/coordinates.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/point/coordinates.cpp -o $(BUILDDIR)/coordinates.o $(GTEST)


$(BUILDDIR)/rigidbody_test.o: $(TESTDIR)/rigidbody_test.cpp
	$(CC) $(CFLAGS) -c $(TESTDIR)/rigidbody_test.cpp -o $(BUILDDIR)/rigidbody_test.o $(GTEST)


test:
	export LD_LIBRARY_PATH=$(SFML_PATH)/lib &&	$(BUILDDIR)/rigidbody_test

clean:
	rm -rf $(BUILDDIR)/*_test $(BUILDDIR)/*.o
