#ifndef COLOR_HPP
#define COLOR_HPP
#include <string>
#include <array>

class Color {
  double r=0,g=0,b=0;
public:
  static Color fromRgb8(int r,int g,int b);
  static Color fromStr(std::string cssColor);
  static Color fromSRgb(double r, double g, double b);
  Color();

  std::array<int, 3> toRgb8();
  std::string toStr();


  bool equals(const Color obj);
  // friend bool operator ==(const Color obj1,const Color obj2) ;
  Color operator +(Color obj);
  Color operator *(double x);

  double relativeLumaFix(double p);
  double relativeLuma();
  double contrastRatio(Color obj);

  void lighten(double percentage);
  void darken(double percentage);

};
#endif // !COLOR_HPP
