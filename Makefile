CC	= g++
CFLAGS	= -Wall -Ofast -std=c++11 -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16 -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16 -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16 -I/opt/ImageMagick/include/ImageMagick-6 -I/usr/local/include
LDFLAGS	= -lcurl -L/opt/ImageMagick/lib -lMagick++-6.Q16 -lMagickCore-6.Q16 -L/usr/local/lib -ltiff
EXE = tiles2bsb
OBJ = 
INC = 

.PHONY: test

all: $(EXE)

clean:
	rm -f *~ *.o core $(EXE)
	rm -rf *.dSYM
	rm tiles/*.png
	rm tiles/*.tif
	rm *.kap
	rm test/test

test:
	$(CC) $(CFLAGS) -o test/test test/test.cpp $(LDFLAGS)
	./test/test

$(EXE): % : %.o $(OBJ)
	$(CC) $(CFLAGS) $@.o -o $@ $(OBJ) $(LDFLAGS)

%.o: %.cpp $(INC)
	$(CC) $(CFLAGS) -c $<