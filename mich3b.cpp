#include <iostream>
#include <vector>
#include <random>
#include <memory>

class Base {
public:
    virtual ~Base() {}
    
    virtual void demonstrateBehavior() {
        std::cout << "Behavior of Base class" << std::endl;
    }
    
    virtual std::unique_ptr<Base> clone() const {
        return std::make_unique<Base>(*this);
    }
};

class Derived : public Base {
public:
    void demonstrateBehavior() override {
        std::cout << "Behavior of Derived class" << std::endl;
    }
    
    std::unique_ptr<Base> clone() const override {
        return std::make_unique<Derived>(*this);
    }
};

void add(std::unique_ptr<Base> item, std::vector<std::unique_ptr<Base>>& storage) {
    storage.push_back(std::move(item));
}

std::unique_ptr<Base> createRandomObject(std::mt19937& gen) {
    std::uniform_int_distribution<> distrib(0, 1);
    if (distrib(gen) == 0) {
        return std::make_unique<Base>();
    } else {
        return std::make_unique<Derived>();
    }
}

void demonstrateAndClone(const std::vector<std::unique_ptr<Base>>& storage) {
    for (const auto& item : storage) {
        item->demonstrateBehavior();
        std::unique_ptr<Base> clonedItem = item->clone();
        clonedItem->demonstrateBehavior();
    }
}

int main() {
    std::vector<std::unique_ptr<Base>> storage;
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int i = 0; i < 5; ++i) {
        add(createRandomObject(gen), storage);
    }
    
    demonstrateAndClone(storage);
    
    return 0;
}
