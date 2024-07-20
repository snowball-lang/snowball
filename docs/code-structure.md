
# Code Structure

```
src/ - Source code
  bin/ - Snowball binary source code (executable)
  main/ - Main compiler structure
    frontend/ - Frontend source code
      lexer/ - Lexer source code
      parser/ - Parser source code
      ast/ - AST source code
    middleend/ - Middleend source code
      typechecker/ - Typechecker source code
      irgen/ - IRGen source code
      semantic/ - Semantic source code
    backend/ - Backend source code
      llvm/ - LLVM backend source code
      lld/ - LLD backend source code
  common/ - Common source code
    utils/ - Utility source code
    io/ - IO source code
    error/ - Error source code
    testing/ - Testing source code
thirdparty/ - Third-party source code
templates/ - Templates
docs/ - Documentation  
```
