#include "CloseWidgetAction.h"

#include "Blueprint/UserWidget.h"

CloseWidgetAction::CloseWidgetAction(UUserWidget* widget)
{
	m_activeWidget = widget;
}

void CloseWidgetAction::OnClickAction()
{
	if(m_activeWidget == nullptr)
	{
		return;
	}

	m_activeWidget->RemoveFromParent();
	m_activeWidget = nullptr;
}
