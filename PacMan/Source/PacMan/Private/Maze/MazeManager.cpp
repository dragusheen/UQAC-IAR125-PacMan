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
	AddFixedZone();
    GenerateMazeDfs();
    BreakMazeWalls();
	AddFixedZone(true);
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

void AMazeManager::AddFixedZone(const bool Large)
{
	constexpr int PatternPacManHeight = 5;
	constexpr int PatternPacManWidth = 5;
	constexpr ETileType PatternPacMan[PatternPacManHeight][PatternPacManWidth]{
		{ETileType::Point, ETileType::Point, ETileType::Point, ETileType::Point, ETileType::Point},
		{ETileType::Point, ETileType::Wall, ETileType::Wall, ETileType::Wall, ETileType::Point},
		{ETileType::Point, ETileType::Wall, ETileType::Empty, ETileType::Wall, ETileType::Point},
		{ETileType::Point, ETileType::Wall, ETileType::Point, ETileType::Wall, ETileType::Point},
		{ETileType::Point, ETileType::Point, ETileType::Point, ETileType::Point, ETileType::Point},
	};
	for (int Y = 0; Y < PatternPacManHeight; Y++)
		for (int X = 0; X < PatternPacManWidth; X++)
			MazeGrid[GridSize.Y / 2 - PatternPacManHeight / 2 + Y][GridSize.X / 2 - PatternPacManWidth / 2 + X] = PatternPacMan[Y][X];

	if (!Large)
	{
		constexpr int PatternHeight = 2;
		constexpr int PatternWidth = 5;
		constexpr ETileType Pattern[PatternHeight][PatternWidth]{
			{ETileType::Wall, ETileType::Empty, ETileType::Empty, ETileType::Empty, ETileType::Wall},
			{ETileType::Wall, ETileType::Wall, ETileType::Empty, ETileType::Wall, ETileType::Wall},
		};
		for (int Y = 0; Y < PatternHeight; Y++)
			for (int X = 0; X < PatternWidth; X++)
				MazeGrid[GridSize.Y - 2 - Y][GridSize.X / 2 - PatternWidth / 2 + X] = Pattern[Y][X];
	} else
	{
		constexpr int PatternHeight = 3;
		constexpr int PatternWidth = 7;
		constexpr ETileType Pattern[PatternHeight][PatternWidth]{
			{ETileType::Point, ETileType::Wall, ETileType::Empty, ETileType::Empty, ETileType::Empty, ETileType::Wall, ETileType::Point},
			{ETileType::Point, ETileType::Wall, ETileType::Wall, ETileType::Empty, ETileType::Wall, ETileType::Wall, ETileType::Point},
			{ETileType::Point, ETileType::Point, ETileType::Point, ETileType::Point, ETileType::Point, ETileType::Point, ETileType::Point},
		};
		for (int Y = 0; Y < PatternHeight; Y++)
			for (int X = 0; X < PatternWidth; X++)
				MazeGrid[GridSize.Y - 2 - Y][GridSize.X / 2 - PatternWidth / 2 + X] = Pattern[Y][X];
	}
}

void AMazeManager::GenerateMazeDfs()
{
    constexpr  int StartX = 1;
    constexpr  int StartY = 1;
    MazeGrid[StartY][StartX] = ETileType::Point;

    TArray<FIntPoint> Stack;
    Stack.Push(FIntPoint(StartX, StartY));

    const TArray<FIntPoint> Directions = { {2,0}, {-2,0}, {0,2}, {0,-2} };

    while(Stack.Num() > 0)
    {
        FIntPoint Current = Stack.Pop();

        TArray<FIntPoint> ShuffledDirs = Directions;
        for(int i=ShuffledDirs.Num()-1; i>0; i--)
            ShuffledDirs.Swap(i,FMath::RandRange(0, i));

        for(FIntPoint Dir : ShuffledDirs)
        {
            FIntPoint Next = Current + Dir;

            if(Next.X <= 0 || Next.X >= GridSize.X-1 || Next.Y <= 0 || Next.Y >= GridSize.Y-1) continue;

            if(MazeGrid[Next.Y][Next.X] == ETileType::Wall)
            {
                const FIntPoint Between = Current + FIntPoint(Dir.X/2, Dir.Y/2);
                MazeGrid[Between.Y][Between.X] = ETileType::Point;
                MazeGrid[Next.Y][Next.X] = ETileType::Point;

                Stack.Push(Next);
            }
        }
    }
}

