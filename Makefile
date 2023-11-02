# Makefile qui genere l'executable distanceEdition et fait des tests de verification
#
#
CC=gcc
LATEXC=pdflatex
DOCC=doxygen
CFLAGS=-g -Wall
OPT=-g

REFDIR=.
SRCDIR=$(REFDIR)/src
BINDIR=$(REFDIR)/bin
DOCDIR=$(REFDIR)/doc
TESTDIR=$(REFDIR)/tests
REPORTDIR=$(REFDIR)/report

LATEXSOURCE=$(wildcard $(REPORTDIR)/*.tex)
CSOURCE=$(wildcard $(SRCDIR)/*.c)
PDF=$(LATEXSOURCE:.tex=.pdf)

all: binary report doc binary_perf

binary: $(BINDIR)/distanceEdition

binary_perf: $(BINDIR)/distanceEdition-perf

$(BINDIR)/distanceEdition-perf: $(SRCDIR)/distanceEdition.c $(BINDIR)/Needleman-Wunsch-recmemo.o
	$(CC) $(OPT) -D__PERF_MESURE__ -I$(SRCDIR) -o $(BINDIR)/distanceEdition-perf $(BINDIR)/Needleman-Wunsch-recmemo.o $(SRCDIR)/distanceEdition.c 

report: $(PDF) 

doc: $(DOCDIR)/index.html

# distanceEdition

$(BINDIR)/distanceEdition: $(SRCDIR)/distanceEdition.c $(BINDIR)/Needleman-Wunsch-recmemo.o 
	$(CC) $(OPT) -I$(SRCDIR) -o $(BINDIR)/distanceEdition $(BINDIR)/Needleman-Wunsch-recmemo.o $(SRCDIR)/distanceEdition.c 

$(BINDIR)/distanceEdition-ite: $(SRCDIR)/distanceEdition.c $(BINDIR)/Needleman-Wunsch-ite.o
	$(CC) $(OPT) -I$(SRCDIR) -D__ITE__ -o $(BINDIR)/distanceEdition $(BINDIR)/Needleman-Wunsch-ite.o $(SRCDIR)/distanceEdition.c 

$(BINDIR)/distanceEdition-caware: $(SRCDIR)/distanceEdition.c $(BINDIR)/Needleman-Wunsch-caware.o
	$(CC) $(OPT) -I$(SRCDIR) -D__CAWARE__ -o $(BINDIR)/distanceEdition $(BINDIR)/Needleman-Wunsch-caware.o $(SRCDIR)/distanceEdition.c 

$(BINDIR)/distanceEdition-coblivious: $(SRCDIR)/distanceEdition.c $(BINDIR)/Needleman-Wunsch-coblivious.o
	$(CC) $(OPT) -I$(SRCDIR) -D__COBLIVIOUS__ -o $(BINDIR)/distanceEdition $(BINDIR)/Needleman-Wunsch-coblivious.o $(SRCDIR)/distanceEdition.c 

# Algorithm

$(BINDIR)/Needleman-Wunsch-recmemo.o: $(SRCDIR)/Needleman-Wunsch-recmemo.h $(SRCDIR)/Needleman-Wunsch-recmemo.c $(SRCDIR)/characters_to_base.h
	$(CC) $(OPT) -I$(SRCDIR) -c  -o $(BINDIR)/Needleman-Wunsch-recmemo.o $(SRCDIR)/Needleman-Wunsch-recmemo.c
	
$(BINDIR)/Needleman-Wunsch-ite.o: $(SRCDIR)/Needleman-Wunsch-ite.h $(SRCDIR)/Needleman-Wunsch-ite.c $(SRCDIR)/characters_to_base.h
	$(CC) $(OPT) -I$(SRCDIR) -c  -o $(BINDIR)/Needleman-Wunsch-ite.o $(SRCDIR)/Needleman-Wunsch-ite.c

$(BINDIR)/Needleman-Wunsch-caware.o: $(SRCDIR)/Needleman-Wunsch-caware.h $(SRCDIR)/Needleman-Wunsch-caware.c $(SRCDIR)/characters_to_base.h
	$(CC) $(OPT) -I$(SRCDIR) -c -o $(BINDIR)/Needleman-Wunsch-caware.o $(SRCDIR)/Needleman-Wunsch-caware.c

$(BINDIR)/Needleman-Wunsch-coblivious.o: $(SRCDIR)/Needleman-Wunsch-coblivious.h $(SRCDIR)/Needleman-Wunsch-coblivious.c $(SRCDIR)/characters_to_base.h
	$(CC) $(OPT) -I$(SRCDIR) -c -o $(BINDIR)/Needleman-Wunsch-coblivious.o $(SRCDIR)/Needleman-Wunsch-coblivious.c


$(BINDIR)/extract-fasta-sequences-size: $(SRCDIR)/extract-fasta-sequences-size.c
	$(CC) $(OPT) -I$(SRCDIR) -o $(BINDIR)/extract-fasta-sequences-size $(SRCDIR)/extract-fasta-sequences-size.c

clean:
	rm -rf $(DOCDIR) $(BINDIR)/* $(REPORTDIR)/*.aux $(REPORTDIR)/*.log  $(REPORTDIR)/rapport.pdf 

#$(BINDIR)/distanceEdition: $(CSOURCE)
#	$(CC) $(CFLAGS)  $^ -o $@ 

$(BINDIR)/distanceEditiondebug: $(CSOURCE)
	$(CC) $(CFLAGS)  $^ -o $@ -DDEBUG

%.pdf: $(LATEXSOURCE)
	$(LATEXC) -output-directory $(REPORTDIR) $^ 

$(DOCDIR)/index.html: $(SRCDIR)/Doxyfile $(CSOURCE)
	$(DOCC) $(SRCDIR)/Doxyfile


test: $(BINDIR)/distanceEdition $(TESTDIR)/Makefile-test
	cd $(TESTDIR) ; make -f Makefile-test all 
	
test-ite: $(BINDIR)/distanceEdition-ite $(TESTDIR)/Makefile-test
	cd $(TESTDIR) ; make -f Makefile-test all 

test-caware: $(BINDIR)/distanceEdition-caware $(TESTDIR)/Makefile-test
	cd $(TESTDIR) ; make -f Makefile-test all 

test-coblivious: $(BINDIR)/distanceEdition-coblivious $(TESTDIR)/Makefile-test
	cd $(TESTDIR) ; make -f Makefile-test all 

test-valgrind: $(BINDIR)/distanceEdition $(TESTDIR)/Makefile-test
	make -f $(TESTDIR)/Makefile-test all-valgrind
	
.PHONY: all doc bin report 

