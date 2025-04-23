#include "includes.hpp"

#include "ProgramMemory.hpp"

#include "OrderedTable.hpp"
#include "UnorderedTable.hpp"
#include "HashTableCA.hpp"
#include "HashTableOA.hpp"
#include "AVLTree.hpp"
#include "RedBlackTree.hpp"

void initMemory(size_t container_id) {

	switch (container_id) {

	case 0:

		global_memory = std::make_unique<MemoryManager<OrderedTable>>();

		break;

	case 1:

		global_memory = std::make_unique<MemoryManager<UnorderedTable>>();

		break;

	case 2:

		global_memory = std::make_unique<MemoryManager<AVLTree>>();

		break;

	case 3:

		global_memory = std::make_unique<MemoryManager<RedBlackTree>>();

		break;

	case 4:

		global_memory = std::make_unique<MemoryManager<HashTableCA>>();

		break;

	case 5:

		global_memory = std::make_unique<MemoryManager<HashTableOA>>();

		break;

	default:
		throw std::logic_error("Wrong Container Type!");
	}



}