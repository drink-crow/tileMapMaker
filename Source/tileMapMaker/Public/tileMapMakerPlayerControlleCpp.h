// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UMG.h"

#include "HUDUserWidget.h"
#include "hexTile.h"

#include "tileMapMakerPlayerControlleCpp.generated.h"

/**
 * 
 */

//格子类型数据
class hexTileType
{
public:	
	UMaterial* SurfaceMat;
	UMaterial* SideMat;
	int32 index;
	FString SurMatName;
	FString SideMatName;
	FString name;
};

//

//六边形格子的顶点信息
struct initMeshData
{
	//基础高度
	float height;
	//每一个格子都是紧密相连的
	//六边形的六个点的坐标，左上，右上，左中，右中，左下，右下
	FVector2D leftTop;
	FVector2D rightTop;
	FVector2D leftMid;
	FVector2D rightMid;
	FVector2D leftBottom;
	FVector2D rightBottom;
	initMeshData & operator+=(const FVector2D & rhs);
	initMeshData & operator+=(const initMeshData & rhs);
};

UCLASS()
class TILEMAPMAKER_API AtileMapMakerPlayerControlleCpp : public APlayerController
{
	GENERATED_BODY()
	
public:

	AtileMapMakerPlayerControlleCpp();

	//用到的UI空间
	//HUD主界面
	UPROPERTY(BlueprintReadOnly, Category = "UIwidget")
		UHUDUserWidget* HUDInstance;
	TSubclassOf<class UUserWidget> HUDclass;

	//供蓝图调用的函数创建新的地图内容
	UFUNCTION(BlueprintCallable)
	void FcreateNewHexTileMap(FString name, int32 Xnum, int32 Ynum);

	//储存格子数据的容器
	TArray<AhexTile *> tileData;
	
	virtual void BeginPlay() override;

	//供外部调用的修改被选中的格子
	void setSelectedTileIndex(int32 index);

	//更新DetailMenu中的数据
	void updataDetailMenu();

	//供蓝图调用的修改内存中格子数据参数
	UFUNCTION(BlueprintCallable)
	void setTileData(float height, int32 type);

	//编写模型数据
	UFUNCTION(BlueprintCallable)
	void generateMeshData();

	UFUNCTION(BlueprintCallable)
	TArray<FString> getTypeName();

	//保存工程文件
	UFUNCTION(BlueprintCallable)
	void saveProject();

	//读取工程文件
	UFUNCTION(BlueprintCallable)
	void loadProject(FString path, FString filename);

private:

	//私有的创建新的地图内容的函数
	void newMap(FString name, int32 Xnum, int32 Ynum);

	//设置格子数据的函数,主要是初始化用的
	void initTileData(AhexTile * inActor, int32 x, int32 y, int32 index);

	//tpye名称，供蓝图读取
	TArray<FString> typeName;

	//被选中的格子的数据索引
	int32 selectedTileIndex;

	//生成网格用的数据
	initMeshData hexMeshData;

	//格子数量
	int32 xNum, yNum;

	//工程名称
	FString worldName;
	//类型
	TArray<hexTileType *> typeDetail;
};


