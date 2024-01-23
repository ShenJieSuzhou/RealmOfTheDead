// Copyright Epic Games, Inc. All Rights Reserved.

#include "ROTDLoadingScreen.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "MoviePlayer.h"
#include "Widgets/Images/SThrobber.h"

// This module must be loaded "PreLoadingScreen" in the .uproject file, otherwise it will not hook in time!
struct FROTDLoadingScreenBrush : public FSlateDynamicImageBrush, public FGCObject
{
	FROTDLoadingScreenBrush(const FName InTextureName, const FVector2D& InImageSize)
		: FSlateDynamicImageBrush(InTextureName, InImageSize)
	{
		SetResourceObject(LoadObject<UObject>(NULL, *InTextureName.ToString()));
	}

	virtual void AddReferencedObjects(FReferenceCollector& Collector)
	{
		if (UObject* CachedResourceObject = GetResourceObject())
		{
			Collector.AddReferencedObject(CachedResourceObject);
		}
	}
};

class SROTDLoadingScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SROTDLoadingScreen) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		// Load version of the logo with text baked in, path is hardcoded because this loads very early in startup
		//static const FName LoadingScreenName(TEXT("/Game/ROTD/UI/BK_ROTD.BK_ROTD"));
		//Texture2D'/Game/ROTD/UI/T_ActionRPG_TransparentLogo.T_ActionRPG_TransparentLogo'
		static const FName LoadingScreenName(TEXT("/Game/ROTD/UI/T_ActionRPG_TransparentLogo.T_ActionRPG_TransparentLogo"));
		//UTexture2D* LoadingScreenTexture = FindObject<UTexture2D>(NULL, *LoadingScreenName.ToString());
		//if (!LoadingScreenTexture)
		//{
		//	LoadingScreenTexture = LoadObject<UTexture2D>(NULL, *LoadingScreenName.ToString());
		//}

		//LoadingScreenBrush = FDeferredCleanupSlateBrush::CreateBrush(LoadingScreenTexture, FVector2D(LoadingScreenTexture->GetSurfaceWidth(), LoadingScreenTexture->GetSurfaceHeight()));

		LoadingScreenBrush = MakeShareable(new FROTDLoadingScreenBrush(LoadingScreenName, FVector2D(1024, 256)));
		
		FSlateBrush *BGBrush = new FSlateBrush();
		BGBrush->TintColor = FLinearColor(0.034f, 0.034f, 0.034f, 1.0f);

		ChildSlot
			[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SBorder)	
				.BorderImage(BGBrush)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(LoadingScreenBrush.Get())
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Right)
				.Padding(FMargin(10.0f))
				[
					SNew(SThrobber)
					.Visibility(this, &SROTDLoadingScreen::GetLoadIndicatorVisibility)
				]
			]
		];
	}

private:
	/** Rather to show the ... indicator */
	EVisibility GetLoadIndicatorVisibility() const
	{
		return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Collapsed : EVisibility::Visible;
	}
	
	/** Loading screen image brush */
	TSharedPtr<FSlateDynamicImageBrush> LoadingScreenBrush;
	//TSharedPtr<FDeferredCleanupSlateBrush> LoadingScreenBrush;
};

class FROTDLoadingScreenModule : public IROTDLoadingScreenModule
{
public:
	virtual void StartupModule() override
	{
		// Force load for cooker reference
		LoadObject<UObject>(nullptr, TEXT("/Game/ROTD/UI/T_ActionRPG_TransparentLogo.T_ActionRPG_TransparentLogo"));

		if (IsMoviePlayerEnabled())
		{
			//GetMoviePlayer()->OnPrepareLoadingScreen().AddRaw(this, &FROTDLoadingScreenModule::OnPrepareLoadingScreen);

			/*if (FParse::Param(FCommandLine::Get(), TEXT("CN")))
			{
				SetupLoadingMovie({ "LoadingScreenCN" }, 15);
			}
			else
			{
				SetupLoadingMovie({ "LoadingScreenCN" }, 15);
			}*/
		}

		if (IsMoviePlayerEnabled())
		{
			CreateScreen();
		}
	}
	
	virtual bool IsGameModule() const override
	{
		return true;
	}

	void OnPrepareLoadingScreen()
	{
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}

	//virtual void StartInGameLoadingScreen(bool bPlayUntilStopped, float PlayTime) override
	//{
	//	FLoadingScreenAttributes LoadingScreen;
	//	LoadingScreen.bAutoCompleteWhenLoadingCompletes = !bPlayUntilStopped;
	//	LoadingScreen.bWaitForManualStop = bPlayUntilStopped;
	//	LoadingScreen.bAllowEngineTick = bPlayUntilStopped;
	//	LoadingScreen.MinimumLoadingScreenDisplayTime = PlayTime;
	//	LoadingScreen.WidgetLoadingScreen = SNew(SRPGLoadingScreen);
	//	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	//}

	//virtual void StopInGameLoadingScreen() override
	//{
	//	GetMoviePlayer()->StopMovie();
	//}

	virtual void SetupLoadingMovie(TArray<FString> MoviePaths, float MinimumLoadingScreenDisplayTime = -1.f) override
	{
		if (IsMoviePlayerEnabled())
		{
			LoadingScreen = FLoadingScreenAttributes();
			LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
			LoadingScreen.MinimumLoadingScreenDisplayTime = MinimumLoadingScreenDisplayTime;
			LoadingScreen.MoviePaths = MoviePaths;
			LoadingScreen.bMoviesAreSkippable = true;
			LoadingScreen.PlaybackType = EMoviePlaybackType::MT_Normal;
			LoadingScreen.bAllowEngineTick = false;
		}
	}

	virtual void SetupLoadingScreen(FString Tooltip, float MinimumLoadingScreenDisplayTime = -1.f) override
	{
		if (IsMoviePlayerEnabled())
		{
			LoadingScreen = FLoadingScreenAttributes();
			LoadingScreen.MinimumLoadingScreenDisplayTime = MinimumLoadingScreenDisplayTime;
			LoadingScreen.bMoviesAreSkippable = false;
			LoadingScreen.WidgetLoadingScreen = SNew(SROTDLoadingScreen);
			GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
		}
	}

	virtual void CreateScreen()
	{
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
		LoadingScreen.MinimumLoadingScreenDisplayTime = 3.f;
		LoadingScreen.WidgetLoadingScreen = SNew(SROTDLoadingScreen);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}

private:
	FLoadingScreenAttributes LoadingScreen;
};

IMPLEMENT_GAME_MODULE(FROTDLoadingScreenModule, ROTDLoadingScreen);
