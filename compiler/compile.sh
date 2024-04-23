#! /bin/sh

# stop script execution when there is an error
set -e

# usage guidance
echo "usage: sh compile.sh <input_toy_g_program> <output_assembly_file_name>"
# ToyG compilation
echo "Compiling $1 using ToyG compiler at ./bin/code_generator"
# use the code generator to emit the compiled assembly
./bin/code_generator $1
# the code generator emits the output file in the home directory. We will move 
# this into as directory
mv out.s ./as/$2
echo "Compilation successful; x86 Assembly generated at ./as/$2"

# x86 Assembling to ELF using clang assembler
echo "Assembling $2 to ELF"
clang ./as/$2 -o ./bin/$2.out -static -O3 -fomit-frame-pointer -Wno-everything
echo "Assembling succesful; x86 ELF generated at ./bin/$2.out"

# run the executable to get the output
echo "Running the generated ELF to demonstrate what the code does"
./bin/$2.out
echo "SUCCESS!"
echo "You can run this ELF file using the command ./bin/$2.out"
echo "Exiting"