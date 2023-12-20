
num = 500000 
name = "tests/main.sn"
with open(name, "w") as f:
    f.write("import std::io\n")
    for i in range(num):
        f.write(f"func hello{i}() {{ io::println(\"Hello {i}\"); }}\n")
    f.write("\npublic func main() i32 {\n")
    for i in range(num):
        f.write(f"\thello{i}()\n")
    f.write("\n}")
