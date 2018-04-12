#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif

#include "aParticleManager.h"

RenderWindow window;
AParticleManager *particleManager;
float pressGap;
int curSceneIndex = 1;

Font font;
Text tipText;

void changeScene()
{
	particleManager->deleteAllSystems();
	particleManager->addNewSystemBySceneId(curSceneIndex);

	if (curSceneIndex == 0)
	{
		return;
	}

	tipText.setString(_SceneTip[curSceneIndex - 1]);
}

void update_state(float dt)
{
	pressGap = pressGap - dt;
	if (pressGap <= 0)
	{
		if (Mouse::isButtonPressed(Mouse::Left) && (curSceneIndex == 0))
		{
			Vector2i mousePos = Mouse::getPosition(window);
			AParticleSystem* newSys = particleManager->addNewSystem(Vector2f(mousePos.x,mousePos.y));
			pressGap = 0.2;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			particleManager->increaseAllMaxNum();
			pressGap = 0.2;
		}

		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			particleManager->decreaseAllMaxNum();
			pressGap = 0.2;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			curSceneIndex++;
			curSceneIndex = curSceneIndex % (SCENE_SIZE + 1);
			changeScene();
			pressGap = 0.2;
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			curSceneIndex--;
			curSceneIndex = (curSceneIndex < 0) ? SCENE_SIZE : curSceneIndex;
			changeScene();
			pressGap = 0.2;
		}
	}

	particleManager->updateWholeSystem(dt);
	if (curSceneIndex == 0)
	{
		tipText.setString(_Scene_0_Tip + to_string(particleManager->getWholeParticleNum()));
	}
}

void render_frame()
{
	window.clear();

	particleManager->drawWholeSystem(&window);
	
	window.draw(tipText);
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	window.create(VideoMode(WIN_WIDTH, WIN_HEIGHT), "Particle !");

	font.loadFromFile("arial.ttf");

	tipText.setFont(font);
	tipText.setCharacterSize(50);
	tipText.setFillColor(Color::Yellow);
	tipText.setPosition(Vector2f(20, 20));

	srand((unsigned)time(0));

	Clock clock;

	pressGap = 0;

	particleManager = new AParticleManager();
	changeScene();

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		float dt = clock.restart().asSeconds();
		update_state(dt);
		render_frame();
		window.display();
	}

	delete particleManager;
	return 0;
}

