
#include "MSGlang.h"
std::vector <Item>args_list;

Item::Item(const std::string& s){
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

Item::Item(std::function<std::any(Let&x)> f){
        this->f = f;
        this->e=METHOD;
        this->is_empty=false;
}

void Item::set(std::function<std::any(Let&x)> f){
        this->f = f;
}
void Item::set(const std::string& s){
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

std::string Item::getStr(){
        return this->s;
}
Item Item::get(){
        return *this;
}
void Item::print(){
    switch (e)
    {
    case INT:
        std::cout<<i;
        break;
    case DOUBLE:
        std::cout<<d;
        break;
    case BOOL:
        if (b) std::cout<<"true";
        else std::cout<<"false";
        break;
    case STRING:
        std::cout<<"\""<<s<<"\"";
        break;
    case OBJECT:
        l->print();
        break;
    case METHOD:
        std::cout<<"Method";
        break;
    default:
        break;
    }
}
std::any Item::get_func(Let& x){
      return  f(x);
 }
Let::Let(){
    this->empty=true;
}
Let::Let(std::string s){
    this->temp=s;
    this->empty=false;
}
Let::Let(const Let& l){
    this->temp=l.temp;
    this->empty=l.empty;
    this->rec_fun_id=l.rec_fun_id;
    this->data=l.data;
    this->rec_data=l.rec_data;
    this->size=l.size;
}
std::map<std::string, Item*> Let::getMap(bool x){
        if(x) return this->rec_data;
        else return this->data;
}
Let Let::add(std::string key,const std::string& s){
        Item* it=new Item(s);
        this->data.insert(std::pair<std::string,Item*>(key,it));
        this->empty=false;
        return *this;
}

Let Let::add(std::string key,const int& i){
        Item* it=new Item(i);
        this->data.insert(std::pair<std::string,Item*>(key,it));
        this->empty=false;
        return *this;
}

Let Let::add(std::string key,const double& d){
        Item* it=new Item(d);
        this->data.insert(std::pair<std::string,Item*>(key,it));
        this->empty=false;
        return *this;
}

Let Let::add(std::string key,const bool& b){
        Item* it=new Item(b);
        this->data.insert(std::pair<std::string,Item*>(key,it));
        this->empty=false;
        return *this;
}

Let Let::add(std::string key,Let *l){
        Item* it=new Item(l);
        this->data.insert(std::pair<std::string,Item*>(key,it));
        this->empty=false;
        return *this;
}
Let Let::add(std::string key,const Item& i){
        Item* it=new Item(i);
        this->data.insert(std::pair<std::string,Item*>(key,it));
        this->empty=false;
        return *this;
}
Let Let::add(std::string key,std::function<std::any(Let&x)>f){
        Item* it=new Item(f);
        this->data.insert(std::pair<std::string,Item*>(key,it));
        this->empty=false;
        return *this;
}
void Let::print(){
        std::cout<<"object ";
        if(this->empty){
            std::cout<<"Empty"<<std::endl;
        }else{
            std::cout<<"[ ";
            for(auto it=this->data.begin();it!=this->data.end();){
                std::cout<<"\""<<it->first<<"\" : ";
                it->second->print();
                it++;
                if(it!=this->data.end()){
                    std::cout<<" , ";
                }
            }
            std::cout<<" ] ";
        }
        std::cout << std::endl;
}
Let Let::operator[](Let x){
        return x;
}
Item& Let::operator[](std::string key){
        Item& item =(*this->data[key]);
        return item;
}

Let Let::operator,(Let x){
        this->data.insert(x.data.begin(),x.data.end());
        return *this;
}
Let Let::operator,(Let* x){
        add(std::to_string(this->size),x);
        size++;
        return *this;
}
Let Let::operator,(int x){
        add(std::to_string(size),x);
        size++;

        return *this;
}
Let Let::operator=(Let l){

        for(auto it: l.data)   //inserting map values into std::vector
        {
                if(it.first.compare(std::string(""))!=0)
                {
                        this->data.insert(std::pair<std::string,Item*>(it.first,it.second));
                }else{
                        this->data.insert(std::pair<std::string,Item*>(this->temp,it.second));

                }
        }
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
Let Let::operator%(std::function<std::any(Let&x)> f){
        add(std::string(""),f);
        return *this;
}
Let Let::operator=(bool b){
        add(temp,b);
        return *this;
}
Let Let::operator=(const char* c){
        add(temp,std::string(c));
        return *this;
}
Let Let::operator=(std::string s){
        add(temp,s);
        return *this;
}
Let Let::operator=(double d){
        add(temp,d);
        return *this;
}
Let Let::operator,(std::function<std::any(Let&x)> f){
        add(std::to_string(size),f);
        size++;
        return *this;
}
Let Let::operator,(const char* x){
        add(std::to_string(size),std::string(x));
        size++;
        return *this;
}
Let Let::operator,(std::string x){
        add(std::to_string(size),x);
        size++;
        return *this;
}

Let Let::operator,(double x){
        add(std::to_string(size),x);
        size++;
        return *this;
}

Let Let::operator,(bool x){
        add(std::to_string(size),x);
        size++;
        return *this;
}
Let Let::operator<<(Let sen){
        this->rec_data.insert(sen.data.begin(),sen.data.end());
        //throw message for call
        //error message for
        
        for(auto i : sen.data)   //inserting map values into std::vector
        {
                args_list.push_back(*i.second);
                
        }

       Item* t= this->data[this->rec_data[std::string("call")]->s];
        t->get_func(*this);
        return *this;
}
Item input(const char*s){
        std::cout<<s;
        
        std::string x=std::string();
        std::cin>>x;
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
std::ostream& operator<<(std::ostream& os, const Item& it){
        
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
        os<< *it.l;
        break;
    case it.METHOD:
        os<<"Method";
        break;
    default:
        break;
    }
        return os;

}


std::ostream& operator<<(std::ostream& os, const Let& l){
       
    os<<"object ";
        if(l.empty){
            os<<"Empty"<<std::endl;
        }else{
            os<<"[ ";
            for(auto it=l.data.begin();it!=l.data.end();){

                if(it->first.compare(std::string("call"))==0)
                       it++;
                else{
                        if(it !=l.data.end() && it !=l.data.begin()){
                                os<<" , ";
                        }
                        os<<"\""<<it->first<<"\" : ";
                        os<<*it->second;
                        it++;
                }
            }
            os<<" ] ";

        }
        os << std::endl;
    return os;
}