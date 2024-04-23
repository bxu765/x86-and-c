# File              : Makefile
# Author            : Alenkruth Krishnan Murali
# 									: Daniel George Graham <dgg6b@virginia.edu>
# Date              : 08.02.2024
# Last Modified Date: 05.04.2024
# Last Modified By  : Alenkruth Krishnan Murali <<firstname>[at]virginia{dot}edu>

SRC := src
BUILD := bin
AS := as
INC := inc

# find the arch on which the makefile is invoked.
# MacOS does not allow -static linking. so creating
# different CFLAGS based on architecture
uname_s := $(shell uname -s)
uname_m := $(shell uname -m)
$(info The OS.architecture is $(uname_s).$(uname_m))

# system specific variables, add more here    
CFLAGS.Linux.x86_64 := -Wall -static -O3 -fomit-frame-pointer
CFLAGS.Darwin.arm64 := -Wall -O3 -fomit-frame-pointer

CFLAGS += $(CFLAGS.$(uname_s).$(uname_m))
$(info CFLAGS are "$(CFLAGS)")

all: compiler # ast

#interpreter: lexer
#	gcc -Wall -g lex.yy.c y.tab.c calc3a.c -o interpreter

compiler: lexer
	gcc $(CFLAGS) -I $(INC) lex.yy.c y.tab.c $(SRC)/code_generator.c -o $(BUILD)/code_generator

# We don't make AST parser in the starter code package. It will compilcate things for the students.
# students can use the grapher executable present in the ref directory to print the ASTs.
# ast: lexer
#	gcc $(CFLAGS) -I $(INC) lex.yy.c y.tab.c $(SRC)/ast_printer.c -o $(BUILD)/ast

lexer: parser
	lex $(SRC)/lex.l

parser: dir
	yacc -d $(SRC)/yacc.y

dir:
	mkdir -p as
	mkdir -p bin

.PHONY: clean
clean:
	rm -vf y.tab.h y.tab.c lex.yy.c
	rm -vf ./test_programs/*.out ./*.out
	rm -vf ./out.s
	rm -rvf $(BUILD) $(AS)
