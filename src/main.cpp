#include "MSGlang.h"


int main() {
  let connection = object[
        call("connect"),
        key("ip") = "1.1.1.1",
        key("port") = 5000,
        func("cond"){ return arg(port) == self(port);},
        func("success"){
            cout << arg(ip) << " connected to " 
            << self(ip) << nl;
            return true;
        },
        func("failure"){
            cout << arg(ip) << " failed to connect to" 
            << self(ip) << nl;
            return false;
        }
    ];

    let conn_impl = object[
        key("ip") = "127.0.0.1",
        key("port") = 3030,
        func("connect"){
            if(eval_cond("cond")){
                eval("success");
            }
            else
                eval("failure");
            return false;
        }
    ];

    conn_impl << connection;
    
    return 0;
}
