# TQemu
Tiny Qemu run on any hosts (including JS/browser)

# How to build Native version to run on your Linux Host
'''
configure
make
'''
# How to build JS version to run on web browser
'''
emconfigure configure --with-host=js
make
'''

# How to build arm linux
reference config: prebuild/linux-3.18.config
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
