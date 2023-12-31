// Fill out your copyright notice in the Description page of Project Settings.


#include "FlibJumpToHelper.h"

#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "Internationalization/Regex.h"
#include "Engine/AssetManager.h"
#include "Kismet/KismetStringLibrary.h"

static FAutoConsoleCommand J2Cmd(
	TEXT("j2"),
	TEXT("jump to directory or asset."),
	FConsoleCommandWithArgsDelegate::CreateStatic(&UFlibJumpToHelper::J2)
	);

#define REF_REGEX_TEXT TEXT("'[^']*/[^']*'")

enum EJumpType
{
	J2DIR,
	J2ASSET
};

void UFlibJumpToHelper::J2(const TArray<FString>& Args)
{
	if(Args.Num())
	{
		FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
		UAssetManager& AssetManager = UAssetManager::Get();
		FString JumpTo = Args[0];
		FPaths::NormalizeFilename(JumpTo);
		EJumpType Type = EJumpType::J2DIR;

		TArray<FString> OutRegStrings;
		if(FPackageName::DoesPackageExist(JumpTo) ||
			IsMatchRegExp(JumpTo,REF_REGEX_TEXT,OutRegStrings) && OutRegStrings.Num()
			)
		{
			Type = EJumpType::J2ASSET;
			if(OutRegStrings.Num())
			{
				JumpTo = OutRegStrings[0];
				while(JumpTo.RemoveFromStart(TEXT("'"))){};
				while(JumpTo.RemoveFromEnd(TEXT("'"))){};
			}
		}

		switch(Type)
		{
			case J2DIR:
				{
					FString Dir;
					FPackageName::TryConvertLongPackageNameToFilename(JumpTo,Dir,"");
					if(FPaths::DirectoryExists(Dir))
					{
						while(JumpTo.RemoveFromEnd(TEXT("/"))){};
						ContentBrowserModule.Get().SyncBrowserToFolders(TArray<FString>{JumpTo},true, true, NAME_None, false);
					}
					break;
				}
		case J2ASSET:
				{
					FAssetData AssetData = GetAssetDataByLongPackageName(*JumpTo);
					if(AssetData.IsValid())
					{
						ContentBrowserModule.Get().SyncBrowserToAssets(TArray<FAssetData>{AssetData},true, true, NAME_None, false);
					}
					break;
				}
		}
	}
}

FString UFlibJumpToHelper::LongPackageNameToPackagePath(const FString& InPackageName)
{
	if(InPackageName.Contains(TEXT(".")))
		return InPackageName;
	FString AssetName;
	{
		int32 FoundIndex;
		InPackageName.FindLastChar('/', FoundIndex);
		if (FoundIndex != INDEX_NONE)
		{
			AssetName = UKismetStringLibrary::GetSubstring(InPackageName, FoundIndex + 1, InPackageName.Len() - FoundIndex);
		}
	}
	AssetName = InPackageName + TEXT(".") + AssetName;
	return AssetName;
}

FAssetData UFlibJumpToHelper::GetAssetDataByLongPackageName(FName LongPackageNames)
{
	FString LongPackageNameStr = LongPackageNames.ToString();
	
	UAssetManager& AssetManager = UAssetManager::Get();
	FAssetData AssetDataForPath;
	FSoftObjectPath PackageObjectPath = LongPackageNameToPackagePath(LongPackageNames.ToString());
	AssetManager.GetAssetDataForPath(PackageObjectPath, AssetDataForPath);
	return AssetDataForPath;	
}

bool UFlibJumpToHelper::IsMatchRegExp(const FString& Str, const FString& RegExp,TArray<FString>& OutMatchStrs)
{
	FRegexPattern Pattern(RegExp);
	FRegexMatcher PattenMatcher(Pattern,Str);
	struct FRegexMatchResult{ int32 Begin,End; };
	TArray<FRegexMatchResult> Results;
	while(PattenMatcher.FindNext())
	{
		FRegexMatchResult MatchStrInfo;
		MatchStrInfo.Begin = PattenMatcher.GetMatchBeginning();
		MatchStrInfo.End = PattenMatcher.GetMatchEnding();
		if(MatchStrInfo.End > MatchStrInfo.Begin)
		{
			Results.Add(MatchStrInfo);
			FString MidStr = Str.Mid(MatchStrInfo.Begin,MatchStrInfo.End - MatchStrInfo.Begin);
			OutMatchStrs.AddUnique(MidStr);
		}
	}
	return !!Results.Num();
}