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
    LEDSwitch(const IRECT& bounds, float hitboxScaleFactor, const ISVG& svgOff, const ISVG& svgOn1, const ISVG& svgOn2, int paramIdx = kNoParameter)
        : ISwitchControlBase(bounds, paramIdx, nullptr, 3)
        , mSVGOff(svgOff)
        , mSVGOn1(svgOn1)
        , mSVGOn2(svgOn2)
    {
        hitboxScale = hitboxScaleFactor;
    }

    virtual ~LEDSwitch() {}
    void Draw(IGraphics& g) override { g.DrawSVG(GetValue() >= 1. ? (tank2 ? mSVGOn2 : mSVGOn1) : mSVGOff, mRECT, &mBlend); }
    void OnMouseDown(float x, float y, const IMouseMod& mod) {
		//if (child) { // If this is a child, don't allow it to be toggled when the parent forces it on
		//	if (linkedParent->GetValue() == 1.) {
		//		return;
		//	}
  //      }
        SetValue(GetValue() + 1.);
        if (GetValue() > 1.) {
            SetValue(0.);
        }
		preferedState = GetValue() >= 1.; //Set the state to return to when the parent turns back off
        SetDirty();
        if (child && !preferedState) {
            linkedParent->SetValue(0.);
			linkedParent->SetDirty();
        }
        if (parent) {
			linkedChild->Update();
        }
    };

    bool IsHit(float x, float y) const override {
        ICircle hitbox = ICircle(mTargetRECT);
        hitbox.Scale(hitboxScale);
        return hitbox.Contains(x, y);
    }

    void SelectTank(bool isTank2) {
        tank2 = isTank2;
        SetDirty();
    }

    float hitboxScale = 1.0f;

	void SetChild(LEDSwitch* child) {
        linkedChild = child;
		parent = true;
		child->SetParent(this);
	}

    void Update() {
        if (child) {
            if (linkedParent->GetValue() >= 1) {
				SetValue(1.);
			}
            else {
                SetValue(preferedState);
            }
			SetDirty();
        }
    }

protected:
    ISVG mSVGOff;
    ISVG mSVGOn1;
    ISVG mSVGOn2;
	bool tank2 = false;
    bool parent = false;
    bool child = false;
	LEDSwitch* linkedChild;
	LEDSwitch* linkedParent;
	bool preferedState = false;

private:
    void SetParent(LEDSwitch* parent) {
        linkedParent = parent;
        child = true;
    }
};
END_IGRAPHICS_NAMESPACE
END_IPLUG_NAMESPACE