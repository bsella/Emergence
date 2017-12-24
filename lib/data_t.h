#ifndef DATA_T_H
#define DATA_T_H

enum class TypeEnum{
    BOOL=0x1,
    DOUBLE=0x2,
    UINT=0x4,
    ANY=0x7
};

struct data_t{
    TypeEnum t;
    bool b;
    double d;
    unsigned int u;
    explicit data_t():t(TypeEnum::ANY){}
    data_t(double v):t(TypeEnum::DOUBLE), d(v){}
    data_t(bool v):t(TypeEnum::BOOL), b(v){}
    data_t(unsigned v):t(TypeEnum::UINT), u(v){}
    operator bool(){
        if(t==TypeEnum::DOUBLE) return d>=1;
        if(t==TypeEnum::UINT) return u!=0;
        return b;
    }
    operator double(){
        if(t==TypeEnum::BOOL) return b? 1.0:0.0;
        if(t==TypeEnum::UINT) return double(u);
        return d;
    }
    operator unsigned(){
        if(t==TypeEnum::BOOL) return b? 0xffffffff:0xff000000;
        if(t==TypeEnum::DOUBLE){
            if(d>1)return 0xffffffff;
            if(d<0)return 0;
            unsigned char c= d*256;
            unsigned int i=0xff;
            i<<=8; i|=c;
            i<<=8; i|=c;
            i<<=8; i|=c;
            return i;
        }
        return u;
    }
    friend bool operator>(data_t d1, data_t d2){return double(d1)>double(d2);}
    friend bool operator<(data_t d1, data_t d2){return double(d1)<double(d2);}
    friend bool operator==(data_t d1, data_t d2){return double(d1)==double(d2);}
    friend bool operator!=(data_t d1, data_t d2){return double(d1)!=double(d2);}
    friend bool operator>=(data_t d1, data_t d2){return double(d1)>=double(d2);}
    friend bool operator<=(data_t d1, data_t d2){return double(d1)<=double(d2);}
    friend bool operator^(data_t b1, data_t b2){return bool(b1)^bool(b2);}
    data_t& operator=(double dd){
        t=TypeEnum::DOUBLE;
        d=dd;
        return *this;
    }
    data_t& operator=(bool bb){
        t=TypeEnum::BOOL;
        b=bb;
        return *this;
    }
    data_t& operator=(unsigned uu){
        t=TypeEnum::UINT;
        u=uu;
        return *this;
    }
};

#endif // DATA_T_H
