#ifndef __SYLAR_SINGLETON_H__
#define __SYLAR_SINGLETON_H__

namespace sylar{
template<class T,class X=void, int N=0>
class Singleton{
public:
    static T* GetInstance(){
    //返回单例的裸指针
        static T v;
        return &v;
    }
};
template<class T,class X=void,int N=0>
class SingletonPtr{
public:
    static std::shared_ptr<T> GetInstence(){
        //返回单例的智能指针
        static std::shared_ptr<T> v(new T);
        return v;
    }
};

}


#endif