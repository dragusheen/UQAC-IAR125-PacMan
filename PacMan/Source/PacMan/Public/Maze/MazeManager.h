/*
    Author:
		>> Nathan TIROLF - { ntirolf@etu.uqac.ca }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/


/* ----- INCLUDES -----*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile/MazeTile.h"
#include "Tile/MazeTilePoint.h"
#include "Player/PacManPlayer.h"
#include "MazeManager.generated.h"


/* ----- ENUM -----*/
UENUM(BlueprintType)
enum class ETileType : uint8
{
	Wall UMETA(DisplayName = "Wall"),
	Empty UMETA(DisplayName = "Empty"),
	PacMan UMETA(DisplayName = "PacMan"),
	Point UMETA(DisplayName = "Point"),
	PacGun UMETA(DisplayName = "PacGun"),
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<AMazeTilePoint> PointTileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<APacManPlayer> PacManPlayerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<class AGhost> RedGhostClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<class AGhost> PinkGhostClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<class AGhost> CyanGhostClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<class AGhost> OrangeGhostClass;

private:
	TArray<TArray<ETileType>> MazeGrid;
	float BaseX;
	float BaseY;

	void GenerateMazeGrid();
	void InitializeMazeGrid();
	void AddFixedZone(const bool Large = false);
	void GenerateMazeDfs();
	void BreakMazeWalls();
	bool CanBreakWall(const int X, const int Y);
	void SpawnMaze();
	void SpawnTile(const int X, const int Y);
	void SetTileNeighbor(const int X, const int Y, AMazeTile* Tile);
	void SpawnGhosts();
};
