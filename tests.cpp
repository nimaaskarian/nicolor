#include <gtest/gtest.h>
#include <nicolor.h>

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
TEST(FromStrTest, Handles3DigitColors) {
  EXPECT_TRUE(Color::fromStr("#fff").equals(Color::fromRgb8(255,255,255)));
  EXPECT_TRUE(Color::fromStr("#000").equals(Color::fromRgb8(0,0,0)));
  EXPECT_TRUE(Color::fromStr("#fe0").equals(Color::fromRgb8(255,238,0)));
  EXPECT_TRUE(Color::fromStr("#f01").equals(Color::fromRgb8(255,0,17)));
}
TEST(FromStrTest, HandleErrors) {
  // no #
  EXPECT_THROW(Color::fromStr("ffffff"),std::runtime_error);
  // not 6 or 3 digits
  EXPECT_THROW(Color::fromStr("#ffff"),std::runtime_error);
}
TEST(LightenTest, HandleValids) {
  Color black = Color::fromSRgb(0,0,0);
  black.lighten(100);
  EXPECT_TRUE(black.equals(Color::fromSRgb(1,1,1)));

  Color pink = Color::fromStr("#bc3897");
  pink.lighten(69);
  EXPECT_TRUE(pink.equals(Color::fromStr("#eac1de")));
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
