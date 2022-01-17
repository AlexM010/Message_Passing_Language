#include <iostream>
#include <string>
#include <string.h>
#include <iterator>
#include <map>
#include <vector>
#include <functional>
#include <any>
#ifndef MSGLANG_H
#define MSGLANG_H
#define nl std::endl
#define let auto
#define object (*new Let())
#define values (*(new Let())),
#define key(s)  (*(new Let(s)))
#define lambda (*(new Let()))%[]([[maybe_unused]] Let& l)
#define func(s) key(s)=lambda
#define ref(s) (Let*)(&s)
#define self(s) *l.getMap(false)[#s]
#define arg(s) *l.getMap(true)[#s]
#define none (*(new Let()))
#define call(s) key("call")=s
#define eval(s) (l.getMap(true)[s]->get_func(l))
#define eval_cond(s) any_cast<bool>(l.getMap(true)[s]->get_func(l))

class Let;

class Item;
extern std::vector <Item>args_list;
extern bool b;


class Item{
    public:
        std::string s;
        int i;
        double d;
        bool b;
        Let* l;
        bool is_empty=true;
        std::function<std::any(Let&)> f;
    enum{
            STRING,
            INT,
            DOUBLE,
            BOOL,
            METHOD,
            OBJECT}e;
       Item(const std::string& s);
       Item(const int& i);
       Item(const double& d);
       Item(const bool& b);
       Item(Let* l);
       Item(std::function<std::any(Let&)> f);

       void set(std::function<std::any(Let&)> f);
       void set(const std::string& s);
       void set(const int& i);
       void set(const double& d);
       void set(const bool& b);
       void set(Let l);
       friend std::ostream& operator<<(std::ostream& os, const Item& it);
       std::any get_func(Let& x);
       Item get();
       bool operator==(const Item& a){
              if(a.e==this->e){
                switch(this->e){
                     case STRING:
                          return (this->s.compare(a.s)==0);
                     case INT:
                          return a.i==this->i;
                     case DOUBLE:
                          return a.d==this->d;
                     case BOOL:
                          return a.b==this->b;
                     default:
                            return false;
                }
              }
              return false;
        }
       operator int(){
           if(this->e!=INT){
                throw std::runtime_error("Item is not an int");
           }
           return i;
       }
        operator double(){
              if(this->e!=DOUBLE){
                 throw std::runtime_error("Item is not a double");
                 }
            return d;
        }
        operator bool(){
                if(this->e!=BOOL){
                     throw std::runtime_error("Item is not a bool");
                     }
            return b;
        }
        operator std::string(){
                if(this->e!=STRING){
                     throw std::runtime_error("Item is not a string");
                     }
            return s;
        }
        operator Let*(){
                if(this->e!=OBJECT){
                     throw std::runtime_error("Item is not an object");
                     }
            return l;
        }
        operator std::function<std::any(Let&)>(){
                if(this->e!=METHOD){
                     throw std::runtime_error("Item is not a method");
                     }
            return f;
        }
        double operator+(const Item& a){
            if(e==DOUBLE && a.e==DOUBLE){
                return d+a.d;
            }
            if(e==INT && a.e==DOUBLE){
                return i+a.d;
            }
            if(e==DOUBLE && a.e==INT){
                return d+a.i;
            }
            if(e==INT && a.e==INT){
                return i+a.i;
            }else{
                throw std::runtime_error("Error: can't multiply");
            }
        }
        double operator-(const Item& a){
            if(e==DOUBLE && a.e==DOUBLE){
                return d-a.d;
            }
            if(e==INT && a.e==DOUBLE){
                return i-a.d;
            }
            if(e==DOUBLE && a.e==INT){
                return d-a.i;
            }
            if(e==INT && a.e==INT){
                return i-a.i;
            }else{
                throw std::runtime_error("Error: can't multiply");
            }
        }
        double operator*(const Item& a){
            if(e==DOUBLE && a.e==DOUBLE){
                return d*a.d;
            }
            if(e==INT && a.e==DOUBLE){
                return i*a.d;
            }
            if(e==DOUBLE && a.e==INT){
                return d*a.i;
            }
            if(e==INT && a.e==INT){
                return i*a.i;
            }else{
                throw std::runtime_error("Error: can't multiply");
            }
        }
        double operator/(const Item& a){
            if(e==DOUBLE && a.e==DOUBLE){
                return d/a.d;
            }
            if(e==INT && a.e==DOUBLE){
                return i/a.d;
            }
            if(e==DOUBLE && a.e==INT){
                return d/a.i;
            }
            if(e==INT && a.e==INT){
                return i/a.i;
            }else{
                throw std::runtime_error("Error: can't multiply");
            }
        }
        
       std::string getStr();
       void print();
};


class Let{
    private:
        std::string temp;
        bool empty=true;
        std::string rec_fun_id;
        std::map<std::string, Item*> data;
        std::map<std::string,Item*> rec_data;
        int size=0;
    public:
        Let();
        Let(std::string s);
        Let(const Let&);
        std::map<std::string, Item*> getMap(bool x);
        Let add(std::string key,const std::string& s);
        Let add(std::string key,const int& i);
        Let add(std::string key,const double& d);
        Let add(std::string key,const bool& b);
        Let add(std::string key,Let * l);
        Let add(std::string key,const Item& i);
        Let add(std::string key,const char& c);
        Let add(std::string key,std::function<std::any(Let&)>f);

        friend std::ostream& operator<<(std::ostream& os, const Let& l);
        void print();
        Let operator[](Let x);
        Item& operator[](std::string key);
        Let operator,(Let x);
        Let operator,(Let* x);
        Let operator,(int x);
        Let operator=(int x);
        Let operator%(std::function<std::any(Let&)> f);
        Let operator=(Item i);
        Let operator=(std::string s);
        Let operator=(double d);
        Let operator=(const char* s);
        Let operator=(bool b);
        Let operator=(Let l);

        Let operator,(const char* x);
        Let operator,(std::string x);
        Let operator,(double x);
        Let operator,(bool x);
        Let operator,(std::function<std::any(Let&)> f);
        Let operator<<(Let sen);
};


Item input(const char*s);
#endif