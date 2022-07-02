// Copyright Jonathan Justin Rampersad 2022


#include "MetalInMotionGameInstance.h"

#include "Engine/RendererSettings.h"
#include "Kismet/GameplayStatics.h"

void UMetalInMotionGameInstance::Check(FSpeedrunStruct Data, int32 Level)
{
	if(Data.Difficulty == EDifficulty::ED_Hard)
		Level += 6;

	if(HighScores[Level].Minute >= Data.Minute)
		if(HighScores[Level].Seconds >= Data.Seconds)
			if(HighScores[Level].Milliseconds > Data.Milliseconds)
				HighScores[Level] = Data;
}

UMetalInMotionGameInstance::UMetalInMotionGameInstance()
{
	HighScores.Init(FSpeedrunStruct{}, 12);
	TempScores.Init(FSpeedrunStruct{}, 6);
	TempScores[5].Level = ESpeedrunData::ESD_Total;
	
	UMetalInMotionSaveGame* SaveGameInstance = Cast<UMetalInMotionSaveGame>(UGameplayStatics::CreateSaveGameObject(UMetalInMotionSaveGame::StaticClass()));
	UMetalInMotionSaveGame* IsSaveGame = Cast<UMetalInMotionSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MainSlot"), 0));

	if(!IsSaveGame)
	{
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("MainSlot"), 0);

		HighScores[0].Level = ESpeedrunData::ESD_L1;
		HighScores[1].Level = ESpeedrunData::ESD_L2;
		HighScores[2].Level = ESpeedrunData::ESD_L3;
		HighScores[3].Level = ESpeedrunData::ESD_L4;
		HighScores[4].Level = ESpeedrunData::ESD_L5;
		HighScores[5].Level = ESpeedrunData::ESD_Total;

		HighScores[6].Level = ESpeedrunData::ESD_L1;
		HighScores[7].Level = ESpeedrunData::ESD_L2;
		HighScores[8].Level = ESpeedrunData::ESD_L3;
		HighScores[9].Level = ESpeedrunData::ESD_L4;
		HighScores[10].Level = ESpeedrunData::ESD_L5;
		HighScores[11].Level = ESpeedrunData::ESD_Total;

		HighScores[6].Difficulty = EDifficulty::ED_Hard;
		HighScores[7].Difficulty = EDifficulty::ED_Hard;
		HighScores[8].Difficulty = EDifficulty::ED_Hard;
		HighScores[9].Difficulty = EDifficulty::ED_Hard;
		HighScores[10].Difficulty = EDifficulty::ED_Hard;
		HighScores[11].Difficulty = EDifficulty::ED_Hard;
	}
	else
	{
		for (int i = 0; i < 12; i++)
			HighScores[i] = IsSaveGame->HighScores[i];
	}
}

void UMetalInMotionGameInstance::SaveGame()
{
	UMetalInMotionSaveGame* SaveGameInstance = Cast<UMetalInMotionSaveGame>(UGameplayStatics::CreateSaveGameObject(UMetalInMotionSaveGame::StaticClass()));
	SaveGameInstance = Cast<UMetalInMotionSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MainSlot"), 0));

	for (int i = 0; i < 12; i++)
	{
		if(SaveGameInstance->HighScores[i].Minute >= HighScores[i].Minute)
			if(SaveGameInstance->HighScores[i].Seconds >= HighScores[i].Seconds)
				if(SaveGameInstance->HighScores[i].Milliseconds > HighScores[i].Milliseconds)
					SaveGameInstance->HighScores[i] = HighScores[i];
	}
}


void UMetalInMotionGameInstance::NewScore(FSpeedrunStruct Data)
{
	switch (Data.Level)
	{
	case ESpeedrunData::ESD_L1:
		TempScores[0] = Data;
		Check(Data, 0);
		break;
	case ESpeedrunData::ESD_L2:
		TempScores[1] = Data;
		Check(Data, 1);
		break;
	case ESpeedrunData::ESD_L3:
		TempScores[2] = Data;
		Check(Data, 2);
		break;
	case ESpeedrunData::ESD_L4:
		TempScores[3] = Data;
		Check(Data, 3);
		break;
	case ESpeedrunData::ESD_L5:
		TempScores[4] = Data;
		Check(Data, 4);

		TempScores[5].Difficulty = Data.Difficulty;
		for (int i = 0; i < 5; i++)
		{
			TempScores[5].Minute += TempScores[i].Minute;
			TempScores[5].Seconds += TempScores[i].Seconds;
			TempScores[5].Milliseconds += TempScores[i].Milliseconds;
		}

		Check(TempScores[5], 5);

		SaveGame();
		break;
	case ESpeedrunData::ESD_Total:
		break;
	}
}