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
		, mParam1Idx(kParam1Idx)
		, mParam2Idx(kParam2Idx)
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
		SetParamIdx(tank2 ? mParam2Idx : mParam1Idx, 0, true);
	}

    float StartAngle = -135.f;
    float EndAngle = 135.f;
    float Bound = 135.f;

private:
    IBitmap mDialFg1;
    IBitmap mDialFg2;
    ISVG mDialBg;
    ISVG mDialPointer;
	int mParam1Idx;
	int mParam2Idx;
	bool tank2 = false;
};

END_IGRAPHICS_NAMESPACE
END_IPLUG_NAMESPACE
