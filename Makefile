CC	= g++
CFLAGS	= -Wall -g -std=c++11 -v
LDFLAGS	= 
EXE = tiles2bsb
OBJ = 
INC = 

.PHONY: test

test:
	$(CC) -o test/test test/test.cc
	./test/test

all: $(EXE)

clean:
	rm -f *~ *.o core $(EXE)
	rm -rf *.dSYM
	rm test/test

$(EXE): % : %.o $(OBJ)
	$(CC) $(CFLAGS) $@.o -o $@ $(OBJ) $(LDFLAGS)

%.o: %.cc $(INC)
	$(CC) $(CFLAGS) -c $<