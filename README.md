# OpencvTest
编译opencv



opencv-3.4.11、CMake 3.19.7、qt5.13.1 mingw32位、vs2017

下载exe，安装好后，默认已有vs2017、vs2019的x64库；打开cmake，选择的sources目录和编译后的目录入下：

![image-20210326164533332](https://github.com/Hongws/OpencvTest/tree/main/img/image-20210326164533332.png)

点击Configure按钮后，选择vs2017+win32编译，没用到的库（类似python、java的）错误提示可以忽略，完成后再点击Generate，然后到编译目录下用vs2017 win32打开编译（如果需要生成单一lib，注意勾选BUILD_opencv_world）

mingw32位编译，点击Configure按钮后，选择NMake Makefiles和Specify native compilers下一步，选择qt安装Qt5.13.1/Tools目录下的gcc.exe和g++.exe，点击Configure按钮后，右上角勾选Advanced选项，CMAKE_MAKE_PROGRAM项填MinGW/bin/mingw32-make.exe（不行，就选择绝对路径）；然后点击Generate按钮，用mingw的命令模式 输入mingw32-make install

