// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonProcGenBase.h"

// Sets default values
ADungeonProcGenBase::ADungeonProcGenBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ADungeonProcGenBase::BeginPlay()
{
	Super::BeginPlay();
	RandStream = FRandomStream(RandomSeed);
	RandRoomStream = FRandomStream(RandomRoomSeed);

	InitializeMap();
	Generate();
	if (bAddRooms)
	{
		AddRooms(NumRooms);
	}
	DrawMap();
	PlaceCharacter();
}

void ADungeonProcGenBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ADungeonProcGenBase::Search2D(int c, int r, TArray<int> Pattern)
{
	int Count = 0;
	int Pos = 0;
	for (int y = 1; y > -2; y--)
	{

		UE_LOG(LogTemp, Warning, TEXT("Pos value before is: %i"), Pos)
			for (int x = -1; x < 2; x++)
			{
				// Logic equals pos 0 c -1, r +1 pos 1 c, r +1, pos 2 c + 1, r +1 
				// pos 3 c, z // or more visually x^ y->  8 5 2
				//                                        7 4 1  4 should always be 2 as that's a room for being tested. 0 is reserved for negative FindRef, 1 indicates a wall in initialize, 2 indicates a room
				//                                        6 3 0
				if (CurrentMap.FindRef(FVector2D(c + x, r + y)) != 0)
				{
					if (Pattern[Pos] == CurrentMap[FVector2D(c + x, r + y)] || Pattern[Pos] == 5)
					{

						Count++;

						UE_LOG(LogTemp, Warning, TEXT("Count match: %i"), Count)

					}
				}
				else { UE_LOG(LogTemp, Warning, TEXT("CurrentMap = 0")) }
				Pos++;

			}
	}
	UE_LOG(LogTemp, Warning, TEXT("Count is : %i"), Count)
		return (Count == 9);
}

void ADungeonProcGenBase::DrawAtPosition_Implementation()
{

}

void ADungeonProcGenBase::PlaceCharacter_Implementation()
{

}

void ADungeonProcGenBase::InitializeMap()
{
	for (int x = 0; x < MapWidth; x++)
	{
		for (int y = 0; y < MapLength; y++)
		{
			FVector2D CurrentMapXY = FVector2D(x, y);
			CurrentMap.Add(CurrentMapXY, Wall);
		}
	}

}

void ADungeonProcGenBase::Generate()
{
	for (int x = 0; x < MapWidth; x++)
	{
		for (int y = 0; y < MapLength; y++)
		{
			FVector2D CurrentMapXY = FVector2D(x, y);
			//			
			CurrentMap.Add(CurrentMapXY, Wall);
		}
	}
}

void ADungeonProcGenBase::DrawMap()
{

	DrawAtPosition(); //passing through bp, which then grabs the values to instantiate the instanced static mesh added there. Just a little less headache than drawing it here and reaching through.
}


void ADungeonProcGenBase::AddRooms(int RoomCount)
{
	for (int c = 0; c < RoomCount; c++)
	{
		int startX = RandRoomStream.RandRange(3, MapWidth - 3);

		int startY = RandRoomStream.RandRange(3, MapLength - 3);
		//int startY = FMath::RandRange(3, MapLength -3); 
		int RoomWidth = RandStream.RandRange(RoomMinSizeX, RoomMaxSizeX);
		int RoomLength = RandStream.RandRange(RoomMinSizeY, RoomMaxSizeY);

		UE_LOG(LogTemp, Warning, TEXT("Start Values are startX: %i, starty: %i /n MapWidth: %i, MapLength: %i"), startX, startY, MapWidth, MapLength)
			for (int x = startX; x < MapWidth - 3 && x < startX + RoomWidth; x++)
			{
				for (int y = startY; y < MapLength - 3 && y < startY + RoomLength; y++)
				{
					CurrentMap.Add(FVector2D(x, y), 2);
					UE_LOG(LogTemp, Warning, TEXT(" Inner most Room added at X: %i, sy: %i"), x, y)
				}
			}


		UE_LOG(LogTemp, Warning, TEXT("Room Added inner loop startX: %i, starty: %i"), startX, startY)
	}
	UE_LOG(LogTemp, Warning, TEXT("Room Added"))
}

int ADungeonProcGenBase::CountSideNeigbhors(int x, int y)
{
	FVector2D CurrentXY;
	int CurrentCount = 0;
	CurrentXY = FVector2D(x - 1, y);
	int MapValue = CurrentMap.FindRef(CurrentXY);
	if (!OutOfBoundsCheck(CurrentXY.X, CurrentXY.Y))
	{
		if (MapValue == Floor || MapValue == Maze)
		{
			CurrentCount++;
		}
	}
	else { CurrentCount = 12;  return CurrentCount; }

	CurrentXY = FVector2D(x + 1, y);
	MapValue = CurrentMap.FindRef(CurrentXY);
	if (!OutOfBoundsCheck(CurrentXY.X, CurrentXY.Y))
	{
		if (MapValue == Floor || MapValue == Maze)
		{
			CurrentCount++;
		}
	}
	else { CurrentCount = 12; return CurrentCount; }

	CurrentXY = FVector2D(x, y + 1);
	MapValue = CurrentMap.FindRef(CurrentXY);
	if (!OutOfBoundsCheck(CurrentXY.X, CurrentXY.Y))
	{
		if (MapValue == Floor || MapValue == Maze)
		{
			CurrentCount++;
		}
	}
	else { CurrentCount = 12; return CurrentCount; }

	CurrentXY = FVector2D(x, y - 1);
	MapValue = CurrentMap.FindRef(CurrentXY);
	if (!OutOfBoundsCheck(CurrentXY.X, CurrentXY.Y))
	{
		if (MapValue == Floor || MapValue == Maze)
		{
			CurrentCount++;
		}
	}
	else { CurrentCount = 12; return CurrentCount; }

	return CurrentCount;
}

int ADungeonProcGenBase::CountDiagNeigbhors(int x, int y)
{

	FVector2D CurrentXY;
	int CurrentCount = 0;
	if (!OutOfBoundsCheck(CurrentXY.X, CurrentXY.Y))
	{
		CurrentXY = FVector2D(x - 1, y - 1); if (CurrentMap.FindRef(CurrentXY) == Floor) { CurrentCount++; }
		CurrentXY = FVector2D(x - 1, y + 1); if (CurrentMap.FindRef(CurrentXY) == Floor) { CurrentCount++; }
		CurrentXY = FVector2D(x + 1, y - 1); if (CurrentMap.FindRef(CurrentXY) == Floor) { CurrentCount++; }
		CurrentXY = FVector2D(x + 1, y + 1); if (CurrentMap.FindRef(CurrentXY) == Floor) { CurrentCount++; }
	}
	else { CurrentCount = 12; return CurrentCount; }
	return CurrentCount;
}

int ADungeonProcGenBase::CountAllNeighbors(int x, int y)
{
	int FinalCount = 0;
	int SideCount = CountSideNeigbhors(x, y);
	int DiagCount = CountDiagNeigbhors(x, y);
	FinalCount = SideCount + DiagCount;
	return FinalCount;
}



bool ADungeonProcGenBase::OutOfBoundsCheck(int x, int y)
{
	bool Out = false;
	if (bClosedMap)
	{
		Out = (x < 1 || x > MapWidth - 2 || y < 1 || y > MapLength - 2);
	}
	else
	{
		Out = (x < 1 || x > MapWidth - 1 || y < 1 || y > MapLength - 1);
	}
	return Out;
}
