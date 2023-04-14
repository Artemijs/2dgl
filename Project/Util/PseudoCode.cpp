/*
* 
	bind FBO
		draw everything 
	unbind fbo

	bind vao of quad
	activate shader 
	bind fbo texture
	draw
	unbind fbo
	unbind vao
	unbind texture


	WITH A GRAPH IT WOULD LOOK LIKE 

	node{
		node* parent
		node* children;
	};


	drawGraph(node){
		draw node
		children chs = too->GetChildren();
		if(children == NULL) retun;
		for child in chs
			drawGraph(child);

	}


	bind fbo
		drawGraph(root);
	unbind fbo;

	bind vao quad
	shader activate
	bind fbo texture
	draw
	unbind vao
	deactivate shader
	unbind texture


	IF THE GRAPH CONTAINED RENDER NODES 
	THAT CONTAINED THE FRAME BUFFER OBJ


		drawGraph(node){
		draw node
		children chs = too->GetChildren();
		if(children == NULL) retun;
		for child in chs
			drawGraph(child);

	}
		

	bind root fbo			because root is always a render obj
		drawGraph(root);
	unbind fbo;

	bind vao quad
	shader activate
	bind fbo texture
	draw
	unbind vao
	deactivate shader
	unbind texture




	bind root
	if node is render node
		skip and dont draw it
	else draw to root
	


	root
	{
		sprite
		sprite
		renderNode1 : last is root
		{
			sprite
			sprite
			sprite
			{
				sprite
			}
			
			//renderNode2{ : last is renderNode 1
			//	sprite
			//	sprite
			//}

		}
		sprite
		sprite
		renderNode3: last is ROOT
		{
			sprite
			sprite
		}
	}

	bind root
	draw sprite
	draw sprite
	
	bind render node1
	draw sprite
	draw sprite
	draw sprite

	bind rendernode2
	draw sprite
	draw sprite

	bind render node 1
	draw renderNode2
	
	bind root
	draw render node 1 

	draw sprite
	draw sprite
	
	bind render node 3
	draw sprite
	draw sprite

	bind root
	draw render node 3

	draw root


	drawNode(root, ROOT)

	drawNode(node, last){

		if(node == renderNode){
			bind node;
		}

		if (children =! null)
			for(int i = 0; i < children.size(); ++i){
				drawNode(children[i], NODE);
			}

		if(node == renderNode)
			BIND LAST
		if(parent == null)
			//you are at root
		node->draw();
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////
	root
	{
		sprite
		sprite
		renderNode1 : last is root
		{
			sprite
			sprite
			sprite
			{
				sprite
			}

			//renderNode2{ : last is renderNode 1
			//	sprite
			//	sprite
			//}

		}
		sprite
		sprite
		renderNode3: last is ROOT
		{
			sprite
			sprite
		}
	}

	root[ s, s, rn1, s, s, rn3]
	rn1[s, s, s,[s]]
	rn3[s, s]

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////COLLISION DETECTION/////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	BUTTON inherits from MOUSE EVENT
	MOUSE EVENT constructor registers the event in MOUSE EVENT CONTROLLER
	MouseEvent controller need PARENT RENDER NODE

	BUTTON is created
	BUTTON is added as child to RENDER NODE and BUTTONS prent is set

	the algorythm checks if window is collided with
	then if window contents are collided with

	I HAVE TO USE THE TREE SOMEHOW

	for each window in tree
		if(mouse in window):
			for each ui in all_ui
				check if mosue in ui

	i can store window nodes in a list and if it has collided then use it as the root of a recursive algorythm

	problem is that i cant check if the object has or does not have collision enabled

	for rendernode rn in allrendernodes:
		if collided with rn:
			CheckCollision(rn);

	CheckCollision(Node* n){
		if (n->GetBB()->collided){
			n->GetMouseEvent()->OnEnter();
		}
		for(child c in children):
			CheckCollision(c);

	}
	THE TWO BIG PROBLEMS HERE ARE NODE NOT HAVING A GETBB FUNCTION BECASUE BEASEOBJECT DOES NOT CONTAIN THAT FUNCTIONALITY
		AND NODE NOT HAVING A MOUSE EVENT FOR SAME REASON

	n->GetComponent<BBox>();

	BaseComponent{};

	BasseObject{
		vector<pair<uint,BaseComponent*>*> components;
		
		template<T> void AddComponent(t){
			uint size = sizeof(t);
			bool exists = CheckIfComponentExists(size);
			
			if(exists) return;

			pair* p = new pair<uint, BaseComponent*>();
			p.first = size;
			p.second = t;

			components->add(t);
		}

		bool CheckCheckIfComponentExists(uint){
			foreach pair p in components:
				if p->first == uint:
					return true;

			return false;
		}

		template<T>  t GetComponent(){
			uint size = sizeof(T);
			foreach pair p in components:
				if p.first == size
					return p.second;

			return NULL;
		}

		template<T>  t GetComponent(uint size){
			foreach pair p in components:
				if p.first == size
					return p.second;

			return NULL;
		}
		void Update(float deltaTime){}
		void Draw(){}
	};

	LETS TRY TO APPROACH THE PROBLEM WITH THE COMPONENTS BEING OBJECTS ADN NOT INHERITED

	
	for rendernode rn in allrendernodes:
		if collided with rn:
			CheckCollision(rn);

	CheckCollision(Node* n){

		uint size = sizeof(BBox);
		BBox bb = n->GeteComponent<BBox>(size);
		if (bb->collided){
			 n->GeteComponent<MouseEvent>();
		}

		for(child c in children):
			CheckCollision(c);
	}


	HOW DOES THE MOUSE EVENT WORK NOW ??



	I NEED TO RECURSIVELLY FIND THE OBJECT THAT MOUSE INTERSECTSS WITH CLOSEST TO THE CAMERA

	HandleMouseEvent(vec3 mousepos){
		//find rneder node closest to the camera that intersects with the mouse
		renderNode old = NULL;
		for (rendernode new in allrendernodes){
			uint size = sizeof(BBox);
			BBox bb = new->GeteComponent<BBox>(size);
			if (bb->collided){
				if(old == null)
					old = new;
					else if(new.z > old.z){
						old = new;
					}
			}
		}
		
		if(old == NULL){
			//not colliding with anything 
			return;
		}

		Node* n = CheckCollided(old, mousePos)
	}


	CheckCollided(Node* n, mousePos, ){
		uint size = sizeof(BBox);
		BBox bb = n->GeteComponent<BBox>(size);
		Node* closest = NULL;
		

		fpr(int i =0; i < _children->size(); ++i){
			
			Node* childN = CheckCollision(_children->at(i), mousepos);
			
			if(n->position.z > closest->position->z){
				closest = childN;
			}
		}
		if(closest == NULL){
			if (bb->collided){
				//compare with closest
				closest = n;
			}
		}
		return closest;
		
	}



	a render node doesnt need to be a different type of node
	it can have an FBO as a component
	to check isRenderNode i can check if compobnents len == 1 
	and component type size == renNodeSize


*/