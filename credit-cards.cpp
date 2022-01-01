#include <iostream>
#include <regex>
#include <vector>
using namespace std;

class CredidCard
{
private:
    string CredidCardNumber;

protected:
    string getCardNumber();

public:
    CredidCard(string CredidCardNumber);
    ~CredidCard();
    virtual bool acceptCard() = 0;
};

CredidCard::CredidCard(string CredidCardNumber)
{
    regex removeNotNumber("[^0-9]");
    this->CredidCardNumber = regex_replace(CredidCardNumber, removeNotNumber, "");
}

CredidCard::~CredidCard()
{
}
string CredidCard::getCardNumber()
{
    return this->CredidCardNumber;
}

class Visa : public CredidCard
{

private:
public:
    const string RegexStr = "^4[0-9]{12}(?:[0-9]{3})?$";
    Visa(string CredidCardNumber);
    ~Visa();
    bool acceptCard();
};

Visa::Visa(string CredidCardNumber) : CredidCard(CredidCardNumber)
{
}

Visa::~Visa()
{
}

bool Visa::acceptCard()
{
    regex pattern(this->RegexStr);
    return regex_match(this->getCardNumber(), pattern);
}

class MasterCard : public CredidCard
{
private:
    /* data */
public:
    const string RegexStr = "^5[1-5][0-9]{14}$";
    MasterCard(string CredidCardNumber);
    ~MasterCard();
    bool acceptCard();
};

MasterCard::MasterCard(string CredidCardNumber) : CredidCard(CredidCardNumber)
{
}

MasterCard::~MasterCard()
{
}
bool MasterCard::acceptCard()
{
    regex pattern(this->RegexStr);
    return regex_match(this->getCardNumber(), pattern);
}

class Amex : public CredidCard
{
private:
    /* data */
public:
    const string RegexStr = "^3[47][0-9]{13}$";
    Amex(string CredidCardNumber);
    ~Amex();
    bool acceptCard();
};

Amex::Amex(string CredidCardNumber) : CredidCard(CredidCardNumber)
{
}

Amex::~Amex()
{
}
bool Amex::acceptCard()
{
    regex pattern(this->RegexStr);
    return regex_match(this->getCardNumber(), pattern);
}

class DinnersClub : public CredidCard
{
private:
    /* data */
public:
    const string RegexStr = "^3(?:0[0-5]|[68][0-9])[0-9]{11}$";
    DinnersClub(string CredidCardNumber);
    ~DinnersClub();
    bool acceptCard();
};

DinnersClub::DinnersClub(string CredidCardNumber) : CredidCard(CredidCardNumber)
{
}

DinnersClub::~DinnersClub()
{
}
bool DinnersClub::acceptCard()
{
    regex pattern(this->RegexStr);
    return regex_match(this->getCardNumber(), pattern);
}

int main()
{
    Visa a("4012 8888 8888 1881");
    if (a.acceptCard())
    {
        cout << "Visa";
    }
    else
    {
        cout << "none";
    }

    return 0;
}
