#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{ 
  // checking that x is in bounds, clipping if not
  if (x >= im.w){
    x = im.w - 1; 
  }
  if (x < 0){
    x = 0;
  }

  // checking that y is in bounds, clipping if not
  if (y >= im.h){
    y = im.h - 1; 
  }
  if (y < 0){
    y = 0;
  }

  // checking that channel is in bounds, clipping if not
  if (c >= im.c){
    c = im.c - 1; 
  }
  
  if (c < 0){
    c = 0;
  }

  // returning desired index
  int index = x + y*im.w + c*im.w*im.h;
  return im.data[index];
  
}


void set_pixel(image im, int x, int y, int c, float v)
{
  if ((x >= im.w) || (x < 0)){
    return;
  }
   if ((y >= im.h) || (y < 0)){
    return;
  }
   if ((c >= im.c) || (c < 0)){
    return;
  }

  int index = x + y*im.w + c*im.w*im.h;
  im.data[index] = v;
}


image copy_image(image im)
{
  image copy = make_image(im.w, im.h, im.c); 
  int i = 0;

  for (i = 0; i < im.w * im.h * im.c; i++){
    copy.data[i] = im.data[i];
  }
  return copy;
}

image rgb_to_grayscale(image im)
{
  assert(im.c == 3);
  image gray = make_image(im.w, im.h, 1);

  float luma_val = 0;
  int r;
  int c;

  for (r = 0; r < im.w; r++){
    for (c = 0; c < im.h; c++ /*  :P  */){
      luma_val = get_pixel(im, r, c, 0) + get_pixel(im, r, c, 1) + get_pixel(im, r, c, 2);
      set_pixel(gray, r, c, 0, luma_val);
    }
  }
  return gray;
}

void shift_image(image im, int c, float v)
{
    // TODO Fill this in
}

void clamp_image(image im)
{
    // TODO Fill this in
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    // TODO Fill this in
}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
}
