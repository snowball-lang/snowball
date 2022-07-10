### Todo

- [ ] constant
- [ ] Void class
- [ ] static methods
- [ ] global variables
- [ ] default return type
- [ ] change location for OPTypes struct inside BinOP node
- [ ] change all compiler error to call macro COMPILER_ERROR
- [ ] change commands to separated folder/file
    - [ ] compile
    - [ ] REPL
    - [ ] unit testing
- [ ] check if class has been initialized
- [ ] Modules
    - [ ] module keyword (like in nodejs)
    - [ ] add a System class for I/O
    - [ ] add system/local modules support
    - [ ] custom variable/selected imports

### Known Bugs

- [ ] Compiler errors/Warnings don't work

### In Progress

- [ ] String class
    - [ ] __sum
    - [ ] __div
    - [ ] __sub
    - [ ] __mul
    - [ ] split
    - [ ] join
    - [x] __init
    - [ ] upper
    - [ ] lower
    - [ ] capitalize
- [ ] Classes
    - [x] Class/static keyword
    - [x] Parse class
    - [ ] Parse class
        - [x] Function
            - [x] Support for static
        - [ ] Variables
            - [ ] Support for static
    - [ ] Generate
        - [x] Struct type
        - [x] Functions
        - [ ] Variables
        - [ ] Self variable
- [ ] add possitions to all nodes
- [ ] Unit testing
    - [x] Add `test` keyword
    - [x] Parse test statement
    - [x] check for -t argument
    - [x] add TestingContext class
    - [x] Generate test statement
    - [x] Execute tests
    - [ ] return result variable as int
    - [ ] Add things like `assert`
- [ ] Number class
- [ ] add optimizations
- [ ] Let user choose in 32/64 bits numbers

### Done ✓

- [x] Variables
- [x] Function mangling
- [x] Function creation
    - [x] Function arguments
- [x] Comments
    - [x] Normal
    - [x] Multilines
- [x] Function return types
- [x] return statement
    - [x] parse return statemnt
    - [x] generate return stmt
    - [x] check if type of return is equal to function's return type
- [x] Perform function calls
    - [x] pass arguments
    - [x] pass self argument if it is a class
    - [x] check if function class is initiated
        - [x] check if function is static