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
