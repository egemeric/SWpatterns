#include <iostream>
#include <algorithm>
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
    ~pcBuilder();
    pcBuilder &buildRam(float price, string brand, int size, int clockSpeed, int DDR_version);
    pcBuilder &buildCPU(float price, string brand, int clockSpeed, string architecture);
    pcBuilder &buildGPU(float price, string brand, int VMem, int Vclock);
    pcBuilder &buildStorage(float price, string brand, string type, int size);
    pcBuilder &buildMotherBoard();
    pcBuilder &buildPSU();
    pcBuilder &buildPeripheral();
};

template <typename T>
struct deleter : std::unary_function<const T *, void>
{
    void operator()(const T *ptr) const
    {
        delete ptr;
    }
};

class Computer
{

public:
    Ram *ram;
    vector<GPU *> gpu;
    CPU *cpu;
    vector<Storage *> storage;
    MotherBoard *mb;
    PSU *psu;
    Peripheral *peripheral;
    Computer()
    {
        
    };
    ~Computer()
    {
        std::for_each(this->gpu.begin(), this->gpu.end(), deleter<GPU>());
        deleter<Ram> ram;
        deleter<CPU> cpu;
        deleter<Storage> storage;
        deleter<MotherBoard> mb;
        deleter<PSU> psu;
        deleter<Peripheral> peripheral;
        gpu.clear();
    }
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
    ~Ram(){}

    void getDescription()
    {
        cout << "\n\tRam Description:\n";
        cout << "\tId:" << this->id << endl;
        cout << "\tBrand:" << this->brand << endl;
        cout << "\tPrice:" << this->price << " TL" << endl;
        cout << "\tSize:" << this->size << "GB" << endl;
    }
};

class GPU : public Component
{
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
        cout << "\n\tGPU Description:\n";
        cout << "\tId:" << this->id << endl;
        cout << "\tBrand:" << this->brand << endl;
        cout << "\tPrice:" << this->price << " TL" << endl;
        cout << "\tVideo Memory:" << this->VMem << "GB" << endl;
        cout << "\tVideo Clock:" << this->Vclock << "Mhz" << endl;
    }
};
class CPU : public Component
{
    int clockSpeed;
    string architecture;

public:
    CPU(float price, string brand, int clockSpeed, string architecture) : Component(price, brand)
    {
        cout << "CPU:";
        this->clockSpeed = clockSpeed;
        this->architecture = architecture;
    }
    void getDescription()
    {
        cout << "\n\tCPU Description:\n";
        cout << "\tId:" << this->id << endl;
        cout << "\tBrand:" << this->brand << endl;
        cout << "\tPrice:" << this->price << " TL" << endl;
        cout << "\tCpu Clock:" << this->clockSpeed << "Mhz" << endl;
        cout << "\tCpu Architecture" << this->architecture << endl;
    }
};

class Storage: public Component
{
    string type;
    int size;

public:
    Storage(float price, string brand, string type, int size): Component(price, brand)
    {
        cout << "Storage:";
        this->type = type;
        this->size = size;
    }
    void getDescription()
    {
        cout << "\n\tStorage Description:\n";
        cout << "\tId:" << this->id << endl;
        cout << "\tBrand:" << this->brand << endl;
        cout << "\tPrice:" << this->price << " TL" << endl;
        cout << "\tStorage Type:" << this->type << endl;
        cout << "\tStorage Size" << this->size<<"Gb"<< endl;
    }
};
class MotherBoard
{
    string cpuPinType;
    uint8_t RamSlotCount;
    uint8_t PCI_ESpeed;

public:
    /**
     * @brief Same WAY with CPU and RAM]
     * 
     */
    MotherBoard()
    {
        cout << "MotherBoard:";
    }
};

class PSU
{
    uint8_t power;

public:
    /**
     * @brief Construct a new PSU object  [Same WAY with CPU and RAM]
     * 
     */
    PSU()
    {
        cout << "PSU";
    }
};

