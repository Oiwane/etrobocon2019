/**
 *  @file   Calibrator.h
 *  @brief  キャリブレーションを行うクラス
 *  @author korosuke613
 **/
#ifndef CALIBRATOR_H
#define CALIBRATOR_H

#include <cstring>
#include "Controller.h"
#include "Display.h"

enum class Brightness { WHITE, BLACK };

class Calibrator {
 public:
  explicit Calibrator(Controller& controller_);

  /** キャリブレーションを行う。
   * @return キャリブレーションが成功したかどうかの真理値(Trueなら正常終了)
   */
  bool calibration();

  /** Leftコースであるかどうかを判断する。
   * @return Leftコースであるかどうかの真偽値（TrueならLeftコース）
   */
  bool isLeftCource();

  /** 白色の値を取得する。
   * @return 明るさ
   */
  int getWhiteBrightness();

  /** 黒色の値を取得する。
   * @return 明るさ
   */
  int getBlackBrightness();
  bool setLRCource();
  bool setBrightness(Brightness b);

 private:
  Controller& controller;
  bool isFinish =
      false;  // キャリブレーションが終了したかどうかの真偽値（Trueなら正常終了）
  bool isLeft = true;  // Leftコースであるかどうかの真偽値（TrueならLeftコース）
  unsigned int brightnessOfWhite = 0;  // 白色の明るさ
  unsigned int brightnessOfBlack = 0;  // 黒色の明るさ
};

#endif