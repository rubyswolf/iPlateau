#include "IControl.h"

BEGIN_IPLUG_NAMESPACE
BEGIN_IGRAPHICS_NAMESPACE

class NeedleKnob : public IKnobControlBase
{
public:
    NeedleKnob(const IRECT& bounds, const ISVG& dialPointer, const ISVG& dialBg, const IBitmap& dialFg1Bmp, const IBitmap& dialFg2Bmp, int kParam1Idx, int kParam2Idx)
        : IKnobControlBase(bounds, kParam1Idx)
        , mDialFg1(dialFg1Bmp)
        , mDialFg2(dialFg2Bmp)
        , mDialBg(dialBg)
        , mDialPointer(dialPointer)
		, Param1Idx(kParam1Idx)
		, Param2Idx(kParam2Idx)
    {
    }

    void Draw(IGraphics& g) override
    {
        g.DrawSVG(mDialBg, mRECT);
        g.DrawRotatedSVG(mDialPointer, mRECT.MW(), mRECT.MH(), mRECT.W(), mRECT.H(), clip<double>(StartAngle + GetValue() * (EndAngle - StartAngle), -Bound, Bound), &mBlend);
        g.DrawFittedBitmap(tank2 ? mDialFg2 : mDialFg1, mRECT);
    }

    bool IsHit(float x, float y) const override {
        ICircle hitbox = ICircle(mTargetRECT);
        return hitbox.Contains(x, y);
    }
    
	void SelectTank(bool isTank2) {
		tank2 = isTank2;
		SetParamIdx(tank2 ? Param2Idx : Param1Idx, 0, true);
	}

    float StartAngle = -135.f;
    float EndAngle = 135.f;
    float Bound = 135.f;
	int Param1Idx;
	int Param2Idx;

private:
    IBitmap mDialFg1;
    IBitmap mDialFg2;
    ISVG mDialBg;
    ISVG mDialPointer;
	bool tank2 = false;
};

END_IGRAPHICS_NAMESPACE
END_IPLUG_NAMESPACE
