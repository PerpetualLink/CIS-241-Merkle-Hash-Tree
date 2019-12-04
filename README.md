# CIS-241-Merkle-Hash
This program is designed to use the MD5 code for file integrity checks.
It is designed for the user to present a file with a list of paths to files that they wish to test.
The paths file in the code is called "Paths.txt"
After this code is provided the code will run through and read it line by line then reading the files at those locations
After that it will hash the contents of each file individually and write it to a file called "theseHash.txt"
The program will then read through the file it just created, that being "theseHash.txt" and store this in an array.
After that it will recursively loop through that array hashing the contents in pairs of two decreasing the size by half with each recursive call until eventually ending with one string.
This string is the *top hash* and is used to check file integrity. After running the program check if a "topHash.txt" file already exists.
If the file exists it compares the contents within that file with the current top hash.
If the file does not exist the program creates it.
