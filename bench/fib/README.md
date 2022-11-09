Last benchmark was ran on October 22, 2022

## Natively compiled, statically typed

| Language | Total | Compile | Time, s | Run | Time, s | Ext |
|----------|-------|---------|---------|-----|---------|-----|
| snowball (compiled) |   10.628 | snowball build -o O3 |    0.120 | ./.sn/bin/out.o |   10.508 | snc |
| C |   11.034 | gcc -O3 -o fib fib.c |    0.049 | ./fib |   10.986 | c |
| C++ |   11.250 | clang++ -O3 -o fib fib.cpp |    0.082 | ./fib |   11.169 | cpp |

## Interpreted, dynamically typed

| Language | Time, s | Run | Ext |
|----------|---------|-----|-----|
| snowball (from run) |   10.626 | snowball run -o O3 | snr |
| Python3 |  806.032 | python3 fib.py | py3 |