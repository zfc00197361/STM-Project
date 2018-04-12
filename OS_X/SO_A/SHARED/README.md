MAC OSx Shared library

https://developer.apple.com/library/content/documentation/DeveloperTools/Conceptual/DynamicLibraries/100-Articles/UsingDynamicLibraries.html




The standard locations for header files are:<br>
~/include<br>
/usr/local/include<br> 
/usr/include<br>
<br>
The standard locations for dynamic libraries (.dylib) are:<br>
~/lib<br>
/usr/local/lib<br>
/usr/lib<br>
<br>
You may also place the .dylib file at a nonstandard location in your file system, but you must add that location to one of these environment variables:<br>
<br>
LD_LIBRARY_PATH<br>
DYLD_LIBRARY_PATH<br>
DYLD_FALLBACK_LIBRARY_PATH<br>
<br>
COPY Shared library to OSX system:<br>
sudo cp lib_o_stm.dylib /usr/lib<br>