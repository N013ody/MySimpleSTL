#pragma once

template <class T> 
class MyAllocator
{

private:
	using size_type = std::size_t;

	size_type allocCount=0;


public:
	using value_type = T;//类型
	using pointer = T*;//地址
	using refrence = T&;//引用

	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using propagate_on_container_move_assignment = std::true_type;

	MyAllocator() = default;
	~MyAllocator() = default;

	// 支持从其他 MyAllocator 隐式转换
	template <class U>
	MyAllocator(const MyAllocator<U>&) noexcept {}


	//重新绑定函数
	template <class U>
	struct rebind
	{
		using other = MyAllocator<U>;
	};



	//分配足够的存储空间来存储T的n个实例，并返回指向它的指针
	pointer allocate(size_type n) {
		//operator new()函数分配内存 其中operator new()函数是C++标准库中定义的一个函数，用于在堆上分配内存。 
		// value pointer 是一个指向T类型的指针，n 是要分配的内存块的数量，sizeof(T) 是每个T类型对象的大小。
		// operator new 默认 返回void* 类型，所以需要使用static_cast进行类型转换
		allocCount += n;

		return  static_cast<pointer>(operator new(n * sizeof(T)));
	}

	//释放分配的内存
	void deallocate(pointer p, size_type n) {
		operator delete(p);
	}

	//在指针 p 指向的 已分配内存 上，构造一个 U 类型的对象。
	template <class U, class... Args>
	void construct(U* p, Args&&... args) {
		new(p) U(std::forward<Args>(args)...);
	}


	//调用p指向的对象的析构函数
	template <class U>
	void destroy(U* p) {  // 模板化以支持任意类型
		p->~U();
	}

	//末尾的 const 表示该成员函数是常量成员函数，即它不会修改调用它的对象的状态
	//可以在 const 对象或通过 const 引用/指针调用
	//const 成员函数 不能修改 成员变量。
	//const 对象 只能调用 const 成员函数。

	//最大内存数
	size_type max_size() const noexcept {
		return std::numeric_limits<size_type>::max();
	}

	// 返回分配计数
	size_type get_allocations() const {  // 修复：返回 size_type
		return allocCount;
	}


};



