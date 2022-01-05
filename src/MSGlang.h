#include <iostream>
#include <string>
#include <iterator>
#include <map>
#include <any>
#ifndef MSGLANG_H
#define MSGLANG_H
#define nl endl
#define let auto
#define object Let()
#define values (*(new Let()))+

using namespace std;

class Let;

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
       Item(const string& s);
       Item(const int& i);
       Item(const double& d);
       Item(const bool& b);
       Item(Let const l);
       void print();
};

class Let{
    private:
        map<string, Item*> data;
        int size=0;
        bool empty=true;
    public:
        void add(string key,const string& s);
        void add(string key,const int& i);
        void add(string key,const double& d);
        void add(string key,const bool& b);
        void add(string key,Let const l);
        void print();
        template<typename T> 
        T operator[](T x){
            return x;
        }
        //nikolh gtxs kane to gia ola ta data types mh gamhsw

        Let operator,(const char* x);
        Let operator+(const char* x);

        Let operator,(int x);
        Let operator+(int x);
        
        Let operator,(double x);
        Let operator+(double x);

        Let operator,(bool x);
        Let operator+(bool x);

        Let operator,(Let const x);
        Let operator+(Let const x);

};


#endif