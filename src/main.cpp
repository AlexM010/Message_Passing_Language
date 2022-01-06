#include "MSGlang.h"


int main() {

    let printf_impl = object [
        key("1")="alex",
        func("printf"){
         cout<<"Hello"<<self(1)<<arg(1)<<endl;
            for (auto& v : args_list)
                std::cout << v << nl;
            return true;
        }
    ];
    cout<<printf_impl<<endl;
    //operator = to do with char*
   printf_impl["1"]=2;
   cout<<printf_impl["1"]<<endl;
    
    
    let o3 = object [ call("printf"), values 1, "4", -3.14 ,true];
    cout<<o3<<endl;
    printf_impl<<o3;
    
    
    return 0;
}