void AMazeManager::BreakMazeWalls()
{
    int TotalWalls = 0;
    for(int Y = 1; Y < GridSize.Y - 1; Y++)
        for(int X = 1; X < GridSize.X - 1; X++)
            if(MazeGrid[Y][X] == ETileType::Wall)
                TotalWalls++;

    const int NumRandomBreaks = FMath::RoundToInt(TotalWalls * (DestructionRate / 100.f));

    for(int i = 0; i < NumRandomBreaks; i++)
    {
        const int X = FMath::RandRange(1, GridSize.X - 2);
        const int Y = FMath::RandRange(1, GridSize.Y - 2);

        if(CanBreakWall(X,Y)) MazeGrid[Y][X] = ETileType::Point;
    }
}

bool AMazeManager::CanBreakWall(const int X, const int Y)
{
	if(MazeGrid[Y][X] != ETileType::Wall) return false;

	const TArray<FIntPoint> Neighbors = { {0,1}, {0,-1}, {1,0}, {-1,0} };
	bool N = false, S = false, E = false, W = false;

	for(const FIntPoint Off : Neighbors)
	{
		const int Nx = X + Off.X;
		const int Ny = Y + Off.Y;
		if(Nx <= 0 || Nx >= GridSize.X - 1 || Ny <= 0 || Ny >= GridSize.Y - 1) continue;

		if(MazeGrid[Ny][Nx] != ETileType::Wall)
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
	if(!GetWorld()) return;

	BaseX = 0 - (GridSize.X * CellSize * CellSpriteSize) / 2;
	BaseY = 0 - (GridSize.Y * CellSize * CellSpriteSize) / 2;

	for(int Y = 0; Y < MazeGrid.Num(); Y++)
		for(int X = 0; X < MazeGrid[Y].Num(); X++)
			SpawnTile(X, Y);
}

void AMazeManager::SpawnTile(const int X, const int Y)
{
	if(MazeGrid[Y][X] == ETileType::Empty) return;

	const FVector Location = FVector(
		BaseX + X * CellSize * CellSpriteSize,
		BaseY + Y * CellSize * CellSpriteSize,
		0.f
	);

	switch (MazeGrid[Y][X])
	{
		case ETileType::Wall:
			if(AMazeTile* Tile = GetWorld()->SpawnActor<AMazeTile>(WallTileClass, Location, FRotator::ZeroRotator))
			{
				Tile->SetActorScale3D(FVector(CellSize, CellSize, CellSize));
				SetTileNeighbor(X, Y, Tile);
			}
			break;
		case ETileType::Point:
			if(AMazeTilePoint* Tile = GetWorld()->SpawnActor<AMazeTilePoint>(PointTileClass, Location, FRotator::ZeroRotator))
			{
				auto Tmp = Tile->GetActorLocation();
				Tile->SetActorScale3D(FVector(CellSize, CellSize, CellSize));
			}
			break;
		default:
			break;
	}
}

void AMazeManager::SetTileNeighbor(const int X, const int Y, AMazeTile* Tile)
{
	const bool N = Y < GridSize.Y - 1 && MazeGrid[Y + 1][X] == ETileType::Wall;
	const bool S = Y > 0 && MazeGrid[Y - 1][X] == ETileType::Wall;
	const bool E = X < GridSize.X - 1 && MazeGrid[Y][X + 1] == ETileType::Wall;
	const bool O = X > 0 && MazeGrid[Y][X - 1] == ETileType::Wall;

	Tile->SetNeighbor(N, S, E, O);
}
