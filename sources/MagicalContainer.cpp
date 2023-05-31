#include <stdexcept>
#include "MagicalContainer.hpp"

void MagicalContainer::addElement(int element) {
    elements.push_back(element);
    std::sort(elements.begin(), elements.end());
}

void MagicalContainer::removeElement(int element) {
    elements.erase(std::remove(elements.begin(), elements.end(), element), elements.end());
    std::sort(elements.begin(), elements.end());
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
                                                       int backwardIndex, bool forwardDir, int counter)
        : container(cont), forwardIndex(forwardIndex), backwardIndex(backwardIndex),
          forwardDirection(forwardDir) ,counter(counter){}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const {
    return SideCrossIterator(container, 0, container.size() - 1, true);
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const {
    return SideCrossIterator(container, container.size(), 0, false);
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {

    if (forwardDirection) {
        ++forwardIndex;
    } else {
        --backwardIndex;
    }
    forwardDirection = !forwardDirection;
    ++counter;

    // Check if the counter reaches a specific value
    if (counter >= container.size()) {
        forwardIndex = container.size();
        backwardIndex = 0;
    }

    return *this;
}

int MagicalContainer::SideCrossIterator::operator*() const {

    if(forwardIndex >= container.size() || backwardIndex < 0) {
        throw std::out_of_range("Iterator out of range.");
    }

    if (forwardDirection) {
        return container.elements[static_cast<std::vector<int>::size_type>(forwardIndex)];
    }
    else {
        return container.elements[static_cast<std::vector<int>::size_type>(backwardIndex)];
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

