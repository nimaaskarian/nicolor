#include <algorithm>
#include <gtest/gtest.h>
#include <nicolor.h>
#include <vector>

int main (int argc, char *argv[]) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(FromStrTest, Handles6DigitColors) {
  EXPECT_TRUE(Color::fromStr("#ffffff").equals(Color::fromRgb8(255,255,255)));
  EXPECT_TRUE(Color::fromStr("#000000").equals(Color::fromRgb8(0,0,0)));
  EXPECT_TRUE(Color::fromStr("#ffee00").equals(Color::fromRgb8(255,238,0)));
  EXPECT_TRUE(Color::fromStr("#ff0011").equals(Color::fromRgb8(255,0,17)));
  EXPECT_TRUE(Color::fromStr("#ef2f2f").equals(Color::fromRgb8(239,47,47)));
}

TEST(FromStrTest, HandlesRgbaFullColors) {
  EXPECT_TRUE(Color::fromStr("#ffffffff").equals(Color::fromRgb8(255,255,255,255)));
  EXPECT_TRUE(Color::fromStr("#ffffff00").equals(Color::fromRgb8(255,255,255,0)));
  EXPECT_TRUE(Color::fromStr("#000000ff").equals(Color::fromRgb8(0,0,0,255)));
  EXPECT_TRUE(Color::fromStr("#ffee0000").equals(Color::fromRgb8(255,238,0,0)));
  EXPECT_TRUE(Color::fromStr("#ff001111").equals(Color::fromRgb8(255,0,17,17)));
}
TEST(FromStrTest, HandlesRgbaLilColors) {
  EXPECT_TRUE(Color::fromStr("#ffff").equals(Color::fromRgb8(255,255,255,255)));
  EXPECT_TRUE(Color::fromStr("#fff0").equals(Color::fromRgb8(255,255,255,0)));
  EXPECT_TRUE(Color::fromStr("#000f").equals(Color::fromRgb8(0,0,0,255)));
  EXPECT_TRUE(Color::fromStr("#fe00").equals(Color::fromRgb8(255,238,0,0)));
  EXPECT_TRUE(Color::fromStr("#f011").equals(Color::fromRgb8(255,0,17,17)));
}

TEST(FromStrTest, Handles3DigitColors) {
  EXPECT_TRUE(Color::fromStr("#fff").equals(Color::fromRgb8(255,255,255)));
  EXPECT_TRUE(Color::fromStr("#000").equals(Color::fromRgb8(0,0,0)));
  EXPECT_TRUE(Color::fromStr("#fe0").equals(Color::fromRgb8(255,238,0)));
  EXPECT_TRUE(Color::fromStr("#f01").equals(Color::fromRgb8(255,0,17)));
}
TEST(FromStrTest, HandlesRgb) {
  EXPECT_TRUE(Color::fromStr("rgb(255,255,255)").equals(Color::fromRgb8(255,255,255)));
  EXPECT_TRUE(Color::fromStr("rgb(0,0,0)").equals(Color::fromRgb8(0,0,0)));
  EXPECT_TRUE(Color::fromStr("rgb(255,238,0)").equals(Color::fromRgb8(255,238,0)));
  EXPECT_TRUE(Color::fromStr("rgb(255,0,17)").equals(Color::fromRgb8(255,0,17)));
}
TEST(FromStrTest, HandleErrors) {
  // no #
  EXPECT_THROW(Color::fromStr("ffffff"),std::runtime_error);
  // not 6 or 3 digits
  EXPECT_THROW(Color::fromStr("#fffff"),std::runtime_error);
}
TEST(LongHex, ValidOutput) {
  ASSERT_EQ(Color::fromStr("#fff").toLongHexadecimal(), 0xFFFFFFFF);
  ASSERT_EQ(Color::fromStr("#000").toLongHexadecimal(), 0x000000FF);
  ASSERT_EQ(Color::fromStr("#fffa").toLongHexadecimal(), 0xFFFFFFAA);
  ASSERT_EQ(Color::fromStr("#fafa").toLongHexadecimal(), 0xFFAAFFAA);
  ASSERT_EQ(Color::fromStr("#0a1a").toLongHexadecimal(), 0x00AA11AA);
}
TEST(DarkenTest, HandleRgb) {
  Color white = Color::fromSRgb(1,1,1);
  white.darken(100);
  EXPECT_TRUE(white.equals(Color::fromSRgb(0,0,0)));

  Color red = Color::fromStr("#AF4D17");
  red.darken(35);
  EXPECT_TRUE(red.equals(Color::fromStr("#71320E")));

}
TEST(DarkenTest, HandleRgba) {
  Color white = Color::fromSRgb(1,1,1, 0.5);
  white.darken(100);
  EXPECT_TRUE(white.equals(Color::fromSRgb(0,0,0, 0.5)));

  Color red = Color::fromStr("#AF4D1711");
  red.darken(35);
  EXPECT_TRUE(red.equals(Color::fromStr("#71320E11")));

}
TEST(LightenTest, HandleRgb) {
  Color black = Color::fromSRgb(0,0,0);
  black.lighten(100);
  EXPECT_TRUE(black.equals(Color::fromSRgb(1,1,1)));

  Color pink = Color::fromStr("#bc3897");
  pink.lighten(69);
  EXPECT_TRUE(pink.equals(Color::fromStr("#eac1de")));

}

