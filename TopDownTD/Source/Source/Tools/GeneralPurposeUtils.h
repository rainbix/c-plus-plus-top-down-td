// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define LOG(format, ...) UE_LOG(LogCore, Log, TEXT(format), ##__VA_ARGS__);
#define LOG_WARNING(format, ...) UE_LOG(LogCore, Warning, TEXT(format), ##__VA_ARGS__);
#define LOG_ERROR(format, ...) UE_LOG(LogCore, Error, TEXT(format), ##__VA_ARGS__);

class GeneralPurposeUtils
{
public:
	static void DisplayScreenMessage(const FString& message, FColor color = FColor::Yellow, float duration = 2.0);
};
