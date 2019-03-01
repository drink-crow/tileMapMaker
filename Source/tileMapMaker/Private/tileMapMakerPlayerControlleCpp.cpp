// Fill out your copyright notice in the Description page of Project Settings.

#include "tileMapMakerPlayerControlleCpp.h"
#include "vertexData.h"
#include <iostream>
#include <sstream>
#include <iomanip>

//initMeshData结构体的操作符重载
initMeshData& initMeshData::operator+=(const FVector2D &rhs)
{
	leftTop += rhs;
	rightTop += rhs;
	leftMid += rhs;
	rightMid += rhs;
	leftBottom += rhs;
	rightBottom += rhs;
	return *this;
}
initMeshData& initMeshData::operator+=(const initMeshData &rhs)
{
	leftTop += rhs.leftTop;
	rightTop += rhs.rightTop;
	leftMid += rhs.leftMid;
	rightMid += rhs.rightMid;
	leftBottom += rhs.leftBottom;
	rightBottom += rhs.rightBottom;
	return *this;
}
initMeshData operator+ (const initMeshData &lhs, const initMeshData &rhs)
{
	initMeshData res = lhs;
	res += rhs;
	return res;
}
initMeshData operator+(const initMeshData &lhs, const FVector2D &rhs)
{
	initMeshData res = lhs;
	res += rhs;
	return res;
}
bool operator==(const initMeshData &lhs, const initMeshData &rhs)
{
	return lhs.leftTop == rhs.leftTop &&
		lhs.rightTop == rhs.rightTop &&
		lhs.leftMid == rhs.leftMid &&
		lhs.rightMid == rhs.rightMid &&
		lhs.leftBottom == rhs.leftBottom &&
		lhs.rightBottom == rhs.rightBottom;
}


