// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FlibJumpToHelper.generated.h"

/**
 * 
 */
UCLASS()
class JUMPTO_API UFlibJumpToHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static void J2(const TArray<FString>& Args);
protected:
	static FAssetData GetAssetDataByLongPackageName(FName LongPackageNames);
	static FString LongPackageNameToPackagePath(const FString& InPackageName);
	static bool IsMatchRegExp(const FString& Str, const FString& RegExp,TArray<FString>& OutMatchStrs);
};
