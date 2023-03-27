ARG ARCH
FROM "docker.io/$ARCH/ubuntu:20.04"

# Set the working directory to /app
WORKDIR /app

# Install dependencies
RUN apt-get update
RUN apt-get install -y \
    cmake \
    git \
    build-essential \
    llvm-14 \
    llvm-14-dev \
    gcc \
    g++

# Copy the source code into the container
COPY . .

# Configure and build the project
RUN sh ./build_scripts/release.sh