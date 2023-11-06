#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H
#include <vector>
template <typename T>
class SList;

class Memory {

public :
	Memory() {};
	virtual ~Memory() { };

};




class MemoryManager {
private:
	/// <summary>
	/// used to dlete objects at runtime during schdeuled times, use this for objects that get dynamically created like bullts and projectiles
	/// </summary>
	static SList<Memory*>* _all_garbage;
	/// <summary>
	/// this memory gets deleted when application closes, used for graphs to avoid infinite recursion
	/// </summary>
	static std::vector<const Memory*>* _garbageCache;

public : 
	/// <summary>
	/// use this to delete objects dynamically
	/// </summary>
	/// <param name="mem"></param>
	static void AddToGarbage(Memory* mem);
	static void ClearMemory();
	static void Clean();
	/// <summary>
	/// use this to delete memory when the application closes
	/// </summary>
	/// <param name="mem"></param>
	static void CacheGarbage(const Memory* mem);
};
#ifndef garbage 
#define garbage MemoryManager::AddToGarbage
#endif
#include "DataStructures.h"
#endif // !MEMORY_MANAGER_H
