CC	= g++
CFLAGS	= -Wall -g -std=c++11 -v
LDFLAGS	= -lcurl
EXE = tiles2bsb
OBJ = 
INC = 

.PHONY: test

all: $(EXE)

clean:
	rm -f *~ *.o core $(EXE)
	rm -rf *.dSYM
	rm test/test

test:
	$(CC) -o test/test test/test.cpp $(LDFLAGS)
	./test/test

$(EXE): % : %.o $(OBJ)
	$(CC) $(CFLAGS) $@.o -o $@ $(OBJ) $(LDFLAGS)

%.o: %.cpp $(INC)
	$(CC) $(CFLAGS) -c $<