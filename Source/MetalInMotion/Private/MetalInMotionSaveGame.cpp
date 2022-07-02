// Copyright Jonathan Justin Rampersad 2022


#include "MetalInMotionSaveGame.h"

UMetalInMotionSaveGame::UMetalInMotionSaveGame()
{
	HighScores.Init(FSpeedrunStruct{}, 12);

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
