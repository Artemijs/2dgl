#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H
#include "Matrix4x4.h"
#include <utility>
#include "Bounds.h"
#define shape std::pair<const unsigned int, Vec3*>

class CollisionDetection {
private:
	
	
	/// <summary>
	/// collision between 2 circles
	/// </summary>
	/// <param name="a">vertices of first bounds</param>
	/// <param name="b">vertices of second bounds</param>
	/// <returns></returns>
	static const SeparationData CircleCircleCollision(const shape& a, const shape& b);

	static const SeparationData SAT(const shape &a, const shape &b);
	static const SeparationData CircleSAT(const shape &a, const shape &b, Vec2& axis);
	static const bool FullSAT(const shape &a, const shape &b);
	static const std::pair<float, int> CheckOverlap(const float minA, const float maxA, const float minB, const float maxB);
	static const Vec2 GetAxis(const Vec3& p1, const Vec3& p2);
	static const void ProjectOnAxis(float& min, float& max, const Vec2 axis, const shape& s);

	
public :
	static bool _print;
	
	static SeparationData CheckCollision( Bounds *a,  Bounds *b);

	/// <summary>
	/// Calls the appropriate collision detection function depending on bound types
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <param name="aRad">radius of a if a is a circle, default to 0 if a is not circle</param>
	/// <param name="bRad">radius of b if b is a circle, default to 0 if b is not circle</param>
	/// <returns></returns>
	static SeparationData CheckCollision(const shape& a, const shape& b, const float aRad = 0, const float bRad = 0);
	/// <summary>
	/// collision between a point and any shape, currently only box
	/// </summary>
	/// <param name="p">vec3</param>
	/// <param name="s">pair of int and vec3* to array of vertices</param>
	/// <returns></returns>
	static const float CheckPointSAT(const Vec3& p, const shape& s);
	
	
	
	/// <summary>
	/// collision between boxes that have not rotated
	/// </summary>
	/// <param name="a">vertices of first bounds</param>
	/// <param name="b">vertices of second bounds</param>
	/// <returns></returns>
	static const SeparationData CheckAABBCollision(const shape& a, const shape& b);
	
	/// <summary>
	/// Checks collision between a Ray and everything that has a collision box on it
	/// </summary>
	/// <param name="ray">The ray it checks</param>
	/// <param name="hitData">The return data variable that is filled here</param>
	/// <returns>collided/not collided</returns>
	static bool LineObjectIntersection(Ray* ray, RayHitData& hitData);
	
};
#endif

