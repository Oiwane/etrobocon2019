/**
 *  @file   Calibrator.cpp
 *  @brief  キャリブレーションを行うクラス
 *  @author korosuke613
 **/
#include "Calibrator.h"

Calibrator::Calibrator(Controller& controller_)
  : controller(controller_), isCameraMode(true), isLeft(true)
{
}

bool Calibrator::calibration()
{
  auto volt = controller.getVolt();
  auto amp = controller.getAmp();
  Display::print(1, "Calibration, mV:%d, mA:%d", volt, amp);
  this->setArm();
  this->deleteDisplayedText(2, 11);
  if(!setCameraMode()) {
    Display::print(2, "Error setCameraMode!");
    return false;
  }

  if(!setLRCourse()) {
    Display::print(2, "Error setLRCourse!");
    return false;
  }

  if(!setBrightness(Brightness::WHITE)) {
    Display::print(2, "Error setBrightness White!");
    return false;
  }

  if(!setBrightness(Brightness::BLACK)) {
    Display::print(2, "Error setBrightness Black!");
    return false;
  }
  Display::print(5, "White: %3d %3d %3d", controller.standardWhite.r, controller.standardWhite.g,
                 controller.standardWhite.b);
  Display::print(6, "Black: %3d %3d %3d", controller.standardBlack.r, controller.standardBlack.g,
                 controller.standardBlack.b);

  Display::print(7, "Calibration was completed!");

  return true;
}

bool Calibrator::setCameraMode()
{
  char cameraMode[8] = "ON";

  controller.tslpTsk(500);
  while(!controller.buttonIsPressedEnter()) {
    if(isCameraMode) {
      std::strcpy(cameraMode, "ON");
    } else {
      std::strcpy(cameraMode, "OFF");
    }
    Display::print(3, "camera system: %s ?", cameraMode);

    if(controller.buttonIsPressedLeft() || controller.buttonIsPressedRight()) {
      isCameraMode = !isCameraMode;
      controller.speakerPlayToneFS6(50);
      controller.tslpTsk(500);
    }
    controller.tslpTsk(4);
  }
  Display::print(3, "camera system: %s", cameraMode);

  controller.speakerPlayToneFS6(100);
  return true;
}

bool Calibrator::setLRCourse()
{
  char course[8] = "Left";

  controller.tslpTsk(500);
  while(!controller.buttonIsPressedEnter()) {
    if(isLeft) {
      std::strcpy(course, "Left");
    } else {
      std::strcpy(course, "Right");
    }
    Display::print(4, "Set LRCourse: %s ?", course);

    if(controller.buttonIsPressedLeft() || controller.buttonIsPressedRight()) {
      isLeft = !isLeft;
      controller.speakerPlayToneFS6(50);
      controller.tslpTsk(500);
    }
    controller.tslpTsk(4);
  }
  Display::print(4, "course: %s", course);

  controller.speakerPlayToneFS6(100);
  return true;
}

bool Calibrator::setBrightness(Brightness brightness)
{
  char name[8] = "none";

  if(brightness == Brightness::WHITE) {
    std::strcpy(name, "White");
  } else if(brightness == Brightness::BLACK) {
    std::strcpy(name, "Black");
  } else {
    return false;
  }
  Display::print(5, "Set Brightness: %s ?", name);

  controller.tslpTsk(500);

  while(1) {
    // ENTERボタンが押されたらループを抜ける
    if(controller.buttonIsPressedEnter()) {
      controller.speakerPlayToneFS6(100);
      break;
    }

    rgb_raw_t rgb;
    controller.colorSensor.getRawColor(rgb);
    Display::print(6, "R:%3d, G:%3d, B:%3d", rgb.r, rgb.g, rgb.b);

    controller.tslpTsk(4);
  }

  controller.speakerPlayToneFS6(200);

  if(brightness == Brightness::WHITE) {
    rgb_raw_t standardWhite;
    controller.colorSensor.getRawColor(standardWhite);
    controller.setStandardWhite(standardWhite);
  } else {
    rgb_raw_t standardBlack;
    controller.colorSensor.getRawColor(standardBlack);
    controller.setStandardBlack(standardBlack);
  }

  return true;
}

bool Calibrator::getCameraMode() const
{
  return isCameraMode;
}

bool Calibrator::isLeftCourse() const
{
  return isLeft;
}

void Calibrator::setArm()
{
  while(!controller.touchSensor.isPressed()) {
    controller.tslpTsk(4);
    Display::print(2, "Adjust the arm position...");
    Display::print(3, "Touch Button : Arm set start!");
  }

  controller.stopLiftMotor();

  while(!controller.touchSensor.isPressed()){
    controller.tslpTsk(4);
    Display::print(2, "UP    Button : Raise Arm");
    Display::print(3, "DOWN  Button : Lower Arm");
    Display::print(5, "Touch Button : Arm set finish!");
    if(controller.buttonIsPressedUp()){
      controller.moveArm(1);
    }else if(controller.buttonIsPressedDown()){
      controller.moveArm(-1);  
    }
  }
}

void Calibrator::deleteDisplayedText(int startTarget,int endTarget)
{
  for (int i = startTarget; i <= endTarget; i++){
    Display::print(i, "");
  }
}
