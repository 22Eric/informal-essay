介绍一些基础的C++设计模式。

## 1.Template Method

先在父类中写好框架，把需要子类完成的功能设计为virtual函数，让子类overide这个函数来完成具体的工作。

当我们用子类的对象调用父类的函数的过程中，如果该函数里面包含有这种被重写的virtual函数，就会调用子类自己重写的函数。

## 2.观察者模式

```c++
#include <iostream>
#include <vector>

class Observer;

class Subject {
public:
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify() = 0;
};

class Observer {
public:
    virtual void update() = 0;
};

class ConcreteSubject : public Subject {
private:
    std::vector<Observer*> observers;
    int state;

public:
    void attach(Observer* observer) override {
        observers.push_back(observer);
    }

    void detach(Observer* observer) override {
        for (auto it = observers.begin(); it != observers.end(); ++it) {
            if (*it == observer) {
                observers.erase(it);
                break;
            }
        }
    }

    void notify() override {
        for (Observer* observer : observers) {
            observer->update();
        }
    }

    void setState(int newState) {
        state = newState;
        notify();
    }

    int getState() const {
        return state;
    }
};

class ConcreteObserver : public Observer {
private:
    ConcreteSubject* subject;

public:
    ConcreteObserver(ConcreteSubject* s) : subject(s) {}

    void update() override {
        int newState = subject->getState();
        std::cout << "Observer: State changed to " << newState << std::endl;
    }
};

int main() {
    ConcreteSubject subject;
    ConcreteObserver observer1(&subject);
    ConcreteObserver observer2(&subject);

    subject.attach(&observer1);
    subject.attach(&observer2);

    subject.setState(10);
    subject.setState(20);

    subject.detach(&observer1);

    subject.setState(30);

    return 0;
}



//观察者模式2
#include <iostream>
#include <vector>


class ConcreteSubject;
class ConcreteObserver;
class Observer;
class Subject;
class OpcValue;

class OpcValue
{
private:
    std::string Name;
    std::string Value;
    std::string OPCDataType;

public:
    
    OpcValue()
    {
        Name = "";
        Value = "";
        OPCDataType = "";
    }
    
    
    OpcValue(std::string name, std::string value):Name(name),Value(value)
    {
        OPCDataType = "";
    }


    std::string GetName()
    {
        return Name;
    }

    void SetName(std::string a)
    {
        Name = a;
    }

    std::string GetValue()
    {
        return Value;
    }

    void SetValue(std::string a)
    {
        Value = a;
    }

    std::string GetOPCDataType()
    {
        return OPCDataType;
    }

    void SetOPCDataType(std::string a)
    {
        OPCDataType = a;
    }

};


class Subject {
public:
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify(int) = 0;
    virtual std::string getName(int i) = 0;
    virtual std::string getValue(int i) = 0;
    virtual void setState(int i, std::string newValue) = 0;
};

class Observer {
public:
    virtual void update(int) = 0;
};

class ConcreteSubject :public Subject {
private:
    std::vector<Observer*> observers;
    //Observer* concreteObserver;

    std::vector<OpcValue> opcValueList ;

public:

    ConcreteSubject()
    {
        InitOpcValueList();
    }

    void InitOpcValueList()
    {
        OpcValue opc("w","2.12");
        OpcValue opc2("q","1");
        opcValueList.push_back(opc);
        opcValueList.push_back(opc2);


    }


    void attach(Observer* observer)  {
        observers.push_back(observer);
    }

    void detach(Observer* observer)  {
        for (auto it = observers.begin(); it != observers.end(); ++it) {
            if (*it == observer) {
                observers.erase(it);
                break;
            }
        }
    }

    void notify(int i)  {
        for (Observer* observer : observers) {
            observer->update(i);
        }
        
    }

    void setState(int i , std::string newValue) {
        opcValueList[i].SetValue(newValue);
        notify(i);
    }

    std::string getName(int i)  {
        return opcValueList[i].GetName();
    }

    std::string getValue(int i) {
        return opcValueList[i].GetValue();
    }


};

class ConcreteObserver : public Observer {
private:
    Subject* subject;

public:
    ConcreteObserver(Subject* s) : subject(s) {}

    void update(int i) override {


        std::string Name = subject->getName(i);
        std::string Value = subject->getValue(i);
       
        //int newState = subject->getState();
        std::cout << "Name: " << Name <<", NewValue: "<< Value << std::endl;
    }
};





int main() 
{
    Subject* subject = new ConcreteSubject();

    //observer1、observer2 观察subject
    ConcreteObserver observer1(subject);
   // ConcreteObserver observer2(&subject);
    

    //subject 接受observer1、observer2的观察
    subject->attach(&observer1);
   //subject.attach(&observer2);

    subject->setState(0, "11");
    






    return 0;
}

```

