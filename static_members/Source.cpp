

struct Foo;
struct S {
	static int a[];  // declaration, incomplete type
	static Foo x;  // same
	static S s;  // same
	constexpr static int f{ 1 };  // must be complete
	const static int n = 1;
	const static int k;
};
int S::a[10];  // definition, complete type
struct Foo {};
Foo S::x;  // same
S S::s;  // same
const int S::k = 7;