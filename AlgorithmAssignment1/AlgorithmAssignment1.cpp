#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <time.h>
using namespace std;

class Shop
{
public:
    void SplitString(string line, int index);
    void Insert(int ID, string name, float price, string category);
    void Update(int ID, float price, string category);
    void Update(string name, float price, string category);
    void Delete(int ID);
    void Delete(string name);
    int Search(int ID);
    int Search(string name, int type);
    void Sort();

    list <int> IDs;
    list <string> names;
    list <float> prices;
    list <string> categories;

    Shop();
};

Shop::Shop() {}

void Shop::Insert(int ID, string name, float price, string category) 
{
    IDs.emplace_back(ID);
    names.emplace_back(name);
    prices.emplace_back(price);
    categories.emplace_back(category);
}

void Shop::Update(int ID, float price, string category)
{
    int index = Search(ID);

    auto it0 = std::next(prices.begin(), index);
    *it0 = price;

    auto it1 = std::next(categories.begin(), index);
    *it1 = category;
}

void Shop::Update(string name, float price, string category)
{
    int index = Search(name, 0);

    auto it0 = std::next(prices.begin(), index);
    *it0 = price;

    auto it1 = std::next(categories.begin(), index);
    *it1 = category;
}

void Shop::Delete(int ID)
{
    int index = Search(ID);

    auto it0 = std::next(names.begin(), index);
    auto it1 = std::next(prices.begin(), index);
    auto it2 = std::next(categories.begin(), index);

    IDs.remove(ID);
    names.remove(*it0);
    prices.remove(*it1);
    categories.remove(*it2);
}

void Shop::Delete(string name)
{
    int index = Search(name, 0);

    auto it0 = std::next(IDs.begin(), index);
    auto it1 = std::next(prices.begin(), index);
    auto it2 = std::next(categories.begin(), index);

    IDs.remove(*it0);
    names.remove(name);
    prices.remove(*it1);
    categories.remove(*it2);
}

int Shop::Search(int ID)
{
    int index = 0;
    for (int i = 0; i < IDs.size(); i++)
    {
        auto it = std::next(IDs.begin(), i);
        if (*it == ID)
        {
            index = i;
            break;
        }
    }

    return index;
}

int Shop::Search(string name, int type)
{
    int index = 0;

    for (int i = 0; i < IDs.size(); i++)
    {
        if (type == 0) {
            auto it = std::next(names.begin(), i);
            if (*it == name) {
                index = i;
                break;
            }
        }
        else if (type == 1)
        {
            auto it = std::next(categories.begin(), i);
            if (*it == name) {
                index = i;
                break;
            }
        }
    }
    return index;
}

void Shop::Sort()
{
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    bool inOrder = false;

    while (!inOrder)
    {
        inOrder = true;
        for (int i = 1; i < prices.size(); i++)
        {
            auto it0 = std::next(prices.begin(), i);
            auto it1 = std::next(prices.begin(), i - 1);
            auto it2 = std::next(IDs.begin(), i);
            auto it3 = std::next(IDs.begin(), i - 1);
            auto it4 = std::next(names.begin(), i);
            auto it5 = std::next(names.begin(), i - 1);
            auto it6 = std::next(categories.begin(), i);
            auto it7 = std::next(categories.begin(), i - 1);

            if (*it0 < *it1)
            {
                *it2 = *it2 + *it3;
                *it3 = *it2 - *it3;
                *it2 = *it2 - *it3;
                cout << to_string(*it3) << ", ";

                string temp = "";


                temp = *it4; 
                *it4 = *it5;
                *it5 = temp;
                cout << *it5 << ", ";

                *it0 = *it0 + *it1;
                *it1 = *it0 - *it1;
                *it0 = *it0 - *it1;
                cout << to_string(*it1) << ", ";

                temp = *it6;
                *it6 = *it7;
                *it7 = temp;
                cout << *it7 << "\n";

                inOrder = false;
            }
        }
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
}

void Shop::SplitString(string line, int index)
{
    int section = 0;
    string tempLine;
    for(int i = 0; i <= line.length(); i++)
    {
        if (line[i] == ',' || i == line.length())
        {
            switch (section)
            {
            case 0:
            {
                IDs.emplace_back(stoi(tempLine));
                break;
            }
            case 1: 
            {
                names.emplace_back(tempLine);
                break;
            }
            case 2: 
            {
                prices.emplace_back(stof(tempLine));
                break;
            }
            case 3:
            {
                categories.emplace_back(tempLine);
                break;
            }
            }
            tempLine = "";
            section++;
        }
        else
        {
            tempLine += line[i];
        }
    }
}

int main()
{
    //Initialization
    Shop shop;

    fstream rFile;
    rFile.open("product_data.txt");
    string line;

    int index = 0;
    while (getline(rFile, line))
    {
        shop.SplitString(line, index);
        index++;
    }

    rFile.close();

    shop.Insert(23013, " Knife Set VOAIW", 23.49, " Home & Kitchen");
    index = shop.Search(23013);
    auto it0 = std::next(shop.IDs.begin(), index);
    auto it1 = std::next(shop.names.begin(), index);
    auto it2 = std::next(shop.prices.begin(), index);
    auto it3 = std::next(shop.categories.begin(), index);

    cout << to_string(*it0) << *it1 << " " << to_string(*it2) << *it3;

    //Writing changes
    ofstream wFile("product_data.txt");

    string textFileText;
    for (int i = 0; i < shop.IDs.size(); i++) 
    {
        auto it0 = std::next(shop.IDs.begin(), i);
        textFileText += to_string(*it0);
        textFileText += ",";

        auto it1 = std::next(shop.names.begin(), i);
        textFileText += *it1;
        textFileText += ",";

        auto it2 = std::next(shop.prices.begin(), i);
        textFileText += to_string(*it2);
        textFileText += ",";

        auto it3 = std::next(shop.categories.begin(), i);
        textFileText += *it3;
        textFileText += "\n";
    }


    wFile << textFileText;

    wFile.close();

    return 0;
}