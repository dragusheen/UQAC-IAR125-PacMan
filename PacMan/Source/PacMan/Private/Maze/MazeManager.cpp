/*
	Author:
		>> Nathan TIROLF - { ntirolf@etu.uqac.ca }

		(„• ֊ •„)❤  <  Have a good day !
		--U-----U------------------------
*/

/* ----- INCLUDES -----*/
#include "Maze/MazeManager.h"


/* ----- PUBLIC -----*/
AMazeManager::AMazeManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMazeManager::BeginPlay()
{
	Super::BeginPlay();

	GenerateMazeGrid();
	SpawnMaze();
}


/* ----- PRIVATE -----*/
void AMazeManager::GenerateMazeGrid()
{
    InitializeMazeGrid();
    GenerateMazeDFS();
    BreakMazeWalls();
}

void AMazeManager::InitializeMazeGrid()
{
    MazeGrid.Empty();
    for(int Y = 0; Y < GridSize.Y; Y++)
    {
        TArray<ETileType> Row;
        for(int X = 0; X < GridSize.X; X++) Row.Add(ETileType::Wall);
        MazeGrid.Add(Row);
    }
}

void AMazeManager::GenerateMazeDFS()
{
    constexpr  int StartX = 1;
    constexpr  int StartY = 1;
    MazeGrid[StartY][StartX] = ETileType::Empty;

    TArray<FIntPoint> Stack;
    Stack.Push(FIntPoint(StartX, StartY));

    const TArray<FIntPoint> Directions = { {2,0}, {-2,0}, {0,2}, {0,-2} };

    while(Stack.Num() > 0)
    {
        FIntPoint Current = Stack.Pop();

        TArray<FIntPoint> ShuffledDirs = Directions;
        for(int i=ShuffledDirs.Num()-1; i>0; i--)
        {
            int j = FMath::RandRange(0, i);
            ShuffledDirs.Swap(i,j);
        }

        for(FIntPoint Dir : ShuffledDirs)
        {
            FIntPoint Next = Current + Dir;

            if(Next.X <= 0 || Next.X >= GridSize.X-1 || Next.Y <= 0 || Next.Y >= GridSize.Y-1) continue;

            if(MazeGrid[Next.Y][Next.X] == ETileType::Wall)
            {
                FIntPoint Between = Current + FIntPoint(Dir.X/2, Dir.Y/2);
                MazeGrid[Between.Y][Between.X] = ETileType::Empty;
                MazeGrid[Next.Y][Next.X] = ETileType::Empty;

                Stack.Push(Next);
            }
        }
    }
}

void AMazeManager::BreakMazeWalls()
{
    int TotalWalls = 0;
    for(int Y=1; Y<GridSize.Y-1; Y++)
        for(int X=1; X<GridSize.X-1; X++)
            if(MazeGrid[Y][X] == ETileType::Wall)
                TotalWalls++;

    int NumRandomBreaks = FMath::RoundToInt(TotalWalls * (DestructionRate / 100.f));

    for(int i=0; i<NumRandomBreaks; i++)
    {
        int X = FMath::RandRange(1, GridSize.X-2);
        int Y = FMath::RandRange(1, GridSize.Y-2);

        if(CanBreakWall(X,Y)) MazeGrid[Y][X] = ETileType::Empty;
    }
}

bool AMazeManager::CanBreakWall(int X, int Y)
{
	if(MazeGrid[Y][X] != ETileType::Wall) return false;

	const TArray<FIntPoint> Neighbors = { {0,1}, {0,-1}, {1,0}, {-1,0} };
	bool N = false, S = false, E = false, W = false;

	for(FIntPoint Off : Neighbors)
	{
		int NX = X + Off.X;
		int NY = Y + Off.Y;
		if(NX <=0 || NX >= GridSize.X-1 || NY <=0 || NY >= GridSize.Y-1) continue;

		if(MazeGrid[NY][NX] == ETileType::Empty)
		{
			if(Off.X == 0 && Off.Y == 1) N = true;
			else if(Off.X == 0 && Off.Y == -1) S = true;
			else if(Off.X == 1 && Off.Y == 0) E = true;
			else if(Off.X == -1 && Off.Y == 0) W = true;
		}
	}

	return ((N && S && !E && !W) || (E && W && !N && !S));
}

void AMazeManager::SpawnMaze()
{
	if(!WallTileClass) return;

	UWorld* World = GetWorld();
	if(!World) return;

	const float BaseX = (GridSize.X * CellSize * CellSpriteSize) / 2;
	const float BaseY = (GridSize.Y * CellSize * CellSpriteSize) / 2;

	for(int Y = 0; Y < MazeGrid.Num(); Y++)
	{
		for(int X=0; X < MazeGrid[Y].Num(); X++)
		{
			if(MazeGrid[Y][X] == ETileType::Wall)
			{
				FVector Location = FVector(
					X * CellSize * CellSpriteSize - BaseX + GridDisplayOffset.X,
					Y * CellSize * CellSpriteSize - BaseY + GridDisplayOffset.Y,
					0.f
				);
				if(AMazeTile* Tile = World->SpawnActor<AMazeTile>(WallTileClass, Location, FRotator::ZeroRotator))
				{
					Tile->SetActorScale3D(FVector(CellSize, CellSize, CellSize));
					SetTileNeighbor(X, Y, Tile);
				}
			}
		}
	}
}

void AMazeManager::SetTileNeighbor(int X, int Y, AMazeTile* Tile)
{
	Tile->SetNeighbor(
		X > 0 && MazeGrid[Y][X - 1] == ETileType::Wall,
		X < GridSize.X - 1 && MazeGrid[Y][X + 1] == ETileType::Wall,
		Y > 0 && MazeGrid[Y][X] == ETileType::Wall,
		Y < GridSize.Y - 1 && MazeGrid[Y + 1][X] == ETileType::Wall
	);
}