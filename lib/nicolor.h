#ifndef COLOR_HPP
#define COLOR_HPP
#include <string>
#include <array>
#include <vector>
#include <string_view>
#include <stdexcept>

class Color {
  double r=0,g=0,b=0, a=1;
public:
  static constexpr std::string_view backgroundEnd = "\e[49m";
  static constexpr std::string_view foregroundEnd = "\e[39m";

  static Color fromRgb8(int r,int g,int b, int a = 255);
  static Color fromStr(std::string cssColor);
  static Color fromSRgb(double r, double g, double b, double a = 1);

  long int toLongHexadecimal();
  std::array<int, 3> toRgb8() const;
  std::array<int, 4> toRgba8() const;
  std::string toRgbStr();
  std::string toRgbaStr();


  bool equals(const Color obj) const;
  Color operator +(Color obj);
  Color operator -(Color obj);
  Color operator *(double x);
  Color operator /(double x);
  bool operator==(Color obj) const;

  std::vector<Color> colorsTo(Color to, std::size_t size=10);

  std::string terminalBackground();
  std::string terminalForeground();

  double relativeLumaFix(double p);
  double relativeLuma();
  double contrastRatio(Color obj);

  void lighten(double percentage);
  void darken(double percentage);

};


#endif // !COLOR_HPP
