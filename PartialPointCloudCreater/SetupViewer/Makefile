CC=g++

OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB) -lglut -lGLU 
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include -I./

BIN=viewer
SRCS=viewer.cpp gl_framework.cpp shader_util.cpp 
INCLUDES=gl_framework.hpp shader_util.hpp viewer.hpp

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	g++ -std=c++11 $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN)
