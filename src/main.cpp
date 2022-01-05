#include "MSGlang.h"


int main() {
    let m = object[key("s")=8,
    key("s2")=12,
    key("FUN")=lambda{
        cout<<"-FUNCTION CALLED-";
        return true;
    },
    func("bb"){
        cout<<"-FUNCTION2 CALLED-"; 
        return true;}
    ];
    let k=object[values 1 , 2, 3];
    m.print();
    k.print();
    k["2"]=input("Enter a number: ");
    k.print();
    return 0;
}
