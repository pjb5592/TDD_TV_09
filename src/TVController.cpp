#include "TVController.h"

// private 메서드 구현
void TVController::setTunerCh() {
  std::cout << "현재 설정하는 채널 : " << processingCH << std::endl;

  // 모킹 테스트 및 실제 동작을 위해 주석을 해제하고 연동합니다.
  if (tuner != nullptr) {
    tuner->setCH(processingCH);
  }
}

// 생성자 구현
TVController::TVController(Tuner *tuner) : tuner(tuner), processingCH("") {}

// public 메서드 구현
void TVController::pushButton(remoteKey key) {
  switch (key) {
  case remoteKey::KEY_1:
  case remoteKey::KEY_2:
  case remoteKey::KEY_3:
  case remoteKey::KEY_4:
  case remoteKey::KEY_5:
  case remoteKey::KEY_6:
  case remoteKey::KEY_7:
  case remoteKey::KEY_8:
  case remoteKey::KEY_9:
  case remoteKey::KEY_0:
    processingCH += to_string(key);
    break;
  case remoteKey::KEY_OK:
    setTunerCh();
    break;
  }
}