class Peripheral
{
    string type;
    string extraInfo;

public:
    /**
     * @brief Construct a new Peripheral object  [Same WAY GPU and Storage]
     * 
     */
    Peripheral()
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

pcBuilder::~pcBuilder(){
    deleter<Computer> computer;
}

pcBuilder &pcBuilder::buildGPU(float price, string brand, int VMem, int Vclock)
{
    GPU *gpu = new GPU(price, brand, VMem, Vclock);
    this->computer->gpu.push_back(gpu);
    return *this;
}
pcBuilder &pcBuilder::buildStorage(float price, string brand, string type, int size)
{
    Storage *storage = new Storage(price, brand,type,size);
    this->computer->storage.push_back(storage);
    return *this;
}
pcBuilder &pcBuilder::buildCPU(float price, string brand, int clockSpeed, string architecture)
{
    this->computer->cpu = new CPU(price, brand, clockSpeed, architecture);
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

    ~computerStore(){
         std::for_each(this->computers.begin(), this->computers.end(), deleter<Computer>());
    }
    vector<Computer *> getComputers()
    {
        return this->computers;
    }

    /**
     * @brief  Create Computers hard coded (create 3 pc)
     * 
     * @return Computer*  Returns last added pc
     */
    Computer *build()
    {r *build()
    {
        pcBuilder *builder;
        builder = builder->computer->buildPc();
        builder
            ->buildRam(199, "hynix", 16, 4, 4)
            .buildGPU(1230, "Nvdia", 2, 1333)
            .buildGPU(2321, "AMD", 4, 1234)
            .buildStorage(123,"Toshiba","HDD",500)
            .buildStorage(500,"Sandisk","SSD",256)
            .buildCPU(2321, "Intel", 20400, "x64");
        this->computers.push_back(builder->computer);

        builder = builder->computer->buildPc();
        builder
        pcBuilder *builder;
        builder = builder->computer->buildPc();
        builder
            ->buildRam(199, "hynix", 16, 4, 4)
            .buildGPU(1230, "Nvdia", 2, 1333)
            .buildGPU(2321, "AMD", 4, 1234)
            .buildStorage(123,"Toshiba","HDD",500)
            .buildStorage(500,"Sandisk","SSD",256)
            .buildCPU(2321, "Intel", 20400, "x64");
        this->computers.push_back(builder->computer);

        builder = builder->computer->buildPc();
        builderr *build()
    {
        pcBuilder *builder;
        builder = builder->computer->buildPc();
        builder
            ->buildRam(199, "hynix", 16, 4, 4)
            .buildGPU(1230, "Nvdia", 2, 1333)
            .buildGPU(2321, "AMD", 4, 1234)
            .buildStorage(123,"Toshiba","HDD",500)
            .buildStorage(500,"Sandisk","SSD",256)
            .buildCPU(2321, "Intel", 20400, "x64");
        this->computers.push_back(builder->computer);

        builder = builder->computer->buildPc();
        builder
            ->buildRam(199, "hynix2", 16, 4, 4)
            .buildGPU(1230, "Nvdia2", 2, 1333)
            .buildGPU(2321, "AMD2", 4, 1234)
            .buildCPU(1000, "Intel2", 20400, "x64");
        this->computers.push_back(builder->computer);

        builder = builder->computer->buildPc();
        builder
            ->buildRam(199, "hynix3", 16, 4, 4)
            .buildGPU(1230, "Nvdia3", 2, 1333)
            .buildGPU(2321, "AMD3", 4, 1234)
            .buildCPU(5000, "Intel3", 20400, "x64");
        this->computers.push_back(builder->computer);

        return builder->computer;
    }
};

int main()
{
    computerStore *cs = new computerStore();
    cs->build();
    vector<Computer *> storeCatalog = cs->getComputers();
    cout <<"\n\n\tCOMPUTER STORE CATALOG\n";
    float pcPricetmp;
    for (vector<Computer *>::iterator it = storeCatalog.begin(); it != storeCatalog.end(); it++)
    {   
        pcPricetmp = 0;
        cout << "\n\t---------PC--------\n";
        (*it)->ram->getDescription();
        pcPricetmp += (*it)->ram->getPrice();
        (*it)->cpu->getDescription();
        pcPricetmp += (*it)->cpu->getPrice();
        for (vector<GPU *>::iterator itt = (*it)->gpu.begin(); itt != (*it)->gpu.end(); itt++)
        {
            (*itt)->getDescription();
            pcPricetmp += (*itt)->getPrice();
        }
         for (vector<Storage *>::iterator itt = (*it)->storage.begin(); itt != (*it)->storage.end(); itt++)
        {
            (*itt)->getDescription();
             pcPricetmp += (*itt)->getPrice();
        }
        cout<<"\nTOTAL PRICE: $"<<pcPricetmp;
        cout << "\n\t---------END PC---------\n";
    }
   //std::for_each(storeCatalog.begin(), storeCatalog.end(), deleter<Computer>());
   delete cs;

}
