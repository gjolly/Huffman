CC=gcc
CFLAGS= -std=c99 -g -Wall -pedantic
LDFLAGS= -std=c99 -g -Wall -pedantic
# -ansi 
#
#Surement pour le dossier tests
GENERES =	\
	tests/test*.txt	\


EXE =	\
	compress	\
	uncompress	\

TESTS =	\
	tests-list	\
	tests-binary	\
	tests-tree	\
	tests-generes	\
	

all:: $(EXE) $(TESTS) tar

compress: couple.o byte.o compress-commun.o list.o binary.o tree.o compress.o exec_compress.o
	$(CC) $(LDFLAGS) -o $@ $^ -lm

uncompress: couple.o byte.o compress-commun.o list.o binary.o tree.o uncompress.o exec_uncompress.o
	$(CC) $(LDFLAGS) -o $@ $^ -lm


#Tests files
tests-list: list.o tests-list.o
	$(CC) $(LDFLAGS) -o $@ $^
	
tests-binary: list.o byte.o binary.o tests-binary.o
	$(CC) $(LDFLAGS) -o $@ $^

tests-tree: tree.o couple.o tests-tree.o list.o
	$(CC) $(LDFLAGS) -o $@ $^

NB_TESTS = 5
tests-generes: test.o
	cd tests;	\
	$(CC) $(LDFLAGS) -o test $^;	\

#Generation des .o
couple.o: couple.h
byte.o: byte.h
list.o: list.h
binary.o: binary.h
tree.o: tree.h
compress.o: compress.h
uncompress.o: uncompress.h
compress-commun.o: compress-commun.h

NB_TESTS = 5
NB_CARACS = 20000
test.o: tests/test.c
	$(CC) $(CFLAGS) -DNB_TESTS=$(NB_TESTS) -DNB_CARACS=$(NB_CARACS) -c -o tests/$@ $^	

clean::
	rm -f *.o
	rm -f ${GENERES}
	rm -f $(EXE) $(TESTS) a.out
	rm -f tests/test*.[\txt\o]

force:: clean all

tar::
	tar czvf livrables/sources.tgz *.[hc] Makefile
