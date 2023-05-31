#include "doctest.h"
#include "sources/MagicalContainer.hpp"
#include <algorithm>

TEST_CASE("AscendingIterator Traversal") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    container.addElement(10);
    container.addElement(7);
    container.addElement(3);
    container.addElement(9);

    MagicalContainer::AscendingIterator ascIter(container);
    std::vector<int> elements;
    for (const auto &element: ascIter.begin()) {
        elements.push_back(element);
    }

    std::vector<int> expected{2, 3, 5, 7, 9, 10};
    CHECK_EQ(elements, expected);
}

TEST_CASE("SideCrossIterator Traversal") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    container.addElement(10);
    container.addElement(7);
    container.addElement(3);
    container.addElement(9);

    MagicalContainer::SideCrossIterator crossIter(container);
    std::vector<int> elements;
    for (const auto &element: crossIter.begin()) {
        elements.push_back(element);
    }

    std::vector<int> expected{5, 2, 10, 7, 3, 9, 10, 2, 7, 5};
    CHECK_EQ(elements, expected);
}

TEST_CASE("PrimeIterator Traversal") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    container.addElement(10);
    container.addElement(7);
    container.addElement(3);
    container.addElement(9);

    MagicalContainer::SideCrossIterator primeIter(container);
    std::vector<int> elements;
    for (const auto &element: primeIter.begin()) {
        elements.push_back(element);
    }

    std::vector<int> expected{2, 3, 5, 7};
    CHECK_EQ(elements, expected);
}

TEST_CASE("Empty Container Iterators") {
    MagicalContainer container;

    // AscendingIterator
    MagicalContainer::SideCrossIterator AscIter(container);
    std::vector<int> ascElements;
    for (const auto &element: AscIter.begin()) {
        ascElements.push_back(element);
    }
    CHECK(ascElements.empty());

    // SideCrossIterator
    MagicalContainer::SideCrossIterator crossIter(container);
    std::vector<int> sideCrossElements;
    for (const auto &element: crossIter.begin()) {
        sideCrossElements.push_back(element);
    }
    CHECK(sideCrossElements.empty());

    // PrimeIterator
    MagicalContainer::SideCrossIterator primeIter(container);
    std::vector<int> primeElements;
    for (const auto &element: primeIter.begin()) {
        primeElements.push_back(element);
    }
    CHECK(primeElements.empty());
}

TEST_CASE("Container Size") {

    MagicalContainer container;
    CHECK_EQ(container.size(), 0);

    container.addElement(5);
    container.addElement(2);
    container.addElement(10);
    CHECK_EQ(container.size(), 3);

    container.addElement(7);
    container.removeElement(5);
    CHECK_EQ(container.size(), 3);

    container.addElement(3);
    container.addElement(9);
    CHECK_EQ(container.size(), 5);

    container.removeElement(10);
    CHECK_EQ(container.size(), 4);
}

TEST_CASE("Container Modification during AscendingIterator Traversal") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    container.addElement(10);
    container.addElement(7);
    container.addElement(3);
    container.addElement(9);

    MagicalContainer::AscendingIterator ascIter(container);
    std::vector<int> elements;
    for (int it : ascIter) {
        elements.push_back(it);
        if (it == 10) {
            container.addElement(4);
            container.removeElement(2);
        }
    }

    std::vector<int> expected{2, 3, 4, 5, 7, 9, 10};
    CHECK_EQ(elements, expected);
}

TEST_CASE("Container Modification during SideCrossIterator Traversal") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    container.addElement(10);
    container.addElement(7);
    container.addElement(3);
    container.addElement(9);

    MagicalContainer::AscendingIterator crossIter(container);
    std::vector<int> elements;
    for (int it : crossIter) {
        elements.push_back(it);
        if (it == 10) {
            container.addElement(4);
            container.removeElement(5);
        }
    }

    std::vector<int> expected{5, 2, 10, 7, 3, 9, 4, 10, 2, 7};
    CHECK_EQ(elements, expected);
}

TEST_CASE("Container Modification during PrimeIterator Traversal") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    container.addElement(10);
    container.addElement(7);
    container.addElement(3);
    container.addElement(9);

    MagicalContainer::SideCrossIterator primeIter(container);
    std::vector<int> elements;
    for (auto it = primeIter.begin(); it != primeIter.end(); ++it) {
        elements.push_back(*it);
        if (*it == 2) {
            container.addElement(7);
            container.removeElement(5);
        }
    }

    std::vector<int> expected{2, 7};
    CHECK_EQ(elements, expected);
}


TEST_CASE("Greater Than Comparison between Iterators") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    container.addElement(10);
    MagicalContainer::AscendingIterator ascIter1(container);
    MagicalContainer::AscendingIterator ascIter2(container);
    CHECK_LT(ascIter1, ascIter2);
    ++ascIter1;
    CHECK_GT(ascIter1, ascIter2);
    ++ascIter2;
    CHECK_LT(ascIter1, ascIter2);
}

