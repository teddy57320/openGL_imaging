# OpenGL_imaging 
This project uses the OpenGL API with Qt (compiled with MINGW 4.9.2 32 bit) to
render basic 3D graphics and rotate them. 

This program's plots coordinates in 3D space and connects them with lines. 
Text files are used to give coordinates and connectivity. 

The first text file is for the coordinates ("XYZ.txt")
This text file has 3 numbers on each line, separated by a space. 
The first, second and third number representing X, Y,
and Z coordinates, respectively, of a single point in 3D space.

The second text file is for connectivity ("CONN.txt")

An example of which is "CONN.txt". 
This text file has 2 numbers on each line, separated by a space. 
The numbers represent a line connection between points with the 
first and second number as indices. 
i.e. "1 2" signifies a connection between the second and third coordinate 
listed in "XYZ.txt" 


