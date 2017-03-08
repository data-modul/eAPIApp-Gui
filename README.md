eAPI-DM-Utility provides a simple GUI- application to use EAPI library.

Each tab window represents one feature of the EApi library. 

Tabs of the window are matched to the following features:

* Board information
* System Monitor
* Read/Write i2c
* GPIO pins
* Watchdog
* Storage

The eAPI-DM-Utility will be built by the following command:
 ~~~bash
$ qmake gui-demo.pro
$ make
~~~
The EApi library should be installed in **/usr/local/lib**. In case of another
installation path, the library path inside **gui-demo.pro** file should be 
referenced by **PREFIX** before run qmake command.
