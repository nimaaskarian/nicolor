#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <nicolor.h>

void printColor(Color &currentColor)
{
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
  while ((ch = getopt(argc, argv , "l:d:f:t:c:")) != -1) {
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

  if (tflag) {
    for (auto color: fromColor.colorsTo(toColor, colorsCount)) {
      printColor(color);
    }
  }

  for (int i = optind; i < argc; i++) {
    Color currentColor = Color::fromStr(argv[i]);
    currentColor.lighten(lightenPercentage);
    currentColor.darken(darkenPercentage);
    printColor(currentColor);
  }
  // black.lighten(99);
  return 0;
}
