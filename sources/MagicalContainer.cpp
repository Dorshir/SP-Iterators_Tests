#include <stdexcept>
#include "MagicalContainer.hpp"

void MagicalContainer::addElement(int element) {
    elements.push_back(element);
}

void MagicalContainer::removeElement(int element) {
    elements.erase(std::remove(elements.begin(), elements.end(), element), elements.end());
}

int MagicalContainer::size() const {
    return elements.size();
}

// AscendingIterator

MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer& cont, int index)
        : container(cont), currentIndex(index) {}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() const {
    return AscendingIterator(container, 0);
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() const {
    return AscendingIterator(container, container.size());
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
    ++currentIndex;
    return *this;
}

int MagicalContainer::AscendingIterator::operator*() const {
    if (currentIndex >= container.size()) {
        throw std::out_of_range("Iterator out of range.");
    }
    return container.elements[static_cast<std::vector<int>::size_type>(currentIndex)];
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const {
    return currentIndex == other.currentIndex;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const {
    return currentIndex != other.currentIndex;
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const {
    return currentIndex > other.currentIndex;
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const {
    return currentIndex < other.currentIndex;
}

// SideCrossIterator

MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer& cont, int forwardIndex,
                                                       int backwardIndex, bool forwardDir)
        : container(cont), forwardIndex(forwardIndex), backwardIndex(backwardIndex),
          forwardDirection(forwardDir) {}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const {
    return SideCrossIterator(container, 0, container.size() - 1, true);
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const {
    return SideCrossIterator(container, container.size(), container.size() - 1, true);
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
    if (forwardDirection) {
        ++forwardIndex;
    }
    else {
        --backwardIndex;
    }
    return *this;
}

int MagicalContainer::SideCrossIterator::operator*() const {
    if (forwardIndex >= container.size()) {
        throw std::out_of_range("Iterator out of range.");
    }
    if (forwardIndex < backwardIndex) {
        return container.elements[static_cast<std::vector<int>::size_type>(forwardIndex)];
    }
    else if (forwardIndex > backwardIndex) {
        return container.elements[static_cast<std::vector<int>::size_type>(backwardIndex)];
    }
    else {
        return container.elements[static_cast<std::vector<int>::size_type>(forwardIndex)];
    }
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const {
    return forwardIndex == other.forwardIndex && backwardIndex == other.backwardIndex &&
           forwardDirection == other.forwardDirection;
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const {
    return forwardIndex != other.forwardIndex || backwardIndex != other.backwardIndex ||
           forwardDirection != other.forwardDirection;
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const {
    return forwardIndex > other.forwardIndex && backwardIndex > other.backwardIndex;
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const {
    return forwardIndex < other.forwardIndex && backwardIndex < other.backwardIndex;
}

// PrimeIterator

bool MagicalContainer::PrimeIterator::isPrime(int number) {
    if (number < 2) {
        return false;
    }
    double sqrtNum = std::sqrt(number);
    for (int i = 2; i <= sqrtNum; ++i) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer& cont, int index)
        : container(cont), currentIndex(index) {}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const {
    return PrimeIterator(container, 0);
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const {
    return PrimeIterator(container, container.size());
}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
    do {
        ++currentIndex;
    } while (currentIndex < container.size() && !isPrime(container.elements[static_cast<std::vector<int>::size_type>(currentIndex)]));
    return *this;
}

int MagicalContainer::PrimeIterator::operator*() const {
    if (currentIndex >= container.size()) {
        throw std::out_of_range("Iterator out of range.");
    }
    return container.elements[static_cast<std::vector<int>::size_type>(currentIndex)];
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const {
    return currentIndex == other.currentIndex;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const {
    return currentIndex != other.currentIndex;
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const {
    return currentIndex > other.currentIndex;
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const {
    return currentIndex < other.currentIndex;
}

// Begin and End functions for iterators

MagicalContainer::AscendingIterator MagicalContainer::beginAscending() const {
    return AscendingIterator(*this, 0);
}

MagicalContainer::AscendingIterator MagicalContainer::endAscending() const {
    return AscendingIterator(*this, size());
}

MagicalContainer::SideCrossIterator MagicalContainer::beginCross() const {
    return SideCrossIterator(*this, 0, size() - 1, true);
}

MagicalContainer::SideCrossIterator MagicalContainer::endCross() const {
    return SideCrossIterator(*this, size(), size() - 1, true);
}

MagicalContainer::PrimeIterator MagicalContainer::beginPrime() const {
    return PrimeIterator(*this, 0);
}

MagicalContainer::PrimeIterator MagicalContainer::endPrime() const {
    return PrimeIterator(*this, size());
}
