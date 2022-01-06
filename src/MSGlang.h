#include <iostream>
#include <string>
#include <string.h>
#include <iterator>
#include <map>
#include <vector>
#include <functional>
#ifndef MSGLANG_H
#define MSGLANG_H
#define nl endl
#define let auto
#define object (*new Let())
#define values (*(new Let())),
#define key(s)  (*(new Let(s)))
#define lambda [](Let& l)
#define func(s) key(s)=lambda
#define ref(s) &s
#define self(s) l.data[#s]->getStr()
#define arg(s) l.rec_data[#s]->getStr()
#define none (*(new Let()))
#define call(s) key("call")=s






using namespace std;

class Let;

class Item;
extern vector <Item>args_list;



class Item{
    private:
        string s;
        int i;
        double d;
        bool b;
        Let* l;
        bool is_empty=true;
        enum{
            STRING,
            INT,
            DOUBLE,
            BOOL,
            METHOD,
            OBJECT}e;
    public:
       function<bool(Let&)> f;
       Item(const string& s);
       Item(const int& i);
       Item(const double& d);
       Item(const bool& b);
       Item(Let* l);
       Item(function<bool(Let&)> f);
       void set(function<bool(Let&)> f);
       void set(const string& s);
       void set(const int& i);
       void set(const double& d);
       void set(const bool& b);
       void set(Let l);
       friend ostream& operator<<(ostream& os, const Item& it);
       Item* get();
       void get_func(Let& x);
       string getStr();
       Item& operator=(void* x);
       void print();
};

class Let{
    private:
        
        string temp;
        bool empty=true;
        string rec_fun_id;
    public:
        map<string, Item*> data;
        map<string,Item*> rec_data;
        int size=0;
        Let();
        Let(string s);
        Let add(string key,const string& s);
        Let add(string key,const int& i);
        Let add(string key,const double& d);
        Let add(string key,const bool& b);
        Let add(string key,Let * l);
        Let add(string key,const Item& i);
        Let add(string key,const char& c);
        Let add(string key,function<bool(Let&)>f);

        friend ostream& operator<<(ostream& os, const Let& l);
        void print();
        Let operator[](Let x);
        Item& operator[](string key);
        Let operator,(Let x);
        
        Let operator,(int x);
        Let operator=(int x);
        Let operator=(function<bool(Let&)> f);
        Let operator=(Item i);
        Let operator=(string s);
        Let operator=(double d);
        Let operator=(const char* s);
        //Let operator=(bool b);

        Let operator,(const char* x);
        Let operator,(string x);
        Let operator,(double x);
        Let operator,(bool x);
        Let operator,(function<bool(Let&)> f);
        Let operator<<(Let sen);
};


Item input(const char*s);
#endif