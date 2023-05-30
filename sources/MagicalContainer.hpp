#ifndef MAGICALCONTAINER_H
#define MAGICALCONTAINER_H

#include <vector>
#include <cmath>
#include <algorithm>

namespace ariel {}
class MagicalContainer {
private:
    std::vector<int> elements;

public:
    void addElement(int element);

    void removeElement(int element);

    [[nodiscard]] int size() const;

    class AscendingIterator;

    class SideCrossIterator;

    class PrimeIterator;

    [[nodiscard]] AscendingIterator beginAscending() const;

    [[nodiscard]] AscendingIterator endAscending() const;

    [[nodiscard]] SideCrossIterator beginCross() const;

    [[nodiscard]] SideCrossIterator endCross() const;

    [[nodiscard]] PrimeIterator beginPrime() const;

    [[nodiscard]] PrimeIterator endPrime() const;
};

class MagicalContainer::AscendingIterator {
private:
    const MagicalContainer &container;
    int currentIndex;

public:
    explicit AscendingIterator(const MagicalContainer &cont, int index = 0);

    [[nodiscard]] AscendingIterator begin() const;

    [[nodiscard]] AscendingIterator end() const;

    AscendingIterator &operator++();

    int operator*() const;

    bool operator==(const AscendingIterator &other) const;

    bool operator!=(const AscendingIterator &other) const;

    bool operator>(const AscendingIterator &other) const;

    bool operator<(const AscendingIterator &other) const;
};

class MagicalContainer::SideCrossIterator {
private:
    const MagicalContainer &container;
    int forwardIndex;
    int backwardIndex;
    bool forwardDirection;

public:
    explicit SideCrossIterator(const MagicalContainer &cont, int forwardIndex = 0, int backwardIndex = 0,
                               bool forwardDir = true);

    [[nodiscard]] SideCrossIterator begin() const;

    [[nodiscard]] SideCrossIterator end() const;

    SideCrossIterator &operator++();

    int operator*() const;

    bool operator==(const SideCrossIterator &other) const;

    bool operator!=(const SideCrossIterator &other) const;

    bool operator>(const SideCrossIterator &other) const;

    bool operator<(const SideCrossIterator &other) const;
};

class MagicalContainer::PrimeIterator {
private:
    const MagicalContainer &container;
    int currentIndex;

    [[nodiscard]] static bool isPrime(int number) ;

public:
    explicit PrimeIterator(const MagicalContainer &cont, int index = 0);

    [[nodiscard]] PrimeIterator begin() const;

    [[nodiscard]] PrimeIterator end() const;

    PrimeIterator &operator++();

    int operator*() const;

    bool operator==(const PrimeIterator &other) const;

    bool operator!=(const PrimeIterator &other) const;

    bool operator>(const PrimeIterator &other) const;

    bool operator<(const PrimeIterator &other) const;
};


#endif  // MAGICALCONTAINER_H
