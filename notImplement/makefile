CC=g++
CPP_COMP_FLAGS=-m64 -fpic -Wall -Wno-unused -fmax-errors=4 -msse2 -O2 -std=c++14
CLIBS=
CPP_INCLUDES=

CPP_FLAGS=$(CPP_COMP_FLAGS) $(CPP_INCLUDES)
LINK_FLAGS=-lm -lstdc++ -lpthread -ldl -lm $(CLIBS)

TARGET=notImplement
SRCS=
INC=

OBJS=notImplement.o

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LINK_FLAGS)

%.o:%.cpp
	$(CC) $(CPP_FLAGS) $(INC) -o $@ -c $<

clean:
	rm *.o notImplement
