
num = 60000
name = "tests/main.sn"

with open(name, "w") as f:

    f.write("use Core::System\n")

    for i in range(num):
        f.write(f"fn hello{i}() {{ System::println(\"Hello {i}\"); }}\n")

    f.write("\npub fn main() i32 {\n")

    for i in range(num):
        f.write(f"\thello{i}()\n")

    f.write("\n}")
