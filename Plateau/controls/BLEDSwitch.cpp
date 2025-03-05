#include "IControl.h"

BEGIN_IPLUG_NAMESPACE
BEGIN_IGRAPHICS_NAMESPACE

class LEDSwitch : public ISwitchControlBase
    , public IBitmapBase
{
public:
    /** Constructs a bitmap switch control
     * @param bounds The control's bounds
     * @param bitmap The bitmap resource for the control
     * @param paramIdx The parameter index to link this control to */
    LEDSwitch(const IRECT& bounds, float hitboxScaleFactor, const IBitmap& bitmap, int paramIdx = kNoParameter)
        : ISwitchControlBase(bounds, paramIdx)
        , IBitmapBase(bitmap)
    {
		hitboxScale = hitboxScaleFactor;
        AttachIControl(this);
    }

    virtual ~LEDSwitch() {}
    void Draw(IGraphics& g) override { DrawBitmap(g); }
    void OnRescale() override { mBitmap = GetUI()->GetScaledBitmap(mBitmap); }
    void OnMouseDown(float x, float y, const IMouseMod& mod) {
        if (mBitmap.N() > 1)
            SetValue(GetValue() + 1.0 / static_cast<double>(mBitmap.N() - 1));
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
};
END_IGRAPHICS_NAMESPACE
END_IPLUG_NAMESPACE
