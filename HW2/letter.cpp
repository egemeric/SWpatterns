#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h> //cross platform

#define LINELENGTH 60

using namespace std;
class LetterBody;
class Paragraph
{
    string paragraph;

public:
    Paragraph(string paragraph)
    {
        this->paragraph = paragraph;
    }
    ~Paragraph()
    {
    }

    string getContent()
    {
        return this->paragraph;
    }
};

const std::string currentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    // http://en.cppreference.com/w/cpp/chrono/c/strftime
    strftime(buf, sizeof(buf), " %d-%m-%Y %X%Z", &tstruct);

    return buf;
}
enum Position
{
    LEFT,
    CENTER,
    RIGHT
};

void formatedprint(Position pos, string s, int linelength)
{
    int spaces = 0;
    switch (pos)
    {
    case CENTER:
        spaces = (linelength - s.size()) / 2;
        break;
    case RIGHT:
        spaces = linelength - s.size();
        break;
    }
    if (spaces > 0)
        cout << string(spaces, ' ');
    cout << s << '\n';
}

class Letter
{
    string header, author, user, timeModified;
    vector<LetterBody *> letterbody;

public:
    Letter();
    Letter(string header, string author, string user);
    ~Letter();
    virtual void addComponent(LetterBody *letterBody);
    virtual void print();
};

class LetterBody : public Letter
{
    vector<Paragraph *> paragraphs;

public:
    LetterBody();
    ~LetterBody();
    virtual void addComponent(Paragraph *paragraph);
    virtual void print();
};

//

Letter::Letter()
{
    this->timeModified = currentDateTime();
}
Letter::Letter(string header, string author, string user)
{
    this->timeModified = currentDateTime();
    this->header = header;
    this->author = author;
    this->user = user;
}
Letter::~Letter()
{
    for (int i = 0; i < this->letterbody.size(); i++)
    {
        delete this->letterbody[i];
    }
    this->letterbody.clear();
}

void Letter::addComponent(LetterBody *letterBody)
{
    this->letterbody.push_back(letterBody);
}

void Letter::print()
{
    string header(LINELENGTH, '=');
    cout << header << "\n";
    formatedprint(RIGHT, this->timeModified, LINELENGTH);
    formatedprint(CENTER, this->header, LINELENGTH);
    cout << "Dear " << this->user << ",\n\n";
    for (vector<LetterBody *>::iterator it = this->letterbody.begin(); it != this->letterbody.end(); it++)
    {
        (*it)->print();
    }
    cout << "Best regards,\n"
         << this->author << endl;
    cout << header << "\n";
}

LetterBody::LetterBody() : Letter()
{
}
LetterBody::~LetterBody()
{

    for (int i = 0; i < this->paragraphs.size(); i++)
    {
        delete this->paragraphs[i];
    }
    this->paragraphs.clear();

}
void LetterBody::addComponent(Paragraph *paragraph)
{
    this->paragraphs.push_back(paragraph);
}
void LetterBody::print()
{
    int pra_len = 0;
    string para = "";
    for (vector<Paragraph *>::iterator it = paragraphs.begin(); it != paragraphs.end(); it++)
    {
        pra_len = (*it)->getContent().length();
        para = (*it)->getContent();
        for (int i = 0; i < pra_len; i++)
        {
            cout << para[i];
            if ((i % LINELENGTH) == LINELENGTH - 1)
            {
                cout << endl;
            }
        }
        cout << "\n\n";
    }
}

int main()
{
    string paragraph1 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque varius quam vel purus tristique, sit amet sodales nulla pulvinar. Morbi tincidunt erat elit, in bibendum est sodales vitae. Ut varius massa nec dolor sodales, in interdum mauris luctus. Phasellus mollis, risus iaculis congue posuere, nunc diam posuere quam, vitae pellentesque ex nunc in eros. Aenean eleifend maximus sem, a semper lacus tempus at. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Proin molestie eros eu justo iaculis consequat. Maecenas gravida aliquam nunc vel feugiat. Vivamus a nisl eros. Suspendisse turpis augue, mollis sed augue nec, ullamcorper cursus ipsum. Donec arcu justo, varius quis dolor at, eleifend pretium massa. Fusce ullamcorper cursus felis id ultricies. Donec ut aliquam mauris. Suspendisse potenti.";
    string paragraph2 = "Curabitur eu laoreet ex. Aenean ullamcorper nulla sed malesuada sollicitudin. Duis non nulla elementum justo pellentesque placerat. In varius odio eget est viverra tempus. Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Mauris sit amet dui nunc. Sed varius ipsum felis, sit amet rhoncus mauris dapibus vitae. Aenean non ex vitae lacus cursus pellentesque. Nullam posuere odio eget laoreet rutrum. Donec tempus tempus vehicula. Proin eget placerat turpis. Curabitur ac massa felis. Mauris vitae lorem ante. Ut nisi nunc, feugiat eu vehicula eget, dapibus semper ipsum. Aenean est sapien, luctus sit amet risus ut, ullamcorper varius neque.";
    string paragraph3 = "Mauris eu mauris mollis risus sagittis tempus ut in dui. In ornare convallis velit, ac sagittis massa. Integer vulputate a magna non elementum. Etiam at tincidunt orci. Sed efficitur velit diam. Nullam eu massa eu lectus convallis blandit vel sit amet sem. Proin iaculis, dui nec laoreet consequat, augue dui tempor augue, eget iaculis dui eros sit amet diam. Vivamus auctor vulputate scelerisque. Phasellus placerat lectus dui, vel varius nisl maximus a. Etiam sollicitudin augue eu neque finibus, vitae dignissim elit aliquet. Duis tellus turpis, scelerisque eget tincidunt a, ornare sed nisl. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Fusce finibus nisl sed tortor viverra commodo.";
    Paragraph par1(paragraph1);
    Paragraph par2(paragraph2);
    Paragraph par3(paragraph3);
    LetterBody *letterBody = new LetterBody();
    letterBody->addComponent(&par1);
    letterBody->addComponent(&par2);
    letterBody->addComponent(&par3);
    Letter *letter = new Letter("SWPatterns", "Ege Meric Erdogan", "Tolga Ustunkok");
    letter->addComponent(letterBody);
    letter->print();
 
}