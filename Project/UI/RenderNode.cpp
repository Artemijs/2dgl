#include "RenderNode.h"
#include "../Graphics/Renderer.h"
RenderNode::RenderNode():
	BaseObject(Vec3(), Vec3(Renderer::instance()->GetWindowSize().x, Renderer::instance()->GetWindowSize().y, 0), Vec3(0, 0, 0), 2) {


}

//uses default image as background
RenderNode::RenderNode(Vec3 pos, Vec3 size, float ang): 
	BaseObject(pos, size, Vec3(0,ang,0), 2){
	
}
