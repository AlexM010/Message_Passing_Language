#include <iostream>
#include <string>
#include <string.h>
#include <iterator>
#include <map>
#include <functional>
#ifndef MSGLANG_H
#define MSGLANG_H
#define nl endl
#define let auto
#define object (*new Let())
#define values (*(new Let()))+
#define key(s)  (*(new Let(s)))
#define lambda []()
#define func(s) key(s)=lambda
#define ref(s) &s



using namespace std;


class Let;

class Item{
    private:
        string s;
        int i;
        double d;
        bool b;
        Let* l;
        function<bool(void)> f;
        bool is_empty=true;
        enum{
            STRING,
            INT,
            DOUBLE,
            BOOL,
            METHOD,
            OBJECT}e;
    public:
       Item(const string& s);
       Item(const int& i);
       Item(const double& d);
       Item(const bool& b);
       Item(Let const l);
       template<typename T>
       Item(function<T(void)> f);
       template<typename T>
       void set(function<T(void)> f);
       void set(const string& s);
       void set(const int& i);
       void set(const double& d);
       void set(const bool& b);
       void set(Let l);
       Item* get();
       Item& operator=(void* x);
       void print();
};

class Let{
    private:
        map<string, Item*> data;
        int size=0;
        string temp;
        bool empty=true;
    public:
        Let();
        Let(string s);
        Let add(string key,const string& s);
        Let add(string key,const int& i);
        Let add(string key,const double& d);
        Let add(string key,const bool& b);
        Let add(string key,Let const l);
        Let add(string key,const Item& i);
        void print();
        Let operator[](Let x);
        Item& operator[](string key);
        Let operator,(Let x);
        //nikolh gtxs kane to gia ola ta data types mh gamhsw
        Let operator,(int x);
        Let operator+(int x);
        Let operator=(int x);
        Let operator=(function<bool(void)> f);
        Let operator=(Item i);
};


Item input(const char*s){
            cout<<s;
            
            string x=string();
            cin>>x;
            try{
                double d=stod(x);
                return(Item(d));
            }catch(...){
                try{
                     int i=stoi(x);
                    return(Item(i));
                }catch(...){
                    if(strcmp(x.c_str(), "true")==0){
                       return(Item( true));
                    }else if(strcmp(x.c_str(), "false")==0){
                      return(Item(false));
                    }
                    return Item( x);
                }
            }
            
        }
#endif