AtileMapMakerPlayerControlleCpp::AtileMapMakerPlayerControlleCpp()
{
	//初始化typeDetail里面的内容，默认有6种类型
	for (int i=0; i < 6; i++)	typeDetail.Push(new hexTileType);

	//草地
	typeDetail[0]->index = 0;
	typeDetail[0]->name = TEXT("0.Grass");
	typeDetail[0]->SurMatName = "Surface_Grass_Mat";
	typeDetail[0]->SideMatName = "Side_Grass_Mat";
	static ConstructorHelpers::FObjectFinder<UMaterial> faceGrass(TEXT("/Game/material/Surface_Grass_Mat"));
	if(faceGrass.Object)
	{
		typeDetail[0]->SurfaceMat = faceGrass.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> sideGrass(TEXT("/Game/material/Side_Grass_Mat"));
	typeDetail[0]->SideMat = sideGrass.Object;
	if (sideGrass.Object)
	{
		typeDetail[0]->SideMat = sideGrass.Object;
	}
	//森林
	typeDetail[1]->index = 1;
	typeDetail[1]->name = "1.Forest";
	typeDetail[1]->SurMatName = "Surface_Forest_Mat";
	typeDetail[1]->SideMatName = "Side_Forest_Mat";
	static ConstructorHelpers::FObjectFinder<UMaterial> faceForest(TEXT("/Game/material/Surface_Forest_Mat"));
	if (faceForest.Object)
	{
		typeDetail[1]->SurfaceMat = faceForest.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> sideForest(TEXT("/Game/material/Side_Forest_Mat"));
	if (sideForest.Object)
	{
		typeDetail[1]->SideMat = sideForest.Object;
	}

	//水面
	typeDetail[2]->index = 2;
	typeDetail[2]->name = "2.Water";
	typeDetail[2]->SurMatName = "Surface_Water_Mat";
	typeDetail[2]->SideMatName = "Side_Water_Mat";
	static ConstructorHelpers::FObjectFinder<UMaterial> faceWater(TEXT("/Game/material/Surface_Water_Mat"));
	if (faceWater.Object)
	{
		typeDetail[2]->SurfaceMat = faceWater.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> sideWater(TEXT("/Game/material/Side_Water_Mat"));
	if (sideWater.Object)
	{
		typeDetail[2]->SideMat = sideWater.Object;
	}

	//山
	typeDetail[3]->index = 3;
	typeDetail[3]->name = "3.Mountain";
	typeDetail[3]->SurMatName = "Surface_Mountain_Mat";
	typeDetail[3]->SideMatName = "Side_Mountain_Mat";
	static ConstructorHelpers::FObjectFinder<UMaterial> faceMountain(TEXT("/Game/material/Surface_Mountain_Mat"));
	if (faceMountain.Object)
	{
		typeDetail[3]->SurfaceMat = faceMountain.Object;

	}
	static ConstructorHelpers::FObjectFinder<UMaterial> sideMountain(TEXT("/Game/material/Side_Mountain_Mat"));
	if (sideMountain.Object)
	{
		typeDetail[3]->SideMat = sideMountain.Object;
	}
	//沼泽
	typeDetail[4]->index = 4;
	typeDetail[4]->name = "4.Swamp";
	typeDetail[4]->SurMatName = "Surface_Swamp_Mat";
	typeDetail[4]->SideMatName = "Side_Swamp_Mat";
	static ConstructorHelpers::FObjectFinder<UMaterial> faceSwamp(TEXT("/Game/material/Surface_Swamp_Mat"));
	if (faceSwamp.Object)
	{
		typeDetail[4]->SurfaceMat = faceSwamp.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> sideSwamp(TEXT("/Game/material/Side_Swamp_Mat"));
	if (sideSwamp.Object)
	{
		typeDetail[4]->SideMat = sideSwamp.Object;
	}

	//沙漠
	typeDetail[5]->index = 5;
	typeDetail[5]->name = "5.Desert";
	typeDetail[5]->SurMatName = "Surface_Desert_Mat";
	typeDetail[5]->SideMatName = "Side_Desert_Mat";
	static ConstructorHelpers::FObjectFinder<UMaterial> faceDesert(TEXT("/Game/material/Surface_Desert_Mat"));
	if (faceDesert.Object)
	{
		typeDetail[5]->SurfaceMat = faceDesert.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> sideDesert(TEXT("/Game/material/Side_Desert_Mat"));
	if (sideDesert.Object)
	{
		typeDetail[5]->SideMat = sideDesert.Object;
	}

	
	typeName.AddDefaulted(6);
	typeName[0] = ("0.Grass");
	typeName[1] = ("1.Forest");
	typeName[2] = ("2.Water");
	typeName[3] = ("3.Mountain");
	typeName[4] = ("4.Swamp");
	typeName[5] = ("5.Desert");
	//显示鼠标
	bShowMouseCursor = true;

	//初始化成员
	selectedTileIndex = -1;


	hexMeshData.height = 100;
	hexMeshData.leftTop = FVector2D(86.6, -50);
	hexMeshData.rightTop = FVector2D(86.6, 50);
	hexMeshData.leftMid = FVector2D(0, -100);
	hexMeshData.rightMid = FVector2D(0, 100);
	hexMeshData.leftBottom = FVector2D(-86.6, -50);
	hexMeshData.rightBottom = FVector2D(-86.6, 50);

	xNum = 0;
	yNum = 0;


	//读取HUD类
	static ConstructorHelpers::FClassFinder<UUserWidget> HUDBP(TEXT("/Game/UI/HUD"));
	if (HUDBP.Succeeded())
	{
		HUDclass = HUDBP.Class;
	}

}

//供蓝图调用的函数创建新的地图内容
void AtileMapMakerPlayerControlleCpp::FcreateNewHexTileMap(FString name, int32 Xnum, int32 Ynum)
{
	//调用内部函数
	newMap(name, Xnum, Ynum);
}

void AtileMapMakerPlayerControlleCpp::BeginPlay()
{
	
	//创建HUD实例并添加到视口里
	HUDInstance = CreateWidget<UHUDUserWidget>(GetWorld(), HUDclass);
	if (HUDInstance != nullptr)
	{
		HUDInstance->AddToViewport();
	}

}

void AtileMapMakerPlayerControlleCpp::setSelectedTileIndex(int32 index)
{
	if (index > -1)
	{
		//首先关闭之前被选中的格子的后处理效果
		if (selectedTileIndex > -1)
		{
			tileData[selectedTileIndex]->hexTileMeshComponent->SetRenderCustomDepth(false);
		}
		//开启新的被选中的棋子的后处理效果
		selectedTileIndex = index;
		tileData[selectedTileIndex]->hexTileMeshComponent->SetRenderCustomDepth(true);
			;
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("clicked"));
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("clicked"));

	}
}

void AtileMapMakerPlayerControlleCpp::saveProject()
{
	//获取单前时间，对于不考虑联机的应用采用Now()函数，该函数考虑当地时区，UtcNow()则不考虑，适合联机应用同一时间判断
	FString nowTime = FDateTime::Now().ToString();

	//obj文件的头部
	FString head = TEXT("# Tile Map Maker Project Exporter\n");
	//附加上创建时间
	head.Append(TEXT("#Create from "));
	head.Append(nowTime);	head.Append(TEXT("\n\n"));

	FString typeString="# Type\n";
	for (auto& type : typeDetail)
	{
		typeString.Append("t " + type->name + " \n");
	}
	typeString.Append(FString::Printf(TEXT("# %d type\n\n"), typeDetail.Num()));

	FString worldString = "# world setting\n";
	worldString.Append(FString::Printf(TEXT("w %d %d\n\n"), xNum, yNum));

	FString tileString = "# hexTiles\n";
	for (auto& hexTile : tileData)
	{
		using namespace std;
		stringstream ss; string res;
		FString height;
		ss << fixed << setprecision(4) << hexTile->height; ss >> res; height = res.c_str(); ss.clear();
		tileString.Append(FString::Printf(TEXT("h %d "), hexTile->type));
		tileString.Append(height+" \n");
	}
	tileString.Append(FString::Printf(TEXT("# %d hexTiles\n\n"), tileData.Num()));


	//
	//开始输出文件
	//
	FString saveDir = FPaths::ProjectSavedDir();
	saveDir.Append("Output");
	FString fileName = worldName + ".tmm";

	FString absoluteFilePath = saveDir + "/" + fileName;
	FString textToSave = head + typeString + worldString + tileString;

	FFileHelper::SaveStringToFile(textToSave, *absoluteFilePath);
}

void AtileMapMakerPlayerControlleCpp::loadProject(FString path, FString filename)
{
	//读取文件到String中
	FString fileString;

	FText FailureMessage;
	FailureMessage = FText::AsCultureInvariant(TEXT("file read failed!"));

	if (!FFileHelper::LoadFileToString(fileString, *(path+ filename)))
	{
		//如果文件读取失败
		FMessageDialog::Open(EAppMsgType::Ok, FailureMessage);
		return;
	}

	//分析语句
	FailureMessage = FText::AsCultureInvariant(TEXT("data wrong!"));
	using namespace std;
		
	stringstream text;
	text << TCHAR_TO_UTF8(*fileString);
	string sentence;
	string item;
		
	//名字
	FString readWorldName = filename;
	readWorldName.RemoveFromEnd(".tmm");
	//工程设定
	int32 readXnum, readYnum;
	//读入的格子
	TArray<int32> typeArray;
	TArray<float> heightArray;
	//按行读入
	while (getline(text,sentence))
	{
		//跳过空句子
		if (sentence.empty()) continue;

		//读入数据
		switch (sentence[0])
		{
		case 't':
			//Type先跳过
			break;

		case 'w':
			if (sscanf_s(sentence.data(), "w %d %d", &readXnum, &readYnum) != 2)
			{
				//错误
				FMessageDialog::Open(EAppMsgType::Ok, FailureMessage);
				return;
			}
				
			break;

		case 'h':
			int32 type; float height;
			if (sscanf_s(sentence.data(), "h %d %f", &type, &height) != 2)
			{
				//错误
				FMessageDialog::Open(EAppMsgType::Ok, FailureMessage);
				return;
				break;
			}
			typeArray.Add(type); heightArray.Add(height);
			break;

		case '#':
			continue;
			break;

		default:
			continue;
			break;
		}
	}
	
	//生成新的世界
	UWorld* const World = GetWorld(); // get a reference to the world 
	check(World);
	//清除所有内容
	//销毁hexTileActor
	for (int32 i = 0; i < tileData.Num(); i++)
	{
		World->DestroyActor(tileData[i]);
	}
	//tileData重置大小
	tileData.Reset(readXnum*readYnum);

	worldName = readWorldName;
	xNum = readXnum;
	yNum = readYnum;

	//生成新的地图
	//生成hexTileActor

	bool Parity;//在哪一列的奇偶标识符，true为奇，false为偶,每一行从位置0开始，视为偶

	//同X坐标，Y轴上的偏移
	float Yoffset = (hexMeshData.rightTop.Y - hexMeshData.leftTop.Y)*1.5;
	//同X坐标，相邻两个格子X坐标上的偏移
	float adjXoffset = -(hexMeshData.leftTop.X - hexMeshData.leftBottom.X) / 2;
	//同Y坐标，X轴上的偏移
	float Xoffset = hexMeshData.leftTop.X - hexMeshData.leftBottom.X;

	//归位摄像机
	//摄像机设置在pawn类里面
	GetPawn()->SetActorLocationAndRotation(FVector((Xoffset / 2 * (readXnum - 1)), Yoffset / 2 * (readYnum - 1), 1000.f), FRotator(0.f, 0.f, 0.f));

	for (int32 x = 0; x < readXnum; x++)
	{
		//每行从false开始
		Parity = false;
		for (int32 y = 0; y < readYnum; y++)
		{
			selectedTileIndex = readXnum * x + y;
			tileData.Push(World->SpawnActor<AhexTile>(FVector(Xoffset*x + adjXoffset * Parity, Yoffset*y, 0.f), FRotator(0.f, 0.f, 0.f)));
			initTileData(tileData[readXnum*x + y], x, y, readXnum*x + y);
			setTileData(heightArray[readXnum*x + y], typeArray[readXnum*x + y]);
			Parity = !Parity;//奇偶翻转
		}

	}
	selectedTileIndex = -1;
	//允许鼠标点击事件
	bEnableClickEvents = true;

	//更新DetailMenu中worldsetting中的设定
	HUDInstance->updataDetailWorldSetting(worldName, xNum, yNum);
}

void AtileMapMakerPlayerControlleCpp::newMap(FString name, int32 Xnum, int32 Ynum)
{
	UWorld* const World = GetWorld(); // get a reference to the world 
	check(World);
	//清除所有内容
	//销毁hexTileActor
	for (int32 i=0;i<tileData.Num();i++)
	{
		World->DestroyActor(tileData[i]);
	}
	//重置所选的格子的索引，避免新地图比旧地图小导致索引越界
	selectedTileIndex = -1;
	//tileData重置大小
	tileData.Reset(Xnum*Ynum);

	worldName = name;
	xNum = Xnum;
	yNum = Ynum;

	//生成新的地图
	//生成hexTileActor

	bool Parity;//在哪一列的奇偶标识符，true为奇，false为偶,每一行从位置0开始，视为偶

	//同X坐标，Y轴上的偏移
	float Yoffset = (hexMeshData.rightTop.Y - hexMeshData.leftTop.Y)*1.5;
	//同X坐标，相邻两个格子X坐标上的偏移
	float adjXoffset = -(hexMeshData.leftTop.X - hexMeshData.leftBottom.X) / 2;
	//同Y坐标，X轴上的偏移
	float Xoffset = hexMeshData.leftTop.X - hexMeshData.leftBottom.X;

	//归位摄像机
	//摄像机设置在pawn类里面
	GetPawn()->SetActorLocationAndRotation(FVector((Xoffset / 2 * (Xnum - 1)), Yoffset / 2 * (Ynum - 1), 1000.f), FRotator(0.f, 0.f, 0.f));

	for (int32 x = 0; x < Xnum; x++)
	{
		//每行从false开始
		Parity = false;
		for (int32 y = 0; y < Ynum; y++)
		{
			//tileData.Push(World->SpawnActor<AhexTile>(FVector((15 * w), 8.66 * 2 * h + (-8.66*Parity), 0.f), FRotator(0.f, 0.f, 0.f)));
			tileData.Push(World->SpawnActor<AhexTile>(FVector(Xoffset*x + adjXoffset * Parity, Yoffset*y, 0.f), FRotator(0.f, 0.f, 0.f)));
			initTileData(tileData[Xnum*x + y], x, y, Xnum*x + y);
			Parity = !Parity;//奇偶翻转
		}

	}
	//允许鼠标点击事件
	bEnableClickEvents = true;

	//更新DetailMenu中worldsetting中的设定
	HUDInstance->updataDetailWorldSetting(worldName, xNum, yNum);
}

void AtileMapMakerPlayerControlleCpp::initTileData(AhexTile * inActor, int32 x, int32 y, int32 index)
{
	//对输入的Actor的各个数值赋值
	inActor->x = x;
	inActor->y = y;
	inActor->index = index;
}

void AtileMapMakerPlayerControlleCpp::generateMeshData()
{	
	//获取单前时间，对于不考虑联机的应用采用Now()函数，该函数考虑当地时区，UtcNow()则不考虑，适合联机应用同一时间判断
	FString nowTime = FDateTime::Now().ToString();

	//obj文件的头部
	FString head = TEXT("# Tile Map Maker OBJ Exporter\n");
	//附加上创建时间
	head.Append(TEXT("#Create from "));
	head.Append(nowTime);	head.Append(TEXT("\n"));
	head.Append(TEXT("\n"));
	//没有用的材质库
	head.Append(TEXT("mtllib NoUse.mtl\n\n"));

	head.Append(TEXT("#\n# object HexMap\n#\n\n"));



	//顶点坐标容器
	vertexData v;
	//法线坐标容器
	//vertexData vn;
	//UV坐标容器
	vertexData vt;

	//用来输出到OBJ文件的字符串
	FString vString = TEXT("\n");
	FString vnString;
	FString vtString;
	TArray<FString> faceString;

	//生成法线，共用下，法线数量非常有限,也就7个法线
	//表面上六边形所有的点的法线，
	//vn.data.Push(FVector( 0.000f,  0.0f, 1.f)); 

	//以下按顺时针排序
	//vn.data.Push(FVector( 1.0f,  0.000f, 0.f)); //上侧面所有的点的法线
	//vn.data.Push(FVector( 0.5f,  0.866f, 0.f)); //右上侧面所有的点的法线
	//vn.data.Push(FVector(-0.5f,  0.866f, 0.f)); //右下侧面所有的点的法线
	//vn.data.Push(FVector(-1.0f,  0.000f, 0.f)); //下侧面所有的点的法线
	//vn.data.Push(FVector(-0.5f, -0.866f, 0.f)); //左下侧面所有的点的法线
	//vn.data.Push(FVector( 0.5f, -0.866f, 0.f)); //左上侧面所有的点的法线

	vnString =     (TEXT("vn 0.0000 0.0000 1.0000\n"));
	vnString.Append(TEXT("vn 1.0000 0.0000 0.0000\n"));
	vnString.Append(TEXT("vn 0.5000 0.8660 0.0000\n"));
	vnString.Append(TEXT("vn -0.5000 0.8660 0.0000\n"));
	vnString.Append(TEXT("vn -1.0000 0.0000 0.0000\n"));
	vnString.Append(TEXT("vn -0.5000 -0.8660 0.0000\n"));
	vnString.Append(TEXT("vn 0.5000 -0.8660 0.0000\n"));
	vnString.Append(TEXT("# 7 vertex normals\n\n"));

	//暂且不考虑太多UV坐标的事，（UE4是左手坐标系，所以要用左手法则）
	//表面的UV坐标，6个坐标，从左下角开始，顺时针
	vtString =      TEXT("vt 0.2500 0.0000 0.0000\n");
	vtString.Append(TEXT("vt 0.0000 0.4330 0.0000\n"));
	vtString.Append(TEXT("vt 0.2500 0.8660 0.0000\n"));
	vtString.Append(TEXT("vt 0.7500 0.8660 0.0000\n"));
	vtString.Append(TEXT("vt 1.0000 0.4330 0.0000\n"));
	vtString.Append(TEXT("vt 0.7500 0.0000 0.0000\n"));
	//侧面的UV坐标,4个坐标，从左下角开始，顺时针
	vtString.Append(TEXT("vt 0.0000 0.0000 0.0000\n"));
	vtString.Append(TEXT("vt 1.0000 0.0000 0.0000\n"));
	vtString.Append(TEXT("vt 1.0000 1.0000 0.0000\n"));
	vtString.Append(TEXT("vt 0.0000 1.0000 0.0000\n"));

	vtString.Append(TEXT("# 10 texture coords\n\n"));

	//生成Surface
	//顶面共有4个三角形组成

	//Parity见newMap()里的解释
	bool Parity;
	//同X坐标，Y轴上的偏移
	float Yoffset = (hexMeshData.rightTop.Y - hexMeshData.leftTop.Y)*1.5;
	//同X坐标，相邻两个格子X坐标上的偏移
	float adjXoffset = -(hexMeshData.leftTop.X - hexMeshData.leftBottom.X) / 2;
	//同Y坐标，X轴上的偏移
	float Xoffset = hexMeshData.leftTop.X - hexMeshData.leftBottom.X;

	//每个格子的X，Y平面中心点
	FVector2D Center;
	//每个格子的顶点坐标
	initMeshData hex;
	//当前生成的格子的在tileData中的索引
	int32 index = 0;
	//当前格子的海拔
	float height;
	//当前格子的类型
	int32 type;
	//顶点坐标的索引,LT=leftTop,RT=rightTop, 以此类推
	int32 vIndex = -1; int32 LTindex, RTindex, LMindex, RMindex, LBindex, RBindex;

	for (auto& t : typeDetail)
	{
		faceString.AddDefaulted(2);
		//表面
		faceString[t->index * 2] = "g " + t->SurMatName;
		faceString[t->index * 2].RemoveFromEnd("_Mat");
		faceString[t->index * 2].Append("\nusemtl " + t->SurMatName + "\ns off\n");
		//侧面
		faceString[t->index * 2 + 1] = "g " + t->SideMatName;
		faceString[t->index * 2 + 1].RemoveFromEnd("_Mat");
		faceString[t->index * 2 + 1].Append("\nusemtl " + t->SideMatName + "\ns off\n");
	}

	
	//faceString =      TEXT("g Surface\n");
	//faceString.Append(TEXT("usemtl Surface\n"));
	//faceString.Append(TEXT("s off\n"));

	//生成表面
	for (int32 x = 0; x < xNum; x++)
	{
		//每行从false开始
		Parity = false;
		for (int32 y = 0; y < yNum; y++)
		{
			//当前处理的格子的索引
			index = xNum * x + y;
			//当前格子的海拔
			height = tileData[index]->height;
			//当前格子的类型
			type = tileData[index]->type;
			//计算中心点，同newMap()里的
			Center = FVector2D(Xoffset*x + adjXoffset * Parity, Yoffset*y);
			//奇偶翻转	
			Parity = !Parity;
			//每个格子Surface的坐标
			hex = hexMeshData + Center;
			//搜索顶点坐标容器里有没有这个顶点以便顶点复用,顺时针顺序
			LBindex = v.findOrPush(FVector(hex.leftBottom, height));
			LMindex = v.findOrPush(FVector(hex.leftMid, height));
			LTindex = v.findOrPush(FVector(hex.leftTop, height));
			RTindex = v.findOrPush(FVector(hex.rightTop, height));
			RMindex = v.findOrPush(FVector(hex.rightMid, height));
			RBindex = v.findOrPush(FVector(hex.rightBottom, height));

			//从左下角起，逆时针
			int32 &vexter1=LBindex, &vexter2= LMindex, &vexter3= LTindex, &vexter4= RTindex, &vexter5= RMindex, &vexter6= RBindex;

			//4个三角形，（UE4是左手坐标系，所以要用左手法则）
			faceString[type * 2].Append(FString::Printf(TEXT("f %d/1/1 %d/2/1 %d/3/1 \n"), vexter1, vexter2, vexter3));
			faceString[type * 2].Append(FString::Printf(TEXT("f %d/3/1 %d/4/1 %d/5/1 \n"), vexter3, vexter4, vexter5));
			faceString[type * 2].Append(FString::Printf(TEXT("f %d/5/1 %d/6/1 %d/1/1 \n"), vexter5, vexter6, vexter1));
			faceString[type * 2].Append(FString::Printf(TEXT("f %d/1/1 %d/3/1 %d/5/1 \n"), vexter1, vexter3, vexter5));
		}
	}

	//生成侧面

	//每一个侧面的索引坐标，正视于次侧面，从左下角开始，逆时针（右手法则）
	//zx=zuo xia,左下，yx, ys, zs依此类推
	int32 zx, yx, ys, zs;
	//相邻格子的高度
	float adjacentHeight;
	for (int32 x = 0; x < xNum; x++)
	{
		//每行从false开始
		Parity = false;
		for (int32 y = 0; y < yNum; y++)
		{
			//当前处理的格子的索引
			index = xNum * x + y;
			//当前格子的海拔
			height = tileData[index]->height;
			//当前格子的类型
			type = tileData[index]->type;
			//计算中心点，同newMap()里的
			Center = FVector2D(Xoffset*x + adjXoffset * Parity, Yoffset*y);
			
			//每个格子Surface的坐标
			hex = hexMeshData + Center;

			//从上侧面开始
			if (x < (xNum - 1))//跳过在上边界的格子的上侧面
			{
				adjacentHeight = tileData[yNum * (x + 1) + y]->height;
				if (height>adjacentHeight)//只有比相邻的格子的海拔高时才生成侧面
				{
					//搜索顶点坐标容器里有没有这个顶点以便顶点复用(应该是都有，不用添加的）
					zx = v.findOrPush(FVector(hex.rightTop, adjacentHeight));
					zs = v.findOrPush(FVector(hex.rightTop, height));
					ys = v.findOrPush(FVector(hex.leftTop, height));
					yx = v.findOrPush(FVector(hex.leftTop, adjacentHeight));

					//2个三角形，注意右手法则
					faceString[type * 2 + 1].Append(FString::Printf(TEXT("f %d/7/2 %d/8/2 %d/9/2 \n"), zx, zs, ys));
					faceString[type * 2 + 1].Append(FString::Printf(TEXT("f %d/9/2 %d/10/2 %d/7/2 \n"), ys, yx, zx));
				}
			}
			//右上侧面
			if (y < (yNum - 1) && (x < (xNum - 1) || Parity))//跳过在右边边界的格子的上侧面和上边界中奇数列的格子的右侧面
			{
				adjacentHeight = Parity ? tileData[index + 1]->height : tileData[yNum * (x + 1) + y + 1]->height;
				if (height > adjacentHeight)//只有比相邻的格子的海拔高时才生成侧面
				{
					//搜索顶点坐标容器里有没有这个顶点以便顶点复用
					zx = v.findOrPush(FVector(hex.rightMid, adjacentHeight));
					zs = v.findOrPush(FVector(hex.rightMid, height));
					ys = v.findOrPush(FVector(hex.rightTop, height));
					yx = v.findOrPush(FVector(hex.rightTop, adjacentHeight));

					//2个三角形，注意右手法则
					faceString[type * 2 + 1].Append(FString::Printf(TEXT("f %d/7/3 %d/8/3 %d/9/3 \n"), zx, zs, ys));
					faceString[type * 2 + 1].Append(FString::Printf(TEXT("f %d/9/3 %d/10/3 %d/7/3 \n"), ys, yx, zx));
				}
			}
			//右下侧面
			if (y < (yNum - 1) && (x > 0 || !Parity))
			{
				adjacentHeight = Parity ? (tileData[yNum * (x - 1) + y + 1]->height) : (tileData[index + 1]->height);
				if (height > adjacentHeight)//只有比相邻的格子的海拔高时才生成侧面
				{
					//搜索顶点坐标容器里有没有这个顶点以便顶点复用
					zx = v.findOrPush(FVector(hex.rightBottom, adjacentHeight));
					zs = v.findOrPush(FVector(hex.rightBottom, height));
					ys = v.findOrPush(FVector(hex.rightMid, height));
					yx = v.findOrPush(FVector(hex.rightMid, adjacentHeight));

					//2个三角形，注意右手法则
					faceString[type * 2 + 1].Append(FString::Printf(TEXT("f %d/7/4 %d/8/4 %d/9/4 \n"), zx, zs, ys));
					faceString[type * 2 + 1].Append(FString::Printf(TEXT("f %d/9/4 %d/10/4 %d/7/4 \n"), ys, yx, zx));
				}
			}
			//下侧面
			if (x > 0)//跳过在下边界的格子的上侧面
			{
				adjacentHeight = tileData[yNum * (x - 1) + y]->height;
				if (height > adjacentHeight)//只有比相邻的格子的海拔高时才生成侧面
				{
					//搜索顶点坐标容器里有没有这个顶点以便顶点复用
					zx = v.findOrPush(FVector(hex.leftBottom, adjacentHeight));
					zs = v.findOrPush(FVector(hex.leftBottom, height));
					ys = v.findOrPush(FVector(hex.rightBottom, height));
					yx = v.findOrPush(FVector(hex.rightBottom, adjacentHeight));

					//2个三角形，注意右手法则
					faceString[type * 2 + 1].Append(FString::Printf(TEXT("f %d/7/5 %d/8/5 %d/9/5 \n"), zx, zs, ys));
					faceString[type * 2 + 1].Append(FString::Printf(TEXT("f %d/9/5 %d/10/5 %d/7/5 \n"), ys, yx, zx));
				}
			}
			//左下侧面
			if (y > 0 && (x > 0 || !Parity))
			{
				adjacentHeight = Parity ? (tileData[yNum * (x - 1) + y - 1]->height) : (tileData[index - 1]->height);
				if (height > adjacentHeight)//只有比相邻的格子的海拔高时才生成侧面
				{
					//搜索顶点坐标容器里有没有这个顶点以便顶点复用
					zx = v.findOrPush(FVector(hex.leftMid, adjacentHeight));
					zs = v.findOrPush(FVector(hex.leftMid, height));
					ys = v.findOrPush(FVector(hex.leftBottom, height));
					yx = v.findOrPush(FVector(hex.leftBottom, adjacentHeight));

					//2个三角形，注意右手法则
					faceString[type * 2 + 1].Append(FString::Printf(TEXT("f %d/7/6 %d/8/6 %d/9/6 \n"), zx, zs, ys));
					faceString[type * 2 + 1].Append(FString::Printf(TEXT("f %d/9/6 %d/10/6 %d/7/6 \n"), ys, yx, zx));
				}
			}
			//左上侧面
			if (y > 0 && (x < (yNum - 1) || Parity))//跳过在右边边界的格子的上侧面和上边界中奇数列的格子的右侧面
			{
				adjacentHeight = Parity ? (tileData[index - 1]->height) : (tileData[yNum * (x + 1) + y - 1]->height);
				if (height > adjacentHeight)//只有比相邻的格子的海拔高时才生成侧面
				{
					//搜索顶点坐标容器里有没有这个顶点以便顶点复用
					zx = v.findOrPush(FVector(hex.leftTop, adjacentHeight));
					zs = v.findOrPush(FVector(hex.leftTop, height));
					ys = v.findOrPush(FVector(hex.leftMid, height));
					yx = v.findOrPush(FVector(hex.leftMid, adjacentHeight));

					//2个三角形，注意右手法则
					faceString[type * 2 + 1].Append(FString::Printf(TEXT("f %d/7/7 %d/8/7 %d/9/7 \n"), zx, zs, ys));
					faceString[type * 2 + 1].Append(FString::Printf(TEXT("f %d/9/7 %d/10/7 %d/7/7 \n"), ys, yx, zx));
				}
			}
			//奇偶翻转	
			Parity = !Parity;
		}
	}

	//生成vString
	for (int32 i = 0; i < v.data.Num(); i++)
	{
		using namespace std;
		stringstream ss; string res;
		FString x, y, z;
		ss << fixed << setprecision(4) << v.data[i].X; ss >> res; x = res.c_str(); ss.clear();
		ss << fixed << setprecision(4) << v.data[i].Y; ss >> res; y = res.c_str(); ss.clear();
		ss << fixed << setprecision(4) << v.data[i].Z; ss >> res; z = res.c_str(); ss.clear();
		vString.Append("v " + x + " " + y + " " + z + "\n");
	}
	vString.Append(FString::Printf(TEXT("# %d vertices\n\n"),v.data.Num()));

	//
	//开始输出文件
	//
	FString saveDir = FPaths::ProjectSavedDir();
	saveDir.Append("Output");
	FString fileName = worldName + ".obj";

	FString absoluteFilePath = saveDir + "/" + fileName;
	FString textToSave = head + vString + vnString + vtString;
	for (auto& s : faceString)	textToSave += s;

	FFileHelper::SaveStringToFile(textToSave, *absoluteFilePath);
}

TArray<FString> AtileMapMakerPlayerControlleCpp::getTypeName()
{
	return typeName;
}

void AtileMapMakerPlayerControlleCpp::updataDetailMenu()
{
	//调用HUD class里面的函数更新DetailMenu的显示出来的数值
	HUDInstance->updataDetailMenuValue(selectedTileIndex, tileData[selectedTileIndex]->x, tileData[selectedTileIndex]->y, tileData[selectedTileIndex]->height, tileData[selectedTileIndex]->type);
}

void AtileMapMakerPlayerControlleCpp::setTileData(float height, int32 type)
{
	//没有选择时不做任何动作
	if (selectedTileIndex < 0)
	{
		return;
	}
	//高度相等时跳过
	if (height != tileData[selectedTileIndex]->height)
	{
		//修改height
		tileData[selectedTileIndex]->height = height;
		FVector oldLocation = tileData[selectedTileIndex]->GetActorLocation();
		//高度大于原始时垂直放大
		if (height > hexMeshData.height)
		{
			//位置设为高度为原始时的
			tileData[selectedTileIndex]->SetActorLocation(FVector(oldLocation.X, oldLocation.Y, 0));
			//垂直放大到对应大小
			tileData[selectedTileIndex]->SetActorScale3D(FVector(1.f, 1.f, height / hexMeshData.height));
		}
		//高度小于原始时
		else
		{
			//先缩放回原来的1倍的大小
			tileData[selectedTileIndex]->SetActorScale3D(FVector(1.f, 1.f, 1.f));
			//移动到对应的高度，10*(height-1)是因为基础模型有10的高度，坐标轴原点在最下面中心
			tileData[selectedTileIndex]->SetActorLocation(FVector(oldLocation.X, oldLocation.Y, height - hexMeshData.height));
		}
	}
	//类型相等时跳过
	if (type != tileData[selectedTileIndex]->type)
	{
		//修改type
		tileData[selectedTileIndex]->type = type;
		//更换材质
		tileData[selectedTileIndex]->hexTileMeshComponent->SetMaterial(0, typeDetail[type]->SurfaceMat);
		tileData[selectedTileIndex]->hexTileMeshComponent->SetMaterial(1, typeDetail[type]->SideMat);
	}


}
