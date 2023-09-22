#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <nicolor.h>
#include <fmt/format.h>
#include <tuple>

#define PARAM_NOT_BETWEEN(P,MIN,MAX) ((P) > (MAX) || (P) < (MIN))
#define rgb8IsInvalid(P) PARAM_NOT_BETWEEN(P,0,255)

Color Color::fromSRgb(double r, double g, double b, double a)
{
  Color c;
  c.r = r;
  c.g = g;
  c.b = b;
  c.a = a;

  return c;
}
Color Color::fromStr(std::string cssColor)
{
  int r,g,b,a;
  int colorsFound = sscanf(cssColor.c_str(), "#%02x%02x%02x%02x", &r,&g,&b, &a);
  if (cssColor.length() == 9 && colorsFound == 4)
      return fromRgb8(r,g,b,a);
  
  if (cssColor.length() == 7 && sscanf(cssColor.c_str(), "#%02x%02x%02x", &r,&g,&b) == 3)
    return fromRgb8(r,g,b);

  if (cssColor.length() == 5 && sscanf(cssColor.c_str(),"#%01x%01x%01x%01x",&r,&g, &b, &a) == 4) 
    return fromRgb8(r*17, g*17, b*17, a*17);

  if (cssColor.length() == 4 && sscanf(cssColor.c_str(),"#%01x%01x%01x",&r,&g, &b) == 3) 
    return fromRgb8(r*17, g*17, b*17);

  colorsFound = sscanf(cssColor.c_str(), "rgb(%d,%d,%d)",&r,&g,&b);
  if (colorsFound == 3) 
    return fromRgb8(r,g,b);
  if (sscanf(cssColor.c_str(), "rgba(%d,%d,%d,%d)",&r,&g,&b,&a) == 4) 
    return fromRgb8(r,g,b,a);

  throw std::runtime_error(fmt::format("Invalid css color: {}", cssColor));
}

Color Color::fromRgb8(int r, int g, int b, int a)
{
  if (rgb8IsInvalid(r) || rgb8IsInvalid(g) || rgb8IsInvalid(b) || rgb8IsInvalid(a))
    throw std::runtime_error("Invalid RGB color. P <= 255 and P > 0.");
  Color c;
  c.r = (double)r/255;
  c.g = (double)g/255;
  c.b = (double)b/255;
  c.a = (double)a/255;

  return c;
}

void Color::lighten(double percentage)
{
  if (PARAM_NOT_BETWEEN(percentage, 0, 100))
    throw std::runtime_error(fmt::format("Percentage '{}' is invalid (Must be between 0 and 100)", percentage));

  double rToWhite = 1 - r;
  double gToWhite = 1 - g;
  double bToWhite = 1 - b;

  *this = *this+Color::fromSRgb(rToWhite, gToWhite, bToWhite, 0)*(percentage/100);
}

void Color::darken(double percentage)
{
  if (PARAM_NOT_BETWEEN(percentage, 0, 100))
    throw std::runtime_error("Percentage is invalid (Must be between 0 and 100)");

  percentage = 100-percentage;
  *this = Color::fromSRgb(r, g, b, a*(100/percentage))*(percentage/100);
}

std::array<int, 3> Color::toRgb8() const
{
  std::array<int, 3> output;
  output[0] = (int)( r*255 );
  output[1] = (int)( g*255 );
  output[2] = (int)( b*255 );

  return output;
}

std::array<int, 4> Color::toRgba8() const
{
  std::array<int, 4> output;
  output[0] = (int)( r*255 );
  output[1] = (int)( g*255 );
  output[2] = (int)( b*255 );
  output[3] = (int)( a*255 );

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

std::string Color::toRgbStr()
{
  auto rgb8 = toRgb8();
  return fmt::format("#{:02X}{:02X}{:02X}",rgb8[0],rgb8[1],rgb8[2]);
}

std::string Color::toRgbaStr()
{
  auto rgb8 = toRgba8();
  return fmt::format("#{:02X}{:02X}{:02X}{:02X}",rgb8[0],rgb8[1],rgb8[2], rgb8[3]);
}

Color Color::operator *(double x)
{
  Color c = Color::fromSRgb(r, g, b, a);
  c.r*=x;
  c.g*=x;
  c.b*=x;
  c.a*=x;

  return c;
}

Color Color::operator /(double x)
{
  Color c = Color::fromSRgb(r, g, b, a);
  c.r/=x;
  c.g/=x;
  c.b/=x;
  c.a/=x;

  return c;
}

Color Color::operator+(Color obj)
{
  Color output;
  output.r = this->r + obj.r;
  output.g = this->g + obj.g;
  output.b = this->b + obj.b;
  output.a = this->a + obj.a;

  return output;
}

Color Color::operator-(Color obj)
{
  Color output;
  output.r = this->r - obj.r;
  output.g = this->g - obj.g;
  output.b = this->b - obj.b;
  output.a = this->a - obj.a;

  return output;
}

std::vector<Color> Color::colorsTo(Color to, std::size_t size)
{
  size++;
  Color dif = (to - *this)/size;
  std::vector<Color> output;

  for (int i = 1; i < size; i++) {
    output.push_back(*this + dif*i);
  }

  return output;
}

bool Color::equals(Color obj) const
{
  if (toRgb8() == obj.toRgb8())
    return true;
  return false;
}

bool Color::operator==(Color obj) const
{
  return equals(obj);
}

long int Color::toLongHexadecimal()
{
  auto rgba8 = toRgba8();
  return (long int)rgba8[0]*16777216+rgba8[1]*65536+rgba8[2]*256+rgba8[3];
}

std::string Color::terminalBackground()
{
  return fmt::format("\e[48:2::{}m", fmt::join(toRgb8(), ":"));
}

std::string Color::terminalForeground()
{
  return fmt::format("\e[38:2::{}m", fmt::join(toRgb8(), ":"));
}
