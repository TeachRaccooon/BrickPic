#include <iostream>
#include <math.h>
#include <chrono>
#include <vector>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>

using std::vector;
using std::string;
using std::ifstream;
using std::ios;

// Generic rgb struct for colors
struct RGB
{
    unsigned char r, g, b;
};

// Generic image struct for pixels and size
struct ImageRGB
{
    int width, height;
    vector<RGB> data;
};

/*
Loads image stored in PPM format into the img data structure.
*/
void load_ppm(ImageRGB &img, string &name)
{
    ifstream f(name.c_str(), ios::binary);

    int mode = 0;
    string s;
    f >> s;

    // P3 stores pixels in ASCII
    if (s == "P3")
        mode = 3;
    // P6 stores pixels in binary
    else if (s == "P6")
        mode = 6;
    
    // Grab width & height
    f >> img.width;
    f >> img.height;
    
    // get bits
    int bits = 0;
    f >> bits;

    // Make sure img's data has enough space
    img.data.resize(img.width * img.height);

    // PPm using P3 format
    if (mode == 6)
    {
        f.get();
        f.read((char*)&img.data[0], img.data.size() * 3);
    }
    // PPM using P6 format
    else if (mode == 3)
    {
        for (int i = 0; i < img.data.size(); i++)
        {
            int v;
            f >> v;
            img.data[i].r = v;
            f >> v;
            img.data[i].g = v;
            f >> v;
            img.data[i].b = v;
        }
    }

    // close file
    f.close();
}

/*
Prints the basic header with axis limits and "newgraph" command
 */
void draw_head(int rows, int cols)
{
    int dim;
    if (cols > rows)
    {
        dim = cols;
    }
    else
    {
        dim = rows;
    }
    printf("newgraph\n\n");
    printf("xaxis min 0 max %d nodraw\n", dim);
    printf("yaxis min 0 max %d nodraw\n\n", dim);
}

/*
Draws a lego-like square with a circle and a shaded area. Real lego dimensions are different, but i think that this looks better.

There is a fun little bug that is not noticeable until you choose the "ratio parameter" of about 0.02.
At that point, size of the shading/padding rings and squares is so small that extrashaded pixel colored or not colored in becomes noticeable and it looks like 
squares are printed on top of each other, although they are not. it is just the shading on the left side that does not get "fullt erased" and shading on the right side that does.
If i were to get rif of the shading and padding part, this issue would not appear, but the picture looks shitty.
*/
void draw_lego(double r, double g, double b, double size, double x, double y)
{
    // Background square with a darker shade
    printf("newcurve marktype box    marksize %f %f cfill %f %f %f pts %f %f\n", size,        size,        r * 0.85,       g * 0.85,         b * 0.85, x, y);
    // Make another backround box to draw over the margin that gets thicker as the block size gets smaller (not sure on how to make the margin smaller by any other way)
    printf("newcurve marktype box    marksize %f %f cfill %f %f %f color %f %f %f pts %f %f\n", size * 0.95,        size * 0.95,        r * 0.85,       g * 0.85,         b * 0.85,        r * 0.85,       g * 0.85,         b * 0.85, x, y);
    // This makes "darker shade" circles around the main one
    for(double i = 0.90, j = 0.85; i > 0.6; i -= 0.01, j -= 0.02)
    {
        printf("newcurve marktype circle marksize %f %f cfill %f %f %f color %f %f %f pts %f %f\n", size * i, size * i, r * j, g * j, b * j, r * j, g * j, b * j, x, y);
    }
    // main circle
    printf("newcurve marktype circle marksize %f %f cfill %f %f %f pts %f %f\n", size * 0.6, size * 0.6, r, g, b, x, y);
    // Once again, another circle to get rid of the black margin
    printf("newcurve marktype circle marksize %f %f cfill %f %f %f color %f %f %f pts %f %f\n", size * 0.6 * 0.95, size * 0.6 * 0.95, r, g, b, r, g, b, x, y);
    printf("\n(* BLOCK END *)\n");
}
/*
Below is an attempt to make every pic render starting from the top left corner.
Unfortunately, the approximation of the proper coordinate does not work as well as I would like it to be
*/

