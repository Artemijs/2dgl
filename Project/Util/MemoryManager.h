#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H
#include <vector>
template <typename T>
class SList;

class Memory {

public :
	Memory() {};
	virtual ~Memory() { printf("CALLING DELETE FROM MEMORY \n"); };

};




class MemoryManager {
private:
	static SList<Memory*>* _all_garbage;
public : 
	static void AddToGarbage(Memory* mem);
	static void ClearMemory();
	static void Clean();
};
#include "DataStructures.h"
#endif // !MEMORY_MANAGER_H
