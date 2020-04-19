# Building Mau on MacOS X

Requirements:

* You have `homebrew` and XCode installed
* You have the following:
	* ```
	  brew install cmake sdl2 sdl2_image sdl2_mixer \
	               mikmod libogg libpng libjpeg \
	               libtiff webp
	               
	  ```
	  
To build and run Mau:

* `cd mau-game`
* `./build.sh`
* `cd build`
* `./mau`

To build a Release version:

`./build.sh Release`


