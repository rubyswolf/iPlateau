#include "IControl.h"

BEGIN_IPLUG_NAMESPACE
BEGIN_IGRAPHICS_NAMESPACE

class LEDButton : public IButtonControlBase
    , public IBitmapBase
{
public:
    LEDButton(const IRECT& bounds, float hitboxScaleFactor, const IBitmap& bitmap, IActionFunction aF)
        : IButtonControlBase(bounds, aF)
        , IBitmapBase(bitmap)
    {
		hitboxScale = hitboxScaleFactor;
        AttachIControl(this);
    }

    void Draw(IGraphics& g) override { DrawBitmap(g); }
    void OnRescale() override { mBitmap = GetUI()->GetScaledBitmap(mBitmap); }
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
};

END_IGRAPHICS_NAMESPACE
END_IPLUG_NAMESPACE
