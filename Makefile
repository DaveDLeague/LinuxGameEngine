CC=g++
CFLAGS=-c -Wall
OUT=-o ../build
LIBS=-lSDL2 -lGL
BIN=*.o
INCLUDE=-I ../include 

build: source
	cd src; $(CC) $(BIN) $(LIBS) $(OUT)
source:
	cd src; make;
clean:
	rm build; cd src; rm *.o
		

