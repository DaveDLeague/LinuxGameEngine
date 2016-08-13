CC=g++
OUT=-o ../build
LIBS=-lSDL2 -lGLEW -lGL
BIN=*.o 

build: source
	cd bin; $(CC) $(BIN) $(LIBS) $(OUT)
source:
	cd src; make;
clean:
	rm build; cd bin; rm *.o
		

