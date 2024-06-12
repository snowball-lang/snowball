<img src="assets/logo.png" height="200" align="left"/>

### `Snowball`
*A fast, high-level programming language 🐱*

Snowball provides a high-level, easy-to-use syntax for writing fast, efficient code. It is designed to be **easy to learn and use**, while still providing the performance of a low-level language.

<br/>
<br/>

### One example to prove itself

Object-oriented programming, high-level abstractions, and low-level control are all possible with Snowball. Here's a simple example to demonstrate its capabilities:

```swift

// Generics and interface bound checks
func print<T: ToString>(x: T) {
  // A simple yet powerful standard library
  std::io::println(x);
}

func main() {
  let mut a; // Mutability safety
  a = 10; // Type safety and type inference
  let b = a; // Borrowing and immutability
  print(b); // Type inference to its best
}
```