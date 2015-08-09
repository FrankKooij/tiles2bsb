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
	$(CC) $(CFLAGS) -o test/test test/test.cc $(LDFLAGS)
	./test/test

$(EXE): % : %.o $(OBJ)
	$(CC) $(CFLAGS) $@.o -o $@ $(OBJ) $(LDFLAGS)

%.o: %.cc $(INC)
	$(CC) $(CFLAGS) -c $<