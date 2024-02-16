export IDF_PATH=/opt/esp-idf
export PATH="$IDF_PATH/tools:$PATH"
export MAKEFLAGS="-j$(nproc)"
export GNUMAKEFLAGS="-j$(nproc)"
source $HOME/esp-python/bin/activate
