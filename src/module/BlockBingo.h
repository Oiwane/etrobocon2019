/**
 *  @file   BlockBingo.h
 *  @brief  ブロックビンゴに使用するクラス
 *  @author Oiwane
 */
#ifndef BLOCKBINGO_H
#define BLOCKBINGO_H

#include <array>
#include <functional>
#include "Controller.h"
#include "Navigator.h"

class BlockBingo {
 private:
  Controller& controller;

 public:
  /**
   * コンストラクタ
   * @param controller_ [Controllerの参照]
   */
  explicit BlockBingo(Controller& controller_);

  /**
   * Lコースのブロックビンゴのブロックサークル4に移動する
   * @brief Lコースのブロックビンゴ開始点からブロックサークル4の手前の
   * 黒線の中点まで斜めに移動し、ブロックサークル4の中央まで移動する。
   */
  void moveCircle4OfL();

  /**
   * パソコンから受け取ったリストの通りに処理を実行する
   * @param orderSize [orderのサイズ]
   * @param order [命令のリスト]
   */
  void execOrder(std::size_t orderSize, std::array<std::function<void(Controller&)>, 9> order);
  // void execOrder(std::function<void(Controller&)> order[]);

  /**
   * Navigator::moveを呼び出す
   * @brief 350mm前進する
   */
  static void move(Controller& controller_);

  /**
   * Navigator::spinを呼び出す
   * @brief 90度左に回頭する
   */
  static void spinLeft(Controller& controller_);

  /**
   * Navigator::spinを呼び出す
   * @brief 90度右に回頭する
   */
  static void spinRight(Controller& controller_);
};

#endif