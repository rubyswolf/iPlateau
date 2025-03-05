#include "IControl.h"

BEGIN_IPLUG_NAMESPACE
BEGIN_IGRAPHICS_NAMESPACE

class NeedleKnob : public IKnobControlBase
{
public:
    NeedleKnob(const IRECT& bounds, const ISVG& dialPointer, const ISVG& dialBg, const IBitmap& dialFgBmp, int kParamIdx)
        : IKnobControlBase(bounds, kParamIdx)
        , mDialFg(dialFgBmp)
        , mDialBg(dialBg)
        , mDialPointer(dialPointer)
    {
    }

    void Draw(IGraphics& g) override
    {
        g.DrawSVG(mDialBg, mRECT);
        g.DrawRotatedSVG(mDialPointer, mRECT.MW(), mRECT.MH(), mRECT.W(), mRECT.H(), mStartAngle + GetValue() * (mEndAngle - mStartAngle), &mBlend);
        g.DrawFittedBitmap(mDialFg, mRECT);
    }

    bool IsHit(float x, float y) const override {
        ICircle hitbox = ICircle(mTargetRECT);
        return hitbox.Contains(x, y);
    }

private:
    IBitmap mDialFg;
    ISVG mDialBg;
    ISVG mDialPointer;
    float mStartAngle = -135.f;
    float mEndAngle = 135.f;
};

END_IGRAPHICS_NAMESPACE
END_IPLUG_NAMESPACE
