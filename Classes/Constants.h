#pragma once
#define kDesignResolutionWidth 768
#define kDesignResolutionHeight 1024

#define kZIndexCloud 10
#define kZIndexWall 20
#define kZIndexBeam 90
#define kZIndexGap  90
#define kZIndexLaser 90
#define kZIndexJuppy 100

#define kTagBarrierBeam 1
#define kTagBarrierGaps 2
#define kTagBarrierLaser 3

#define kDistanceBarrierMin 250
#define kDistanceBarrierMax 500

#define kInitStartPosBarrier 434

#define GETWINSIZE_WIDTH (Director::getInstance()->getWinSize().width)
#define GETWINSIZE_HEIGHT (Director::getInstance()->getWinSize().height)

#define GETVISIBLESIZE_WIDTH (Director::getInstance()->getVisibleSize().width)
#define GETVISIBLESIZE_HEIGHT (Director::getInstance()->getVisibleSize().height)

#define SIZECELL 80

#define kTypeBeam1 1
#define kTypeBeam2 2
#define kTypeBeam3 3
#define kTypeBeam4 4

#define kDirectRight 1
#define kDirectLeft -1

#define kTypeLaserBlue	 1
#define kTypeLaserGreen	 2
#define kTypeLaserRed	 3
#define kTypeLaserYellow 4

#define kNumMemBeamMin 3
#define kNumMemBeamMax 6

#define kDistanceBeamMin 3
#define kDistanceBeamMax 5

#define kNumBeamsMin 3
#define kNumBeamMax 6

#define kSpeedBarrierBeam 200

#define kTimeMoveGaps 2.0f
#define kTimeDelayGaps 2.0f

#define kSpeedLaser 1.0f
#define kTimeDelayLaserBeam 2.0f