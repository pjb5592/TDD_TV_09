#include "TVController.h"
#include "Tuner.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class MockTuner : public Tuner {
public:
  MOCK_METHOD(std::string, seekCH, (), (override));
  MOCK_METHOD(void, setCH, (const std::string &ch), (override));
  MOCK_METHOD(std::string, getCurrentCH, (), (override));
};

class TVControllerTest : public ::testing::Test {
protected:
  MockTuner mockTuner;
  TVController *controller;

  void SetUp() override { controller = new TVController(&mockTuner); }

  void TearDown() override { delete controller; }

  void pushKeys(const std::vector<remoteKey> &keys) {
    for (auto key : keys) {
      controller->pushButton(key);
    }
  }
};

// TEST(TVControllerTest, testFramework) {
//   // fail();
// }

// TC-01: 한자리 숫자 입력 + 확인 → 채널변경
TEST_F(TVControllerTest, TC01_SingleDigitWithOk_ChangesChannel) {
  EXPECT_CALL(mockTuner, setCH("5")).Times(1);
  pushKeys({remoteKey::KEY_5, remoteKey::KEY_OK});
}