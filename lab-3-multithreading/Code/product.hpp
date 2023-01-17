
#pragma once
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

static int ID = 0;

class Product {
    friend class Shop;

    public:

    Product(){};
    Product(string name){
        _id = ID++;
        _name = name;
        if (_name == "A") _price = 1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(10-1)));
        else _price = 10 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(20-10)));
    }

    private:
    
    int _id;
    string _name;
    float _price;
};

// int ID = 0;

// struct Product{
//     int id;
//     string Name;
//     float price;
// };

// Product GetProductA(){
//     Product tmp;
//     tmp.id = ID++;
//     tmp.Name = 'A';
//     tmp.price = 1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(10-1)));;
//     return tmp;
// }

// Product GetProductB(){
//     Product tmp;
//     tmp.id = ID++;
//     tmp.Name = 'B';
//     tmp.price = 10 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(20-10)));;
//     return tmp;
// }

