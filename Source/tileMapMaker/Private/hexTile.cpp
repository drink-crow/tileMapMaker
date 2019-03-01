// Fill out your copyright notice in the Description page of Project Settings.

#include "hexTile.h"
#include "tileMapMakerPlayerControlleCpp.h"

// Sets default values
AhexTile::AhexTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//开启自定义渲染深度后处理


	//创建并赋值到根组件
	hexTileRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("hexTileComponentRoot"));
	RootComponent = hexTileRootComponent;

	//创建，加载资源，附加到hexTileRootComponent下
	hexTileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("hexTileComponent"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> hexMeshAsset(TEXT("/Game/hexTile/hexTile"));
	hexTileMeshComponent->SetStaticMesh(hexMeshAsset.Object);
	hexTileMeshComponent->SetupAttachment(hexTileRootComponent);

	//开启自定义渲染深度后处理
	//hexTileMeshComponent->bRenderCustomDepth = true;
	//hexTileMeshComponent->CustomDepthStencilValue = 254;

	OnClicked.AddDynamic(this, &AhexTile::OnclickedAction);

	//对应的坐标位置
	x = 0 ; y = 0;
	//单元格子海拔高度,单位cm
	height=100;
	//格子类型
	type=0;
	//格子索引
	index=0;
	//该位置是否放置了可用的格子
	isPlace=true;

}

// Called when the game starts or when spawned
void AhexTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AhexTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AhexTile::OnclickedAction(AActor* TouchedActor, FKey ButtonPressed)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%d,%d"), x, y));

	AtileMapMakerPlayerControlleCpp* Pc = Cast<AtileMapMakerPlayerControlleCpp>(GetWorld()->GetFirstPlayerController());
	Pc->setSelectedTileIndex(index);
	Pc->updataDetailMenu();
}

