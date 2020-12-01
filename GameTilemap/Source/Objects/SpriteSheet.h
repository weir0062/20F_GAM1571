#pragma once


namespace fw {

class SpriteSheet
{
public:
	struct SpriteInfo
	{
		vec2 m_UVScale = vec2(1,1);
		vec2 m_UVOffset = vec2(0,0);

		SpriteInfo() {}
		SpriteInfo(vec2 scale, vec2 offset) { m_UVScale = scale, m_UVOffset = offset; }
	};

public:
	SpriteSheet(const char* filename);
	virtual ~SpriteSheet();

	SpriteInfo* GetSpriteInfo(const char* spriteName);

private:
	std::map<std::string, SpriteInfo> m_Sprites;
};

} // namespace fw
