#!/usr/bin/env bash
set -e

SNOWBALL_INSTALL_DIR=~/.snowball

OS=$(uname -s | awk '{print tolower($0)}')
ARCH=$(uname -m)

if [[ "$LIB_FOLDER" == "" ]]; then
    LIB_FOLDER="/usr/local/lib"
fi

YES="$1"

if test -t 1; then

    ncolors=$(tput colors)

    if test -n "$ncolors" && test $ncolors -ge 8; then
        bold="$(tput bold)"
        underline="$(tput smul)"
        standout="$(tput smso)"
        normal="$(tput sgr0)"
        black="${bold}$(tput setaf 0)"
        red="${bold}$(tput setaf 1)"
        green="${bold}$(tput setaf 2)"
        yellow="${bold}$(tput setaf 3)"
        blue="${bold}$(tput setaf 4)"
        magenta="${bold}$(tput setaf 5)"
        cyan="${bold}$(tput setaf 6)"
    fi
fi

log() {
  local output=/dev/stdout

  if [ $# -eq 0 ]; then
    log warn "LOGGER: missing log level; fallback to log as \"unknown\""
    log unknown
    return
  fi

  case $1 in
    unknown)
      level=unknown
      color="$black"
      ;;
    info)
      level=info
      color="$green"
      ;;
    warn)
      level=warn
      color="$yellow"
      ;;
    error)
      level=error
      output=/dev/stderr
      color="$red"
      ;;
    *)
      log warn "LOGGER: unknown log level \"$1\"; fallback to log as \"unknown\""
      log unknown $*
      return
  esac

  if [ $# -eq 1 ]; then
    if read line; then
      printf " ${color}%s${normal}: %s\n" "$level" "$line"
    fi < /dev/stdin
    while read line; do
      printf "  %s\n" "$line"
    done < /dev/stdin
  else
    printf " ${color}%s${normal}: %s\n" "$level" "${*:2}"
  fi >> $output
}

log info "Checking for valid operating system"

if [ "$OS" != "linux" ] && [ "$OS" != "darwin" ]; then
  echo "error: Pre-built binaries only exist for Linux and macOS." >&2
  exit 1
fi


SNOWBALL_BUILD_ARCHIVE=snowball-$OS-$ARCH.tar.gz
log info "Creating target directory: $SNOWBALL_INSTALL_DIR"

mkdir -p $SNOWBALL_INSTALL_DIR
cd $SNOWBALL_INSTALL_DIR
x=$(curl -L https://github.com/snowball-lang/snowball/releases/latest/download/"$SNOWBALL_BUILD_ARCHIVE" | tar zxvf - --strip-components=1)

log info "Moving required shared libraries to lib folder"
log warn "You may need to use 'sudo' password for this action"

if [[ "$OSTYPE" == "darwin"* ]]; then
    mv libSnowballRuntime.dylib $LIB_FOLDER
    mv libSnowball.dylib $LIB_FOLDER
else
    mv libSnowballRuntime.so $LIB_FOLDER
    mv libSnowball.so $LIB_FOLDER
fi

log info "Exporting snowball to PATH"

EXPORT_COMMAND="$(pwd)/bin"
log warn "PATH export command:"
log warn "  $EXPORT_COMMAND"

# function to check if a file exists and is writable
check_file_writable() {
    local file="$1"
    if [[ -e "$file" ]]; then
        if [[ -w "$file" ]]; then
            return 0
        else
            log error "$file is not writable"
            return 1
        fi
    else
        return 1
    fi
}

# function to prompt the user for input
prompt_user() {
    local message="$1"
    local default_value="$2"
    local allowed_values="$3"
    
    read -p "$message" -i "$default_value" -e value
    if [[ -n "$allowed_values" ]]; then
        if [[ "$allowed_values" == *"$value"* ]]; then
            echo "$value"
        else
            echo "$default_value"
        fi
    else
        echo "$value"
    fi
}

# function to add the command to the PATH in the config file
add_command_to_path() {
    local config_file="$1"

    if grep -q "$EXPORT_COMMAND" "$config_file"; then
        log warn "PATH already updated in $config_file; skipping update."
        return
    fi

    if [[ "$YES" == "-y" ]]; then
        add_to_path="y"
    else
        read -p "Do you want to add $EXPORT_COMMAND to PATH in $config_file? [y/n]: " add_to_path
    fi
    if [[ "$add_to_path" == "y" ]]; then
        log info "Updating $config_file ..."
        echo "" >> "$config_file"
        log info "executing \"export PATH=\"\$PATH:$EXPORT_COMMAND\"\""
        echo "export PATH=\"\$PATH:$EXPORT_COMMAND\"" >> "$config_file"
    else
        log warn "Skipping update of $config_file."
    fi
}

# function to update the appropriate config file based on the shell
update_config_file() {
    local shell="$1"

    case "$shell" in
        *zsh)
            local zshrc="$HOME/.zshrc"
            local zshenv="$HOME/.zshenv"
            if check_file_writable "$zshrc"; then
                add_command_to_path "$zshrc"
            elif check_file_writable "$zshenv"; then
                add_command_to_path "$zshenv"
            else
                log error "Cannot find a writable zsh config file"
                exit 1
            fi
            ;;
        *bash)
            local bashrc="$HOME/.bashrc"
            local bash_profile="$HOME/.bash_profile"
            if check_file_writable "$bash_profile"; then
                add_command_to_path "$bash_profile"
            elif check_file_writable "$bashrc"; then
                add_command_to_path "$bashrc"
            else
                log error "Cannot find a writable bash config file"
                exit 1
            fi
            ;;
        *)
            log error "Unknown shell type $shell"
            exit 1
            ;;
    esac
}

log info "Detecting user default shell"

if [[ "$SNOWBALL_SHELL" == "" ]]; then
    shell="$SHELL"
else
    shell="$SNOWBALL_SHELL"
fi

if [[ -z "$shell" ]]; then
    shell=$(ps -p $$ -o args= | awk '{print $1}')
fi

log info "Updating configuration file"

update_config_file "$shell"

printf "\n    ${green}snowball-${OS}-${ARCH}${normal} - successfully installed with stdlib\n\n"

log info "Snowball successfully installed at: $(pwd)"
log info "Open a new terminal session or update your PATH to use snowball"
echo ""
log info "Checkoutt the documentation at: https://github.com/snowball-lang/docs"
log info "Happy coding! 🐱"
