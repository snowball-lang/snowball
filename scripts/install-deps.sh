set -ex

# Download the llvm.sh script
wget https://apt.llvm.org/llvm.sh

# Make the script executable
chmod +x llvm.sh

# Run the script to install LLVM 16
sudo ./llvm.sh 16

# Clean up
rm llvm.sh

# Verify installation
dpkg -l | grep llvm-16

# Manually install if necessary
sudo apt-get update
sudo apt-get install liblld-16-dev cmake llvm-16-tools libpolly-16-dev -y --reinstall

# Verify directories and binaries
ls /usr/lib | grep llvm-16
ls /usr/bin | grep llvm
ls /usr/bin | grep lld

ls /usr/lib/llvm-16/include

# Verify versions
llvm-config-16 --version


