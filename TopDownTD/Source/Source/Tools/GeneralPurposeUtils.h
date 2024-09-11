// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define LOG(text, ...) UE_LOG(LogCore, Log, TEXT(text), __VA_ARGS__);
#define LOG_WARNING(text, ...) UE_LOG(LogCore, Warning, TEXT(text), __VA_ARGS__);
#define LOG_ERROR(text, ...) UE_LOG(LogCore, Error, TEXT(text), __VA_ARGS__);

class GeneralPurposeUtils
{
public:
	static void DisplayScreenMessage(const FString& message, FColor color = FColor::Yellow, float duration = 2.0);
};
