set -ex

# Clear file
echo "" > assets.h

# append to header file
xxd -i EXECUTABLE_MAIN >> assets.h
xxd -i LIBRARY_MAIN >> assets.h
xxd -i LIBRARY_TEST >> assets.h
xxd -i SN_CONFY >> assets.h
xxd -i SN_REKY >> assets.h
xxd -i _GITIGNORE >> assets.h
