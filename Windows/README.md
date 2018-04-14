Windows solution.<br>
CLIENT_FILES directory contains the client application files.<br>
LIBRARY_FILES directory contains the library files.<br>
Platform specific executable.<br>
<br>

Visual Studio settings to create application:<br>
* Property Pages<br>
* Linker : Input<br>
** Additional Dependencies : (append) O_STMDLL.LIB
* VC++ Directories :<br> 
** Library Directories : path/to/the/O_STMDLL.LIB directory EG: C:\Users\username\Documents\Visual Studio 2017\Projects\O_STMDLL\Release<br>
<br>
Make changes for Configuration - Release, Debugging and to Win32, x64 as well in order to copile the application x86 zn x64 version.<br>
<br>
For SHARED DLL usage<br>
When the applicatin has built, copy the shared library O_STMDLL.DLL to the same directory where the *.exe file created.<br>
Run the application.<br>
<br>
OR you can use the shared library from a specific folder with multiple application.<br>
Description :<br>
1. Create a folder somewhere in your file system EG: C:\DLL<br>
2. Copy the shared library to the directory created /C:\DLL\O_STMDLL.DLL<br>
3. Change the Environment Variables in your system.<br>
4. Add C:\DLL to the System Path<br>
5. Run the application.<br>

