This project uses the OpenGL API with Qt (compiled with MINGW 4.9.2 32 bit) to
render basic 3D graphics and rotate them. 

This program's ability is limited to simply plotting coordinates in 3D space and 
connecting them through lines. We do this by making text files for Qt to 
read from to render the image. 

The first text file we make is for the coordinates.

An example of which is "XYZ.txt". This text file is to have 3 numbers on each 
line, separated by a space. The first, second and third number representing X, Y,
and Z coordinates, respectively. Each line would therefore symbolize a coordinate.
These coordinates are read and stored in a vector of type QVector3D (which we 
initialize as "std::vector<QVector3D> coordinates;").

The second text file is for connectivity.

An example of which is "CONN.txt". This text file is similar to that the text 
file for coordinates, but each line has 2 numbers instead of three. The numbers 
represent the indices of coordinates in the vector "coordinates that are to be
connected, as discussed in  the paragraph above. Therefore, the line "2 15" would
mean that the 2nd and 15th coordinate are connected with a line. Note that the 
example text file starts counting coordinates from 1 (as opposed to 0), so the 
function "readCoordinates" is designed to solve this problem when utilizing indices. 


Other notes:

-In "mainwindow.cpp", "xSlider" and "ySlider" refer to the custom set names for the 
 two sliders. Similarly, "Rotate" is a custom name for the rotation toggle button. 

-xSlider and ySlider can be used to rotate the image about the X and Y axes. 

-The directory names should be modified according to each user. 

-"initializeGL", "paintGL", and "resizeGL" are default openGL functions that 
 are automatically called

-Pressing "Toggle Rotate" will toggle between non-rotating and rotating modes.
 In rotating mode, click and drag to rotate the image. 

-The efficiency of this program has room for improvement.