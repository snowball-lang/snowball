
if [[ "$OSTYPE" == "darwin"* ]]; then
    SNOWBALL_INSTALL_DIR="~/Library/Application\ Support//.snowball"
else
    SNOWBALL_INSTALL_DIR=~/.snowball
fi

mkdir -p "$SNOWBALL_INSTALL_DIR"/libs
cp -r stdlib/. "$SNOWBALL_INSTALL_DIR"/libs