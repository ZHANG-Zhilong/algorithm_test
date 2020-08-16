#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <stack>
#include <queue>

using namespace std;

class Pet {
protected :
    string type;
public :
    string getPetType() {
        return this->type;
    }
};

class Dog : public Pet {
public:
    Dog() {
        this->type = "dog";
    }
};

class Cat : public Pet {
public :
    Cat() {
        this->type = "cat";
    }
};

class QueuePet {
private:
    Pet _pet;
    int _count;
public:
    QueuePet(Pet pet, int count);

    Pet getPet();

    int getCount();

    string getPetType();
};

QueuePet::QueuePet(Pet pet, int count) {
    _pet = pet;
    _count = count;
}

Pet QueuePet::getPet() {
    return _pet;
}

int QueuePet::getCount() {
    return _count;
}

string QueuePet::getPetType() {
    return this->_pet.getPetType();
}

class DogCatQueue {
private:
    queue<QueuePet> dogq;
    queue<QueuePet> catq;
    int _index;
public:
    DogCatQueue();

    int add(Pet pet);

    Pet pollAll();

    Pet pollDog();

    Pet pollCat();

    bool isEmpty();

    bool isDogEmpty();

    bool isCatEmpty();
};

DogCatQueue::DogCatQueue() {
    _index = 0;
}

int DogCatQueue::add(Pet pet) {
    if (pet.getPetType() == "dog") {
        QueuePet qpd(pet, _index++);
        dogq.push(qpd);
    } else if (pet.getPetType() == "cat") {
        QueuePet qpc(pet, _index++);
        catq.push(qpc);
    } else {
        cout << "unvalid type\n";
        return -1;
    }
    return 0;
}

Pet DogCatQueue::pollAll() {
    if (!dogq.empty() && !catq.empty()) {
        if (dogq.front().getCount() < catq.front().getCount()) {
            QueuePet rtv = dogq.front();
            dogq.pop();
            return rtv.getPet();
        } else {
            QueuePet rtv = catq.front();
            QueuePet rtv = catq.front();
            catq.pop();
            return rtv.getPet();
        }
    } else if (!dogq.empty()) {
        QueuePet rtv = dogq.front();
        dogq.pop();
        return rtv.getPet();
    } else if (!catq.empty()) {
        QueuePet rtv = catq.front();
        catq.pop();
        return rtv.getPet();
    } else {
        cout << "allpull err, the queue is empty.\n";
        exit(-1);
    }
}

Pet DogCatQueue::pollCat() {
    if (catq.empty()) {
        cout << "pollCat err, the cat queue is empty\n";
        exit(-1);
    }
    Pet rtv = catq.front().getPet();
    catq.pop();
    return rtv;
}

Pet DogCatQueue::pollDog() {
    if (dogq.empty()) {
        cout << "pollDog err, the dog queue is empty\n";
        exit(-1);
    }
    Pet rtv = dogq.front().getPet();
    dogq.pop();
    return rtv;
}

bool DogCatQueue::isEmpty() {
    return (dogq.empty() && catq.empty());
}

bool DogCatQueue::isCatEmpty() {
    return catq.empty();
}

bool DogCatQueue::isDogEmpty() {
    return dogq.empty();
}

int main() {
    bool succeed = false;
    Pet *pet;
    Cat cat1;
    Cat cat2;
    Dog dog1;
    Cat cat3;
    DogCatQueue dcq;
    dcq.add(cat1);
    dcq.add(cat2);
    dcq.add(dog1);
    dcq.add(cat3);

    cout << dcq.pollAll().getPetType() << endl;
    cout << dcq.pollAll().getPetType() << endl;
    cout << dcq.pollAll().getPetType() << endl;
    cout << dcq.pollAll().getPetType() << endl;

    string str = succeed ? "\nnice" : "\nfreaking fucking fuck!";
    cout << str << endl;
    system("pause");
}