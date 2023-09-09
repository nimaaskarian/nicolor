#include <iostream>
#include <stdio.h>
#include <stdexcept>
#include <cmath>
#include "nicolor.h"
#include <tuple>
#define PARAM_NOT_BETWEEN(P,MIN,MAX) ((P) > (MAX) || (P) < (MIN))
#define rgb8IsInvalid(P) PARAM_NOT_BETWEEN(P,0,255)

Color::Color() 
{
}
Color Color::fromSRgb(double r, double g, double b)
{
  Color c;
  c.r = r;
  c.g = g;
  c.b = b;

  return c;
}
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
  if (rgb8IsInvalid(r) || rgb8IsInvalid(g) || rgb8IsInvalid(b))
    throw std::runtime_error("Invalid RGB color. P <= 255 and P > 0.");
  Color c;
  c.r = (double)r/255;
  c.g = (double)g/255;
  c.b = (double)b/255;

  return c;
}

void Color::lighten(double percentage)
{
  if (PARAM_NOT_BETWEEN(percentage, 0, 100))
    throw std::runtime_error("Percentage is invalid (Must be between 0 and 100)");

  double rToWhite = 1 - r;
  double gToWhite = 1 - g;
  double bToWhite = 1 - b;

  *this = *this+Color::fromSRgb(rToWhite, gToWhite, bToWhite)*(percentage/100);
}

void Color::darken(double percentage)
{
  if (PARAM_NOT_BETWEEN(percentage, 0, 100))
    throw std::runtime_error("Percentage is invalid (Must be between 0 and 100)");

  percentage = 100-percentage;
  *this = Color::fromSRgb(r, g, b)*(percentage/100);
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

double Color::contrastRatio(Color obj)
{
  double luma1 = relativeLuma();
  double luma2 = obj.relativeLuma();

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
  return std::string(c_str);
}
Color Color::operator *(double x)
{
  Color c = Color::fromSRgb(r, g, b);
  c.r*=x;
  c.g*=x;
  c.b*=x;

  return c;
}

Color Color::operator+(Color obj)
{
  Color output;
  output.r = this->r + obj.r;
  output.g = this->g + obj.g;
  output.b = this->b + obj.b;

  return output;
}

bool Color::equals(Color obj)
{
  if (toRgb8() == obj.toRgb8())
    return true;
  return false;
}
