Windows solution of Software Transactional Memory library.
CLIENT_FILES directory contains the client application files.
LIBRARY_FILES directory contains the library files.

Visual Studio settings to create application:
* Property Pages
* Linker : Input
** Additional Dependencies : (append) STM.LIB
* VC++ Directories : 
** Library Directories : path/to/the/STM.LIB directory EG: C:\Users\username\Documents\Visual Studio 2017\Projects\STM\Release

Make changes for Configuration - Release, Debugging and to Win32, x64 as well in order to copile the application x86 and x64 version.

For SHARED DLL usage
When the applicatin has built, copy the shared library STM.DLL to the same directory where the *.exe file created.
Run the application.

OR you can use the shared library from a specific folder with multiple application.
Description :
1. Create a folder somewhere in your file system EG: C:\DLL
2. Copy the shared library to the directory created /C:\DLL\STM.DLL
3. Change the Environment Variables in your system.
4. Add C:\DLL to the System Path
5. Run the application.

