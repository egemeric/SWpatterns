#include <iostream>
#include <regex>
using namespace std;

class CredidCard
{
private:
    string CredidCardNumber;

protected:
    string getCardNumber();
    string CardType = "";
    bool isValid = false;

public:
    CredidCard(string CredidCardNumber);
    ~CredidCard();
    virtual bool acceptCard() = 0;
    virtual void describeCard() = 0;
    string getCardType();
    static string returnCardNoIndex(string str, int start, int end);
};

string CredidCard::returnCardNoIndex(string str, int start, int end)
{

    string result = "";
    for (int i = start-1; i < end; i++)
    {
        result += str.at(i);
    }
    return result;
}

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

string CredidCard::getCardType()
{
    return this->CardType;
}

class Visa : public CredidCard
{

private:
public:
    const int bankNoIndex[2] = {2, 6};
    const int accountNoIndex[2][2] = {{7, 12}, {7, 15}};
    const int checkDigits[2] = {13, 16};
    const string RegexStr = "^4[0-9]{12}(?:[0-9]{3})?$";
    Visa(string CredidCardNumber);
    ~Visa();
    virtual bool acceptCard();
    virtual void describeCard();
};

Visa::Visa(string CredidCardNumber) : CredidCard(CredidCardNumber)
{
    regex pattern(this->RegexStr);
    this->isValid = regex_match(this->getCardNumber(), pattern);
    this->isValid ? this->CardType = "Visa" : this->CardType = "Undefined";
}

Visa::~Visa()
{
}

bool Visa::acceptCard()
{
    return this->isValid;
}

void Visa::describeCard()
{
    string cardNo = this->getCardNumber();
    cout << "Possible Bank numbers:";
    for (int i = bankNoIndex[0] - 1; i < bankNoIndex[1]; i++)
    {
        cout << cardNo.at(i);
    }
    cout << endl
         << "Possible account numbers:";
    for (int i = accountNoIndex[0][0] - 1; i < accountNoIndex[0][1]; i++)
    {
        cout << cardNo.at(i);
    }
    cout << ", ";
    for (int i = accountNoIndex[1][0] - 1; i < accountNoIndex[1][1]; i++)
    {
        cout << cardNo.at(i);
    }
    cout << endl
         << "Possible check Digits: ";
    cout << cardNo.at(checkDigits[0] - 1) << ", " << cardNo.at(checkDigits[1] - 1) << endl;
}

class MasterCard : public CredidCard
{
private:
    /* data */
public:
    const int bankNoIndex[4][2] = {{2, 3}, {2, 4}, {2, 5}, {2, 6}};
    const int checkDigit = 16;
    const string RegexStr = "^5[1-5][0-9]{5,}|222[1-9][0-9]{3,}|22[3-9][0-9]{4,}|2[3-6][0-9]{5,}|27[01][0-9]{4,}|2720[0-9]{3,}$";
    MasterCard(string CredidCardNumber);
    ~MasterCard();
    virtual bool acceptCard();
    virtual void describeCard();
};

MasterCard::MasterCard(string CredidCardNumber) : CredidCard(CredidCardNumber)
{
    regex pattern(this->RegexStr);
    this->isValid = regex_match(this->getCardNumber(), pattern);
    this->isValid ? this->CardType = "MasterCard" : this->CardType = "Undefined";
}

MasterCard::~MasterCard()
{
}
bool MasterCard::acceptCard()
{
    return this->isValid;
}

void MasterCard::describeCard()
{
    string cardNo = this->getCardNumber();
    int banknoDepend = int(cardNo.at(1));
    int guessBank[2];
    switch (banknoDepend)
    {
    case 1:
        copy(begin(this->bankNoIndex[0]), end(this->bankNoIndex[0]), begin(guessBank));
        break;
    case 2:
        copy(begin(this->bankNoIndex[1]), end(this->bankNoIndex[1]), begin(guessBank));
        break;
    case 3:
        copy(begin(this->bankNoIndex[2]), end(this->bankNoIndex[2]), begin(guessBank));
        break;
    default:
        copy(begin(this->bankNoIndex[3]), end(this->bankNoIndex[3]), begin(guessBank));
        break;
    }

    cout<< "Possible Bank Numbers: "<< CredidCard::returnCardNoIndex(cardNo,guessBank[0],guessBank[1])<<endl;
    cout<< "Account Number: "<<CredidCard::returnCardNoIndex(cardNo,guessBank[1],checkDigit)<<endl;
    cout<<"Check Digit: "<< cardNo.at(checkDigit-1)<<endl;
}

