#include<iostream>
#include"skiplist.h"
#define FILE_PATH "./store/dumpFile"

int main(){

    SkipList<int,std::string> skipList(6);
    skipList.insert_element(1,"戴");
    skipList.insert_element(3,"阳");
    skipList.insert_element(4,"网络");
    skipList.insert_element(6,"空间");
    skipList.insert_element(8,"安全");
    skipList.insert_element(10,"学院");
    skipList.insert_element(13,"跳表");
    skipList.insert_element(19,"学习");
    skipList.insert_element(24,"项目");

    std::cout<<"SkipList size: "<<skipList.size()<<std::endl;
    skipList.dump_file();
    skipList.load_file();
    skipList.search_element(6);
    skipList.search_element(11);

    skipList.display_list();
    skipList.delete_element(19);
    skipList.delete_element(20);

    std::cout<<"SkipList size: "<<skipList.size()<<std::endl;

    skipList.display_list();
    skipList.dump_file();
    return 0;
}