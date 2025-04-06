#include "IControl.h"

BEGIN_IPLUG_NAMESPACE
BEGIN_IGRAPHICS_NAMESPACE

class LEDButton : public IButtonControlBase
{
public:
    LEDButton(const IRECT& bounds, double hitboxScaleFactor, const ISVG& svgOff, const ISVG& svgOn1, const ISVG& svgOn2, IActionFunction aF, IControl* linkedControl = nullptr)
        : IButtonControlBase(bounds, aF)
		, mSVGOff(svgOff)
		, mSVGOn1(svgOn1)
		, mSVGOn2(svgOn2)
        , mLinkedControl(linkedControl)
    {
		hitboxScale = hitboxScaleFactor;
    }

    void Draw(IGraphics& g) override { g.DrawSVG(GetValue()>=1.?(tank2 ? mSVGOn2 : mSVGOn1) : mSVGOff, mRECT, &mBlend); }
    void OnMouseUp(float x, float y, const IMouseMod& mod) override {
        this->SetValue(0.);
        SetDirty(false);
        if (mLinkedControl)
        {
            mLinkedControl->SetValue(0.);
			mLinkedControl->SetDirty();
        }
    }

    bool IsHit(float x, float y) const override {
        ICircle hitbox = ICircle(mTargetRECT);
        hitbox.Scale(hitboxScale);
        return hitbox.Contains(x, y);
    }

    void SelectTank(bool isTank2) {
        tank2 = isTank2;
        SetDirty(false);
    }

    double hitboxScale = 1.0f;
protected:
    ISVG mSVGOff;
    ISVG mSVGOn1;
    ISVG mSVGOn2;
	IControl* mLinkedControl;
    bool tank2 = false;
};

END_IGRAPHICS_NAMESPACE
END_IPLUG_NAMESPACE
