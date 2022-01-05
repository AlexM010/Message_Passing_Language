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

void Let::add(string key,Let const l){
        Item* it=new Item(l);
        this->data.insert(pair<string,Item*>(key,it));
        this->empty=false;
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


Let Let::operator,(const char* x){
        add(to_string(size),string(x));
        size++;
        return *this;
}
Let Let::operator+(const char* x){
        add(to_string(size),string(x));
        size++;
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


Let Let::operator,(double x){
        add(to_string(size),x);
        size++;
        return *this;
}
Let Let::operator+(double x){
        add(to_string(size),x);
        size++;
        return *this;
}

Let Let::operator,(bool x){
        add(to_string(size),x);
        size++;
        return *this;
}
Let Let::operator+(bool x){
        add(to_string(size),x);
        size++;
        return *this;
}

Let Let::operator,(Let const x){
        add(to_string(size),x);
        size++;
        return *this;
}
Let Let::operator+(Let const x){
        add(to_string(size),x);
        size++;
        return *this;
}
