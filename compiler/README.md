# cso1-codegenerator
X86 code generator for the CSO1 course. Complete docs can be found at `../docs/hwX-codegenerator.md`

### Directory Structure:
src - contains the code generator, ast printer, lex and yacc files.

inc - contains the include.h file which has the AST node data structures and variable symbol table declarations.

ref - contains the reference compiler that the students can use to implement the code.

scratch - contains some test code

test_programs - contains all test programs

### Usage:
```make``` generates the necessary executables

```sh compile.sh <toy_g_program> <output_assembly_file_name.g>``` uses the code generator to generate the assembly file, compile it with clang and then run the generated executable as a demonstration. Second argument can be any string, the compiler creates the file. BOTH ARGUMENTS ARE MANDATORY.

```sh ast.sh <toy_g_program>``` uses the AST printer to print the AST of the provided program. The argument is optional.
