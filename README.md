# abacus.c
Terminal program for handling numerical computation.
## Installation
git clone https://github.com/druidicgnosis/abacus.git<br />
cd abacus<br />
gcc -c ablib.c -o ablib.o && ar rcs ablib.a ablib.o && gcc abacus.c ablib.a -g -o abacus
## Usage
You can run it with no arguments which will prompt you to give an expression (10 + 8 etc). It also takes arguments of two numbers, and as of rn two flags: -s & -a. (-a is not currently implemented)<br />
Use +, -, ., /, % for addition, subtraction, multiplication, division, and modulus.
## Fun
A good command you can use is:<br />tr -dc 0-9 </dev/urandom | head -c 5G > file.txt.<br />This will generate a really big number which you can add to other big numbers using cat. This could take awhile but the number at the end will be really big.
