// #include <fmt/core.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <nicolor.h>
#include <fmt/format.h>

void printColor(Color &currentColor)
{
  Color white = Color::fromSRgb(1,1,1);
  Color black = Color::fromSRgb(0,0,0);
  Color foregroundColor = white;

  if (currentColor.contrastRatio(white) < currentColor.contrastRatio(black)) 
    foregroundColor = black;

  fmt::print("{}{}{}{}{}\n", foregroundColor.terminalForeground(), currentColor.terminalBackground(), 
             currentColor.toStr(), Color::backgroundEnd, Color::foregroundEnd);
}

void printRaw(Color &currentColor)
{
  fmt::print("{}\n", currentColor.toStr());
}

void printNoText(Color &currentColor)
{
  fmt::print("{}       {}\n",currentColor.terminalBackground(), Color::backgroundEnd);
}

void rflagNflagBothExists() {
  fmt::system_error(1,"Can't use both r and n flags at the same time.\n");
}

int main (int argc, char *argv[]) 
{
  int ch;
  double lightenPercentage = 0, darkenPercentage = 0;
  std::size_t colorsCount = 20;
  bool fflag{}, tflag{}, rflag{}, nflag;
  Color fromColor, toColor;
  while ((ch = getopt(argc, argv , "l:d:f:t:c:rn")) != -1) {
    switch (ch) {
      case 'l':
        sscanf(optarg, "%lf", &lightenPercentage);
        break;
      case 'd':
        sscanf(optarg, "%lf", &darkenPercentage);
        break;
      case 'r':
        if (nflag) {
          rflagNflagBothExists();
        }
        rflag = true;
      break;
      case 'n':
        if (rflag) {
          rflagNflagBothExists();
        }
        nflag = true;
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

  // if its pipe read the stdin untill the end
  if (!isatty(fileno(stdin))) {
    std::string lineInput;
    while (getline(std::cin,lineInput)) {
      if (lineInput.length())
        colors.push_back(Color::fromStr(lineInput));
    }
  }

  for (auto color: colors) {
    color.lighten(lightenPercentage);
    color.darken(darkenPercentage);
    if (rflag) {
      printRaw(color);
      continue;
    }
    if (nflag) {
      printNoText(color);
      continue;
    }
    printColor(color);
  }
  return 0;
}
