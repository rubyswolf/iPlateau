#include "IControl.h"

BEGIN_IPLUG_NAMESPACE
BEGIN_IGRAPHICS_NAMESPACE

class LEDRadio : public IButtonControlBase
{
public:
    LEDRadio(const IRECT& bounds, double hitboxScaleFactor, const ISVG& svgOff, const ISVG& svgOn, IActionFunction aF)
        : IButtonControlBase(bounds, aF)
        , mSVGOff(svgOff)
        , mSVGOn(svgOn)
    {
        hitboxScale = hitboxScaleFactor;
    }

    void Draw(IGraphics& g) override { g.DrawSVG(GetValue()>=1.? mSVGOn : mSVGOff, mRECT, &mBlend); }

    bool IsHit(float x, float y) const override {
        ICircle hitbox = ICircle(mTargetRECT);
        hitbox.Scale(hitboxScale);
        return hitbox.Contains(x, y);
    }

    void OnMouseDown(float x, float y, const IMouseMod& mod) override
    {
        SetValue(1.);
        SetDirty(true);
		for (IControl* control : mLinkedControls)
		{
			control->SetValue(0.);
			control->SetDirty(false);
		}
    }

	void linkControls(std::vector<IControl*> linkedControls)
	{
		//Exclude self from linked controls
		for (IControl* control : linkedControls)
		{
			if (control != this)
			{
				mLinkedControls.push_back(control);
			}
		}
	}

    double hitboxScale = 1.0f;
protected:
    ISVG mSVGOff;
    ISVG mSVGOn;
    std::vector<IControl*> mLinkedControls;
};

END_IGRAPHICS_NAMESPACE
END_IPLUG_NAMESPACE
