#pragma once

namespace fw {
    class FWCore;
	
class GameCore
{
public:
    GameCore(FWCore* pFramework);
    virtual ~GameCore();

    virtual void Update(float delta) = 0;
    virtual void Draw() = 0;
    FWCore* m_pFramework = nullptr;
};

} // namespace fw
