#include "CollisionDetection.h"
#include <functional>
const bool CollisionDetection::SAT(shape a, shape b) {

	std::function<float(float, float, float, float)> checkOverlap = [&](float minA, float maxA, float minB, float maxB) {

		return 0.0f;
	};

	std::function< Vec2(Vec3, Vec3)> getAxis = [&]( Vec3 p1, Vec3 p2) {
		//direction from a to b
		Vec2 dir2p2 = Vec2(p2.x - p1.x, p2.y - p1.y);
		dir2p2.Normalize();
		//get the normal vector that will be used as the axis for translation
		float x = dir2p2.x;
		dir2p2.x = -dir2p2.y;
		dir2p2.y = x;
		return  dir2p2;
	};

	Vec2 axis = getAxis(a.second[0], a.second[1]);

	std::function<void(float, float, shape)> dot =
		[&, axis](float min, float max, shape s) {

		auto points = s.second;

		for (int i = 0; i < s.first; ++i) {
			float d = Vec2::Dot(points[i].x, points[i].y, axis.x, axis.y);
			if (d < min)
				min = d;
			if (d > max)
				max = d;
		}
	};

	float minA = 10000000000;
	float maxA = -11111111111;
	float minB = 10000000000;
	float maxB = -11111111111;
	dot(minA, maxA, a);
	dot(minB, maxB, b);
	float penetrationDistance = checkOverlap(minA, maxA, minB, maxB);
}

