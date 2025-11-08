# abacus.c
Terminal program for handling numerical computation.
## Installation
gcc abacus.c -o abacus && ./abacus 67 41 -a
## Usage
You can run it with no arguments which will prompt you to give numbers. It also takes arguments of two numbers, and as of rn two flags: -s & -a.
-s returns only the result converted back into digits, while -a plays a jank animation.
## Fun
A good command you can use is:<br />tr -dc 0-9 </dev/urandom | head -c 5G > file.txt.<br />This will generate a really big number which you can add to other big numbers using cat. This could take awhile but the number at the end will be really big.
