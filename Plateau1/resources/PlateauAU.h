
#include <TargetConditionals.h>
#if TARGET_OS_IOS == 1
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif

#define IPLUG_AUVIEWCONTROLLER IPlugAUViewController_vPlateau
#define IPLUG_AUAUDIOUNIT IPlugAUAudioUnit_vPlateau
#import <PlateauAU/IPlugAUViewController.h>
#import <PlateauAU/IPlugAUAudioUnit.h>

//! Project version number for PlateauAU.
FOUNDATION_EXPORT double PlateauAUVersionNumber;

//! Project version string for PlateauAU.
FOUNDATION_EXPORT const unsigned char PlateauAUVersionString[];

@class IPlugAUViewController_vPlateau;
