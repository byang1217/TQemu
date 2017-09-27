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

# Technical Notes
## JS Limitation
emcc has func pointer limitation, which needs function prototype being matched strictly. 
	g_list cmp function needs to be reworked.


## JS debug
It can find corresponding C functions in JS code with additional prefix "\_" 

Sometimes, it needs to extend the exceptions levels to find error code. (change Error.stackTraceLimit by JS console)