/*
bool SATCheck(point, box){

}
bool SATCheck(point, circle){

}
bool SATCheck(box, box){
		
}
bool SATCheck(box, circle){

}


bool SATCeck(pointsA, pointsB){
	for every point in pointsA and then pointsB
	{
		calculate axis

		dot product between axis and every point in points a
	
		get min and max of of dot product result to get the 1d shape
	
		dot product between axis and every point in points b

		get min and max of of dot product result to get the 1d shape

		check if the 2 overlap
	}

}
*/
/*
function checkCollision(a, b){
	this.get_overlap=function(min, max, minB, maxB){
		//translate the values to ensure that they are all positive
		var translate_by
		if(minB < min)
			translate_by = Math.abs(minB);
		else
			translate_by = Math.abs(min);

		minB+=translate_by;
		maxB+=translate_by;
		min+=translate_by;
		max+=translate_by;
		//if its not collided itll become 0 otherwise remain 1
		collided = 1;
		
		i need to check if
		a is in b
		b is in a
		any edge of b is in a
		any edge of is in b
		
		//have o do this twice for both 
			//check if bot point is inside
			//if(min > minB && min < maxB)
			//check if top point is inside
			//if(max > minB && max < maxB)
		//check if all of A is inside B
		//if(minB < min && maxB > max)
		//check if all of B is inside A
		//if(min < minB && max > maxB)

		//if A is in B
if (minB < min && maxB > max) {
	//val = max - min
	var nr = max - min;
	if (nr < normalV.val) {
		normalV.val = nr;
		normalV.dir = normal;
	}
}
//if B is in A
else if (min < minB && max > maxB) {
	//val = maxB - minB
	var nr = maxB - minB;
	if (nr < normalV.val) {
		normalV.val = nr;
		normalV.dir = normal;
	}
}
//check corners of A
else if (min > minB && min < maxB) {
	//val = maxB - min
	var nr = maxB - min;
	if (nr < normalV.val) {
		normalV.val = nr;
		normalV.dir = normal;
	}
}
else if (max > minB && max < maxB) {
	//val = max - closest
	var nr = max - minB;
	if (nr < normalV.val) {
		normalV.val = nr;
		normalV.dir = normal;
	}
}
//check corners of B
else if (minB > min && minB < max) {
	//val = closest - minB
	var nr = max - minB;
	if (nr < normalV.val) {
		normalV.val = nr;
		normalV.dir = normal;
	}
}
else if (maxB > min && maxB < max) {
	//val = maxB - closest
	var nr = maxB - min;
	if (nr < normalV.val) {
		normalV.val = nr;
		normalV.dir = normal;
	}
}
//not colided aka no overlap
else {
	collided = 0;
	return;
}
	}


	this.get_normal = function(v1, v2) {
		var nv = v1.directionTo(v2);
		return new Vector2D(-nv.y, nv.x);
	}
	this.do_dot = function(itt, normal, arr) {
		console.log(itt);
		if (itt >= arr.length) return;
		var dot_val = arr[itt].dot(normal);
		if (dot_val > max)max = dot_val;
		if (dot_val < min)min = dot_val;
		this.do_dot(++itt, normal, arr);
	}


	////////////////////////////////
	//START HERE
	////////////////////////////////


	var pointsA = a.get_points();
	var pointsB = b.get_points();
	var collided = -1;
	var normalV = new Object();// this is used for the response
	normalV.val = 1000000000;//how much to move by when responding
	normalV.dir = new Vector2D();//direction to move in when responding
	//for every normal vector in A
	for (var i = 0; i < pointsA.length - 1; i++) {
		//get normal
		var normal = this.get_normal(pointsA[i], pointsA[i + 1]);

		//get dots between all points of object A and normal
		//and find the min and max of those dots
		var min = 100000000; var max = -100000000;
		this.do_dot(0, normal, pointsA);

		//store the min max of A
		var minA = min; var maxA = max;
		//get dots between all points of object B and normal
		min = 100000000; max = -100000000;
		//and get the min/max of B
		this.do_dot(0, normal, pointsB);//fills min and max with vales
		//this is the important part
		//this checks if they collide and stores the collision response normal vector
		//as well as the depth of penetration
		this.get_overlap(minA, maxA, min, max);
		if (collided == 0) {
			//IF THERE IS EVEN A SINGLE OPERATION THAT DOES NOT OVERLAP
			//IF THERE IS EVER A GAP BETWIIN a AND b
			//STOP AND LEAVE 
			//one gap proves that the objects dont collide at all
			return;
		}

	}
	//store the test results of A to later compare with B
	var n1 = normalV;
	//NOW DO THE EXACT SAME THING FOR OBJECT B
	collided = -1;
	normalV = new Object();
	normalV.val = 1000000000;
	normalV.dir = new Vector2D();
	for (var i = 0; i < pointsB.length - 1; i++) {
		//get normal
		var normal = this.get_normal(pointsB[i], pointsB[i + 1]);
		//get dots between all points of object B and normal
		var min = 100000000; var max = -100000000;
		this.do_dot(0, normal, pointsA);
		//get dots between all points of object A and normal
		var minA = min; var maxA = max;
		min = 100000000; max = -100000000;
		this.do_dot(0, normal, pointsB);//fills min and max with vales
		this.get_overlap(minA, maxA, min, max);
		if (collided == 0) {
			return;
		}
	}
	//==========
	response
	//==========
	//compare how deep the penetration is for A and for B, pick the smallest one
	if (n1.val < normalV.val) {
		normalV = n1;
	}
	if (normalV.val > 10000 || normalV.val < -10000)return;//in case of errorkind of thing

	//this is to see if you go in the direction of normal or oppositte to it
	//may or may not cause bugs in the future
	var aPos = a.getCentre();
	var bPos = b.getCentre();
	var c2c = aPos.directionTo(bPos);
	var dirDot = normalV.dir.dot(c2c);
	var sign = 1;
	if (dirDot > 0) sign = -1;

	var fp = a.getPosition();
	fp.x += normalV.dir.x * normalV.val * sign;
	fp.y += normalV.dir.y * normalV.val * sign;
	a.setPosition(fp);
}


*/