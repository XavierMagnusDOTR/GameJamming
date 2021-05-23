// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonProcGenBase.h"
#include "CrawlerDungeon.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAMMING_API ACrawlerDungeon : public ADungeonProcGenBase
{
	GENERATED_BODY()


		void Generate() override;

	void VCrawler();
	void HCrawler();
	void CenterOutCrawler();
	void RunPrims();



	UPROPERTY(EditAnywhere, Category = "Spawn Controls")
		bool RandomVertGenerator = true;

	UPROPERTY(EditAnywhere, Category = "Spawn Controls")
		bool bRunPrims = false;
	UPROPERTY(EditAnywhere, Category = "Spawn Controls")
		int PrimsGeneratorCount;

	UPROPERTY(EditAnywhere, Category = "Spawn Controls")
		float RandomVertDeviation = .25;


	UPROPERTY(EditAnywhere, Category = "Spawn Controls")
		bool RandomHorizontalGenerator = true;

	UPROPERTY(EditAnywhere, Category = "Spawn Controls")
		float RandomHorizDeviation = .25;


	UPROPERTY(EditAnywhere, Category = "Spawn Controls")
		int HorizontalGeneratorCount = 2;


	UPROPERTY(EditAnywhere, Category = "Spawn Controls")
		int VerticalGeneratorCount = 2;


	UPROPERTY(EditAnywhere, Category = "Spawn Controls")
		int CenterGeneratorCount = 2;



};
