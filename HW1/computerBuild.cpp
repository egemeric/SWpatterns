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
    Computer *computer;
    pcBuilder();
    pcBuilder &buildRam(float price, string brand, int size, int clockSpeed, int DDR_version);
    pcBuilder &buildCPU(float price, string brand, int clockSpeed, string architecture);
    pcBuilder &buildGPU(float price, string brand, int VMem, int Vclock);
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
    Computer()
    {
        cout << "Computer Class\n";
    };
    pcBuilder *buildPc()
    {
        pcBuilder *build;
        build = new pcBuilder();
        return build;
    };
};

class Component
{
protected:
    float price;
    string brand;
    int id;

public:
    static int ct;
    Component(float price, string brand)
    {
        ct++;
        this->id = ct;
        this->brand = brand;
        this->price = price;
    }
    float getPrice()
    {
        return this->price;
    }
    string getBrand()
    {
        return this->brand;
    }
    virtual void getDescription() = 0;
};
int Component::ct = 0;
class Ram : public Component
{
    int size;
    int clockSpeed;
    int DDR_version;

public:
    Ram(float price, string brand, int size, int clockSpeed, int DDR_version) : Component(price, brand)
    {
        cout << "RAM:";
        this->size = size;
        this->clockSpeed = clockSpeed;
        this->DDR_version = DDR_version;
    }

    void getDescription()
    {
        cout << "\nRam Description:\n";
        cout << "\tId:" << this->id << endl;
        cout << "\tBrand:" << this->brand << endl;
        cout << "\tPrice:" << this->price << " TL" << endl;
        cout << "\tSize:" << this->size << "GB" << endl;
    }
};

class GPU : public Component
{
    vector<GPU *> gpus;
    int VMem;
    int Vclock;

public:
    GPU(float price, string brand, int VMem, int Vclock) : Component(price, brand)
    {
        cout << "GPU:";
        this->VMem = VMem;
        this->Vclock = Vclock;
    }
    void getDescription()
    {
        cout << "\nGPU Description:\n";
        cout << "\tId:" << this->id << endl;
        cout << "\tBrand:" << this->brand << endl;
        cout << "\tPrice:" << this->price << " TL" << endl;
        cout << "\tVideo Memory:" << this->VMem << "GB" << endl;
        cout << "\tVideo Clock:" << this->Vclock << "Mhz" << endl;
    }
};
class CPU:public Component
{
    int clockSpeed;
    string architecture;

public:
    CPU(float price, string brand, int clockSpeed, string architecture): Component(price,brand)
    {
        cout << "CPU:";
        this->clockSpeed = clockSpeed;
        this->architecture = architecture;
    }
    void getDescription()
    {
        cout << "\nCPU Description:\n";
        cout << "\tId:" << this->id << endl;
        cout << "\tBrand:" << this->brand << endl;
        cout << "\tPrice:" << this->price << " TL" << endl;
        cout << "\tCpu Clock:" << this->clockSpeed << "Mhz" << endl;
        cout << "\tCpu Architecture" << this->architecture  << endl;
    }
};

class Storage
{
    string type;
    uint8_t size;

public:
    Storage()
    {
        cout << "Storage:";
    }
};
class MotherBoard
{
    string cpuPinType;
    uint8_t RamSlotCount;
    uint8_t PCI_ESpeed;

public:
    MotherBoard()
    {
        cout << "MotherBoard:";
    }
};

class PSU
{
    uint8_t poewer;

public:
    PSU()
    {
        cout << "PSU";
    }
};

//* PC builder
pcBuilder::pcBuilder()
{
    this->computer = new Computer();
    cout << "Build a pc:";
};

pcBuilder &pcBuilder::buildGPU(float price, string brand, int VMem, int Vclock)
{
    this->computer->gpu = new GPU(price, brand, VMem, Vclock);
    return *this;
}
pcBuilder &pcBuilder::buildCPU(float price, string brand, int clockSpeed, string architecture)
{
    this->computer->cpu = new CPU(price,brand,clockSpeed,architecture);
    return *this;
}

pcBuilder &pcBuilder::buildRam(float price, string brand, int size, int clockSpeed, int DDR_version)
{
    this->computer->ram = new Ram(price, brand, size, clockSpeed, DDR_version);
    return *this;
}

// End pc builder

class computerStore
{
    vector<Computer *> computers;

public:
    computerStore()
    {
        cout << "ComputerStore\n";
    }

    Computer *build()
    {
        pcBuilder *builder;
        builder = builder->computer->buildPc();
        builder
            ->buildRam(199, "hynix", 16, 4, 4)
            .buildGPU(1230, "Nvdia", 2, 1333)
            .buildCPU(2000,"Intel",20400,"x64");

        builder->computer->ram->getDescription();
        builder->computer->gpu->getDescription();
        builder->computer->cpu->getDescription();
        this->computers.push_back(builder->computer);
        return builder->computer;
    }
};

int main()
{
    computerStore *cs = new computerStore();
    Computer *pcb = new Computer();

    pcb = cs->build();
}
