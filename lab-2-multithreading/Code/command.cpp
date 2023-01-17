
#include "command.hpp"
#include "machine.hpp"
#include "shop.hpp"
#include "people.hpp"

Command::Command(){
    object = 0;
    method = 0;
}

Command::Command(Machine *obj, void(Machine:: *mth)()){
    object = obj;
    method = mth;
}

Command::Command(People *obj, void(People:: *mth)()){
    object_2 = obj;
    method_2 = mth;
}