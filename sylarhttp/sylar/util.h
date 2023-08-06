#ifndef __SYLAR_UTIL_H__
#define __SYLAR_UTIL_H__
#include<thread>
#include<pthread.h>
#include<sys/types.h>
#include<sys/syscall.h>
#include<iostream>
#include<unistd.h>
#include<stdint.h>


namespace sylar{
pid_t GetThreadId();
uint32_t GetFiberId();


}


#endif