在上述示例中，`Subject` 类表示主题，有 `attach`、`detach` 和 `notify` 方法来管理观察者。`ConcreteSubject` 是具体的主题类，维护一个状态并在状态变化时通知观察者。

`Observer` 是观察者抽象类，定义了一个 `update` 方法，用于在主题状态变化时执行更新操作。`ConcreteObserver` 是具体的观察者类，它持有一个主题对象，并在 `update` 方法中获取主题状态的变化。

在 `main` 函数中，我们创建了一个主题对象和两个观察者对象，然后通过 `attach` 方法将观察者绑定到主题上。当主题状态发生变化时，观察者会收到通知并更新。

这个示例演示了观察者模式的基本工作原理，通过观察者模式，主题和观察者之间实现了解耦，从而使系统更具有灵活性和可扩展性。



## 3.Composite

委托+继承

```c++
class Component{
  int value;
public:
    Componet(int val){ value = val;}
    virtual void add(Component *){}
};

class Primitive : public Component{
public:
    Primitive(int val):Component(val){}
};

class Composite : public Component{
    vector<Component *> c;
public:
    Composite(int val):Component(val){}
    void add(Component *elem)
    {
        c.push_back(elem);
    }
    
    
    
};
```

## 4.Prototype

委托+继承

一个父类想调用子类的func，可以在父类中存放子类的“原型”，即将指向子类的指针发送到父类，以指向父类的指针存放。

```c++
class A{
public:
    void addElemtoA(A *_a){a.push_back(_a);}  //把子类的原型放入a中
    virtual A* clone()=0;
    void findandClone(){a[0]->clone();}       //通过子类的原型访问子类的函数，通过子类的函数得到子类的对象
private:
    static vector<A*> a;

};

vector<A*> A::a;


class B : A{

public:

     virtual A* clone(){return new B(1);}
private:
    static B b;
    B(){addElemtoA(&b);}
    B(int){}


};
B B::b;

```

5. ### 工厂设计模式

   ```C++
   #include <iostream>
   
   // Abstract Product
   class Product {
   public:
       virtual void showInfo() = 0;
   };
   
   // Concrete Products
   class ConcreteProductA : public Product {
   public:
       void showInfo() override {
           std::cout << "This is ConcreteProductA." << std::endl;
       }
   };
   
   class ConcreteProductB : public Product {
   public:
       void showInfo() override {
           std::cout << "This is ConcreteProductB." << std::endl;
       }
   };
   
   // Abstract Factory
   class Factory {
   public:
       virtual Product* createProduct() = 0;
   };
   
   // Concrete Factories
   class ConcreteFactoryA : public Factory {
   public:
       Product* createProduct() override {
           return new ConcreteProductA();
       }
   };
   
   class ConcreteFactoryB : public Factory {
   public:
       Product* createProduct() override {
           return new ConcreteProductB();
       }
   };
   
   int main() {
       Factory* factoryA = new ConcreteFactoryA();
       Product* productA = factoryA->createProduct();
       productA->showInfo();
   
       Factory* factoryB = new ConcreteFactoryB();
       Product* productB = factoryB->createProduct();
       productB->showInfo();
   
       delete factoryA;
       delete factoryB;
       delete productA;
       delete productB;
   
       return 0;
   }
   
   ```

   在这个示例中，我们有两个具体的产品类 `ConcreteProductA` 和 `ConcreteProductB`，它们都继承自抽象产品类 `Product`。每个产品类都有一个 `showInfo` 方法来展示产品信息。

   然后，我们定义了一个抽象工厂类 `Factory`，其中有一个纯虚函数 `createProduct`，用于创建产品。接着，我们有两个具体的工厂类 `ConcreteFactoryA` 和 `ConcreteFactoryB`，它们分别实现了 `createProduct` 方法来创建不同的产品。

   在 `main` 函数中，我们可以看到如何使用工厂模式来创建不同的产品。客户端代码通过工厂类来创建产品，而无需直接与具体产品类耦合。这样可以使代码更加灵活和可维护。

## 6. 装饰者模式

