
#include<iostream>
#include<memory>
#include<mutex>
class defaultConstructorClass
{
};

class fruit
{
private:
    int weight;
    double price;
    bool locked=false;
//constructor initialize everything in the object (member initialization list instead of assignments)
//order is correct
public:
    fruit(int w, double p):
        weight(w),
        price(p)
   {
       //std::cout<<"Fruit constructor\n";
   }
   fruit(const fruit &f):
   weight(f.weight),
   price(f.price)
   {
       //std::cout<<"Fruit copy-constructor\n";

   }
   fruit& operator=(const fruit &f)
   {
       //std::cout<<"Fruit assignment\n";
       if(this==&f)
            return *this;
       this->weight=f.weight;
       this->price=f.price;
        return *this;
   }

     ~fruit(){
         //std::cout<<"Fruit destructor\n";
     }
    int getWeight() {
        return weight;
    }
    void setIsLocked(bool l){
        locked=l;
    }
    void verifyLock(){
        if(this->locked){
            std::cout<<"IS LOCKED"<<std::endl;
        }
        else
        std::cout<<"IS UNLOCKED"<<std::endl;

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
        //std::cout<<"Apple constructor\n";
    }
    ~apple();
    apple(const apple &a):
    fruit(a),
    type(a.type)
    {
       //std::cout<<"Apple copy-constructor\n";
   }
   apple& operator=(const apple &a){
       fruit::operator=(a);
       //std::cout<<"Apple assignment\n";
       //this->type=a.type;
               return *this;
   }
   int getType(){
       return type;
   }

};


apple::~apple()
{
    //std::cout<<"Apple destructor\n";
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
        //std::cout<<"Fruit constructor\n";
    };
        vegetable(){

        }

        ~vegetable(){
            //std::cout<<"Vegetable destructor\n";
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
        //std::cout<<"Tomato constructor\n";
    }
     ~tomato(){
            //std::cout<<"Tomato destructor\n";
        }

};
void lock(fruit &f){
    std::cout<<"Lock mutex"<<std::endl;
    f.setIsLocked(true);
}
void unlock(fruit &f){
    std::cout<<"Unlock mutex"<<std::endl;
    f.setIsLocked(false);
}
class Lock{
    private:
    fruit &fruitlock;
    public:
    Lock(fruit(&fruit))
    :fruitlock(fruit)
    {
        //aquire resource
        lock(fruitlock);
    }
    ~Lock(){
        //release resource
        unlock(fruitlock);
    };
};

using namespace std;
fruit* createFruitInstance(int w, int p){
    return (new fruit(w,p));
}



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

   //tema2
   //item10
    fruit fruit1(2,3);
    fruit fruit2(1,1);
    fruit fruit3(5,4);
    fruit1=fruit2=fruit3;
    std::cout<<"\n"<<fruit1.getWeight()<<"\n";


    //item11->verificare cu if in assignment op. fruit

    //item12 ->stergere schimbare type din assignment
    //apple2 nu ma avea tipul schimbat
    apple apple1(1,2,4);
    apple apple2(7,9,3);
    apple2=apple1;
    std::cout<<"\n"<<apple2.getType();

    //tema3
    //item13
    //auto_ptr
    auto_ptr<fruit> fruitAuto(createFruitInstance(1,2));
    std::cout<<"\nAuto_ptr "<<fruitAuto->getWeight();
    auto_ptr<fruit> fruitAuto2(fruitAuto);
    std::cout<<"\nAuto_ptr2 "<<fruitAuto2->getWeight();
    /*Segmentation fault fruitAuto=null dupa copiere
    std::cout<<"\nAuto_ptr "<<fruitAuto->getWeight();
    */

    //shared_ptr
    //same adress
    shared_ptr<fruit> fruitShared(createFruitInstance(3,4));
    std::cout<<"\nShared_ptr "<<fruitShared->getWeight();
    shared_ptr<fruit> fruitShared2(fruitShared);
    shared_ptr<fruit> fruitShared3(fruitShared2);
    std::cout<<"\nShared_ptr3 "<<fruitShared3->getWeight();
    std::cout<<"\nNumber of copies: "<<fruitShared.use_count();
    std::cout<<"\n";
    //item14
    fruit fruitToLock(10,11);
    fruitToLock.verifyLock();
    Lock *lockForFruit= new Lock(fruitToLock);
    fruitToLock.verifyLock();
    delete lockForFruit;
    fruitToLock.verifyLock();


    //finally destructors for all objects created
    return 0;
}
