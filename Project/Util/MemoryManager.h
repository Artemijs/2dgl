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
	static SList<Memory*>* _all_garbage;
public : 
	static void AddToGarbage(Memory* mem);
	static void ClearMemory();
	static void Clean();
};
#ifndef garbage 
#define garbage MemoryManager::AddToGarbage
#endif
#include "DataStructures.h"
#endif // !MEMORY_MANAGER_H
