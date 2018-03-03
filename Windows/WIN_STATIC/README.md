Windows STATIC library.<br>
The APP and LIB solution directory contains cpp, h files, test application and the Static lib project.<br> 
The STATIC_LIB directory containing the x64 .lib file.<br>
<br>
HOW TO BUILD THE APPLICATION WITH THE LIBRARY:<br>
<br>
The settings must change if the application build as a x86 or x64 application.<br>
To build x86 application use x86 .lib otherwise use x64 .lib at build time.<br>
Visual Studio settings to create application:<br>
1. Create empty project. This project will be the Application<br>
2. Add cpp and h files.<br>
3. Add new project to the project. This project will be the Static Library<br>
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

