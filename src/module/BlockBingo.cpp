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

void BlockBingo::execOrder(std::size_t orderSize, std::array<std::function<void(void)>, orderSize> order)
{
  for(std::function<void(void)> f : order){
    f;
    controller.tslpTsk(1000);
  }
}

void BlockBingo::move()
{
  Navigator navigator(controller);
  navigator.move(350, 10);
}

void BlockBingo::spinLeft()
{
  Navigator navigator(controller);
  navigator.spin(90, false);
}

void BlockBingo::spinRight()
{
  Navigator navigator(controller);
  navigator.spin(90);
}