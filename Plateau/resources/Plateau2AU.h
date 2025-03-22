
#include <TargetConditionals.h>
#if TARGET_OS_IOS == 1
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif

#define IPLUG_AUVIEWCONTROLLER IPlugAUViewController_vPlateau2
#define IPLUG_AUAUDIOUNIT IPlugAUAudioUnit_vPlateau2
#import <Plateau2AU/IPlugAUViewController.h>
#import <Plateau2AU/IPlugAUAudioUnit.h>

//! Project version number for Plateau2AU.
FOUNDATION_EXPORT double Plateau2AUVersionNumber;

//! Project version string for Plateau2AU.
FOUNDATION_EXPORT const unsigned char Plateau2AUVersionString[];

@class IPlugAUViewController_vPlateau2;
