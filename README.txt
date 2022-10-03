


DESCRIPTION:

    This project takes in images stored in .ppm format and produces 
    .jpeg images, construcred from top-view lego bricks. Brick size can be adjusted with respect
    to the lowe dimesion of the image size.

    The main issue is that the output images have large white borders. I am only aware of one way
    of getting rid of those - modifying the postscript, which i don't know how to modify on-the-fly
    (and manual modification is not suitable for the demo purposes).

    Additionally, when the size of the rendered figures becomes too small, it starts to look like the figures
    are slightly shifted (even though they are not). It looks that way because of the slight rendering
    offset which is not noticeable for the larger figure sizes. 

    This project consists of the following files:
    Makefile
    dotter.cp 
    Stadium.ppm Lisa.ppm Max.ppm Plank.ppm

    Upon run, produces:
    dotter.o
    Stadium_Dense.jgr Stadium.jgr Lisa.jgr Max.jgr Plank.jgr
    Stadium_Dense.jpg Stadium.jpg Lisa.jpg Max.jpg Plank.jpg

    dotter.cpp prints lines that correspond to JGRAPH commands.
    The output of dotter is piped into the appropriate .jgf files.
    After that, .jgraph is ran, the output is transformed into .jpeg. 

Instructions:
    Note: this makefile is suitable SPECIFICALLY for hydra. It uses jgraph executable 
    form Plank's directory. If you want to run it anywhere else, you will have to modify a portion
    of the makefile to use your local jgraph.

    Simpy type "make run" in the terminal to compile and run the project.
    If you would like to remove generated files, type "make clean." 