CC	= g++
CFLAGS	= -Wall -g -std=c++11 -Ofast
LDFLAGS	= 
EXE = tiles2bsb
OBJ = 
INC = 

all: $(EXE)

clean:
	rm -f *~ *.o core $(EXE)
	rm -rf *.dSYM

$(EXE): % : %.o $(OBJ)
	$(CC) $(CFLAGS) $@.o -o $@ $(OBJ) $(LDFLAGS)

%.o: %.cc $(INC)
	$(CC) $(CFLAGS) -c $<