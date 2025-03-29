#pragma once

template <class T> 
class MyAllocator
{

private:
	using size_type = std::size_t;

	size_type allocCount=0;


public:
	using value_type = T;//����
	using pointer = T*;//��ַ
	using refrence = T&;//����

	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using propagate_on_container_move_assignment = std::true_type;

	MyAllocator() = default;
	~MyAllocator() = default;

	// ֧�ִ����� MyAllocator ��ʽת��
	template <class U>
	MyAllocator(const MyAllocator<U>&) noexcept {}


	//���°󶨺���
	template <class U>
	struct rebind
	{
		using other = MyAllocator<U>;
	};



	//�����㹻�Ĵ洢�ռ����洢T��n��ʵ����������ָ������ָ��
	pointer allocate(size_type n) {
		//operator new()���������ڴ� ����operator new()������C++��׼���ж����һ�������������ڶ��Ϸ����ڴ档 
		// value pointer ��һ��ָ��T���͵�ָ�룬n ��Ҫ������ڴ���������sizeof(T) ��ÿ��T���Ͷ���Ĵ�С��
		// operator new Ĭ�� ����void* ���ͣ�������Ҫʹ��static_cast��������ת��
		allocCount += n;

		return  static_cast<pointer>(operator new(n * sizeof(T)));
	}

	//�ͷŷ�����ڴ�
	void deallocate(pointer p, size_type n) {
		operator delete(p);
	}

	//��ָ�� p ָ��� �ѷ����ڴ� �ϣ�����һ�� U ���͵Ķ���
	template <class U, class... Args>
	void construct(U* p, Args&&... args) {
		new(p) U(std::forward<Args>(args)...);
	}


	//����pָ��Ķ������������
	template <class U>
	void destroy(U* p) {  // ģ�廯��֧����������
		p->~U();
	}

	//ĩβ�� const ��ʾ�ó�Ա�����ǳ�����Ա���������������޸ĵ������Ķ����״̬
	//������ const �����ͨ�� const ����/ָ�����
	//const ��Ա���� �����޸� ��Ա������
	//const ���� ֻ�ܵ��� const ��Ա������

	//����ڴ���
	size_type max_size() const noexcept {
		return std::numeric_limits<size_type>::max();
	}

	// ���ط������
	size_type get_allocations() const {  // �޸������� size_type
		return allocCount;
	}


};



