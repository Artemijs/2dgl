#include "MemoryManager.h"
#include "DataStructures.h"

SList<Memory*>* MemoryManager::_all_garbage = new SList<Memory*>();

void MemoryManager::AddToGarbage(Memory* mem) {
	_all_garbage->Add(mem);
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
}


void MemoryManager::Clean() {

	delete _all_garbage;

}