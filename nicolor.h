#ifndef COLOR_HPP
#define COLOR_HPP
#include <string>
#include <array>

class Color {
public:
  double r=0,g=0,b=0;
  static Color fromRgb8(int r,int g,int b);
  static Color fromStr(std::string cssColor);
  static Color fromSRgb(double r, double g, double b);
  Color();

  std::array<int, 3> toRgb8();
  std::string toStr();


  bool operator ==(Color const &obj) const;
  Color operator +(Color &obj);

  double relativeLumaFix(double p);
  double relativeLuma();
  double contrastRatio(Color obj);
  
};
#endif // !COLOR_HPP
