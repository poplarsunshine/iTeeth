#include "SceneManager.h"
#include "MainScene.h"
#include "GameScene.h"

using namespace cocos2d;

SceneManager* SceneManager::s_pIntance = NULL;
SceneManager::SceneManager(void)
{
}


SceneManager::~SceneManager(void)
{
}

SceneManager* SceneManager::sharedSceneManager()
{
	if (!s_pIntance)
	{
		s_pIntance = new SceneManager;
	}
	return s_pIntance;
}

void SceneManager::runScene(cocos2d::Scene *pScene, bool useTransition)
{
    Scene *pCurScene = Director::getInstance()->getRunningScene();
    TransitionScene *transition = TransitionFade::create(0.3, pScene, Color3B::WHITE);
    if (!pCurScene)
        Director::getInstance()->runWithScene(useTransition ? transition : pScene);
    else
    {
        Director::getInstance()->replaceScene(useTransition ? transition : pScene);
    }
}

//void SceneManager::runMainScene()
//{
//    Scene *pScene = MainScene::createScene();
//	TransitionScene *transition = TransitionFade::create(0.3, pScene, Color3B::WHITE);
//	Scene *pCurScene = Director::getInstance()->getRunningScene();
//	if (!pCurScene)
//		Director::getInstance()->runWithScene(pScene);
//	else
//		Director::getInstance()->replaceScene(transition);
//}
//
//void SceneManager::runGameScene()
//{
//    Scene *pScene = GameScene::createScene();
//    TransitionScene *transition = TransitionFade::create(0.3, pScene, Color3B::WHITE);
//    Scene *pCurScene = Director::getInstance()->getRunningScene();
//    if (!pCurScene)
//        Director::getInstance()->runWithScene(pScene);
//    else
//        Director::getInstance()->replaceScene(transition);
//}

