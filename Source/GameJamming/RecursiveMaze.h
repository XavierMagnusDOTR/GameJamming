// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonProcGenBase.h"
#include "RecursiveMaze.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAMMING_API ARecursiveMaze : public ADungeonProcGenBase
{
	GENERATED_BODY()

		void Generate() override;


	void Generate(int x, int y);


	int LoopCount = 0;
};
