#pragma once
#include <map>
#include <d2d1.h>
class ResourceManger
{
private:
	static std::map<char*, class Bitmap*> m_resource;
public:
	static Bitmap* GetBitmap(char* _key, ID2D1HwndRenderTarget** _rrt);
	static void* LoadBinaryData(const char* _path);
};

