CC=g++
CFLAGS=-std=c++17 -I $(EIGEN_PATH)
SFML_PATH=/home/artem/Soft/SFML-2.5.1
EIGEN_PATH=/home/artem/Soft/eigen
all: geometry

geometry: point3d.o coordinates.o point3d_test.o
	$(CC) -o point3d_test point3d.o coordinates.o point3d_test.o -L$(SFML_PATH)/lib -lsfml-graphics -lsfml-window -lsfml-system



point3d.o: point3d.cpp
	$(CC) $(CFLAGS) -c point3d.cpp

coordinates.o: coordinates.cpp
	$(CC) $(CFLAGS) -c coordinates.cpp

point3d_test.o: point3d_test.cpp
	$(CC) $(CFLAGS) -c point3d_test.cpp

test:
	export LD_LIBRARY_PATH=$(SFML_PATH)/lib &&	./point3d_test

clean:
	rm -rf point3d_test *.o
