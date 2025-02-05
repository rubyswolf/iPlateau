#include "IControl.h"

BEGIN_IPLUG_NAMESPACE
BEGIN_IGRAPHICS_NAMESPACE

class IBButtonHoldControl : public IButtonControlBase
    , public IBitmapBase
{
public:

    IBButtonHoldControl::IBButtonHoldControl(float x, float y, const IBitmap& bitmap, IActionFunction aF)
        : IButtonControlBase(IRECT(x, y, bitmap), aF)
        , IBitmapBase(bitmap)
    {
        AttachIControl(this);
    }

    IBButtonHoldControl::IBButtonHoldControl(const IRECT& bounds, const IBitmap& bitmap, IActionFunction aF)
        : IButtonControlBase(bounds.GetCentredInside(bitmap), aF)
        , IBitmapBase(bitmap)
    {
        AttachIControl(this);
    }

    void Draw(IGraphics& g) override { DrawBitmap(g); }
    void OnRescale() override { mBitmap = GetUI()->GetScaledBitmap(mBitmap); }
    void OnMouseUp(float x, float y, const IMouseMod& mod) override {
        this->SetValue(0.);
        SetDirty(false);
    }
};

END_IGRAPHICS_NAMESPACE
END_IPLUG_NAMESPACE
