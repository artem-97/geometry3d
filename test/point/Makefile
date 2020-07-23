CC=g++-10
CFLAGS=-std=c++20 -I $(EIGEN_PATH)
GTEST=-lgtest -lpthread
SRCDIR=../../src
BUILDDIR=../../build
TESTDIR=.

SFML_PATH=/home/artem/Soft/SFML-2.5.1
EIGEN_PATH=/home/artem/Soft/eigen

all: $(BUILDDIR)/point3d_test

$(BUILDDIR)/point3d_test: $(BUILDDIR)/point3d.o $(BUILDDIR)/coordinates.o  $(BUILDDIR)/point3dxyz.o $(BUILDDIR)/point3dsph.o $(BUILDDIR)/point3d_test.o
	$(CC) $(CFLAGS) -o $(BUILDDIR)/point3d_test $(BUILDDIR)/point3d.o $(BUILDDIR)/coordinates.o $(BUILDDIR)/point3d_test.o $(BUILDDIR)/point3dxyz.o $(BUILDDIR)/point3dsph.o -L$(SFML_PATH)/lib -lsfml-graphics -lsfml-window -lsfml-system $(GTEST)


$(BUILDDIR)/point3d.o: $(SRCDIR)/point/point3d.cpp $(SRCDIR)/point/point3d.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/point/point3d.cpp -o $(BUILDDIR)/point3d.o $(GTEST)


$(BUILDDIR)/point3dxyz.o: $(BUILDDIR)/point3d.o $(SRCDIR)/point/point3dxyz.cpp $(SRCDIR)/point/point3dxyz.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/point/point3dxyz.cpp -o $(BUILDDIR)/point3dxyz.o $(GTEST)


$(BUILDDIR)/point3dsph.o: $(BUILDDIR)/point3d.o $(SRCDIR)/point/point3dsph.cpp $(SRCDIR)/point/point3dsph.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/point/point3dsph.cpp -o $(BUILDDIR)/point3dsph.o $(GTEST)


$(BUILDDIR)/coordinates.o: $(SRCDIR)/point/coordinates.cpp $(SRCDIR)/point/coordinates.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/point/coordinates.cpp -o $(BUILDDIR)/coordinates.o $(GTEST)


$(BUILDDIR)/point3d_test.o: $(TESTDIR)/point3d_test.cpp
	$(CC) $(CFLAGS) -c $(TESTDIR)/point3d_test.cpp -o $(BUILDDIR)/point3d_test.o $(GTEST)


test:
	export LD_LIBRARY_PATH=$(SFML_PATH)/lib &&	$(BUILDDIR)/point3d_test

clean:
	rm -rf $(BUILDDIR)/point3d_test $(BUILDDIR)/*.o
