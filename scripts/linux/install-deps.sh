wget https://apt.llvm.org/llvm.sh && chmod +x llvm.sh

./llvm.sh 18
rm llvm.sh

sudo apt-get install -y clang-18 clang++-18 lld-18 libc++-18-dev libc++abi-18-dev
