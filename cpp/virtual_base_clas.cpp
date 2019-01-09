//公共基类
class N
{
public:
    N(int data1, int data2, int data3) :
        m_data1(data1),
        m_data2(data2),
        m_data3(data3)
    {
        std::cout << "call common constructor" << std::endl;
    }
    virtual ~N(){}

    void    display()
    {
        std::cout << m_data1 << std::endl;
    }

public:
    int     m_data1;
    int     m_data2;
    int     m_data3;
};

//虚继承方式
class A : virtual public N
{
public:
    A() :N(11, 12, 13), m_a(1)
    {
        std::cout << "call class A constructor" << std::endl;
    }
    ~A(){}

public:
    int m_a;
};

//虚继承方式
class B :  virtual public N
{
public:
    B() :N(21, 22, 23), m_b(2)
    {
        std::cout << "call class B constructor" << std::endl;
    }
    ~B(){}

public:
    int m_b;
};

  // 类A和类B是虚继承方式
class C : public A, public B
{
public:
    //负责对直接基类的初始化 以及虚基类的初始化
    C() : A(), B(), N(31,32,33), 
        m_c(3)
    {
        std::cout << "call class C constructor" << std::endl;
    }
    void show()
    {
        std::cout << "m_c=" << m_c << std::endl;
    }

public:
    int m_c;
};


//此时基类N不是虚基类
class D : public N
{
public:
    //负责对基类的初始化
    D() :N(41, 42, 43),
        m_d(4)
    {
        std::cout << "call class D constructor" << std::endl;
    }
    void show()
    {
        std::cout << "m_d=" << m_d << std::endl;
    }

public:
    int m_d;
};


int _tmain(int argc,  _TCHAR* argv[])
{
    C data;   
    //直接使用基类数据
    data.m_data1 = 10;
    
    return 0;
}

