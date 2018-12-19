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
     class GA
     {
     public:
         GA()
         {
             std::cout << "ga construct \n";
         }

         ~GA()
         {
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
     static  GA m_ga;
 };
