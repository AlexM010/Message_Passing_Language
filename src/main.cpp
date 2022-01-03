#include <iostream>
#include <string>
#include <vector>
#include "MSGlang.h"
int main() {
    let l=object;
    l->add("name",string("name"));
    l->add("age",20);
    l->add("is_empty",false);
    l->print();
    return 0;
}
