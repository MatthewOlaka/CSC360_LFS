Matthew Olaka
V00888684
Assignment 3
CSC360 

This assignment was to implement a Little Log File System, Specifically to 1. Manipulate a simulated disk, and format that disk, reading and writing of files in the root directory, creation of sub-directories, reading and writing of files in any directory, deletion of files and directories, Make LLFS robust, so that the file system is less likely to be corrupted if the machine it is running on crashes.

# Helpful links that helped me write the code:

https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
https://www.programiz.com/c-programming/library-function/string.h/strlen
https://stackoverflow.com/questions/9882252/weird-c-compiler-getting-an-error-ld-duplicate-symbol-main/19937679
https://en.wikipedia.org/wiki/Log-structured_file_system
https://www.geeksforgeeks.org/log-structured-file-system-lfs/

#Bugs
Doesn't read files from sub directories flawlessly.
Doesn't update inode map from subdirectories flawlessly either.
