APP=fuckyou
CFLAGS= -g 
CLIB=
CINC=

all:$(APP)

$(APP):config.o main.o
	g++ config.o main.o -o $(APP) -L$(CLIB) -I$(CINC)

config.o:config.cpp config.hpp
	g++ config.cpp -c -o config.o $(CFLAGS)

main.o:main.cpp
	g++ main.cpp -c -o main.o $(CFLAGS)