```c++
#include <iostream>
#include <vector>

using namespace std;


class Coffee
{
    
public:
    virtual void getDescription()  = 0;
    virtual double cost() = 0;

};

//浓缩咖啡类
class Espresso : public Coffee
{
public:
    void getDescription() override
    {
        cout << "浓缩咖啡";
    }

    double cost() override
    {
        return 2;
    }
};


class CondimentDecorator :public Coffee
{
protected:

    //如果将 coffee 设为private，派生类无法访问，所以改为protect
    Coffee* coffee;

public:
    CondimentDecorator(Coffee* c): coffee(c) {}
    void getDescription() override
    {
        coffee->getDescription();
    }

    double cost() override
    {
        return coffee->cost();
    }
};


class Mocha : public CondimentDecorator
{
private:
    //Coffee* coffee;

public:
    Mocha(Coffee* c) : CondimentDecorator(c) {}

    void getDescription() override
    {
        coffee->getDescription();
        cout << "加了摩卡";
    }

    double cost() override
    {
        return coffee->cost() + 1;
    }

};

class Whip : public CondimentDecorator
{
private:

    //把派生类的coffe放到基类上
   // Coffee* coffee;

public:
    Whip(Coffee* c) :CondimentDecorator(c) {}

    void getDescription() override
    {
        coffee->getDescription();
        cout << "加了奶泡";
    }

    double cost() override
    {
        return coffee->cost() + 0.5;
    }

};




int main() 
{
    Coffee* coffee = new Espresso();
    
    coffee->getDescription();
    cout << "  价格是：" << coffee->cost() << endl;


    Mocha mocha(coffee);
    mocha.getDescription();
    cout << "  价格是：" << mocha.cost() << endl;


    Whip whip(&mocha);
    whip.getDescription();
    cout << "  价格是：" << whip.cost() << endl;

    return 0;
}

```

在这个例子中，`Coffee` 是一个抽象基类，表示咖啡。`Espresso` 是一个具体的咖啡类，实现了抽象基类的接口。

`CondimentDecorator` 是装饰者的基类，包含一个指向被装饰对象的指针。`Mocha` 和 `Whip` 是具体的装饰者类，分别在咖啡上添加摩卡和奶泡。

通过将不同的装饰者组合在一起，我们可以在运行时动态地为咖啡添加不同的调料，而不需要修改原始咖啡类的代码。这就是装饰者模式的精髓所在。

### 7. 策略模式

```c++
#include <iostream>

// 策略接口：折扣策略
class DiscountStrategy {
public:
    virtual double applyDiscount(double amount) const = 0;
};

// 具体策略类：无折扣
class NoDiscount : public DiscountStrategy {
public:
    double applyDiscount(double amount) const override {
        return amount;
    }
};

// 具体策略类：打折折扣
class PercentageDiscount : public DiscountStrategy {
private:
    double discountPercentage;

public:
    PercentageDiscount(double percentage) : discountPercentage(percentage) {}

    double applyDiscount(double amount) const override {
        return amount * (1 - discountPercentage / 100);
    }
};

// 上下文：订单
class Order {
private:
    double orderAmount;
    DiscountStrategy* discountStrategy;

public:
    Order(double amount, DiscountStrategy* strategy) : orderAmount(amount), discountStrategy(strategy) {}

    void setDiscountStrategy(DiscountStrategy* strategy) {
        discountStrategy = strategy;
    }

    double calculateTotal() const {
        double discountedAmount = discountStrategy->applyDiscount(orderAmount);
        return discountedAmount;
    }
};

int main() {
    Order order1(100.0, new NoDiscount());
    std::cout << "Total amount (No Discount): $" << order1.calculateTotal() << std::endl;

    Order order2(200.0, new PercentageDiscount(20.0));
    std::cout << "Total amount (20% Discount): $" << order2.calculateTotal() << std::endl;

    order2.setDiscountStrategy(new PercentageDiscount(15.0));
    std::cout << "Total amount (15% Discount): $" << order2.calculateTotal() << std::endl;

    delete order1;
    delete order2;

    return 0;
}

```

在这个例子中，`DiscountStrategy` 是策略接口，定义了应用折扣的方法。`NoDiscount` 和 `PercentageDiscount` 是具体的策略类，分别表示没有折扣和按百分比计算折扣。

`Order` 是上下文类，维护了订单的总金额和当前的折扣策略。通过设置不同的折扣策略，客户端可以动态地改变折扣计算方式。

策略模式允许在运行时选择不同的算法，而不需要改变上下文类的代码，从而实现了算法的独立变化和高度灵活性。

### 8. 观察者模式 + 策略模式

