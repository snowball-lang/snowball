
# Snowball 🐈 

<p>

  Snowball is a low-weight, dynamically typed, object oriented programming language with garbage collector and module system.
    <br />
    <a href=""><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="">Website</a> ·<a href="">Report Bug</a>·<a href="">Request Feature</a>
</p>

<hr>

## About The Project

Snowball is a low-weight, dynamically typed, object oriented programming language with garbage collector and module system.

Features:
* Object oriented programming
* It is memory safe
* Built-in functions for better productions
* Faster than other programming lanugages
* Garbage collector
* Unit testing

It has a lot more features that can be explored! You can check them out in the [documentation]().

## Getting Started with Snowball

### Installation

Before we get started, you'll need to have snowball installed into your compuiter. Linux and macOS users, you are in luck! You can use this simple command to download snowball and get started.

```
curl -fsSL https://raw.githubusercontent.com/snowball-lang/snowball/dev/scripts/install.sh | bash -s
```

### Writing Your First Snowball Program

First, you will need a new snowball project. For that, create a new directory and execute the following command:

```
mkdir myProject
cd myProject

snowball init
```

### Executing snowball code

In order to execute snowball code, you can run the following command to build **and** run the program:

```
snowball run
```

## How does snowball feel?

Here is an example of a class in snowball.

```rs
use Core::System

class Vector {

    priv let x: i32 = 0
    priv let y: i32 = 0

  pub:
    Vector(x: Int, y: Int) {
        self.x = x
        self.y = y
    }

    // JS equivalent: const __sum = (this, vec2) => new Vector(...)
    // overrides operator +
    operator +(vec2: Vector) Vector =>
        new Vector(self.x + vec2.x, self.y + vec2.y)

    operator str() String {
        return "Vector(x=${self.x} y=${self.y})"
    }
}

fn main() Int {
    let vec1 = new Vector(1,2)
    let vec2 = new Vector(10,22)

    System::println(vec1 + vec2)
    return 0
}
```

## Roadmap

The TODO list can be found in [TODO.md](./TODO.md)

See the [open issues]() for a full list of proposed features (and known issues).

## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

Distributed under the MIT License. See `LICENSE` for more information.

## Links

Follow this links and tell us your thoughts, ask questions and be part of the Snowball community!

* GitHub : https://github.com/snowball-lang/snowball
* ORG    : https://github.com/snowball-lang
