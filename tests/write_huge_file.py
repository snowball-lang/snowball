
import sys
import os

print("This script will generate a huge file for testing purposes.")
print("If you want to delete the files, run this script with the argument 'd'.")
if len(sys.argv) > 1 and sys.argv[1] == "d":
  print("Deleting files...")
  os.remove("huge_file.sn")
  os.remove("huge_file2.sn")
  exit()

content1 = """\
func test{}(_x: i32) {{}}
"""

content2 = """\
\ttest{}({});\
"""

temp = """\
public func test() i32 {
"""

num = int((10000)/2)

def write(f):
  for i in range(1, num):
    f.write(content1.format(i))

  f.write(temp)
  for i in range(1, num):
    f.write(content2.format(i, i))
  f.write("}")

write(open("huge_file.sn", "w"))
write(open("huge_file2.sn", "w"))

