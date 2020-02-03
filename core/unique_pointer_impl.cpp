#include<iostream>


template<typename T>
class UniquePtr{
private:
	T* m_;

public:
	//UniquePtr(){m_ = nullptr};
	UniquePtr(T* m = nullptr): m_(m){}
	UniquePtr(const UniquePtr<T>& other) = delete;
	UniquePtr& Operator=(const UniquePtr<T>& other) = delete;
	T& Operator*() const{ //dereference operator
		return *m_;
	}
	T* Operator->() const{
		return m_;
	}
	UniquePtr(const UniquePtr<T>&& other): m_(other){
		other.m_ = nullptr;
	}
	UniquePtr& Operator=(const UniquePtr<T>&& other){
		if(&other==this) return *this;
		if(m_) delete m_;
		m_ = other.m_;
		other.m_ = nullptr;
		return *this;
	}
	~UniquePtr(){
		if(m_) delete m_;
	}
};