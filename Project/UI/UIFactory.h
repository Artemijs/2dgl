#ifndef UI_FACTORY_H
#define UI_FACTORY_H


class {
private:

public :
	//static void 
};

#endif


/*
base_window.h


UI_State{
	//to turn the entire ui  off
	BaseObject* _ui_root;
	//individual ui elements btns, pop ups, etc
	std::vector<BaseObject*>* _elements;

};

GameState : UI_State{
	BaseObject* _root;
	_enemies[3]
	_turrets[3];

	Update(float deltaTime);
	Start();
	Pause();
	End();



};


class Screen{
	BaseObject* _root;

	void Update(float deltaTime);

};

UI_Hnadler{
	static std::vector<BaseObject*>* _screens;
	static void BaseObject* _current;
	static void Update(flaot deltaTime);
	static void ChangeScreen(int id);
}

game{
	baseobjects[3] screens
	Game(){
		UIFactory::MakeAllUI(_world, screens);

	}
	ChangeScreen(int newScreen){
		//any screen off callbacks here 
		screens[current]->setEnabled(fasle);
		_current = newSCreen;
		screens[current]->setEnabled(true);
		//any screen on callbacks here
	}
	Update(deltaTime);
}

*/