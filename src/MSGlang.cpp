#include <iostream>
#include <string>
#include "MSGlang.h"
Item::Item(const string& s){
        this->s = s;
        this->e=STRING;
        this->is_empty=false;
}

Item::Item(const int& i){
        this->i = i;
        this->e=INT;
        this->is_empty=false;
}

Item::Item(const double& d){
        this->d = d;
        this->e=DOUBLE;
        this->is_empty=false;
}

Item::Item(const bool& b){
        this->b = b;
        this->e=BOOL;
        this->is_empty=false;
}

Item::Item(Let* const l){
        this->l = l;
        this->e=OBJECT;
        this->is_empty=false;
}

void Item::print(){
    switch (e)
    {
    case INT:
        cout<<"Value: "<<i<<endl;
        break;
    case DOUBLE:
        cout<<"Value: "<<d<<endl;
        break;
    case BOOL:
        cout<<"Value: "<<b<<endl;
        break;
    case STRING:
        cout<<"Value: "<<s<<endl;
        break;
    case OBJECT:
        cout<<"Value: ";
        l->print();
        cout<<endl;
        break;
    case METHOD:
        cout<<"Value: "<<"Method"<<endl;
        break;
    default:
        break;
    }
}

void Let::add(string key,const string& s){
        Item* it=new Item(s);
        this->data.insert(pair<string,Item*>(key,it));
        this->empty=false;
}

void Let::add(string key,const int& i){
        Item* it=new Item(i);
        this->data.insert(pair<string,Item*>(key,it));
        this->empty=false;
}

void Let::add(string key,const double& d){
        Item* it=new Item(d);
        this->data.insert(pair<string,Item*>(key,it));
        this->empty=false;
}

void Let::add(string key,const bool& b){
        Item* it=new Item(b);
        this->data.insert(pair<string,Item*>(key,it));
        this->empty=false;
}

void Let::add(string key,Let* const l){
        Item* it=new Item(l);
        this->data.insert(pair<string,Item*>(key,it));
        this->empty=false;
}

void Let::print(){
        if(this->empty){
            cout<<"{}";
        }else{
            cout<<"{";
            for(auto it=this->data.begin();it!=this->data.end();it++){
                cout<<it->first<<" - ";
                it->second->print();
                cout<<",";
            }
            cout<<"}";
        }
        cout << endl;
}
