#include <gtest/gtest.h>
#include <nicolor.h>

int main (int argc, char *argv[]) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(fromStrTest, handles6DigitColors) {
  ASSERT_EQ(Color::fromStr("#ffffff"), Color::fromRgb8(255,255,255));
  ASSERT_EQ(Color::fromStr("#000000"), Color::fromRgb8(0,0,0));
  ASSERT_EQ(Color::fromStr("#ffee00"), Color::fromRgb8(255,238,0));
  ASSERT_EQ(Color::fromStr("#ff0011"), Color::fromRgb8(255,0,17));
  ASSERT_EQ(Color::fromStr("#ef2f2f"), Color::fromRgb8(239,47,47));
}
TEST(fromStrTest, handles3DigitColors) {
  ASSERT_EQ(Color::fromStr("#fff"), Color::fromRgb8(255,255,255));
  ASSERT_EQ(Color::fromStr("#000"), Color::fromRgb8(0,0,0));
  ASSERT_EQ(Color::fromStr("#fe0"), Color::fromRgb8(255,238,0));
  ASSERT_EQ(Color::fromStr("#f01"), Color::fromRgb8(255,0,17));
}
TEST(fromStrTest, handleErrors) {
  // no #
  EXPECT_THROW(Color::fromStr("ffffff"),std::runtime_error);
  // not 6 or 3 digits
  EXPECT_THROW(Color::fromStr("#ffff"),std::runtime_error);
}

TEST(fromRgb8Test, handleValids) {
  ASSERT_EQ(Color::fromRgb8(10,10,10),Color::fromSRgb(0.039215686274509803,0.039215686274509803,0.039215686274509803));
  ASSERT_EQ(Color::fromRgb8(0,0,0),Color::fromSRgb(0, 0, 0));
  ASSERT_EQ(Color::fromRgb8(255,255,255),Color::fromSRgb(1, 1, 1));
}
TEST(fromRgb8Test, handleInvalids) {
  EXPECT_THROW(Color::fromRgb8(-1,-1,-1),std::runtime_error);
  EXPECT_THROW(Color::fromRgb8(256,256,256),std::runtime_error);
}

TEST(relativeLumaTest, caluclatesRight) {
  ASSERT_EQ(Color::fromRgb8(255, 255, 255).contrastRatio(Color::fromRgb8(0,0,0)), 21.0);
  ASSERT_EQ(Color::fromRgb8(0,0,0).contrastRatio(Color::fromRgb8(0,0,0)), 1.0);
  ASSERT_EQ(Color::fromStr("#8d4444").contrastRatio(Color::fromRgb8(0,0,0)), 3.0428639462706979);
}
