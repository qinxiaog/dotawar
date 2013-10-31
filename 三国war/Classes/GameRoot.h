#ifndef _GAME_ROOT_H_
#define _GAME_ROOT_H_

#include "cocos2d.h"
using namespace cocos2d;

#include "SceneStart.h"
#include "SceneSelect.h"
#include "SceneGame.h"
#include "SceneOver.h"

class GameRoot:public CCObject
{
public :
    ~GameRoot();
    virtual bool init();
    static GameRoot* shareGameRoot();
	void InitializeResource();
	SceneStart* getSceneStart();
	SceneSelect* getSceneSelect();
	SceneGame* getSceneGame();
	SceneOver* getSceneOver();

};

#endif