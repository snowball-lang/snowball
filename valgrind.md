
# Valgrind notes:

execute:

```sh
valgrind --tool=callgrind bin/Debug/snowball build -O0 --emit snowball-ir
callgrind_annotate callgrind.out.[pid] > analysis.txt
```
