#include "EtRobocon2019.h"
#include "Controller.h"
#include "Calibrator.h"
#include "Display.h"
#include "NormalCourse.h"
#include "Navigator.h"
#include "BlockBingo.h"

void EtRobocon2019::start()
{
  Controller controller;
  BlockBingo bingo(controller);

  // タッチセンサーが押されるまで待つ（これを書かないと自動で走り出す．）
  while(!controller.touchSensor.isPressed()) {
  }

  std::size_t orderSize = 9;
  std::array<std::function<void(void)>, orderSize> order
    = { move, spinRight, move, spinLeft, spinLeft, spinRight, move, spinRight, spinLeft };

  bingo.execOrder(orderSize, order);
}
