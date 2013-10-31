#include "ActorBase.h"
bool ActorBase::initWithActorData(ActorData *data)
{
    bool bRet = false;
    do {
        setActorData(data);
        _action_attack = NULL;
        _action_attack_flip = NULL;
        _action_run = NULL;
        _action_run_flip = NULL;
        _action_stand = NULL;
        _action_stand_flip = NULL;
        _action_dead = NULL;
        _action_dead_flip = NULL;

        _currentAnimateAction = NULL;
        
        CCSpriteFrameCache* cache =
        CCSpriteFrameCache::sharedSpriteFrameCache();
        char str[64] = {0};
        char strf[64] = {0};
        
        CCArray* _attackFrames =  CCArray::createWithCapacity(10);
        CCArray* _attackFrames_flip =  CCArray::createWithCapacity(10);
        for (int i = 0; i < 4; i++) {
            sprintf(str, "%s_%d.png", data->getActorID().c_str(), i);
            sprintf(strf, "%sf_%d.png", data->getActorID().c_str(), i);
            _attackFrames->addObject(cache->spriteFrameByName(str));
            _attackFrames_flip->addObject(cache->spriteFrameByName(strf));
        }
        _action_attack = CCAnimate::create(
                                           CCAnimation::create(_attackFrames, 0.1f));
        _action_attack->retain();
        _action_attack_flip = CCAnimate::create(
                                                CCAnimation::create(_attackFrames_flip, 0.1f));
        _action_attack_flip->retain();
        
        CCArray* _runFrames =  CCArray::createWithCapacity(10);
        CCArray* _runFrames_flip =  CCArray::createWithCapacity(10);
        for (int i = 4; i < 6; i++) {
            sprintf(str, "%s_%d.png", data->getActorID().c_str(), i);
            sprintf(strf, "%sf_%d.png", data->getActorID().c_str(), i);
            _runFrames->addObject(cache->spriteFrameByName(str));
            _runFrames_flip->addObject(cache->spriteFrameByName(strf));
        }
        _action_run = CCAnimate::create(
                                        CCAnimation::create(_runFrames, 0.1f));
        _action_run->retain();
        _action_run_flip = CCAnimate::create(
                                             CCAnimation::create(_runFrames_flip, 0.1f));
        _action_run_flip->retain();
        
        CCArray* _standFrames =   CCArray::createWithCapacity(10);
        CCArray* _standFrames_flip =   CCArray::createWithCapacity(10);
        for (int i = 6; i < 7; i++) {
            sprintf(str, "%s_%d.png", data->getActorID().c_str(), i);
            sprintf(strf, "%sf_%d.png", data->getActorID().c_str(), i);
            _standFrames->addObject(cache->spriteFrameByName(str));
            _standFrames_flip->addObject(cache->spriteFrameByName(strf));
        }
        _action_stand = CCAnimate::create(
                                          CCAnimation::create(_standFrames, 0.1f));
        _action_stand->retain();
        _action_stand_flip = CCAnimate::create(
                                               CCAnimation::create(_standFrames_flip, 0.1f));
        _action_stand_flip->retain();
        
        CCArray* _deadFrames =  CCArray::createWithCapacity(10);
        CCArray* _deadFrames_flip =  CCArray::createWithCapacity(10);
        for (int i = 7; i < 9; i++) {
            sprintf(str, "%s_%d.png", data->getActorID().c_str(), i);
            sprintf(strf, "%sf_%d.png", data->getActorID().c_str(), i);
            _deadFrames->addObject(cache->spriteFrameByName(str));
            _deadFrames_flip->addObject(cache->spriteFrameByName(strf));
        }
        _action_dead = CCAnimate::create(
                                         CCAnimation::create(_deadFrames, 0.1f));
        _action_dead->retain();
        _action_dead_flip = CCAnimate::create(
                                              CCAnimation::create(_deadFrames_flip, 0.1f));
        _action_dead_flip->retain();
        
        sprintf(str, "%s_%d.png", data->getActorID().c_str(), 6);
       _sprite =  CCSprite::create(str);
        _sprite->retain();
        this->addChild(_sprite);
        bRet = true;
    } while (0);
    return bRet;
}
ActorBase* ActorBase::create(ActorData* data)
{
    ActorBase* actorbase =new ActorBase();
    if (actorbase&&actorbase->initWithActorData(data)) {
        actorbase->autorelease();
        return actorbase;
    }else
    {
       
        delete actorbase;
        actorbase =NULL;
        return NULL;
    }
}

ActorBase::~ActorBase()
{
    CC_SAFE_RELEASE_NULL(mActorData);
    CC_SAFE_RELEASE_NULL(_action_attack);
    CC_SAFE_RELEASE_NULL(_action_attack_flip);
    CC_SAFE_RELEASE_NULL(_action_dead);
    CC_SAFE_RELEASE_NULL(_action_dead_flip);
    CC_SAFE_RELEASE_NULL(_action_run);
    CC_SAFE_RELEASE_NULL(_action_run_flip);
    CC_SAFE_RELEASE_NULL(_action_stand);
    CC_SAFE_RELEASE_NULL(_action_stand_flip);
}

void ActorBase::StateToRun()
{
	if (mActorDir == Left)
		RunAnimateAction_RepeatForever(_action_run);
	else
		RunAnimateAction_RepeatForever(_action_run_flip);
}

void ActorBase::StateToAttack()
{
	currentAnimateActionStop();
	if (mActorDir == Left)
		RunAnimateAction_RepeatForever(_action_attack);
	else
		RunAnimateAction_RepeatForever(_action_attack_flip);
}

void ActorBase::StateToDead()
{
	currentAnimateActionStop();
	if (mActorDir == Left)
		RunAnimateAction_RepeatForever(_action_dead);
	else
		RunAnimateAction_RepeatForever(_action_dead_flip);
}

void ActorBase::StateToStand()
{
	if (mActorDir == Left)
		RunAnimateAction_RepeatForever(_action_stand);
	else
		RunAnimateAction_RepeatForever(_action_stand_flip);
}

void ActorBase::currentAnimateActionStop()
{
	if (_currentAnimateAction != NULL)
		this->stopAction(_currentAnimateAction);
}

void ActorBase::RunAnimateAction_RepeatForever(CCAnimate* action)
{
	currentAnimateActionStop();
	_currentAnimateAction = runAction(CCRepeatForever::create(action));
}