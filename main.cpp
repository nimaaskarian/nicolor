#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <nicolor.h>


int main (int argc, char *argv[]) {
  int ch;
  double lightenPercentage = 0, darkenPercentage = 0;
  while ((ch = getopt(argc, argv , "l:d:")) != -1) {
    switch (ch) {
      case 'l':
        sscanf(optarg, "%lf", &lightenPercentage);
        break;
      case 'd':
        sscanf(optarg, "%lf", &darkenPercentage);
        break;
      case '?':
        printf("?\n");
        break;
      default:
        printf("Hey. %s\n", optarg);
        return 1;
    }
  }
  for (int i = optind; i < argc; i++) {
    Color currentColor = Color::fromStr(argv[i]);
    currentColor.lighten(lightenPercentage);
    currentColor.darken(darkenPercentage);
    std::cout << currentColor.toStr() << '\n';
  }
  // black.lighten(99);
  return 0;
}
