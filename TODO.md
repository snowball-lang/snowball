### Todo

- [ ] constant
- [ ] Add a preprocesor
- [ ] handle if function returns void, it can't be used as variable
- [ ] test for all operators
- [ ] default return type
- [ ] Add readonly variables for classes
- [ ] check if class has been initialized
- [ ] call public function or private `e.g. (pub)function()`

### Known Bugs

- [ ] Check if class function is already defined
- [ ] Generics for class functions
- [ ] Check if namespaces/modules are the same while checking if var/func is private
    - [ ] Index node
    - [ ] identifier node
- [ ] Generic functions 'type "T" doe snot exist!'
- [ ] Compiler errors/Warnings don't work

### None important
- [ ] Add a Any type

### In Progress

- [ ] Add all operators missing
- [ ] Attributes
- [ ] Add a generic system
    - [x] Functions
    - [ ] Classes
    - [ ] Default types
    - [x] Infer types without explicitly typing it
- [ ] Modules
    - [ ] if library ends with .so, dlopen
    - [ ] check entry with a *.json
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
        - [x] generate struct with parent fields
        - [ ] Generate parent's functions/variables if they don't exist
        - [ ] virtual tables/functions
    - [x] Add `new` keyword support
    - [ ] Add all default override methods


### Done ✓

- [x] Variables
- [x] Function mangling
- [x] rework for operators
- [x] global variables
- [x] Function creation
    - [x] Function arguments
- [x] change location for OPTypes struct inside BinOP node
- [x] Comments
    - [x] Normal
    - [x] Multilines
- [x] Function return types
- [x] return statement
    - [x] parse return statemnt
    - [x] generate return stmt
    - [x] check if type of return is equal to function's return type
- [x] Generate class function to scope before generating blocks
- [x] change all compiler error to call macro COMPILER_ERROR
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
- [x] change commands to separated folder/file
    - [x] compile
    - [x] build
    - [x] unit testing