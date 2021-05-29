// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonProcGenBase.generated.h"



UENUM()
enum TileType
{
	Empty UMETA(DisplayName = "Empty"),
	Wall UMETA(DisplayName = "Wall"),
	Floor UMETA(DisplayName = "Floor"),
	Maze UMETA(DisplayName = "Maze")
};

UCLASS()
class GAMEJAMMING_API ADungeonProcGenBase : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ADungeonProcGenBase();
	UPROPERTY(EditAnywhere)
		int32 MapWidth = 20; //default map width of 20

	UPROPERTY(EditAnywhere)
		int32 MapLength = 20;// default map height of 20

	UPROPERTY(EditAnywhere)
		bool bAddRooms = true; //default 2 rooms

	UPROPERTY(EditAnywhere)
		int32 NumRooms = 2; //default 2 rooms


	UPROPERTY(EditAnywhere)
		int32 RoomMinSizeX = 2; //default 2 rooms

	UPROPERTY(EditAnywhere)
		int32 RoomMinSizeY = 2; //default 2 rooms

	UPROPERTY(EditAnywhere)
		int32 RoomMaxSizeX = 2; //default 2 rooms

	UPROPERTY(EditAnywhere)
		int32 RoomMaxSizeY = 2; //default 2 rooms

	UPROPERTY(EditAnywhere)
		float tileSizeMultiplier = 400; //Used for scaling up

	UPROPERTY(EditAnywhere)
		float TileXScale = 4;

	UPROPERTY(EditAnywhere)
		float TileYScale = 4;


	UPROPERTY(EditAnywhere)
		float TileZScale = 4;


	UPROPERTY(EditAnywhere)
		int32 RandomSeed = 0;

	UPROPERTY(EditAnywhere)
		int32 RandomRoomSeed = 0;


	UPROPERTY(EditAnywhere, Category = "Spawn Controls")
		bool bClosedMap = true;

	FRandomStream RandStream;

	FRandomStream RandRoomStream;

	int CurrentMapX;
	int CurrentMapY;

	UFUNCTION(BlueprintCallable)
		int GetCurrentMapX() { return CurrentMapX; };

	UFUNCTION(BlueprintCallable)
		int GetCurrentMapY() { return CurrentMapY; };

	UFUNCTION(BlueprintCallable)
		float GetTileMultiplier() { return tileSizeMultiplier; };

	UFUNCTION(BlueprintCallable)
		bool Search2D(int c, int r, TArray<int> Pattern);


	UFUNCTION(BlueprintCallable)
	bool FloorCheck(FVector2D MapPos);


	UFUNCTION(BlueprintCallable)
		float GetTileScaleX() { return TileXScale; };

	UFUNCTION(BlueprintCallable)
		float GetTileScaleY() { return TileYScale; };

	UFUNCTION(BlueprintCallable)
		float GetTileScaleZ() { return TileZScale; };

	UFUNCTION(BlueprintNativeEvent)
		void DrawAtPosition();

	UFUNCTION(BlueprintNativeEvent)
		void PlaceCharacter();

	TMap<FVector2D, int32> CurrentMap;
	UFUNCTION(BlueprintCallable)
		TMap<FVector2D, int32> GetMap() { return CurrentMap; }

	void InitializeMap();
	virtual void Generate();
	void DrawMap();
	virtual void AddRooms(int RoomCount);

	int CountSideNeigbhors(int x, int y);

	int CountDiagNeigbhors(int x, int y);

	int CountAllNeighbors(int x, int y);



	bool OutOfBoundsCheck(int x, int y);

	FVector2D UpX{ 1,0 };
	FVector2D UpY{ 0,1 };
	FVector2D DownX{ -1,0 };
	FVector2D DownY{ 0,-1 };

	UPROPERTY(BlueprintReadOnly)
	bool TopWall;
	UPROPERTY(BlueprintReadOnly)
	bool BottomWall;
	UPROPERTY(BlueprintReadOnly)
	bool LeftWall;
	UPROPERTY(BlueprintReadOnly)
	bool RightWall;



	UFUNCTION(BlueprintCallable)
	void LocateWalls(FVector2D MapPos);


	TArray<FVector2D> MapDirections{ UpX, UpY, DownX, DownY };
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
