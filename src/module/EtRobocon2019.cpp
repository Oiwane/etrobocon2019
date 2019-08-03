#include "EtRobocon2019.h"
#include "Controller.h"
#include "Calibrator.h"
#include "Display.h"
#include "NormalCourse.h"
#include "Navigator.h"
#include "BlockBingo.h"
#include <array>
#include <functional>

void EtRobocon2019::start()
{
  Controller controller;
  BlockBingo bingo(controller);

  // タッチセンサーが押されるまで待つ（これを書かないと自動で走り出す．）
  while(!controller.touchSensor.isPressed()) {
  }

  const std::size_t orderSize = 9;
  std::array<std::function<void(Controller&)>, orderSize> order{
    BlockBingo::move, BlockBingo::spinRight, BlockBingo::move,
    BlockBingo::spinLeft, BlockBingo::spinLeft, BlockBingo::spinRight,
    BlockBingo::move, BlockBingo::spinRight, BlockBingo::spinLeft };
  // std::function<void(Controller&)> order[orderSize]
  //   = { BlockBingo::move, BlockBingo::spinRight, BlockBingo::move,
  //   BlockBingo::spinLeft, BlockBingo::spinLeft, BlockBingo::spinRight,
  //   BlockBingo::move, BlockBingo::spinRight, BlockBingo::spinLeft };
    // = { move, spinRight, move, spinLeft, spinLeft, spinRight, move, spinRight, spinLeft };

  // bingo.execOrder(order);
  bingo.execOrder(orderSize, order);
}
