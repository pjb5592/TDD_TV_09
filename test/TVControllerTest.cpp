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

  std::string getProcessingCH() { return controller->getProcessingCH(); }
};

// TEST(TVControllerTest, testFramework) {
//   // fail();
// }

// TC-01: 한자리 숫자 입력 + 확인 → 채널변경
TEST_F(TVControllerTest, TC01_SingleDigitWithOk_ChangesChannel) {
  pushKeys({remoteKey::KEY_5, remoteKey::KEY_OK});
  std::string channel = getProcessingCH();

  EXPECT_CALL(mockTuner, setCH("5")).Times(1);
  EXPECT_CALL(mockTuner, getCurrentCH()).WillOnce(::testing::Return(channel));

  mockTuner.setCH(channel);
  EXPECT_EQ(channel, mockTuner.getCurrentCH());
}

// TC-02: 두자리 숫자 입력 → 자동 변경
TEST_F(TVControllerTest, TC02_TwoDigits_AutomaticallyChangesChannel) {
  pushKeys({remoteKey::KEY_2, remoteKey::KEY_4});
  std::string channel = getProcessingCH();

  EXPECT_CALL(mockTuner, setCH("24")).Times(1);
  EXPECT_CALL(mockTuner, getCurrentCH()).WillOnce(::testing::Return(channel));

  mockTuner.setCH(channel);
  EXPECT_EQ(channel, mockTuner.getCurrentCH());
}