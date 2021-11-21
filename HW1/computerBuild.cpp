#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
class Ram;
class GPU;
class Storage;
class MotherBoard;
class PSU;
class CPU;
class Peripheral;
class Computer;
class pcBuilder
{
public:
    Computer *cmp;
    pcBuilder();
    pcBuilder &buildRam();
    pcBuilder &buildCPU();
    pcBuilder &buildGPU();
    pcBuilder &buildStorage();
    pcBuilder &buildMotherBoard();
    pcBuilder &buildPSU();
    ;
    pcBuilder &buildPeripheral();
};

class Computer
{

public:
    Ram *ram;
    GPU *gpu;
    CPU *cpu;
    Storage *storage;
    MotherBoard *mb;
    PSU *psu;
    Peripheral *peripheral;
    Computer() = default;
    pcBuilder *buildPc()
    {
        pcBuilder *build;
        build = new pcBuilder();
        return build;
    };
};

class Component {
    protected: 
    float price;
    string brand;
    public:
        Component(float price, string brand){
            this->brand = brand;
            this->price = price;
        }
        virtual float getPrice() = 0;
        virtual string getBrand() = 0;


};

class Ram : public Component
{
public:
    Ram(float price, string brand):Component(price,brand)
    {
        cout << "RAM:";
    }

    virtual float getPrice(){
        return this->price;
    }
    virtual string getBrand(){
        return this->brand;
    }
};

class GPU
{
public:
    GPU()
    {
        cout << "GPU:";
    }
};
class CPU
{
public:
    CPU()
    {
        cout << "CPU:";
    }
};

class Storage
{
public:
    Storage()
    {
        cout << "Storage:";
    }
};
class MotherBoard
{
public:
    MotherBoard()
    {
        cout << "MotherBoard:";
    }
};

class PSU
{

public:
    PSU()
    {
        cout << "PSU";
    }
};

//* PC builder
pcBuilder::pcBuilder()
{
    this->cmp = new Computer();
    cout << "Build a pc:";
};

pcBuilder &pcBuilder::buildGPU()
{
    this->cmp->gpu = new GPU();
    return *this;
}
pcBuilder &pcBuilder::buildCPU()
{
    this->cmp->cpu = new CPU();
    return *this;
}

pcBuilder &pcBuilder::buildRam(){
    this->cmp->ram= new Ram(0.2,"hynix");
    return *this;
}

// End pc builder

class computerStore
{
    vector<Computer *> computers;

public:
    computerStore()
    {
        __asm__("nop");
    }

    Computer *build()
    {
        Computer *cmp;
        cmp = new Computer();
        cmp->buildPc()->buildCPU().buildGPU();
        this->computers.push_back(cmp);
        return cmp;
    }
};

int main()
{
    computerStore *cs;
    Computer *pcb;
    cs = new computerStore();

    pcb = cs->build();
}
