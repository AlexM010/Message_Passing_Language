#include <iostream>
#include <string>
#include "MSGlang.h"
vector <Item>args_list;
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

Item::Item(Let *l){
        this->l =l;
        this->e=OBJECT;
        this->is_empty=false;
}

Item::Item(function<bool(Let& x)> f){
        this->f = f;
        this->e=METHOD;
        this->is_empty=false;
}

void Item::set(function<bool(Let& x)> f){
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
string Item::getStr(){
        return this->s;
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
        cout<<"Method";
        break;
    default:
        break;
    }
}
 void Item::get_func(Let& x){
        f(x);
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

Let Let::add(string key,Let *l){
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
Let Let::add(string key,function<bool(Let& x)>f){
        Item* it=new Item(f);
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
Let Let::operator=(int x){
        add(temp,x);
        return *this;
}
Let Let::operator=(Item i){
        add(temp,i);
        return *this;
}
Let Let::operator=(function<bool(Let& x)> f){
        add(temp,f);
        return *this;
}
Let Let::operator=(const char* c){
        add(temp,string(c));
        return *this;
}
Let Let::operator=(string s){
        add(temp,s);
        return *this;
}
Let Let::operator=(double d){
        add(temp,d);
        return *this;
}
Let Let::operator,(function<bool(Let& x)> f){
        add(to_string(size),f);
        size++;
        return *this;
}
Let Let::operator,(const char* x){
        add(to_string(size),string(x));
        size++;
        return *this;
}
Let Let::operator,(string x){
        add(to_string(size),x);
        size++;
        return *this;
}

Let Let::operator,(double x){
        add(to_string(size),x);
        size++;
        return *this;
}

Let Let::operator,(bool x){
        add(to_string(size),x);
        size++;
        return *this;
}
Let Let::operator<<(Let sen){
        this->rec_data.insert(sen.data.begin(),sen.data.end());
        //throw message for call
        //error message for
        for(auto i : sen.data)   //inserting map values into vector
        {
                args_list.push_back(*i.second);
        }
       Item* t= this->data[this->rec_data["call"]->getStr()];
       
        t->get_func(*this);
        return *this;
}
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
ostream& operator<<(ostream& os, const Item& it){
        cerr<<"In Item "<<it.e<<" "<<it.i<<endl;
    switch (it.e)
    {
    case it.INT:
        os<<it.i;
        break;
    case it.DOUBLE:
        os<<it.d;
        break;
    case it.BOOL:
        if (it.b) os<<"true";
        else os<<"false";
        break;
    case it.STRING:
        os<<"\""<<it.s<<"\"";
        break;
    case it.OBJECT:
        os<< it.l;
        break;
    case it.METHOD:
        os<<"Method";
        break;
    default:
        break;
    }
        return os;

}

ostream& operator<<(ostream& os, const Let& l){
       
    os<<"object ";
        if(l.empty){
            os<<"Empty"<<endl;
        }else{
            os<<"[ ";
            for(auto it=l.data.begin();it!=l.data.end();){
                        os<<"\""<<it->first<<"\" : ";
                        os<<*it->second;
                        it++;
                        cout<<__LINE__<<endl;
                        if(it->first.compare(string("call"))==0)
                                it++;
                        cout<<__LINE__<<endl;
                       if(it !=l.data.end()){
                               os<<" , ";
                }
            }
            os<<" ] ";

        }
        os << endl;
    return os;
}