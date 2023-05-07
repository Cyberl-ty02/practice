#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct DogF;
struct DogM;
struct Puppy;

struct Animal {
    Animal(const string& name) :aname(name) {
        //cout << "Animal created: " << name << endl;
    }
    virtual ~Animal()
    {
        //cout << "Animal destroyed:" << aname << endl;
    }
    void bark()
    {
        std::cout << aname << " is barking..." << endl;
    }
    const string& name() {
        return aname;
    }
    string aname;
};
struct  Puppy :Animal {
    Puppy(const string& name) :Animal(name)
    {
        cout << "Poppy created:" << name << endl;
    }
    ~Puppy()
    {
        cout << "Poppy destroyed:" << name() << endl;
    }
    weak_ptr<DogF> father;
    weak_ptr<DogM> mother;
};
struct  DogF :Animal {
    DogF(const string& name) :Animal(name)
    {
        cout << "DogF created: " << name << endl;
    }
    ~DogF()
    {
        cout << "DogF destroyed:" << name() << endl;
    }
    vector<shared_ptr<Puppy>> offs;
    shared_ptr<DogM> peer;

};

struct DogM :Animal {
    DogM(const string& name) :Animal(name)
    {
        cout << "DogM created: " << name << endl;
    }
    ~DogM()
    {
        cout << "DogM destroyed:" << name() << endl;
    }

    vector<shared_ptr<Puppy>> offs; //offspring
    shared_ptr<DogF> peer;
};
namespace RelationMgr {

    void notifyPuppyEated(shared_ptr<Puppy>& pup)
    {

        if (shared_ptr<DogF>  fa = pup->father.lock())
        {
            auto pos = find(fa->offs.begin(), fa->offs.end(), pup);
            if (pos != fa->offs.end())
                fa->offs.erase(pos);
            cout << "Fa ref:" << fa.use_count() << " and Pup ref:" << pup.use_count() << endl;
        }


        if (shared_ptr<DogM>  mo = pup->mother.lock())
        {
            auto pos = find(mo->offs.begin(), mo->offs.end(), pup);
            if (pos != mo->offs.end())
                mo->offs.erase(pos);
            cout << "Mo ref:" << mo.use_count() << " and Pup ref:" << pup.use_count() << endl;
        }

    }

    void makeFather(shared_ptr<Puppy>& pup, shared_ptr<DogF> fa) {
        pup->father = fa;
        fa->offs.push_back(pup);
        cout << "Fa ref:" << fa.use_count() << " and Pup ref:" << pup.use_count() << endl;

    }
    void makeMother(shared_ptr<Puppy>& pup, shared_ptr<DogM> mo)
    {
        pup->mother = mo;
        mo->offs.push_back(pup);
        cout << "Mo ref:" << mo.use_count() << " and Pup ref:" << pup.use_count() << endl;
    }
    void pair(shared_ptr<DogF> a, shared_ptr<DogM> b)
    {
        a->peer = b;
        b->peer = a;
    }
};
struct Monster : Animal {
    Monster(const string& name) :Animal(name) {
        cout << "Monster created :" << name << endl;

    }
    ~Monster() {
        cout << "Monster destroyed: " << name() << endl;
    }

    void eatPuppy(shared_ptr<Puppy>& pup)
    {
        cout << pup->name() << " was eated by " << name() << endl;
        RelationMgr::notifyPuppyEated(pup);

        pup.reset();
    }

};
struct AnimalFactory {

    static shared_ptr<Puppy> createDog(const string& name)
    {
        return make_shared<Puppy>(name);
    }
    static shared_ptr<DogF> createDogF(const string& name)
    {
        return make_shared<DogF>(name);
    }
    static shared_ptr<DogM> createDogM(const string& name)
    {
        return make_shared<DogM>(name);
    }
    static unique_ptr<Monster> createMoster(const string& name)
    {
        return unique_ptr<Monster>(new Monster(name));
    }
};


int main()
{

    {
        shared_ptr<DogF>  f1 = AnimalFactory::createDogF("WC Father");
        shared_ptr<DogM>  m1 = AnimalFactory::createDogM("WC Mother");
        shared_ptr<Puppy>  d1 = AnimalFactory::createDog("wangcai");
        shared_ptr<Puppy>  d2 = AnimalFactory::createDog("orphan");

        RelationMgr::makeFather(d1, f1);
        RelationMgr::makeMother(d1, m1);


        unique_ptr<Monster> mon = AnimalFactory::createMoster("gesila");
        mon->eatPuppy(d1);
        mon->eatPuppy(d2);

    }
    cout << "end of world" << endl;
}