  //类只能在堆上实例化
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
             std::cout << "ga construct \n";
         }

         ~GC()
         {
           //析构时释放资源
		   std::cout << "ga delete instance \n";
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

 private:
     //外部禁止调用 new运算符 
     void* operator new(std::size_t count)
     {

     }

     void* operator new[](std::size_t count)
     {

     }
 };


int _tmain(int argc, _TCHAR* argv[])
{
    //具有垃圾回收功能
	CClassInstanceHeap::GetInstance()->print_log();
	
	//无法访问 operate new[]运算符
    //CClassInstanceStack* pStack = new CClassInstanceStack[10];
    CClassInstanceStack  stack;
    stack.print_log();
	
    return 0;
}


