EXECUTABLE      := Main

CXX        := g++
CC         := gcc
LINK       := g++ -fPIC

INCLUDES  += -I. -I/ncsu/gcc346/include/c++/ -I/ncsu/gcc346/include/c++/3.4.6/backward 
LIB       := -L/ncsu/gcc346/lib

default:
	$(CXX) -v -g $(EXECUTABLE).cpp -o $(EXECUTABLE) $(INCLUDES) $(LIB) 

clean:
	rm -f $(EXECUTABLE)

