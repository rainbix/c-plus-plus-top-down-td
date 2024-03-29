#pragma once
#include "IClickAction.h"

class CloseWidgetAction : public IClickAction
{
public:
	CloseWidgetAction(UUserWidget* widget);
private:
	UUserWidget* m_activeWidget;
	
public:
	virtual ~CloseWidgetAction() = default;
	virtual void OnClickAction() override;
};
