// Fill out your copyright notice in the Description page of Project Settings.


#include "CrawlerDungeon.h"

void ACrawlerDungeon::Generate()
{
	if (bRunPrims)
	{
		if (PrimsGeneratorCount < 0) { PrimsGeneratorCount = 0; }
		for (int i = 0; i < PrimsGeneratorCount; i++)
		{
			RunPrims();
		}
	}
	else
	{
		if (CenterGeneratorCount < 0) { CenterGeneratorCount = 0; }
		for (int i = 0; i < CenterGeneratorCount; i++)
		{
			CenterOutCrawler();
		}


		if (HorizontalGeneratorCount < 0) { HorizontalGeneratorCount = 0; }
		for (int i = 0; i < HorizontalGeneratorCount; i++)
		{
			HCrawler();

		}


		if (VerticalGeneratorCount < 0) { VerticalGeneratorCount = 0; }
		for (int i = 0; i < VerticalGeneratorCount; i++)
		{
			VCrawler();

		}
	}

}

void ACrawlerDungeon::VCrawler()
{

	bool Done = false;
	int x = MapWidth / 2;
	int y = 0;
	if (bClosedMap) { y = 1; }
	if (RandomVertGenerator)
	{

		int NewRandomPos = RandStream.RandRange(1, MapWidth - 1);
		if (bClosedMap) { if (NewRandomPos == MapLength - 1) { NewRandomPos -= 1; } }
		x = NewRandomPos;
	}
	FVector2D currentPosition = FVector2D(x, y);
	CurrentMap.Add(currentPosition, Floor);
	while (!Done)
	{
		int NewRandomX = RandStream.RandRange(-1, 1);
		int NewRandomY = RandStream.RandRange(0, 1);

		int NewRandDirection = RandStream.RandRange(0, 100);
		if (RandomVertDeviation < 0) { RandomVertDeviation = 0; }
		if (RandomVertDeviation > 1) { RandomVertDeviation = 1; }
		if (NewRandDirection < RandomVertDeviation * 100)
			currentPosition.X += NewRandomX;
		else
			currentPosition.Y += NewRandomY;


		if (!bClosedMap)
			Done = (currentPosition.X < 0 || currentPosition.X > MapWidth - 1 || currentPosition.Y < 0 || currentPosition.Y > MapLength - 1);
		else
			Done = (currentPosition.X < 1 || currentPosition.X > MapWidth - 2 || currentPosition.Y < 1 || currentPosition.Y > MapLength - 2);

		if (!Done)
		{
			CurrentMap.Add(currentPosition, Floor);
		}

	}
}

void ACrawlerDungeon::HCrawler()
{
	bool Done = false;
	//int x = MapWidth / 2; // For half map
	int x = 0;
	if (bClosedMap) { x = 1; }
	int y = MapLength / 2;
	if (RandomVertGenerator)
	{

		int NewRandomPos = RandStream.RandRange(1, MapWidth - 1);
		if (bClosedMap) { if (NewRandomPos == MapWidth - 1) { NewRandomPos -= 1; } }
		y = NewRandomPos;
	}
	FVector2D currentPosition = FVector2D(x, y);
	CurrentMap.Add(currentPosition, Floor);
	while (!Done)
	{
		int NewRandomX = RandStream.RandRange(0, 1);
		int NewRandomY = RandStream.RandRange(-1, 1);

		int NewRandDirection = RandStream.RandRange(0, 100);
		if (RandomHorizDeviation < 0) { RandomHorizDeviation = 0; }
		if (RandomHorizDeviation > 1) { RandomHorizDeviation = 1; }
		if (NewRandDirection > RandomHorizDeviation * 100)
			currentPosition.X += NewRandomX;
		else
			currentPosition.Y += NewRandomY;


		if (!bClosedMap)
			Done = (currentPosition.X < 0 || currentPosition.X > MapWidth - 1 || currentPosition.Y < 0 || currentPosition.Y > MapLength - 1);
		else
			Done = (currentPosition.X < 1 || currentPosition.X > MapWidth - 2 || currentPosition.Y < 1 || currentPosition.Y > MapLength - 2);

		if (!Done)
		{
			CurrentMap.Add(currentPosition, Floor);
		}

	}
}

void ACrawlerDungeon::CenterOutCrawler()
{
	bool Done = false;
	//int x = MapWidth / 2; // For half map
	int x = MapWidth / 2;
	int y = MapLength / 2;

	FVector2D currentPosition = FVector2D(x, y);
	CurrentMap.Add(currentPosition, Floor);
	while (!Done)
	{
		int NewRandomX = RandStream.RandRange(-1, 1);
		int NewRandomY = RandStream.RandRange(-1, 1);

		int NewRandDirection = RandStream.RandRange(0, 100);
		if (NewRandDirection > 50)
			currentPosition.X += NewRandomX;
		else
			currentPosition.Y += NewRandomY;


		if (!bClosedMap)
			Done = (currentPosition.X < 0 || currentPosition.X > MapWidth - 1 || currentPosition.Y < 0 || currentPosition.Y > MapLength - 1);
		else
			Done = (currentPosition.X < 1 || currentPosition.X > MapWidth - 2 || currentPosition.Y < 1 || currentPosition.Y > MapLength - 2);

		if (!Done)
		{
			CurrentMap.Add(currentPosition, Floor);
		}

	}
}

void ACrawlerDungeon::RunPrims()
{
	bool Done = false;
	int x = RandStream.RandRange(1, MapWidth - 1);;
	int y = RandStream.RandRange(1, MapLength - 1);;

	FVector2D currentPosition = FVector2D(x, y);
	TArray<FVector2D> walls;
	walls.Add(FVector2D(currentPosition.X + 1, currentPosition.Y));
	walls.Add(FVector2D(currentPosition.X - 1, currentPosition.Y));
	walls.Add(FVector2D(currentPosition.X, currentPosition.Y + 1));
	walls.Add(FVector2D(currentPosition.X, currentPosition.Y - 1));

	CurrentMap.Add(currentPosition, Floor);

	int CountLoops = 0;
	while (walls.Num() > 0 && CountLoops < 5000)
	{
		int rWall = RandStream.RandRange(0, walls.Num() - 1);
		currentPosition.X = walls[rWall].X;
		currentPosition.Y = walls[rWall].Y;

		walls.Remove(currentPosition);
		if (CountSideNeigbhors(currentPosition.X, currentPosition.Y) == 1)
		{
			CurrentMap.Add(currentPosition, Floor);

			walls.Add(FVector2D(currentPosition.X + 1, currentPosition.Y));
			walls.Add(FVector2D(currentPosition.X - 1, currentPosition.Y));
			walls.Add(FVector2D(currentPosition.X, currentPosition.Y + 1));
			walls.Add(FVector2D(currentPosition.X, currentPosition.Y - 1));

		}
		else { UE_LOG(LogTemp, Warning, TEXT("Value of CountSideNeighbors is %i"), CountSideNeigbhors(currentPosition.X, currentPosition.Y)) }

		CountLoops++;
	}


}
