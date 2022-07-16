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

### Known Bugs

- [ ] Compiler errors/Warnings don't work

### None important
- [ ] Generate class function to scope before generating blocks

### In Progress

- [ ] String class
    - [x] __sum
    - [ ] __div
    - [ ] __sub
    - [ ] __mul
    - [ ] split
    - [ ] join
    - [x] __init
    - [ ] upper
    - [ ] lower
    - [ ] capitalize
- [ ] Modules
    - [ ] if library ends with .so, dlopen
    - [ ] check entry with a snowball.json
    - [ ] add a System class for I/O
    - [ ] add system/local modules support
    - [ ] custom variable/selected imports
- [ ] New keyword
- [ ] Classes
    - [x] Class/static keyword
    - [x] Parse class
    - [ ] Parse class
        - [x] Function
            - [x] Support for static
            - [ ] Public methods diferentiate from private methods (can have the same name)
        - [ ] Variables
            - [ ] Support for static
    - [x] Generate
        - [x] Struct type
        - [x] Functions
        - [x] Variables
        - [x] Self variable
    - [x] Call static methods
    - [x] Add `new` keyword support
    - [ ] Add all default override methods
        - [ ] __init
        - [ ] __sum
        - [ ] __sub
        - [ ] __div
        - [ ] __str
        - [ ] __repr
        - [ ] __bool
        - [ ] __eqeq
- [ ] add possitions to all nodes
- [ ] Unit testing
    - [x] Add a new class
        - [x] Add a function to class
    - [ ] Add a function
    - [ ] Add class/function to global
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