
#include<iostream>

class defaultConstructorClass
{
};

class fruit
{
private:
    int weight;
    double price;
//constructor initialize everything in the object (member initialization list instead of assignments)
//order is correct
public:
    fruit(int w, double p):
        weight(w),
        price(p)
   {
       std::cout<<"Fruit constructor\n";                        
   }                        
   fruit(const fruit &f):
   weight(f.weight),
   price(f.price)
   {
       std::cout<<"Fruit copy-constructor\n";
   
   }
   fruit& operator=(const fruit &f)
   {
       std::cout<<"Fruit assignment\n";
       this->weight=f.weight;
       this->price=f.price;
               return *this;
   }
     ~fruit(){
         std::cout<<"Fruit destructor\n";
     }
    int getWeight() {
        return weight;
    }
};



class apple : public fruit
{
private:
    int type;
public:
    apple(int w, double p, int t): fruit(w,p),
        type(t)
    {
        std::cout<<"Apple constructor\n";
    }
    ~apple();
    apple(const apple &a):
    fruit(a),
    type(a.type)
    {
       std::cout<<"Apple copy-constructor\n";
   }
   apple& operator=(const apple &a){
       fruit::operator=(a);
       std::cout<<"Apple assignment\n";
       this->type=a.type;
               return *this;
   }
    
};


apple::~apple()
{
    std::cout<<"Apple destructor\n";
}

class vegetable
{
    private:
        int weight;
        double price;
        
    public:
    vegetable(int w, double p):
            weight(w),
            price(p)
    {
        std::cout<<"Fruit constructor\n";                        
    };                 
        vegetable(){

        }
      
        ~vegetable(){
            std::cout<<"Vegetable destructor\n";
        }
    private:
         vegetable(const vegetable &v);
  
         vegetable& operator=(const vegetable &v);
};

class tomato : private vegetable
{
private:
    int type;
public:
    tomato(int w, double p, int t): vegetable(w,p),
        type(t)
    {
        std::cout<<"Tomato constructor\n";
    }
     ~tomato(){
            std::cout<<"Tomato destructor\n";
        }
    
};




int main(){
    defaultConstructorClass d1;  //call defauld constructor from class
    defaultConstructorClass d2=d1; //copy-constructor from empty class
    d2=d1; //copy assignment from empty class


    //manual initialization of an int
    int w=100;

    {
        fruit f3(10,3);
        apple a3(10,2,3);
    }

    fruit f1(w,2.5); //fruit constructor
    apple a1(w,1.76,2); //fruit constructor, apple constructor
    fruit f2(f1); //fruit copy-constructor
    apple a2(a1); //fruit copy-constructor, apple copy-constructor
    a1=a2; //fruit assignment, apple assignment
    f2=f1; //fruit assignment
    f2=a2; //fruit assignment
    
    tomato t1(1,2,3);
    vegetable v1(1,2);

    /*copy constructor and assignment are not allowed (in superclass vegetable this methods are private)
    tomato t2(t1);
    t2=t1;
    vegetable v2(v1);
    v2=v1;
    */


    //finally destructors for all objects created
    return 0;
}
