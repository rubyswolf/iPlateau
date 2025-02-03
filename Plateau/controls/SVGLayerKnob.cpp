#include "SVGLayerKnob.hpp"

using namespace iplug;
using namespace igraphics;

ISVGLayerKnobControl::ISVGLayerKnobControl(const IRECT& bounds, const ISVG& svg, const ISVG& backgroundSvg, const ISVG& foregroundSVG, int paramIdx)
: IKnobControlBase(bounds, paramIdx)
  , mSVG(svg)
  , bSVG(backgroundSvg)
  , fSVG(foregroundSVG)
{
}

void ISVGLayerKnobControl::Draw(IGraphics& g)
{
  g.DrawSVG(bSVG, mRECT);
  g.DrawRotatedSVG(mSVG, mRECT.MW(), mRECT.MH(), mRECT.W(), mRECT.H(), mStartAngle + GetValue() * (mEndAngle - mStartAngle), &mBlend);
  g.DrawSVG(fSVG, mRECT);
}

void ISVGLayerKnobControl::SetSVG(ISVG& svg)
{
  mSVG = svg;
  SetDirty(false);
}