#include "IControl.h"

BEGIN_IPLUG_NAMESPACE
BEGIN_IGRAPHICS_NAMESPACE

class LEDButton : public IButtonControlBase
{
public:
    LEDButton(const IRECT& bounds, float hitboxScaleFactor, const std::initializer_list<ISVG>& svgs, IActionFunction aF)
        : IButtonControlBase(bounds, aF)
        , mSVGs(svgs)
    {
		hitboxScale = hitboxScaleFactor;
    }

    void Draw(IGraphics& g) override { g.DrawSVG(mSVGs[GetValue()], mRECT, &mBlend); }
    void OnMouseUp(float x, float y, const IMouseMod& mod) override {
        this->SetValue(0.);
        SetDirty(false);
    }

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
