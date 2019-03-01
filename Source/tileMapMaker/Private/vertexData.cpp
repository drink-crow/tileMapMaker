#include "vertexData.h"

int32 vertexData::findOrPush(FVector target)
{
	int32 index = data.Find(target);
	if (index == INDEX_NONE)
	{
		//如果没有这个顶点，新建一个进去
		data.Push(target);
		index = data.Num();
		return index;
	}
	else
	{
		return index+1;
	}

}