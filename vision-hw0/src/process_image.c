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
  int x;
  int y;

  for (x = 0; x < im.w; x++){
    for (y = 0; y < im.h; y++ /*  :P  */){
      luma_val = 0.299 * get_pixel(im, x, y, 0) + 0.587 * get_pixel(im, x, y, 1) + 0.114 * get_pixel(im, x, y, 2);
      set_pixel(gray, x, y, 0, luma_val);
    }
  }
  return gray;
}

void shift_image(image im, int c, float v)
{
  int x, y;
  for (x = 0; x < im.w; x++){
    for (y = 0; y < im.h; y++){
      float new_val = get_pixel(im, x, y, c) + v;
      set_pixel(im, x, y, c, new_val);
    }
  }
}

void clamp_image(image im)
{
  int i = 0;
  for (i = 0; i < im.w * im.h * im.c; i++){
    if (im.data[i] < 0){
      im.data[i] = 0;
    }
    if (im.data[i] > 1){
      im.data[i] = 1;
    }
  }
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
    int x, y;

    for (x = 0; x < im.w; x++) {
        for (y = 0; y < im.h; y++) {
            float r_chan = get_pixel(im, x, y, 0);
            float g_chan = get_pixel(im, x, y, 1);
            float b_chan = get_pixel(im, x, y, 2);

            float V = three_way_max(r_chan, g_chan, b_chan);
            float C = V - three_way_min(r_chan, g_chan, b_chan);
            float S = (V == 0) ? 0 : C / V;

            float H = 0;
            if (C != 0) {
                if (V == r_chan) {
                    H = (g_chan - b_chan) / C;
                } else if (V == g_chan) {
                    H = (b_chan - r_chan) / C + 2;
                } else { // V == b_chan
                    H = (r_chan - g_chan) / C + 4;
                }
                H *= 60;
                if (H < 0) H += 360;
            }

            set_pixel(im, x, y, 0, H / 360.0); // Normalize H to be in [0, 1]
            set_pixel(im, x, y, 1, S);
            set_pixel(im, x, y, 2, V);
        }
    }
}

void hsv_to_rgb(image im)
{
    int x, y;

    for (x = 0; x < im.w; x++) {
        for (y = 0; y < im.h; y++) {
            float H = get_pixel(im, x, y, 0) * 360.0; // Convert back to degrees
            float S = get_pixel(im, x, y, 1);
            float V = get_pixel(im, x, y, 2);

            float C = V * S;
            float X = C * (1 - fabs(fmod(H / 60.0, 2) - 1));
            float m = V - C;

            float r_prime, g_prime, b_prime;

            if (H >= 0 && H < 60) {
                r_prime = C; g_prime = X; b_prime = 0;
            } else if (H >= 60 && H < 120) {
                r_prime = X; g_prime = C; b_prime = 0;
            } else if (H >= 120 && H < 180) {
                r_prime = 0; g_prime = C; b_prime = X;
            } else if (H >= 180 && H < 240) {
                r_prime = 0; g_prime = X; b_prime = C;
            } else if (H >= 240 && H < 300) {
                r_prime = X; g_prime = 0; b_prime = C;
            } else {
                r_prime = C; g_prime = 0; b_prime = X;
            }

            float r = r_prime + m;
            float g = g_prime + m;
            float b = b_prime + m;

            set_pixel(im, x, y, 0, r);
            set_pixel(im, x, y, 1, g);
            set_pixel(im, x, y, 2, b);
        }
    }
}
