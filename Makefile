CC	= g++
CFLAGS	= -Wall -g -std=c++11 -v
LDFLAGS	= -lcurl -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16 -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16 -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16 -I/usr/local/include/ImageMagick-6 
-DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16 -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16 -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16 -I/usr/local/include/ImageMagick-6 -L/usr/local/lib -lMagick++-6.Q16 -lMagickWand-6.Q16 -lMagickCore-6.Q16 -L/usr/local/lib -lMagick++-6.Q16 -lMagickWand-6.Q16 -lMagickCore-6.Q16 
EXE = tiles2bsb
OBJ = 
INC = 

.PHONY: test

all: $(EXE)

clean:
	rm -f *~ *.o core $(EXE)
	rm -rf *.dSYM
	rm test/test
	rm tiles/*.png

test:
	$(CC) -o test/test test/test.cpp $(LDFLAGS)
	./test/test

$(EXE): % : %.o $(OBJ)
	$(CC) $(CFLAGS) $@.o -o $@ $(OBJ) $(LDFLAGS)

%.o: %.cpp $(INC)
	$(CC) $(CFLAGS) -c $<