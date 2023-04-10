#ifndef ELEMENT_H
#define ELEMENT_H
#include <vector>
#include "../Math/Matrix4x4.h"
namespace v1_5 {
	class Element {
	private:

	protected:
		std::vector<Element*>* _children;
		Element* _parent;

	public:
		Element();
		Element(Element* parent);
		~Element();
		int AddChild(Element* child);
		void SetParent(Element* parent);
		Element* GetChild(int id);
		Element* GetParent();
		virtual void UpdateTransform(Matrix4x4 parent) = 0;
		virtual Matrix4x4 GetTransform() = 0;

	};
}
#endif