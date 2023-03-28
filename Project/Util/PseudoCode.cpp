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

*/