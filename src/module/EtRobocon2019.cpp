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

  constexpr int propertySize = 4;
  std::array<OrderProperty, propertySize> propertys = { { { Order::MOVE, 0.0, Color::black },
                                                          { Order::SPIN, 45.0, Color::black },
                                                          { Order::SPIN, -90.0, Color::black },
                                                          { Order::COLOR, 0.0, Color::black } } };

  bingo.execOrder<propertySize>(propertys);
}