/*
void ppm_to_lego(ImageRGB &img, string &name, double block_ratio)
{

    // Process input img
    load_ppm(img, name);
    int cols = img.width;
    int rows = img.height;

    printf("(* Cols: %d *)\n", cols);

    double block_size;
    if (cols > rows)
    {
        block_size = (double) rows * block_ratio;
    }
    else
    {
        block_size = (double) cols * block_ratio;
    }

    // Set the "plot size" to 2000 by 2000. Idk why this number, just made sense.
    draw_head(2000, 2000);

    double x_start = 0.4776 * block_size - 1800;
    double y_start = -0.4858 * block_size + 5100;

    printf("(* Cols: %d *)\n", cols);
    printf("(* BLOCK SIZE %f *) \n\n", block_size);

    int dsiplay_scale = 4;

    double i, j = 0;
    for (i = 0; i < rows; i += block_size)
    {
        for(j = 0; j < cols; j += block_size)
        {
            RGB color = img.data[(((int) i) * cols) + (int) j];
            //draw_lego(((int) color.r) / (double) 255, ((int) color.g) / (double) 255, ((int) color.b) / (double) 255, 2 * block_size, (2 * j), 2 * ((double) rows - i));
            draw_lego(((int) color.r) / (double) 255, ((int) color.g) / (double) 255, ((int) color.b) / (double) 255, dsiplay_scale * block_size, x_start + dsiplay_scale * j, y_start - dsiplay_scale * i);
        }
        printf("\n\n(* ROW END *)\n\n");
    }
    printf("newcurve marktype box    marksize %d %d cfill %d %d %d pts %f %f\n", 1500, 1500, 1, 0, 0, -1776 + 670.5, 5079 - 682.5);
    printf("newcurve marktype box    marksize %d %d cfill %d %d %d pts %d %d\n", 1000, 1000, 1, 0, 0, -1776 + 447, 5079 - 455);
    printf("newcurve marktype box    marksize %d %d cfill %d %d %d pts %d %d\n", 500, 500, 1, 0, 0, -1776 + 210, 5079 - 215);

    // Function to compute 0, 0
    printf("newcurve marktype box    marksize %d %d cfill %d %d %d pts %f %f\n", 175, 175, 1, 0, 0, 0.4776 * 175 - 1814.2619, -0.4858 * 175 + 5117.3973);
    printf("newcurve marktype box    marksize %d %d cfill %d %d %d pts %f %f\n", 175, 175, 1, 0, 0, 0.4776 * 175 - 1814.2619 + 175, -0.4858 * 175 + 5117.3973);
    
    printf("newcurve marktype box    marksize %d %d cfill %d %d %d pts %d %d\n", 100, 100, 1, 0, 0, -1776, 5079);
}
*/

/**
 Main routine doing the whole job.
 Essentially, parses the picture, checks what the color is at a certain coordinate and makes a 
 lego brick of the same color, placing it where it belongs on an output picture.
 */
void ppm_to_lego(ImageRGB &img, string &name, double block_ratio)
{
    // Process input img
    load_ppm(img, name);
    int cols = img.width;
    int rows = img.height;

    //printf("(* Cols: %d *)\n", cols);

    // Figure out what the blocks size is based on the block ratio
    double block_size;
    if (cols > rows)
    {
        block_size = (double) rows * block_ratio;
    }
    else
    {
        block_size = (double) cols * block_ratio;
    }

    // Draws the basic header based on the image dimesnions(honestly, img dim do not matter too much here)
    draw_head(rows, cols);

    //printf("(* BLOCK SIZE %f *) \n\n", block_size);

    // Picture parsing + lego rpinting
    double i, j = 0;
    for (i = block_size / 2; i < rows; i += block_size)
    {
        for(j = block_size / 2; j < cols; j += block_size)
        {
            RGB color = img.data[(((int) i) * cols) + (int) j];
            draw_lego(((int) color.r) / (double) 255, ((int) color.g) / (double) 255, ((int) color.b) / (double) 255, 2 * block_size, (2 * j) - cols / 2, 2 * ((double) rows - i));
        }
        printf("\n\n(* ROW END *)\n\n");
    }
}


/*
Main takes in args. 
The first one is the "block ratio" - what % of the input picture size should one block represent.
The larger the parameter, the larger the block and the more "compressed" the picture is.

The second is an input picture in a ppm format.
*/
int main(int argc, char **argv){

    struct ImageRGB img;
    double block_ratio = std::atof(argv[1]);

    for (int i = 2; i < argc; ++i)
    {
        string name = argv[i];
        ppm_to_lego(img, name, block_ratio);
    }

    return 0;
}