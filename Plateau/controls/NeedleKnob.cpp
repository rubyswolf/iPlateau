#include "IControl.h"

BEGIN_IPLUG_NAMESPACE
BEGIN_IGRAPHICS_NAMESPACE

class NeedleKnob : public IKnobControlBase
{
public:
    NeedleKnob(const IRECT& bounds, const ISVG& dialPointer, const ISVG& dialBg, const IBitmap& dialFg1Bmp, const IBitmap& dialFg2Bmp, int kParamIdx)
        : IKnobControlBase(bounds, kParamIdx)
        , mDialFg1(dialFg1Bmp)
        , mDialFg2(dialFg2Bmp)
        , mDialBg(dialBg)
        , mDialPointer(dialPointer)
    {
    }

    void Draw(IGraphics& g) override
    {
        g.DrawSVG(mDialBg, mRECT);
        g.DrawRotatedSVG(mDialPointer, mRECT.MW(), mRECT.MH(), mRECT.W(), mRECT.H(), mStartAngle + GetValue() * (mEndAngle - mStartAngle), &mBlend);
        g.DrawFittedBitmap(tank2 ? mDialFg2 : mDialFg1, mRECT);
    }

    bool IsHit(float x, float y) const override {
        ICircle hitbox = ICircle(mTargetRECT);
        return hitbox.Contains(x, y);
    }
    
	void SelectTank(bool isTank2) {
		tank2 = isTank2;
		SetDirty(false);
	}

private:
    IBitmap mDialFg1;
    IBitmap mDialFg2;
    ISVG mDialBg;
    ISVG mDialPointer;
    float mStartAngle = -135.f;
    float mEndAngle = 135.f;
	bool tank2 = false;
};

END_IGRAPHICS_NAMESPACE
END_IPLUG_NAMESPACE
