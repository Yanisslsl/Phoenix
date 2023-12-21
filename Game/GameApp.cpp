#include "Phoenix.h"

class GameApp : public Phoenix::Application
{
public:
	GameApp()
	{

	}

	~GameApp()
	{

	}
};

Phoenix::Application* Phoenix::CreateApplication()
{
	return new GameApp();
}