```c++
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Subject;
class OpcValue
{
private:
    std::string Name;
    std::string Value;
    std::string OPCDataType;

public:

    OpcValue()
    {
        Name = "";
        Value = "";
        OPCDataType = "";
    }


    OpcValue(std::string name, std::string value) :Name(name), Value(value)
    {
        OPCDataType = "";
    }


    std::string GetName()
    {
        return Name;
    }

    void SetName(std::string a)
    {
        Name = a;
    }

    std::string GetValue()
    {
        return Value;
    }

    void SetValue(std::string a)
    {
        Value = a;
    }

    std::string GetOPCDataType()
    {
        return OPCDataType;
    }

    void SetOPCDataType(std::string a)
    {
        OPCDataType = a;
    }

};


class Handle
{
protected:
    Subject* subject;
public:
    Handle(Subject* s): subject(s){}
    virtual void HandlePLCData(string value) = 0;
};
class LaserWidUploadHandle : public Handle
{
private:
    

public:
    LaserWidUploadHandle(Subject* subject) : Handle(subject) {}

    void HandlePLCData(string value) override
    {
        cout << "一些关于 LaserWidUpload的处理，value是" << value<< endl;
    }


};
class LaserFormuGetHandle : public Handle
{
private:


public:
    LaserFormuGetHandle(Subject* subject) : Handle(subject) {}
    void HandlePLCData(string value) override
    {
        cout << "一些关于 LaserFormuGet 的处理，value是" << value<<endl;
    }
};



class Subject
{
protected:
    //vector<OpcValue> v;
    //vector<Handle*> handleList;
    unordered_map<string, OpcValue> vMap;
    unordered_map<string, Handle*> strategyMap;

private:


public:
    virtual void initVector() = 0;
    virtual void setState(string name,string value) = 0;
    virtual void notify(string name, string value) = 0;
    virtual void attach(string name, Handle* handle) = 0;

};
class PLCSubject : public Subject
{
public:

    void initVector()
    {
        vMap["LaserWidUpload"] = OpcValue("LaserWidUpload", "0");
        vMap["LaserFormuGet"]  = OpcValue("LaserFormuGet", "0");
    }
    void setState(string name, string value) override
    {
        vMap[name].SetName(value);
        notify(name,value);
    }

    void attach(string name,Handle* handle) override
    {
        strategyMap[name] = handle;
    }
    void notify(string name,string value) override
    {
        strategyMap[name]->HandlePLCData(value);
    }


};



int main() 
{
    Subject* s = new PLCSubject();
    Handle* h1 = new LaserWidUploadHandle(s);
    Handle* h2 = new LaserFormuGetHandle(s);
    s->initVector();
    
    s->attach("LaserFormuGet",h2);
    s->attach("LaserWidUpload", h1);




    s->setState("LaserWidUpload","11");
    s->setState("LaserFormuGet", "12");



    delete s;
    delete h1;
    delete h2;
    
    return 0;
}

```

### 9. 适配器模式

```c++
#include <iostream>

// 目标接口
class Target {
public:
    virtual void request() = 0;
};

// 被适配类
class Adaptee {
public:
    void specificRequest() {
        std::cout << "Adaptee's specific request" << std::endl;
    }
};

// 适配器类
class Adapter : public Target {
private:
    Adaptee* adaptee;
    
public:
    Adapter(Adaptee* a) : adaptee(a) {}
    
    void request() override {
        std::cout << "Adapter's request, using Adaptee's functionality: ";
        adaptee->specificRequest();
    }
};

int main() {
    Adaptee* adaptee = new Adaptee();
    Target* target = new Adapter(adaptee);
    
    target->request();
    
    delete target;
    delete adaptee;
    
    return 0;
}

```

在这个示例中，`Target` 是目标接口，`Adaptee` 是被适配类，`Adapter` 是适配器类。`Adapter` 继承了 `Target` 接口，并在其 `request` 方法中调用了 `Adaptee` 类的 `specificRequest` 方法，从而将两者协同工作。这就是适配器模式的典型应用。

### 10.  代理模式

代理模式（Proxy Pattern）是一种结构性设计模式，用于提供一个代理对象，以控制对另一个对象的访问。代理模式可以在不改变原始类的情况下，增加一些额外的功能，例如延迟加载、访问控制、缓存等

```c++
#include <iostream>

// 抽象主题
class Subject {
public:
    virtual void request() = 0;
};

// 真实主题
class RealSubject : public Subject {
public:
    void request() override {
        std::cout << "RealSubject handles the request." << std::endl;
    }
};

// 代理
class Proxy : public Subject {
private:
    RealSubject* realSubject;
    
public:
    Proxy() : realSubject(nullptr) {}
    
    void request() override {
        if (realSubject == nullptr) {
            realSubject = new RealSubject();
        }
        std::cout << "Proxy handles the request by delegating to RealSubject: ";
        realSubject->request();
    }
    
    ~Proxy() {
        delete realSubject;
    }
};

int main() {
    Proxy proxy;
    
    proxy.request();
    proxy.request();
    
    return 0;
}

```

在这个示例中，`Subject` 是抽象主题接口，`RealSubject` 是真实主题，`Proxy` 是代理类。`Proxy` 类内部持有一个 `RealSubject` 类的引用，在代理的 `request` 方法中通过代理来控制对真实主题的访问。第一次调用 `proxy.request()` 时，代理会创建一个真实主题对象并调用它的方法，之后的调用则直接委托给真实主题处理。这就是代理模式的典型应用。