TEST_CASE("AscendingIterator Equality Comparison") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    container.addElement(10);
    MagicalContainer::AscendingIterator ascIter1(container);
    MagicalContainer::AscendingIterator ascIter2(container);
    CHECK_EQ(ascIter1, ascIter2);
    ++ascIter1;
    CHECK_EQ(ascIter1, ascIter2);
    ++ascIter2;
    CHECK_EQ(ascIter1, ascIter2);
}

TEST_CASE("AscendingIterator Inequality Comparison") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    container.addElement(10);
    MagicalContainer::AscendingIterator ascIter1(container);
    MagicalContainer::AscendingIterator ascIter2(container);
    CHECK_FALSE((ascIter1 != ascIter2));
    ++ascIter1;
    CHECK((ascIter1 != ascIter2));
    ++ascIter2;
    CHECK_FALSE((ascIter1 != ascIter2));
}

TEST_CASE("SideCrossIterator Equality Comparison") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    container.addElement(10);
    MagicalContainer::SideCrossIterator crossIter1(container);
    MagicalContainer::SideCrossIterator crossIter2(container);
    CHECK((crossIter1 == crossIter2));
    ++crossIter1;
    CHECK_FALSE((crossIter1 == crossIter2));
    ++crossIter2;
    CHECK((crossIter1 == crossIter2));
}

TEST_CASE("SideCrossIterator Inequality Comparison") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    container.addElement(10);
    MagicalContainer::SideCrossIterator crossIter1(container);
    MagicalContainer::SideCrossIterator crossIter2(container);
    CHECK_FALSE((crossIter1 != crossIter2));
    ++crossIter1;
    CHECK((crossIter1 != crossIter2));
    ++crossIter2;
    CHECK_FALSE((crossIter1 != crossIter2));
}

TEST_CASE("PrimeIterator Equality Comparison") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    container.addElement(10);
    MagicalContainer::PrimeIterator primeIter1(container);
    MagicalContainer::PrimeIterator primeIter2(container);
    CHECK_EQ(primeIter1, primeIter2);
    ++primeIter1;
    CHECK_NE(primeIter1, primeIter2);
    ++primeIter2;
    CHECK_EQ(primeIter1, primeIter2);
}

TEST_CASE("PrimeIterator Inequality Comparison") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    container.addElement(10);
    MagicalContainer::PrimeIterator primeIter1(container);
    MagicalContainer::PrimeIterator primeIter2(container);
    CHECK_FALSE((primeIter1 != primeIter2));
    ++primeIter1;
    CHECK((primeIter1 != primeIter2));
    ++primeIter2;
    CHECK_FALSE((primeIter1 != primeIter2));
}

TEST_CASE("AscendingIterator Begin and End Pointers") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    container.addElement(10);
    MagicalContainer::AscendingIterator ascIter(container);
    CHECK_EQ(ascIter.begin(), ascIter);

    int count = 0;
    for (auto it = ascIter.begin(); it != ascIter.end(); ++it) {
        ++count;
    }
    CHECK_EQ(count, 3);
}

TEST_CASE("SideCrossIterator Begin and End Pointers") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    container.addElement(10);
    MagicalContainer::SideCrossIterator crossIter(container);
    CHECK_EQ(crossIter.begin(), crossIter);

    // Calculate the distance manually
    int count = 0;
    for (auto it = crossIter.begin(); it != crossIter.end(); ++it) {
        ++count;
    }
    CHECK_EQ(count, 3);
}

TEST_CASE("PrimeIterator Begin and End Pointers") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    container.addElement(10);
    MagicalContainer::PrimeIterator primeIter(container);
    CHECK_EQ(primeIter.begin(), primeIter);
    // Calculate the distance manually
    int count = 0;
    for (auto it = primeIter.begin(); it != primeIter.end(); ++it) {
        ++count;
    }
    CHECK_EQ(count, 2);
}

TEST_CASE("AscendingIterator Dereference Operator") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    MagicalContainer::AscendingIterator ascIter(container);
    CHECK_EQ(*ascIter, 2);
    ++ascIter;
    CHECK_EQ(*ascIter, 5);
}

TEST_CASE("SideCrossIterator Dereference Operator") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    MagicalContainer::SideCrossIterator crossIter(container);
    CHECK_EQ(*crossIter, 2);
    ++crossIter;
    CHECK_EQ(*crossIter, 5);
}

TEST_CASE("PrimeIterator Dereference Operator") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    container.addElement(10);
    MagicalContainer::PrimeIterator primeIter(container);
    CHECK_EQ(*primeIter, 2);
    ++primeIter;
    CHECK_EQ(*primeIter, 5);
}

TEST_CASE("Empty Container - AscendingIterator") {
    MagicalContainer container;
    MagicalContainer::AscendingIterator ascIter(container);

    CHECK_EQ(ascIter.begin(), ascIter.end());

    CHECK_THROWS(++ascIter);
    CHECK_THROWS(*ascIter);
}

