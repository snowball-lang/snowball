ARG ARCH
ARG BUILDPLATFORM
FROM --platform=$BUILDPLATFORM "docker.io/$ARCH:20.04"

# Set the working directory to /app
WORKDIR /app

# Install dependencies
RUN apt-get update
RUN apt-get install -y \
    cmake \
    git \
    build-essential \
    sudo \
    gcc \
    wget \
    g++

RUN wget https://apt.llvm.org/llvm.sh
RUN chmod +x llvm.sh
RUN sudo ./llvm.sh 14

# Copy the source code into the container
COPY . .

# Configure and build the project
RUN sh ./build_scripts/release.sh