/*
   想要达到只能在堆上创建对象，其设计要求如下：
   1.该类的构造函数或者析构函数至少有一个是private属性
   2.提供一个创建对象接口，用于类内部创建堆对象
   3.提供堆对象销毁函数，这个非必须，需要看析构是否public属性
*/
class COnlyHeap
{

private:
    COnlyHeap():m_data(0){}
    ~COnlyHeap(){}

public:
    static COnlyHeap* CreateObj()
    {
        return new (std::nothrow) COnlyHeap;
    }

    static void DestroyObj(COnlyHeap* &pInstance)
    {
          if (NULL != pInstance)
          {
              delete pInstance;
              pInstance = NULL;
          }
    }

    int m_data;
};


//如何设计类只能建立在栈
class CClassInstanceStack
{
public:
    CClassInstanceStack()
    {
        std::cout << "call construct function\n";
    }

    ~CClassInstanceStack()
    {
        std::cout << "call destruction function\n";
    }

    void print_log()
    {
        std::cout << "call print log\n";
    }

    /**/
    //new 运算符是private,外部禁止调用  因此该类只能在栈上创建
    //重载了new运算符也需要重载delete运算符
private:

    void* operator new(std::size_t count){}

    void* operator new[](std::size_t count){}

    void operator delete[]( void* ptr ){}

    void operator delete( void* ptr ){}
};


//类只能在堆上实例化
//如何设计类只能建立在堆上&单例模式只有一个模式
class CClassInstanceHeap
{
private:
    CClassInstanceHeap()
    {
    }

    ~CClassInstanceHeap()
    {

    }
public: 
    static CClassInstanceHeap* GetInstance()
    {
        return m_pIns;
    }

    void print_log()
    {
        std::cout << "print log by instance\n";
    }

private:
    // 是CClassInstanceHeap的辅助类，用于资源的释放
    class GC
    {
    public:
        GC()
        {
            std::cout << "gc construct \n";
        }

        ~GC()
        {
            //析构时释放资源
            std::cout << "gc delete instance \n";
            if (m_pIns != NULL)
            {
                delete m_pIns;
                m_pIns = NULL;
            }
        }
    };


private:
    static  CClassInstanceHeap* m_pIns;
    static  GC m_gc;
};

//懒汉式 避免了多线程竞争问题   
//对象的初始化
CClassInstanceHeap*  CClassInstanceHeap::m_pIns  = new CClassInstanceHeap;
CClassInstanceHeap::GC CClassInstanceHeap::m_gc;