class Amex : public CredidCard
{
private:
    /* data */
public:
    const int currency[2] = {3, 4};
    const int cardNoIndex[2] = {12, 14};
    const int accountNoIndex[2] = {5, 11};
    const int checkDigits[1] = {15};
    const string RegexStr = "^3[47][0-9]{13}$";
    Amex(string CredidCardNumber);
    ~Amex();
    virtual bool acceptCard();
    virtual void describeCard();
};

Amex::Amex(string CredidCardNumber) : CredidCard(CredidCardNumber)
{
    regex pattern(this->RegexStr);
    this->isValid = regex_match(this->getCardNumber(), pattern);
    this->isValid ? this->CardType = "AmericanExpress" : this->CardType = "Undefined";
}

Amex::~Amex()
{
}
bool Amex::acceptCard()
{
    return this->isValid;
}

void Amex::describeCard()
{
    string cardNo = this->getCardNumber();
    cout << "Currency Digits: " << cardNo.at(currency[0] - 1) << cardNo.at(currency[0] - 1) << endl;
    cout << "Account number: ";
    for (int i = accountNoIndex[0]; i < accountNoIndex[1]; i++)
    {
        cout << cardNo.at(i);
    }
    cout << endl
         << "Card No:";
    for (int i = cardNoIndex[0] - 1; i < cardNoIndex[1]; i++)
    {
        cout << cardNo.at(i);
    }
    cout << endl
         << "Account number: ";

    for (int i = accountNoIndex[0] - 1; i < accountNoIndex[1]; i++)
    {
        cout << cardNo.at(i);
    }

    cout << endl
         << "Check Digit: " << cardNo.at(checkDigits[0] - 1) << endl;
    ;
}

class DinnersClub : public CredidCard
{
private:
    /* data */
public:
    const string RegexStr = "^3(?:0[0-5]|[68][0-9])[0-9]{11}$";
    DinnersClub(string CredidCardNumber);
    ~DinnersClub();
    virtual bool acceptCard();
    virtual void describeCard();
};

DinnersClub::DinnersClub(string CredidCardNumber) : CredidCard(CredidCardNumber)
{
    regex pattern(this->RegexStr);
    this->isValid = regex_match(this->getCardNumber(), pattern);
    this->isValid ? this->CardType = "DinnersClub" : this->CardType = "Undefined";
}

DinnersClub::~DinnersClub()
{
}
bool DinnersClub::acceptCard()
{
    return this->isValid;
}

void DinnersClub::describeCard()
{
}

class Context
{
private:
    CredidCard *card;

public:
    Context(/* args */);
    ~Context();
    bool ValidateCard();
    void SetCard(CredidCard *card); // set strategy to find card type;
};
Context::Context(/* args */)
{
}
Context::~Context()
{
}
bool Context::ValidateCard()
{
    if (this->card->acceptCard())
    {
        cout << "Card Type:" << this->card->getCardType() << endl;
        this->card->describeCard();
        return true;
    }
    else
    {
        return false;
    }
}

void Context::SetCard(CredidCard *card)
{
    delete this->card;
    this->card = card;
}

int main()
{
    Context *context = new Context();
    CredidCard *card;
    string CardNumber;
    cout << "Enter Card Number:";
    getline(cin, CardNumber);
    CredidCard *cardTypes[] = {new Visa(CardNumber), new MasterCard(CardNumber), new Amex(CardNumber), new DinnersClub(CardNumber)};
    int arrSize = *(&cardTypes + 1) - cardTypes;

    for (int i = 0; i < arrSize; i++)
    {
        context->SetCard(cardTypes[i]);
        if (context->ValidateCard())
        {
            card = cardTypes[i];
            break;
        }
    }
}
