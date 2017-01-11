# CC=g++

# OPENGLLIB= -lGL
# GLEWLIB= -lGLEW
# GLFWLIB = -lglfw
# LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB) -lglut -lGLU 
# LDFLAGS=-L/usr/local/lib 
# CPPFLAGS=-I/usr/local/include -I./

# BIN=coreg
# SRCS=coreg.cpp load_obj.cpp 
# INCLUDES=load_obj.h

CC=g++ -std=c++11
CFLAGS=-I.
DEPS = load_obj.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

coreg: coreg.o load_obj.o 
	$(CC) -o coreg coreg.o load_obj.o -I.

clean:
	rm -f *.o coreg

# all: $(BIN)

# $(BIN): $(SRCS) $(INCLUDES)
# 	g++ -std=c++11 $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

# clean:
# 	rm -f *~ *.o $(BIN)


# all : load_obj coreg

# load_obj: load_obj.cpp load_obj.h
# 	g++ -std=c++11 load_obj.cpp

# coreg: load_obj coreg.cpp
# 	g++ coreg.cpp -o coreg