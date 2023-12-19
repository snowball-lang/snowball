
<!-- This code was brought to you by Fluffy the Cat -->

# Snowball 🐈

<p>

  Snowball is a low-weight, statically typed, object oriented programming language with garbage collector and module system.
    <br />
    <a href="https://snowball-lang.gitbook.io/docs/"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="">Website</a> · <a href="">Report Bug</a> · <a href="">Request Feature</a>
</p>

<hr>

## About The Project

👋 Greetings! Allow me to introduce you to Snowball, a statically-typed, low-weight, object-oriented programming language complete with a garbage collector and module system.

🚀 With a myriad of features to offer, Snowball boasts object-oriented programming, memory safety, built-in functions for enhanced productivity, and faster execution than other languages. Plus, its garbage collector and unit testing make it a comprehensive tool for developers.

🔍 So why not dive in and explore Snowball's capabilities? For more information, check out the [installation guide](#installation). Happy coding!

* [Discord](https://discord.gg/nnShMQzR4b)

## Getting Started with Snowball

### Installation

Before we get started, you'll need to have snowball installed into your compuiter. Linux and macOS users, you are in luck! You can use this simple command to download snowball and get started.

```
curl -fsSL https://raw.githubusercontent.com/snowball-lang/snowball/dev/scripts/install.sh | sudo -E bash -s -- -y
```

### Installation from source (unix)

```shell
git clone https://github.com/snowball-lang/snowball
cd snowball

# INSTALL REQUIRED DEPENDENCIES
sh ./build_scripts/install_deps.sh

sh ./build_scripts/release.sh
sudo make install -j100
```

**note**: We use -j100 to create *100 threads* to make the compilation faster. This will make your computer slower, it can be removed.

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

```kt
import Core::System;

public func main() i32 {
    System::println("Hello, world! 🐱");
}
```

* [Try it online](https://godbolt.org/z/6vrsWTbre)

## Roadmap

See the [open issues](https://github.com/snowball-lang/snowball/issues) for a full list of proposed features (and known issues).

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
* Discord: https://discord.com/invite/nnShMQzR4b
