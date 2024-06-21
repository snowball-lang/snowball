set -ex

if [ ! -f "EXECUTABLE_MAIN" ]; then
    echo "Please run this script from the src/app/src/files directory"
    exit 1
fi

# Clear file
echo "" > assets.h

# append to header file
xxd -i EXECUTABLE_MAIN >> assets.h
xxd -i LIBRARY_MAIN >> assets.h
xxd -i LIBRARY_TEST >> assets.h
xxd -i SN_CONFY >> assets.h
xxd -i SN_REKY >> assets.h
xxd -i _GITIGNORE >> assets.h
