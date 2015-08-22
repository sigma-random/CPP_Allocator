
/*
 *		
 *		mailto: random1990s@gmail.com
 *
 *
 */

#ifndef _MALLOC_ALLOCATOR_
#define _MALLOC_ALLOCATOR_


#include <iostream>
#include <limits> 
#include <typeinfo> 


#define DEBUG 	true



template <typename T>
class malloc_allocator
{
	public:
		typedef	T 					value_type;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
	 	typedef std::size_t			size_type;  
	 	typedef std::ptrdiff_t 		difference_type;

	 	template<typename U>
		struct rebind 
		{
			typedef malloc_allocator<U> other;
		};


	public:

		malloc_allocator() throw();
	    malloc_allocator(const malloc_allocator &) throw();
	    template<typename U> malloc_allocator(const malloc_allocator<U> &) throw();
	    ~malloc_allocator() throw();

		bool operator==(const malloc_allocator &) const throw();
		bool operator!=(const malloc_allocator &) const throw();
		template<typename U> bool operator==(const malloc_allocator<U> &) const throw();
		template<typename U> bool operator!=(const malloc_allocator<U> &) const throw();

		size_type max_size() const throw();

	    // the use of u is unspecified, but it is intended as an aid to locality.
	    pointer allocate(size_type n, const_pointer u=0) throw(std::bad_alloc);

	    void deallocate(pointer p, size_type n) throw();

	    void construct(pointer p, const_reference val) throw();

	    void destroy(pointer p) throw();

};


template<> 
class malloc_allocator<void>
{
	public:
		typedef void value_type;
		typedef void *pointer;
		typedef const void *const_pointer;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		template<typename U> 
		struct rebind 
		{ 
			typedef malloc_allocator<U> other; 
		};

		malloc_allocator() throw() {}
		malloc_allocator(const malloc_allocator &) throw() {}
		template<typename U> malloc_allocator(const malloc_allocator<U> &) throw() {}
		~malloc_allocator() throw() {}
};




/*******************************************************************************/

template <typename T>
malloc_allocator<T>::malloc_allocator() 
throw()
{
	
}


template <typename T>
malloc_allocator<T>::malloc_allocator(const malloc_allocator &) 
throw()
{

}


template <typename T>
template<typename U> 
malloc_allocator<T>::malloc_allocator(const malloc_allocator<U> &) 
throw()
{

}


template <typename T>
malloc_allocator<T>::~malloc_allocator() 
throw()
{

}


template<typename T>
bool 
malloc_allocator<T>::operator==(const malloc_allocator<T> &other) const 
throw()
{
    return true;
}


template<typename T>
bool 
malloc_allocator<T>::operator!=(const malloc_allocator<T> &other) const 
throw()
{
    return !(*this==other);
}


template<typename T>
template<typename U>
bool 
malloc_allocator<T>::operator==(const malloc_allocator<U> &other) const 
throw()
{
    return ( (*this) == static_cast<typename malloc_allocator<U>::template rebind<T>::other>(other) );
}


template<typename T>
template<typename U>
bool 
malloc_allocator<T>::operator!=(const malloc_allocator<U> &other) const 
throw()
{
    return !(*this==other);
}


template<typename T>
typename malloc_allocator<T>::size_type 
malloc_allocator<T>::max_size() const
throw()
{
    // return ( static_cast<int>(-1) / sizeof(malloc_allocator<T>::size_type) ) ;
    return  std::numeric_limits<size_type>::max();
}


template <typename T>
typename malloc_allocator<T>::pointer 
malloc_allocator<T>::allocate(typename malloc_allocator<T>::size_type n, 
							  typename malloc_allocator<T>::const_pointer u) 
throw(std::bad_alloc) 
{ 
	void *p = NULL;
	p = std::malloc(n * sizeof(T));
	if (!p) {
		throw std::bad_alloc();	
	} 
	
	// logger
	if (DEBUG) {
		std::cout 	<< std::endl;
		std::cout 	<< "malloc_allocator<typename "
					<< typeid(T).name()
					<< ">::allocate(size=" 
					<< static_cast<size_type>(n)   
					<< ")" 
					<< "   ==>  "
					<< std::hex
					<< static_cast<void*>(p)  
					<< std::endl;
	}

	return static_cast<pointer>(p);
} 


template <typename T>
void 
malloc_allocator<T>::deallocate(typename malloc_allocator<T>::pointer p, 
								typename malloc_allocator<T>::size_type n) 
throw() 
{  
	std::free(p);  

	// logger
	if (DEBUG) {
		std::cout 	<< "malloc_allocator<typename "
					<< typeid(T).name()
					<< ">::deallocate(pointer p="
					<< std::hex 
					<< static_cast<void*>(p)   
					<< ")" 
					<< std::endl;
		std::cout 	<< std::endl;
	}
}


template <typename T>
void 
malloc_allocator<T>::construct(typename malloc_allocator<T>::pointer p, 
							   typename malloc_allocator<T>::const_reference var) 
throw()
{

	// new(p) T();						// construct
	new(p) T(var);					// copy construct

	// logger
	if (DEBUG) {
		std::cout 	<< "malloc_allocator<typename "
					<< typeid(T).name()
					<< ">::construct(pointer p="
					<< std::hex 
					<< static_cast<void*>(p)  
					// << ", const_reference var="
					// << std::hex 
					// << var 
					<< ")" 
					<< std::endl;
	}
}


template <typename T>
void 
malloc_allocator<T>::destroy(typename malloc_allocator<T>::pointer p) 
throw()
{ 

	p->~T(); 					// destruct

	// logger
	if (DEBUG) {
		std::cout 	<< "malloc_allocator<typename "
					<< typeid(T).name()
					<< ">::destroy(pointer p="
					<< std::hex 
					<< static_cast<void*>(p)   
					<< ")" 
					<< std::endl;
	}

}  



#endif