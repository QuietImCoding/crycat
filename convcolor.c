#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int convColorRGB(int r, int g, int b) {
  int red = r / 85;
  int green = g / 85;
  int blue = b / 85;

  //printf("Got colors:\n\tred: %d\n\tgreen: %d\n\tblue: %d\n", r, g, b);
  return 16 + (red * 36) + (green * 6) + blue;
}

int hue2rgb(double p, double q, double t){
  if(t < 0) t += 1;
  if(t > 1) t -= 1;
  if(t < 1.0/6) return (int)round((p + (q - p) * 6 * t) * 255);
  if(t < 1.0/2) return (int)round(q * 255);
  if(t < 2.0/3) return (int)round((p + (q - p) * (2.0/3 - t) * 6) * 255);
  return p;
}

int* hsl_to_rgb(double h, double s, double l) {
  int* rgb = malloc(sizeof(int) * 3);
  float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
  float p = 2 * l - q;
  rgb[0] = hue2rgb(p, q, h + 1.0/3);
  rgb[1] = hue2rgb(p, q, h);
  rgb[2] = hue2rgb(p, q, h - 1.0/3);
  return rgb;
}

int main(int argc, char** argv) {
  // Red goes down from up from 16 to 196
  // Green is which group of 6 from 
  double s = 1, l = 0.5;
  /*sscanf(argv[1], "%lf", &h);
  sscanf(argv[2], "%lf", &s);
  sscanf(argv[3], "%lf", &l);*/
  int arglen;
  for (int anum = 1; anum < argc; anum++ ) {
    arglen = strlen(argv[anum]);
    for (int i = 0; i < arglen; i++) {
      int* rgb = hsl_to_rgb( i * (1.0 / arglen), s, l );
      int color = convColorRGB(rgb[0], rgb[1], rgb[2]);
      free(rgb);
      printf("\x1B[38;5;%dm%c",color, argv[anum][i]);
    }
    printf(" ");
  }

  return EXIT_SUCCESS;
}
