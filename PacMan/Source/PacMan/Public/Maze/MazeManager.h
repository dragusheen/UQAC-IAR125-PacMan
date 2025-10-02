/*
    Author:
		>> Nathan TIROLF - { ntirolf@etu.uqac.ca }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/


/* ----- INCLUDES -----*/
#pragma once

#include "CoreMinimal.h"
#include "MazeTile.h"
#include "GameFramework/Actor.h"
#include "MazeManager.generated.h"


/* ----- ENUM -----*/
UENUM(BlueprintType)
enum class ETileType : uint8
{
	Wall UMETA(DisplayName = "Wall"),
	Empty UMETA(DisplayName = "Empty"),
};


/* ----- CLASS -----*/
UCLASS()
class PACMAN_API AMazeManager : public AActor
{
	GENERATED_BODY()

public:
	AMazeManager();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "1"))
	FIntPoint GridSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "1"))
	float CellSize = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "1"))
	int CellSpriteSize = 16;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0", ClampMax = "80"))
	float DestructionRate = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<AMazeTile> WallTileClass;

private:
	TArray<TArray<ETileType>> MazeGrid;
	float BaseX;
	float BaseY;

	void GenerateMazeGrid();
	void InitializeMazeGrid();
	void AddFixedZone();
	void GenerateMazeDFS();
	void BreakMazeWalls();
	bool CanBreakWall(int X, int Y);
	void SpawnMaze();
	void SpawnTile(int X, int Y);
	void SetTileNeighbor(int X, int Y, AMazeTile* Tile);
};
