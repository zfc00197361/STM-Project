Windows STATIC library.<br>
The 32 bit dll version can be found in the x86 directory.<br>
The 64 bit dll version can be found in the x64 directory.<br>
The APP solution directory contains cpp, h files and the test application.<br> 
The DLL solution directory contains the c, h files and the Visual Studio DLL solution.<br>
<br>
HOW TO USE THE LIBRARY:<br>
The DLL solution directory containing the Visual Studio 2017 solution to build the x64 and x86 version of the library.<br>
The APP solution directory containing the Visual Studio 2017 solution to build the test app to use the static library.<br>
<br>
The settings must change if the application buil as a x86 or x64 application.<br>
To build x86 application use x86 DLL otherwise use x64 DLL at linking time.<br>
Visual Studio settings to create application:<br>
1. Create empty project. This project will be the application<br>
2. Add cpp and h files.<br>
3. Add new project to the project. This project will be the static library<br>
5. Add cpp and h files.<br>
4. Property Pages<br>
* General.<br>
** Configuration type : Change to Static library (.lib).<br>
5. Application properties.<br>
* Property Pages<br>
* General.<br>
**Additional Include Directories - path/to/the/*.lib file EG: C:\Users\user\Documents\Visual Studio 2017\Projects\O_STMDLL_S\x64\Release.<br>
6. Add reference to the application.<br>
* In the properti windows select the Static library project.<br>
7. Build Static library.<br>
8. Build Application.<br>
9. Run the Application *.exe file

