#include <math.h>
#include "image.h"

float nn_interpolate(image im, float x, float y, int c)
{
  // simple implementation of nearest neighbor interpolation
  // round() returns the rounded value in C
  return get_pixel(im, round(x), round(y), c);
}

image nn_resize(image im, int w, int h)
{
  /* tricker than i thought! you have to remember ot offset it by 0.5 and scale it as well to map new coordinate plane -> points in old coordinate plane. */
  image resized_img = make_image(w, h, im.c);
  float x_scale = (float) im.w / w;
  float y_scale = (float) im.h / h;

  for (int x = 0; x < w; x++){
    for (int y = 0;  y < h; y++){
      for (int z = 0; z < im.c; z++){
        float scaled_x = (x + 0.5) * x_scale - 0.5;
        float scaled_y = (y + 0.5) * y_scale - 0.5;
        float interpolated_val = nn_interpolate(im, scaled_x, scaled_y, z);

        set_pixel(resized_img, x, y, z, interpolated_val);
      }
    }
  }
  
  return resized_img;
}

float bilinear_interpolate(image im, float x, float y, int c)
{
    // TODO
    return 0;
}

image bilinear_resize(image im, int w, int h)
{
    // TODO
    return make_image(1,1,1);
}

