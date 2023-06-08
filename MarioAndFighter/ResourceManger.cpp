#include "ResourceManger.h"
#include "D2D1Core.h"
#include "Bitmap.h"
#include "FileUtils.h"
#include "Type.h"
#include "Map.h"
#include "Sprite.h"
#include "Animation.h"
std::map<char*, class Bitmap*> ResourceManger::m_resource;
Bitmap* ResourceManger::GetBitmap(char* _key, ID2D1HwndRenderTarget** _rrt)
{
	if (m_resource.find(_key) != m_resource.end())
		return m_resource.find(_key)->second;
	else
	{
		TCHAR path[256] = {0,};
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, _key, strlen(_key), path, strlen(_key));
		Bitmap* ret = D2D1Core::GetInstance()->LoadBitmapByFileName(_rrt, path);
		m_resource.insert({ _key, ret });
		return ret;
	}
}

void* ResourceManger::LoadBinaryData(const char* _path)
{
	void* ret = nullptr;
	FILE* p_file = NULL;
	fopen_s(&p_file, _path, "rb");
	char exp[256];
	if (p_file != NULL)
	{
		FileUtils::GetFileExp(_path, exp);
		if (0 == strcmp(exp, "spr"))
		{
			SpriteBinaryFileHeader* header = new SpriteBinaryFileHeader();
			fread(header, sizeof(SpriteBinaryFileHeader), 1, p_file);

			if (header)
			{
				SpriteBinaryFileData* bStream = new SpriteBinaryFileData[header->spriteCount];
				fread(bStream, sizeof(SpriteBinaryFileData), header->spriteCount, p_file);

				switch (header->resourceType)
				{
				case SPRITE:
					for (int i = 0; i < header->spriteCount; i++)
					{
						ret = new Sprite(bStream[i].rect, bStream[i].pivotPos);
					}
					break;
				case  ANIMATION:
				{
					ret = new Animation();
					for (int i = 0; i < header->spriteCount; i++)
					{
						Sprite* sprite = new Sprite(bStream[i].rect, bStream[i].pivotPos);
						reinterpret_cast<Animation*>(ret)->AddClip(sprite);
					}
					break;
				}
				}
				delete[] bStream;
			}
			delete header;
		}
	}

	return ret;
}