TEST_CASE("Empty Container - SideCrossIterator") {
    MagicalContainer container;
    MagicalContainer::SideCrossIterator crossIter(container);

    CHECK_EQ(crossIter.begin(), crossIter.end());

    CHECK_THROWS(++crossIter);
    CHECK_THROWS(*crossIter);
}

TEST_CASE("Empty Container - PrimeIterator") {
    MagicalContainer container;
    MagicalContainer::PrimeIterator primeIter(container);

    CHECK_EQ(primeIter.begin(), primeIter.end());

    CHECK_THROWS(++primeIter);
    CHECK_THROWS(*primeIter);
}

TEST_CASE("AscendingIterator with Single Element") {
    MagicalContainer container;
    container.addElement(5);
    MagicalContainer::AscendingIterator ascIter(container);

    CHECK_EQ(*ascIter, 5);

    ++ascIter;
    CHECK_EQ(ascIter.begin(), ascIter.end());
    CHECK_THROWS(++ascIter);
    CHECK_THROWS(*ascIter);
}

TEST_CASE("SideCrossIterator with Single Element") {
    MagicalContainer container;
    container.addElement(5);
    MagicalContainer::SideCrossIterator crossIter(container);

    CHECK_EQ(*crossIter, 5);

    ++crossIter;
    CHECK_EQ(crossIter.begin(), crossIter.end());
    CHECK_THROWS(++crossIter);
    CHECK_THROWS(*crossIter);
}

TEST_CASE("PrimeIterator with Single Element") {
    MagicalContainer container;
    container.addElement(5);
    MagicalContainer::PrimeIterator primeIter(container);

    CHECK_EQ(*primeIter, 5);

    ++primeIter;
    CHECK_EQ(primeIter.begin(), primeIter.end());
    CHECK_THROWS(++primeIter);
    CHECK_THROWS(*primeIter);
}

TEST_CASE("Remove Element while Iterating - AscendingIterator") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    container.addElement(10);
    MagicalContainer::AscendingIterator ascIter(container);

    CHECK_EQ(*ascIter, 2);

    container.removeElement(2);

    CHECK_EQ(*ascIter, 5);

    ++ascIter;
    CHECK_EQ(*ascIter, 10);

    ++ascIter;
    CHECK_EQ(ascIter.begin(), ascIter.end());
    CHECK_THROWS(++ascIter);
    CHECK_THROWS(*ascIter);
}

TEST_CASE("Remove Element while Iterating - SideCrossIterator") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    container.addElement(10);
    MagicalContainer::SideCrossIterator crossIter(container);

    CHECK_EQ(*crossIter, 2);

    container.removeElement(2);

    CHECK_EQ(*crossIter, 5);

    ++crossIter;
    CHECK_EQ(*crossIter, 10);

    ++crossIter;
    CHECK_EQ(crossIter.begin(), crossIter.end());
    CHECK_THROWS(++crossIter);
    CHECK_THROWS(*crossIter);
}

TEST_CASE("Remove Element while Iterating - PrimeIterator") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    container.addElement(10);
    MagicalContainer::PrimeIterator primeIter(container);

    CHECK_EQ(*primeIter, 2);

    container.removeElement(2);

    CHECK_EQ(*primeIter, 5);

    ++primeIter;
    CHECK_EQ(primeIter.begin(), primeIter.end());
    CHECK_THROWS(++primeIter);
    CHECK_THROWS(*primeIter);
}

TEST_CASE("Add Element while Iterating - AscendingIterator") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    MagicalContainer::AscendingIterator ascIter(container);

    CHECK_EQ(*ascIter, 2);

    container.addElement(3);

    ++ascIter;
    CHECK_EQ(*ascIter, 3);

    ++ascIter;
    CHECK_EQ(*ascIter, 5);

    ++ascIter;
    CHECK_EQ(ascIter.begin(), ascIter.end());
    CHECK_THROWS(++ascIter);
    CHECK_THROWS(*ascIter);
}

TEST_CASE("Add Element while Iterating - SideCrossIterator") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    MagicalContainer::SideCrossIterator crossIter(container);

    CHECK_EQ(*crossIter, 2);

    container.addElement(3);

    ++crossIter;
    CHECK_EQ(*crossIter, 3);

    ++crossIter;
    CHECK_EQ(*crossIter, 5);

    ++crossIter;
    CHECK_EQ(crossIter.begin(), crossIter.end());
    CHECK_THROWS(++crossIter);
    CHECK_THROWS(*crossIter);
}

TEST_CASE("Add Element while Iterating - PrimeIterator") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(2);
    MagicalContainer::PrimeIterator primeIter(container);

    CHECK_EQ(*primeIter, 2);

    container.addElement(3);

    ++primeIter;
    CHECK_EQ(*primeIter, 3);

    ++primeIter;
    CHECK_EQ(*primeIter, 5);

    ++primeIter;
    CHECK_EQ(primeIter.begin(), primeIter.end());
    CHECK_THROWS(++primeIter);
    CHECK_THROWS(*primeIter);
}


