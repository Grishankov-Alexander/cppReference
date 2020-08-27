#include <iostream>
#include <type_traits>

// SFINAE implementation 3
namespace ns1 {
	
	struct Test {
		typedef int foo;
	};

	template<typename T>
	bool has_foo_type(typename T::foo) { return true; }  // definition 1

	template<typename T>
	bool has_foo_type(T) { return false; }  // definition 2

	int main() {
		bool a = has_foo_type<Test>(1);
		bool b = has_foo_type<int>(1);
		return 0;
	}
}


struct Foo {
	using foobar = float;
};


// SFINAE implementation 2
namespace ns2 {
	
	template<typename T>
	struct has_typedef_foobar {
		// Types "yes" and "no" are guaranteed to have different sizes,
		// specifically sizeof(yes) == 1 and sizeof(no) == 2.
		typedef char yes[1];
		typedef char no[2];

		template<typename C>
		static yes &test(typename C::foobar *);
		template<typename>
		static no &test(...);

		// If the "sizeof" of the result of calling test<T>(nullptr) is equal to
		// sizeof(yes), the first overload worked and T has a nested type named
		// foobar.
		static const bool value = sizeof(test<T>(nullptr)) == sizeof(yes);
	};

	template<typename T>
	static bool has_typedef_foobar_v = has_typedef_foobar<T>::value;

	int main()
	{
		bool b1 = has_typedef_foobar_v<Foo>;
		bool b2 = has_typedef_foobar_v<int>;
		return 0;
	}
}


// C++11
namespace ns3 {
	
	template<typename... Ts>
	using void_t = void;

	template<typename A, typename = void>
	struct has_typedef_foobar : std::false_type {};

	template<typename T>
	struct has_typedef_foobar<T, void_t<typename T::foobar>> : std::true_type {};

	int main()
	{
		std::cout << std::boolalpha;
		bool b1 =  has_typedef_foobar<Foo>::value;
		bool b2 =  has_typedef_foobar<int>::value;
		return 0;
	}
}


// experimental as of 2020
namespace ns4 {

	template<typename T>
	using has_typedef_foobar_t = typename T::foobar;

	int main()
	{
		/* Following lines are not working yet
		*	std::cout << std::is_detected<has_typedef_foobar_t, int>::value << std::endl;
		*	std::cout << std::is_detected<has_typedef_foobar_t, Foo>::value << std::endl;
		*/
		return 0;
	}
}


int main() {
	ns1::main();
	ns2::main();
	ns3::main();
	ns4::main();
}