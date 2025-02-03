/** A vector knob/dial control which rotates an SVG image and also has a static SVG above and below the rotating one*/
#include "IControl.h"

BEGIN_IPLUG_NAMESPACE
BEGIN_IGRAPHICS_NAMESPACE

class ISVGLayerKnobControl : public IKnobControlBase
{
public:
  ISVGLayerKnobControl(const IRECT& bounds, const ISVG& svg, const ISVG& backgroundSvg, const ISVG& foregroundSvg, int paramIdx = kNoParameter);
  
  void Draw(IGraphics& g) override;
  void SetSVG(ISVG& svg);
  
private:
  ISVG mSVG;
  ISVG bSVG;
  ISVG fSVG;
  float mStartAngle = -135.f;
  float mEndAngle = 135.f;
};

END_IGRAPHICS_NAMESPACE
END_IPLUG_NAMESPACE