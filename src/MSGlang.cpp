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

Item::Item(Let const l){
        this->l =(Let*) &l;
        this->e=OBJECT;
        this->is_empty=false;
}
template<typename T>
Item::Item(function<T(void)> f){
        this->f = f;
        this->e=METHOD;
        this->is_empty=false;
}
template<typename T>
void Item::set(function<T(void)> f){
        this->f = f;
}
void Item::set(const string& s){
        this->s = s;
}
void Item::set(const int& i){
        this->i = i;
}
void Item::set(const double& d){
        this->d = d;
}
void Item::set(const bool& b){
        this->b = b;
}
void Item::set(Let l){
        this->l = &l;
}

Item* Item::get(){
        return this;
}

Item& Item::operator=(void* x){
        this->set(x);
        return *this;
}

void Item::print(){
    switch (e)
    {
    case INT:
        cout<<i;
        break;
    case DOUBLE:
        cout<<d;
        break;
    case BOOL:
        if (b) cout<<"true";
        else cout<<"false";
        break;
    case STRING:
        cout<<"\""<<s<<"\"";
        break;
    case OBJECT:
        l->print();
        break;
    case METHOD:
        f();
        cout<<"Method";
        break;
    default:
        break;
    }
}
Let::Let(){
    this->empty=true;
}
Let::Let(string s){
    this->temp=s;
    this->empty=false;
}
Let Let::add(string key,const string& s){
        Item* it=new Item(s);
        this->data.insert(pair<string,Item*>(key,it));
        this->empty=false;
        return *this;
}

Let Let::add(string key,const int& i){
        Item* it=new Item(i);
        this->data.insert(pair<string,Item*>(key,it));
        this->empty=false;
        return *this;
}

Let Let::add(string key,const double& d){
        Item* it=new Item(d);
        this->data.insert(pair<string,Item*>(key,it));
        this->empty=false;
        return *this;
}

Let Let::add(string key,const bool& b){
        Item* it=new Item(b);
        this->data.insert(pair<string,Item*>(key,it));
        this->empty=false;
        return *this;
}

Let Let::add(string key,Let const l){
        Item* it=new Item(l);
        this->data.insert(pair<string,Item*>(key,it));
        this->empty=false;
        return *this;
}
Let Let::add(string key,const Item& i){
        Item* it=new Item(i);
        this->data.insert(pair<string,Item*>(key,it));
        this->empty=false;
        return *this;
}
void Let::print(){
        cout<<"object ";
        if(this->empty){
            cout<<"Empty"<<endl;
        }else{
            cout<<"[ ";
            for(auto it=this->data.begin();it!=this->data.end();){
                cout<<"\""<<it->first<<"\" : ";
                it->second->print();
                it++;
                if(it!=this->data.end()){
                    cout<<" , ";
                }
            }
            cout<<" ] ";
        }
        cout << endl;
}
Let Let::operator[](Let x){
        return x;
}
Item& Let::operator[](string key){
        Item& item =(*this->data[key]->get());
        return item;
}


Let Let::operator,(Let x){
        this->data.insert(x.data.begin(),x.data.end());
        return *this;
}
Let Let::operator,(int x){
        add(to_string(size),x);
        size++;

        return *this;
}
Let Let::operator+(int x){
        add(to_string(size),x);
        size++;
        return *this;
}
Let Let::operator=(int x){
        add(temp,x);
        return *this;
}
Let Let::operator=(Item i){
        add(temp,i);
        return *this;
}
Let Let::operator=(function<bool(void)> f){
        add(temp,f);
        return *this;
}