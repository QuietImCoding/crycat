#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int convColorRGB(int r, int g, int b) {
  int red = r / 85;
  int green = g / 85;
  int blue = b / 85;

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

int main() {
  double h = 0, s = 1, l = 0.5;
  char cchar;
  
  while ( (cchar = getchar()) && cchar != EOF ) {
    int* rgb = hsl_to_rgb( h, s, l );
    int color = convColorRGB(rgb[0], rgb[1], rgb[2]);
    free(rgb);
    printf("\x1B[38;5;%dm%c",color, cchar);
    h = h > 1 ? 0 : h + (1.0 / 25);
  }
  printf("\x1B[30m");
  return EXIT_SUCCESS;
}
