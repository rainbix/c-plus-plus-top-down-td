// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Source/UI/IClickAction.h"
#include "PauseMenuWidget.generated.h"

class IClickAction;
/**
 * 
 */
UCLASS()
class SOURCE_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	IClickAction* m_onClickAction;
	
public:
	void Show(IClickAction* m_onClickAction);

	UFUNCTION(BlueprintCallable)
	void Resume() const;
	
	UFUNCTION(BlueprintCallable)
	void GoMainMenu() const;
};
