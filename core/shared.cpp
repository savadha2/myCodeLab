#include <iostream>
#include <memory>

class Resource{
    private:
    int m_;
    public:
    Resource(int m):m_(m){
        std::cout<<"Initializing Resource "<<m_<<std::endl;
    }
    ~Resource(){
        std::cout<<"Resource "<<m_<<" destroyed"<<std::endl;
    }
};

int main(int argc, char* argv[]){
    Resource* res1 = new Resource(1);
    //Resource res2 = Resource(2);
    {
        std::cout<<"In scope"<<std::endl;
        std::shared_ptr<Resource> p1(res1);
        //std::shared_ptr<Resource> p2 = std::make_shared<Resource>(res2);
        //std::cout<<"Move "<<std::endl;
        //p1 = p2;
        std::cout<<"Exiting scope"<<std::endl;
    }
    return 0;
}