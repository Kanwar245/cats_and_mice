/*
   UTSC - CSC B63 Winter 2012

   Image management utilities header file. You should look at this
   file and remember the functions used to create, delete, or
   change pixels in images since you will use them in this
   assignment. However, you do not need to change any code in
   this file or in imageUtils.c

   Updated by F. Estrada, March. 2012
*/

#ifndef __imageUtils_header
#define __imageUtils_header

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/*
  The structure below holds all the data needed to represent and
  manipulate a colour image. We store the number of pixels along
  the x and y direction, and provide a pointer to the memory
  area that will hold the image itself.

  The image data is organized as follows:

  Each pixel is represented by 3 colour components, R, G, and B that
  can have values in [0,255]. The higher the value, the brighter
  the corresponding colour component will be for the pixel. For
  example, a purely red pixel would have R=255, G=0, B=0. A
  white pixel would have R=255, G=255, B=255. Combinations of
  R,G, and B give all the colours your computer han candle.

  The RGB values for each pixel are stored consecutively in
  memory, for example, for a 2x2 image with pixels numbered
  p0 to p3, numbered in the standard raster order as follows

  p0 p1
  p2 p3

  The pixel data will be stored in memory as

  p0.R p0.G p0.B p1.R p1.G p1.B p2.R p2.G p2.B p3.R p3.G p3.B

  With this, you can easily work out the location in memory for
  each colour component for any given pixel. The setpixel()
  function simplifies setting pixel colours, but keep in mind
  that calling a function every time you need to change a pixel
  is slow (remember CSC B58!), and so, if you want your code to
  be very fast, you would access the image data directly
  through pointers.

  Here we are not so concerned with the speed of image
  manipulation, so feel free to use setpixel() whenever you
  want to change a pixel's colour.
*/
struct image{
	int sx;				// Image size on x
	int sy;				// Image size on y
	unsigned char *rgbdata;		// RGB data for each pixel
};

// Image management output. Note that you will need to de-allocate any images
// you allocate with newImage() using deleteImage().
struct image *readPPMimage(const char *filename);
struct image *newImage(int size_x, int size_y);
void setpixel(struct image *im, int x, int y, unsigned char R, unsigned char G, unsigned char B);
void getpixel(struct image *im, int x, int y, unsigned char *R, unsigned char *G, unsigned char *B);
void imageOutput(struct image *im, const char *filename);
void deleteImage(struct image *im);

/*
  In case you're wondering about the image format handled by this program.
  .ppm stands for 'portable pix map', and is a very simple format used
  in Linux/Unix systems along with related .pgm, .pnm, and .pfm formats.
  Windows doesn't know what to do with .ppm files on its own, you need
  The Gimp or a similar image manipulation program to see .ppm files on
  Windows.

  As a side note. If you're reading images using readPPMimage() make sure
  they are *properly* formatted. When in doubt, use The Gimp to output
  images in .ppm format.
*/

#endif
