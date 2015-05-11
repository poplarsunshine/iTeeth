#ifndef  __SSSCENEMANGAGER_H_
#define  __SSSCENEMANGAGER_H_

class SceneManager
{
	
public:
	SceneManager(void);
	~SceneManager(void);

	static SceneManager* sharedSceneManager();

    void runScene(cocos2d::Scene *scene, bool useTransition = false);
    
	void runLogoScene();

	void runLoadingScene();

	void runMainScene();

	void runGameScene();

private:
	static SceneManager* s_pIntance;

public:
};

#endif  //__SSSCENEMANGAGER_H_