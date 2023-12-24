#include "Util/MemoryManager.h"
#include "Util/DataStructures.h"




SList<Memory*>* MemoryManager::_all_garbage = new SList<Memory*>();
std::vector<const Memory*>* MemoryManager::_garbageCache = new std::vector<const Memory*>();
void MemoryManager::AddToGarbage(Memory* mem) {

	_all_garbage->Add(mem);
	mem = NULL;
}
void MemoryManager::CacheGarbage(const Memory* mem) {
	_garbageCache->push_back(mem);
}

/// <summary>
/// wallk the list and call delete and hope that virtual inheritance constructor will be called properly
/// </summary>
void MemoryManager::ClearMemory() {

	//delete _all_garbage->_head;
	auto head = _all_garbage->_head;
	auto tempNode = head;

	while (head != NULL) {

		tempNode = head->_next;
		delete head;
		head = tempNode;

	}
	_all_garbage->_head = NULL;
	_all_garbage->_tail = NULL;
}


void MemoryManager::Clean() {
/*	if (_all_garbage->_head != NULL)
		printf("MEMORY NOT EMPTY!\n");
	delete _all_garbage;

	for (int i = 0; i < _garbageCache->size(); i++) {
		delete _garbageCache->at(i);
	}
	delete _garbageCache;*/
	delete _all_garbage;
	delete _garbageCache;

}