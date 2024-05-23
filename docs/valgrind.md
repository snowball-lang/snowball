
# Valgrind notes:

execute:

```sh
valgrind --tool=callgrind bin/Debug/snowball build -O0 --emit snowball-ir
callgrind_annotate callgrind.out.[pid] > analysis.txt
```

## For overall memory leak analysis:

```sh
valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s bin/Debug/snowball build &> analysis.txt
```