TEST(LightenTest, HandleRgba) {
  Color black = Color::fromSRgb(0,0,0, 0.6);
  black.lighten(100);
  EXPECT_TRUE(black.equals(Color::fromSRgb(1,1,1, 0.6)));

  Color pink = Color::fromStr("#bc3897fe");
  pink.lighten(69);
  EXPECT_TRUE(pink.equals(Color::fromStr("#eac1defe")));
}

TEST(LightenTest, HandleInvalids) {
  Color black = Color::fromSRgb(0,0,0);
  EXPECT_THROW(black.lighten(-1),std::runtime_error);
  EXPECT_THROW(black.lighten(101),std::runtime_error);
}

TEST(FromRgb8Test, HandleValids) {
  EXPECT_TRUE(Color::fromRgb8(10,10,10).equals(Color::fromSRgb(0.039215686274509803,0.039215686274509803,0.039215686274509803)));
  EXPECT_TRUE(Color::fromRgb8(0,0,0).equals(Color::fromSRgb(0, 0, 0)));
  EXPECT_TRUE(Color::fromRgb8(255,255,255).equals(Color::fromSRgb(1, 1, 1)));
}

TEST(FromRgb8Test, HandleInvalids) {
  EXPECT_THROW(Color::fromRgb8(-1,-1,-1),std::runtime_error);
  EXPECT_THROW(Color::fromRgb8(256,256,256),std::runtime_error);
}

TEST(ContrastRatioTest, CaluclatesRight) {
  ASSERT_EQ(Color::fromRgb8(255, 255, 255).contrastRatio(Color::fromRgb8(0,0,0)), 21.0);
  ASSERT_EQ(Color::fromRgb8(0,0,0).contrastRatio(Color::fromRgb8(0,0,0)), 1.0);
  ASSERT_EQ(Color::fromStr("#8d4444").contrastRatio(Color::fromRgb8(0,0,0)), 3.0428639462706979);
}

TEST(ColorsToTest, CalculatesRight)
{
  std::vector<Color> testsVec = {
    Color::fromStr("#2a2a2a"), Color::fromStr("#555555"),
    Color::fromStr("#7f7f7f"), Color::fromStr("#aaaaaa"),
    Color::fromStr("#d4d4d4"),
  };
  std::vector<Color> blackToWhite = Color::fromStr("#000").colorsTo(Color::fromStr("#fff"), 5);
  std::vector<Color> whiteToBlack = Color::fromStr("#fff").colorsTo(Color::fromStr("#000"), 5);
  
  ASSERT_TRUE(testsVec == blackToWhite);
  std::reverse(testsVec.begin(), testsVec.end());
  ASSERT_TRUE(testsVec == whiteToBlack);
}

TEST(ToStrTest, FormattingNormalRight) 
{
  ASSERT_EQ(Color::fromStr("#fff").toRgbStr(), "#FFFFFF");
  ASSERT_EQ(Color::fromStr("#000").toRgbStr(), "#000000");
  ASSERT_EQ(Color::fromStr("#f00").toRgbStr(), "#FF0000");
}

TEST(ToStrTest, FormattingNormalEdgeCases)
{
  ASSERT_EQ(Color::fromStr("#0c0c0c").toRgbStr(), "#0C0C0C");
  ASSERT_EQ(Color::fromStr("#0a0a0a").toRgbStr(), "#0A0A0A");
  ASSERT_EQ(Color::fromStr("#0f0f0f").toRgbStr(), "#0F0F0F");

}
