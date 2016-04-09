#include "Heap.h"

#include "Assert.h"
#include "Maze.h"

namespace mackAlgoTwo {

Heap::Heap() : m_size(0) {
}

byte Heap::size() {
    return m_size;
}

void Heap::push(byte cell) {
    ASSERT_LT(m_size, CAPACITY);
    m_data[m_size] = cell;
    Maze::info[cell].heapIndex = m_size;
    m_size += 1;
    if (1 < m_size) {
        heapifyUp(m_size - 1);
    }
}

void Heap::update(byte cell) {
    ASSERT_LE(0, Maze::info[cell].heapIndex);
    heapifyUp(Maze::info[cell].heapIndex);
}

byte Heap::pop() {
    ASSERT_LT(0, m_size);
    byte cell = m_data[0];
    Maze::info[cell].heapIndex = SENTINEL;
    m_data[0] = m_data[m_size - 1];
    Maze::info[m_data[0]].heapIndex = 0;
    m_size -= 1;
    if (1 < m_size) {
        heapifyDown(0);
    }
    return cell;
}

byte Heap::getParentIndex(byte index) {
    if (index == 0) {
        return SENTINEL;
    }
    return (index - 1) / 2;
}

byte Heap::getLeftChildIndex(byte index) {
    if (getParentIndex(CAPACITY - 1) < index) {
        return SENTINEL;
    }
    return (index * 2) + 1;
}

byte Heap::getRightChildIndex(byte index) {
    if (getParentIndex(CAPACITY - 1) < index) {
        return SENTINEL;
    }
    return (index + 1) * 2;
}

byte Heap::getMinChildIndex(byte index) {

    byte left = getLeftChildIndex(index);
    byte right = getRightChildIndex(index);

    if (m_size <= left) {
        return SENTINEL;
    }

    if (m_size <= right) {
        return left;
    }

    return (Maze::info[m_data[left]].distance < Maze::info[m_data[right]].distance ?  left : right);
}

void Heap::heapifyUp(byte index) {
    ASSERT_LE(0, index);
    ASSERT_LT(index, m_size);
    byte parentHeapIndex = getParentIndex(index);
    while (
        parentHeapIndex != SENTINEL &&
        Maze::info[m_data[index]].distance < Maze::info[m_data[parentHeapIndex]].distance
    ) {
        swap(index, parentHeapIndex);
        index = parentHeapIndex;
        parentHeapIndex = getParentIndex(index);
    }
}

void Heap::heapifyDown(byte index) {
    ASSERT_LE(0, index);
    ASSERT_LT(index, m_size);
    byte minChildHeapIndex = getMinChildIndex(index);
    while (
        minChildHeapIndex != SENTINEL &&
        Maze::info[m_data[minChildHeapIndex]].distance < Maze::info[m_data[index]].distance
    ) {
        swap(index, minChildHeapIndex);
        index = minChildHeapIndex;
        minChildHeapIndex = getMinChildIndex(index);
    }
}

void Heap::swap(byte index1, byte index2) {
    ASSERT_LE(0, index1);
    ASSERT_LE(0, index2);
    ASSERT_LT(index1, m_size);
    ASSERT_LT(index2, m_size);
    ASSERT_NE(index1, index2);
    byte temp = m_data[index1];
    m_data[index1] = m_data[index2];
    m_data[index2] = temp;
    Maze::info[m_data[index1]].heapIndex = index1;
    Maze::info[m_data[index2]].heapIndex = index2;
}

} // namespace mackAlgoTwo