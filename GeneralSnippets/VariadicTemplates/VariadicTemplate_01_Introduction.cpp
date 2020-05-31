// =====================================================================================
// Variadic Templates: Introduction
// =====================================================================================

#include <iostream>
#include <string>
#include <memory>

namespace VariadicTemplates_01 {

    /* Erstes Beispiel f�r ein variadisches Template:
    */

    // Non-recursive template part (regular template)
    template<typename T>
    T adder(T v) {
        return v;
    }

    // Recursive template part
    // Note: ... specifies a so called 'parameter pack')
    template<typename T, typename ...Args>
    T adder(T first, Args... args) {
        return first + adder(args...);
    }

    void test_01() {

        int sum = adder(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
        std::cout << "Sum from 1 up to 10: " << sum << std::endl;

        std::string stringConcat = adder(
            std::string("ABC"),
            std::string("DEF"),
            std::string("GHI"),
            std::string("JKL"),
            std::string("MNO")
        );
        std::cout << "String Concatenation: " << stringConcat << std::endl;
    }

    // =================================================================================

    // Ein variadisches Template in zwei Realisierungsvarianten:
    //
    // a) Eine rekursive Template Funktion
    // b) Eine nicht-rekursive Non-Template Funktion

    void print()
    {
    }

    template<typename T, typename... Types>
    void print(T firstArg, Types... args)
    {
        std::cout << firstArg << std::endl; // print first argument
        print(args...); // call print() for remaining arguments
    }

    // Oder:
    // a) Eine rekursive Template Funktion
    // b) Eine nicht-rekursive Template Funktion
    //
    // Man beachte: Wenn sich zwei Template Funktionen nur um das Parameter Pack
    // unterscheiden, wird - wenn m�glich - die Template Funktionen ohne Parameter Pack bevorzugt:

    //template<typename T>
    //void print(T arg)
    //{
    //    std::cout << arg << std::endl; // print passed argument
    //}

    //template<typename T, typename... Types>
    //void print(T firstArg, Types... args)
    //{
    //    print(firstArg); // call print() for first argument
    //    print(args...);  // call print() for remaining arguments
    //}

    void test_02()
    {
        std::string s("World");
        print(123.456, "Hello", s);

        // same as
        print<double, const char*, std::string>(123.456, "Hello", s);
    }
}


namespace VariadicTemplates_02 {

    // =============================================================
    // "Unpacking" a parameter pack to call a matching constructor
    // =============================================================

    /* Zweites Beispiel f�r ein variadisches Template:
    */

    // Test Class - only c'tors are interesting ..
    //
    class Unknown {
    private:
        int m_var1;
        int m_var2;
        int m_var3;

    public:
        Unknown() : m_var1(-1), m_var2(-1), m_var3(-1) {
            std::cout << "c'tor()" << std::endl;
        }

        Unknown(int n) : m_var1(n), m_var2(-1), m_var3(-1) {
            std::cout << "c'tor(int)" << std::endl;
        }

        Unknown(int n, int m) : m_var1(n), m_var2(m), m_var3(-1) {
            std::cout << "c'tor(int, int)" << std::endl;
        }

        Unknown(int n, int m, int k) : m_var1(n), m_var2(m), m_var3(k) {
            std::cout << "c'tor(int, int, int)" << std::endl;
        }

        friend std::ostream& operator<< (std::ostream&, const Unknown&);
    };

    std::ostream& operator<< (std::ostream& os, const Unknown& obj) {
        os << "var1: " << obj.m_var1
            << ", var2: " << obj.m_var2
            << ", var3: " << obj.m_var3 << std::endl;
        return os;
    }

    // =============================================================
    // variadic template

    template<typename T, typename... Args>
    T make_an_object(Args&&... args)
    {
        return T(std::forward<Args>(args)...);
    }

    // =============================================================

    void test_01()
    {
        Unknown u1 = make_an_object<Unknown>();
        std::cout << u1 << std::endl;

        Unknown u2 = make_an_object<Unknown>(1);
        std::cout << u2 << std::endl;

        Unknown u3 = make_an_object<Unknown>(10, 11);
        std::cout << u3 << std::endl;

        Unknown u4 = make_an_object<Unknown>(100, 101, 102);
        std::cout << u4 << std::endl;

        // doesn't compile
        // Unknown u5 = make_an_object<Unknown>(1000, 1001, 1002, 1003);
        // std::cout << u4 << std::endl;

        int n = 50;
        const int m = 52;

        Unknown u6 = make_an_object<Unknown>(n, 51, m);
        std::cout << u6 << std::endl;
    }
}

namespace VariadicTemplates_03 {

    // =============================================================
    // Anwendungsfall bei std::unique_ptr
    // =============================================================

    // Test Class - only c'tors (and d'tor) are important ..

    class Unknown {

    public:
        Unknown() {
            std::cout << "c'tor()" << std::endl;
        }

        Unknown(int n) {
            std::cout << "c'tor(int)" << std::endl;
        }

        Unknown(int n, int m) {
            std::cout << "c'tor(int, int)" << std::endl;
        }

        Unknown(int n, int m, int k) {
            std::cout << "c'tor(int, int, int)" << std::endl;
        }

        ~Unknown() {
            std::cout << "d'tor()" << std::endl;
        }
    };

    // =============================================================
    //  variadic template

    template<typename T, typename... Args>
    std::unique_ptr<T> my_make_unique(Args&&... args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

    // =============================================================

    void test_01()
    {
        std::unique_ptr<Unknown> up1 = my_make_unique<Unknown>();
        std::unique_ptr<Unknown> up2 = my_make_unique<Unknown>(1);
        std::unique_ptr<Unknown> up3 = my_make_unique<Unknown>(10, 11);
        std::unique_ptr<Unknown> up4 = my_make_unique<Unknown>(100, 101, 102);

        int n = 33, m = 34;
        std::unique_ptr<Unknown> up5 = my_make_unique<Unknown>(n, m);
    }
}

int main()
// int main_variadic_templates_intro()
{
    // using namespace VariadicTemplates_01;
    // test_01();
    // test_02();

    // using namespace VariadicTemplates_02;
    using namespace VariadicTemplates_03;
    test_01();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
