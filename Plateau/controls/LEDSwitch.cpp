#include "IControl.h"

BEGIN_IPLUG_NAMESPACE
BEGIN_IGRAPHICS_NAMESPACE

class LEDSwitch : public ISwitchControlBase
{
public:
    /** Constructs a bitmap switch control
     * @param bounds The control's bounds
     * @param bitmap The bitmap resource for the control
     * @param paramIdx The parameter index to link this control to */
    LEDSwitch(const IRECT& bounds, float hitboxScaleFactor, const std::initializer_list<ISVG>& svgs, int paramIdx = kNoParameter)
        : ISwitchControlBase(bounds, paramIdx, nullptr, static_cast<int>(svgs.size()))
        , mSVGs(svgs)
    {
        hitboxScale = hitboxScaleFactor;
        //AttachIControl(this);
    }

    virtual ~LEDSwitch() {}
    void Draw(IGraphics& g) override { g.DrawSVG(mSVGs[GetSelectedIdx()], mRECT, &mBlend); }
    void OnMouseDown(float x, float y, const IMouseMod& mod) {
        if (mSVGs.size() > 1)
            SetValue(GetValue() + 1.0 / static_cast<double>(mSVGs.size() - 1));
        else
            SetValue(GetValue() + 1.0);

        if (GetValue() > 1.001)
            SetValue(0.);

        SetDirty();
    };

    bool IsHit(float x, float y) const override {
        ICircle hitbox = ICircle(mTargetRECT);
        hitbox.Scale(hitboxScale);
        return hitbox.Contains(x, y);
    }

    float hitboxScale = 1.0f;

protected:
    std::vector<ISVG> mSVGs;
};
END_IGRAPHICS_NAMESPACE
END_IPLUG_NAMESPACE