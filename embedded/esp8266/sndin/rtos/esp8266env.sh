export IDF_PATH=/opt/esp8266-rtos
export PATH="$IDF_PATH/tools:$PATH"
export MAKEFLAGS="-j$(nproc)"
export GNUMAKEFLAGS="-j$(nproc)"
source $HOME/esp-python/bin/activate
