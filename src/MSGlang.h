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
#define self(s) this->data[#s]
#define arg(s) this->rec_data[#s]
#define none (*(new Let()))



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
       friend ostream& operator<<(ostream& os, const Item& it);
       Item* get();
       Item& operator=(void* x);
       void print();
};

class Let{
    private:
        map<string, Item*> data;
        map<string,Item*> rec_data;
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

        friend ostream& operator<<(ostream& os, const Let& l);
        void print();
        Let operator[](Let x);
        Item& operator[](string key);
        Let operator,(Let x);
        Let operator,(int x);
        Let operator+(int x);
        Let operator=(int x);
        Let operator=(function<bool(void)> f);
        Let operator=(Item i);
        Let operator,(const char* x);
        Let operator+(const char* x);
    
        Let operator,(double x);
        Let operator+(double x);
        Let operator,(bool x);
        Let operator+(bool x);
        Let operator+(Let const x);
        Let operator,(function<bool(void)> f);
};


Item input(const char*s);
#endif