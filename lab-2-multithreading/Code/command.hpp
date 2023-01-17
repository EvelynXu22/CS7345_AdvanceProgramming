#pragma once

class Machine;
class Shop;
class People;

class Command{
    public:
    typedef void(Machine:: *Callback)();
    Machine* object;
    Callback method;

    typedef void(People:: *Callback_2)();
    People* object_2;
    Callback_2 method_2;


    Command();
    Command(Machine *obj, void(Machine:: *mth)());
    Command(People *obj, void(People:: *mth)());

    void execute(){
        (object->*(method))();
    }
    void execute2(){
        (object_2->*(method_2))();
    }
};