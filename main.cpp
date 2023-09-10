#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <nicolor.h>

void printColor(Color &currentColor, bool raw)
{
  if (raw) {
    std::cout << currentColor.toStr() << '\n';
    return;
  }
  Color white = Color::fromSRgb(1,1,1);
  Color black = Color::fromSRgb(0,0,0);
  Color foregroundColor = white;

  if (currentColor.contrastRatio(white) < currentColor.contrastRatio(black)) 
    foregroundColor = black;

  std::cout << foregroundColor.terminalForeground()
    << currentColor.terminalBackground() << currentColor.toStr() 
    << Color::backgroundEnd << Color::foregroundEnd << '\n';
}

int main (int argc, char *argv[]) 
{
  int ch;
  double lightenPercentage = 0, darkenPercentage = 0;
  std::size_t colorsCount = 20;
  bool fflag{}, tflag{}, rflag{};
  Color fromColor, toColor;
  while ((ch = getopt(argc, argv , "l:d:f:t:c:r")) != -1) {
    switch (ch) {
      case 'l':
        sscanf(optarg, "%lf", &lightenPercentage);
        break;
      case 'd':
        sscanf(optarg, "%lf", &darkenPercentage);
        break;
      // case 's':
      //   std::cout << argc - optind  << '\n';
      // break;
      case 'r':
        rflag = true;
      break;
      case 'f':
        fromColor = Color::fromStr(optarg);
        fflag = true;
      break;
      case 't':
          toColor = Color::fromStr(optarg);
          tflag = true;
        break;
      case 'c':
        sscanf(optarg, "%lu", &colorsCount);
        tflag = true;
      break;
      case '?':
        printf("?\n");
      break;
      default:
        printf("Hey. %s\n", optarg);
        return 1;
    }
  }
  if (tflag != fflag) {
    std::cerr << "-t and -f options should both be present or both not.\n";
    return 1;
  }
  std::vector<Color> colors;
  if (tflag) {
    colors = fromColor.colorsTo(toColor, colorsCount);
  }

  for (int i = optind; i < argc; i++) {
    colors.push_back(Color::fromStr(argv[i]));
  }

  for (auto color: colors) {
    color.lighten(lightenPercentage);
    color.darken(darkenPercentage);
    printColor(color, rflag);
  }
  return 0;
}
