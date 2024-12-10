#include <iostream>
#include <vector>
#include <memory>
#include <string>

class Part {
protected:
    std::string name_;
    Part(const std::string& name) : name_(name) {}

public:
    virtual void print() const { std::cout << "Part: " << name_ << std::endl; }
    virtual ~Part() = default;

    static std::unique_ptr<Part> create(const std::string& name) { // Part's factory method
        return std::unique_ptr<Part>(new Part(name));
    }
};

class Assembly : public Part {
protected:
    std::vector<std::unique_ptr<Part>> parts_;
    Assembly(const std::string& name) : Part(name) {}

public:
    void addPart(std::unique_ptr<Part> part) { parts_.push_back(std::move(part)); }
    void print() const override {
        std::cout << "Assembly: " << name_ << std::endl;
        for (const auto& part : parts_) {
            part->print();
        }
    }

    static std::unique_ptr<Assembly> create(const std::string& name) { // Assembly's factory method
        return std::unique_ptr<Assembly>(new Assembly(name));
    }
};

int main() {
    std::vector<std::unique_ptr<Part>> storage;

    storage.push_back(Part::create("Wheel"));               // Use Part::create
    storage.push_back(Assembly::create("Engine"));        // Use Assembly::create
    dynamic_cast<Assembly*>(storage.back().get())->addPart(Part::create("Piston"));
    dynamic_cast<Assembly*>(storage.back().get())->addPart(Part::create("Crankshaft"));
    storage.push_back(Assembly::create("Car"));
    dynamic_cast<Assembly*>(storage.back().get())->addPart(Assembly::create("Engine"));
    dynamic_cast<Assembly*>(storage.back().get())->addPart(Part::create("Wheel"));


    for (const auto& part : storage) {
        part->print();
    }

    return 0;
}
    
