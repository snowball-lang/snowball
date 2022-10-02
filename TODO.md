### Todo

- [ ] constant
- [ ] Add a preprocesor
- [ ] handle if function returns void, it can't be used as variable
- [ ] test for all operators
- [ ] default return type
- [ ] change location for OPTypes struct inside BinOP node
- [ ] change all compiler error to call macro COMPILER_ERROR
- [ ] Add readonly variables for classes
- [ ] change commands to separated folder/file
    - [ ] compile
    - [ ] REPL
    - [ ] unit testing
- [ ] check if class has been initialized
- [ ] call public function or private `e.g. (pub)function()`

### Known Bugs

- [ ] Check if class function is already defined
- [ ] Generics for class functions
- [ ] Compiler errors/Warnings don't work

### None important
- [ ] Generate class function to scope before generating blocks
- [ ] Add a Any type

### In Progress

- [ ] rework for operators
- [ ] global variables
- [ ] Attributes
- [ ] Add a generic system
    - [x] Functions
    - [ ] Classes
    - [ ] Default types
    - [ ] Infer types without explicitly typing it
- [ ] Modules
    - [ ] if library ends with .so, dlopen
    - [ ] check entry with a snowball.json
    - [x] add a System class for I/O
    - [x] add system/local modules support
    - [ ] custom variable/selected imports
- [ ] Classes
    - [x] Class/static keyword
    - [x] Parse class
    - [x] Parse class
        - [x] Function
            - [x] Support for static
            - [x] Public methods diferentiate from private methods (can have the same name)
        - [x] Variables
            - [x] Support for static
    - [x] Generate
        - [x] Struct type
        - [x] Functions
        - [x] Variables
        - [x] Self variable
    - [x] Call static methods
    - [ ] Inheritance
    - [x] Add `new` keyword support
    - [ ] Add all default override methods


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
- [x] New keyword
- [x] API
    - [x] Add a new class
        - [x] Add a function to class
    - [x] Add a function
    - [x] Add class/function to global
- [x] add optimizations
- [x] Let user choose in 32/64 bits numbers
- [x] `alloca` should not really be in the enviroment
- [x] Unit testing
    - [x] Add `test` keyword
    - [x] Parse test statement
    - [x] check for -t argument
    - [x] add TestingContext class
    - [x] Generate test statement
    - [x] Execute tests
    - [x] return result variable as int
    - [x] Add things like `assert`
- [x] Add a Void type
- [x] Int class
    - [x] Different types of integers
- [x] String class
- [x] Some "built in type" constructors are not found (sometimes)
