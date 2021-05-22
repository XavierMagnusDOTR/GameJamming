// Fill out your copyright notice in the Description page of Project Settings.


#include "RecursiveMaze.h"

void ARecursiveMaze::Generate()
{
	Generate(RandStream.RandRange(3, MapLength - 2), RandStream.RandRange(3, MapWidth - 3));
}

void ARecursiveMaze::Generate(int x, int y)
{
	LoopCount++;
	if (LoopCount > 50000) { return; }

	if (CountSideNeigbhors(x, y) >= 2) { return; }
	CurrentMap.Add(FVector2D(x, y), Floor);

	for (int32 i = 0; i < MapDirections.Num() - 1; i++)
	{
		int32 swapIndex = RandStream.RandRange(i, MapDirections.Num() - 1);
		MapDirections.Swap(i, swapIndex);
	}
	Generate(x + MapDirections[0].X, y + MapDirections[0].Y);
	Generate(x + MapDirections[1].X, y + MapDirections[1].Y);
	Generate(x + MapDirections[2].X, y + MapDirections[2].Y);
	Generate(x + MapDirections[3].X, y + MapDirections[3].Y);

}

