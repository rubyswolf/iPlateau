#include "IControl.h"
#include "Plateau2.h"

BEGIN_IPLUG_NAMESPACE
BEGIN_IGRAPHICS_NAMESPACE

class LEDSwitch : public ISwitchControlBase
{
public:
    /** Constructs a bitmap switch control
     * @param bounds The control's bounds
     * @param bitmap The bitmap resource for the control
     * @param paramIdx The parameter index to link this control to */
    LEDSwitch(const IRECT& bounds, double hitboxScaleFactor, const ISVG& svgOff, const ISVG& svgOn1, const ISVG& svgOn2, int param1Idx = kNoParameter, int param2Idx = kNoParameter)
        : ISwitchControlBase(bounds, param1Idx, nullptr, 3)
        , mSVGOff(svgOff)
        , mSVGOn1(svgOn1)
        , mSVGOn2(svgOn2)
		, mParam1Idx(param1Idx)
		, mParam2Idx(param2Idx)
    {
        hitboxScale = hitboxScaleFactor;
    }

    virtual ~LEDSwitch() {}
    void Draw(IGraphics& g) override { g.DrawSVG(GetValue() >= 0.5 ? (tank2 ? mSVGOn2 : mSVGOn1) : mSVGOff, mRECT, &mBlend); }
    void OnMouseDown(float x, float y, const IMouseMod& mod) override {
        SetValue(GetValue() + 1.);
        if (GetValue() > 1.) {
            SetValue(0.);
        }
        SetDirty();
    };

    bool IsHit(float x, float y) const override {
        ICircle hitbox = ICircle(mTargetRECT);
        hitbox.Scale(hitboxScale);
        return hitbox.Contains(x, y);
    }

    void SelectTank(bool isTank2) {
        tank2 = isTank2;
        SetParamIdx(tank2 ? mParam2Idx : mParam1Idx, 0, true);
    }

    double hitboxScale = 1.0f;

protected:
    ISVG mSVGOff;
    ISVG mSVGOn1;
    ISVG mSVGOn2;
    int mParam1Idx;
    int mParam2Idx;
	bool tank2 = false;
};
END_IGRAPHICS_NAMESPACE
END_IPLUG_NAMESPACE