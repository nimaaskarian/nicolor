#include <iostream>
#include <stdio.h>
#include <stdexcept>
#include <cmath>
#include <nicolor.h>

Color Color::fromStr(std::string cssColor)
{
  int r,g,b;
  int colorsFound = sscanf(cssColor.c_str(), "#%02x%02x%02x", &r,&g,&b);
  if (cssColor.length() == 4  || cssColor.length() == 7) {

    if(colorsFound == 3) 
      return fromRgb8(r,g,b);

    if (sscanf(cssColor.c_str(),"#%01x%01x%01x",&r,&g, &b) == 3) 
      return fromRgb8(r*17, g*17, b*17);

  }

  throw std::runtime_error("Invalid css color");
}

Color Color::fromRgb8(int r, int g, int b)
{
  Color c;
  c.r = (double)r/255;
  c.g = (double)g/255;
  c.b = (double)b/255;

  return c;
}

std::array<int, 3> Color::toRgb8()
{
  std::array<int, 3> output;
  output[0] = (int)( r*255 );
  output[1] = (int)( g*255 );
  output[2] = (int)( b*255 );

  return output;
}

double Color::relativeLumaFix(double p) 
{
  if (p <= 0.04045)
    p = p/12.92;
  else
    p = pow(((p+0.055)/1.055), 2.4);

  return p;
}

double Color::relativeLuma()
{

  double r = relativeLumaFix(this->r);
  double g = relativeLumaFix(this->g);
  double b = relativeLumaFix(this->b);

  return 0.2126*r + 0.7152*g + 0.0722 * b;
}

double Color::contrastRatio(Color &obj)
{
  double luma1 = relativeLuma();
  double luma2 = relativeLuma();

  if (luma1>luma2)
     return ( luma1 +0.05 )/( luma2 +0.05);
  else
     return ( luma2 +0.05 )/( luma1 +0.05);
}

std::string Color::toStr()
{
  std::array<int, 3> rgb8 = toRgb8();
  char *c_str = new char[8];
  snprintf(c_str, 8, "#%02x%02x%02x", rgb8[0],rgb8[1],rgb8[2]);
  std::cout << rgb8[2];
  return std::string(c_str);
}

Color Color::operator+(Color &obj)
{
  Color output;
  output.r = this->r + obj.r;
  output.g = this->g + obj.g;
  output.b = this->b + obj.b;

  return output;
}

bool Color::operator==(Color obj) const
{
  if (r == obj.r && g == obj.g && b == obj.b)
    return true;

  return false;
}

