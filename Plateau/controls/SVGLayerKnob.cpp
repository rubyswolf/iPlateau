#include "IControl.h"

BEGIN_IPLUG_NAMESPACE
BEGIN_IGRAPHICS_NAMESPACE

class ISVGLayerKnobControl : public IKnobControlBase
{
public:
  ISVGLayerKnobControl(const IRECT& bounds, const ISVG& svg, const ISVG& backgroundSvg, const ISVG& foregroundSvg, int paramIdx = kNoParameter)
    : IKnobControlBase(bounds, paramIdx)
    , mSVG(svg)
    , bSVG(backgroundSvg)
    , fSVG(foregroundSvg)
  {
  }

  void Draw(IGraphics& g) override
  {
    g.DrawSVG(bSVG, mRECT);
    g.DrawRotatedSVG(mSVG, mRECT.MW(), mRECT.MH(), mRECT.W(), mRECT.H(), mStartAngle + GetValue() * (mEndAngle - mStartAngle), &mBlend);
    g.DrawSVG(fSVG, mRECT);
  }

  void SetSVG(ISVG& svg)
  {
    mSVG = svg;
    SetDirty(false);
  }

private:
  ISVG mSVG;
  ISVG bSVG;
  ISVG fSVG;
  float mStartAngle = -135.f;
  float mEndAngle = 135.f;
};

END_IGRAPHICS_NAMESPACE
END_IPLUG_NAMESPACE
