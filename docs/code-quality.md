
# Code Quality

## Code Style

We make use of PascalCase for types and functions, camelCase for variables and constants.

Note that for constants and fields we need to use a prefix to indicate the type of the constant or field. For example, `kConstant` for constants and `mField` for fields. We also need to use a prefix for boolean variables, for example, `isFlag` or `hasValue` for booleans for arguments.

## Code Formatting

We use 2 spaces for indentation and no tabs. We also use a space after the `:` in type annotations and a space before and after operators.

## Code Documentation

We use JSDoc comments for documenting functions, types, and constants. We also use comments to explain complex logic or algorithms.

## Code Organization

We organize our code into modules and files. Each module should be responsible for a single concern and should be self-contained. We also use namespaces to avoid naming conflicts.

Each function should be as small as possible and should have a single responsibility. We also use descriptive names for functions and variables.

Bad example:

```c++
int DoSomething() {
  mValues.push_back(2);
  for (int i = 0; i < mValues.size(); i++) {
    if (mValues[i] == 2) {
      return i;
    }
  }

  if (mValues.size() > 0) {
    while (mValues.size() > 0) {
      mValues.pop_back();
    }
  }

  return -1;
}
```

Good example:

```c++
int DoSomething() {
  AddValue(2);
  return FindValue(2);
}
```

> Of course, this is a simplified example. In real-world scenarios, functions can be more complex.
> and believe me, in language development, they are.

