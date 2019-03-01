// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Engine.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"



#include "hexTile.generated.h"

UCLASS()
class TILEMAPMAKER_API AhexTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AhexTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "hexTile", meta = (AllowPrivateAccess = "true"))
		USceneComponent* hexTileRootComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "hexTile", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* hexTileMeshComponent;

	//可以暴露的公共数据

	//格子海拔
	float height;
	//格子位置
	int32 x, y;
	//格子类型
	int32 type;
	//格子索引
	int32 index;
	//格子是否放置
	bool isPlace;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnclickedAction(AActor* TouchedActor, FKey ButtonPressed);
	
};
