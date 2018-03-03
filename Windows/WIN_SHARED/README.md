Windows Shared library<br>
The 32 bit dll version can be found in the x86 directory.<br>
The 64 bit dll version can be found in the x64 directory.<br>
The APP solution directory contains cpp, h files and the test application.<br> 
The DLL solution directory contains the c, h files and the Visual Studio DLL solution.<br>
<br>
HOW TO USE THE LIBRARY:<br>
The DLL solution directory containing the Visual Studio 2017 solution to build the x64 and x86 version of the library.<br>
The APP solution directory containing the Visual Studio 2017 solution to build the test app to use the shared library.<br>
<br>
Visual Studio settings to create application:<br>
* Property Pages<br>
* Linker : Input<br>
** Additional Dependencies : O_STMDLL.LIB
* VC++ Directories :<br> 
** Library Directories : path/to/the/O_STMDLL.LIB directory EG: C:\Users\username\Documents\Visual Studio 2017\Projects\O_STMDLL\Release<br>
<br>
Make changes for Configuration - Release, Debugging and to Win32, x64 as well in order to copile the application x86 zn x64 version.<br>
<br>
When the applicatin has built, copy the shared library O_STMDLL.DLL to the same directory where the *.exe file created.<br>
Run the application.<br>
<br>
OR you can use the shared library from a specific folder with multiple application.<br>
Description :<br>
1. Create a folder somewhere in your file system EG: C:\DLL<br>
2. Copy the shared library to the directory created /C:\DLL\O_STMDLL.DLL<br>
3. Change the Environment Variables in your system.<br>
4. Add C:\DLL to the Path<br>
5. Run the application.<br>

