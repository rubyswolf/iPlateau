#include "IControl.h"

BEGIN_IPLUG_NAMESPACE
BEGIN_IGRAPHICS_NAMESPACE

class NavigatorButton : public IButtonControlBase
{
public:
	/** Constructs an SVG button control, with an action function
	 * @param bounds The control's bounds
	 * @param aF An action function to execute when a button is clicked \see IActionFunction
	 * @param offImage An SVG for the off state of the button
	 * @param onImage An SVG for the on state of the button */
	NavigatorButton(const IRECT& bounds, IActionFunction aF, const ISVG& svg)
		: IButtonControlBase(bounds, aF)
		, mSVG(svg)
	{
	}

	void Draw(IGraphics& g) override
    {
        g.DrawSVG(mSVG, mRECT);
    };

	void SetSVG(const ISVG& svg) {
		mSVG = svg;
		this->SetDirty(false);
	}

protected:
	ISVG mSVG;
};

END_IGRAPHICS_NAMESPACE
END_IPLUG_NAMESPACE
