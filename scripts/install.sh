#!/usr/bin/env bash
set -e

# function to update the shell configuration file with the command
function update_config_file {
    local config_file="$1"

    if [[ -w "$config_file" ]]; then
        if ! grep -q "$COMMAND_TO_EXPORT" "$config_file"; then
            read -p "Do you want to update PATH in $config_file? [y/n] " -n 1 -r
            echo

            if [[ $REPLY =~ ^[Yy]$ ]]; then
                echo "Updating $config_file ..."
                echo "export PATH=\"\$PATH:$COMMAND_TO_EXPORT\"" >> "$config_file"
                echo "Command added to PATH in $config_file."
            else
                echo "Skipping update of $config_file."
            fi
        else
            echo "Command already in PATH in $config_file; skipping update."
        fi
    else
        echo "Error: Cannot write to $config_file. Please check file permissions."
    fi
}

SNOWBALL_INSTALL_DIR=~/.snowball
OS=$(uname -s | awk '{print tolower($0)}')
ARCH=$(uname -m)

LIB_FOLDER="/usr/lib"

if [ "$OS" != "linux" ] && [ "$OS" != "darwin" ]; then
  echo "error: Pre-built binaries only exist for Linux and macOS." >&2
  exit 1
fi

SNOWBALL_BUILD_ARCHIVE=snowball-$OS.tar.gz

mkdir -p $SNOWBALL_INSTALL_DIR
cd $SNOWBALL_INSTALL_DIR
curl -L https://github.com/snowball-lang/snowball/releases/latest/download/"$SNOWBALL_BUILD_ARCHIVE" | tar zxvf - --strip-components=1

sudo mv libSnowballRuntime.so $LIB_FOLDER

EXPORT_COMMAND="export PATH=$(pwd)/bin:\$PATH"
echo "PATH export command:"
echo "  $EXPORT_COMMAND"

# check the shell and update the appropriate config file
if [[ "$SHELL" == *zsh ]]; then
    if [[ -e "$HOME/.zshrc" ]]; then
        update_config_file "$HOME/.zshrc"
    elif [[ -e "$HOME/.zshenv" ]]; then
        update_config_file "$HOME/.zshenv"
    else
        echo "Could not find a zsh configuration file to update PATH"
    fi
elif [[ "$SHELL" == *bash ]]; then
    if [[ -e "$HOME/.bash_profile" ]]; then
        update_config_file "$HOME/.bash_profile"
    elif [[ -e "$HOME/.bashrc" ]]; then
        update_config_file "$HOME/.bashrc"
    else
        echo "Could not find a bash configuration file to update PATH"
    fi
else
    echo "Error: Unknown shell type $SHELL"
fi

echo "Snowball successfully installed at: $(pwd)"
echo "Open a new terminal session or update your PATH to use snowball"

echo "Happy coding! 🐱"