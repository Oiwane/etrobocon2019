/**
 *  @file   BlockBingo.cpp
 *  @brief  ブロックビンゴに使用するクラス
 *  @author Oiwane
 */
#include "BlockBingo.h"

BlockBingo::BlockBingo(Controller& controller_) : controller(controller_) {}

void BlockBingo::moveCircle4OfL()
{
  Navigator navigator(controller);

  // 色識別が上手くいったら下のコメントを処理に加える
  // navigator.moveToSpecifiedColor(Color::yellow, 10);
  navigator.move(-90.0, 10);
  navigator.spin(45.0, false);
  navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.spin(45.0);
}

void BlockBingo::execOrder(std::size_t orderSize, std::array<std::function<void(Controller&)>, 9> order)
{
  for(auto& func : order) {
    func(controller);
    controller.tslpTsk(1000);
  }
  // for(std::size_t i = 0; i < orderSize; i++) {
  //   order[i](controller);
  //   controller.tslpTsk(1000);
  // }
}

void BlockBingo::move(Controller& controller_)
{
  Navigator navigator(controller_);
  navigator.move(350, 10);
}

void BlockBingo::spinLeft(Controller& controller_)
{
  Navigator navigator(controller_);
  navigator.spin(90, false);
}

void BlockBingo::spinRight(Controller& controller_)
{
  Navigator navigator(controller_);
  navigator.spin(90);
}