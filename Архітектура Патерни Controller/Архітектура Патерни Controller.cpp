#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;

// Абстракція для посередника
class Mediator {
public:
    virtual void sendMessage(const string& message, class Colleague* colleague) = 0;
    virtual ~Mediator() = default;
};

// Абстракція для колег
class Colleague {
protected:
    Mediator* mediator;
public:
    Colleague(Mediator* mediator) : mediator(mediator) {}
    virtual void send(const string& message) = 0;
    virtual void receive(const string& message) = 0;
    virtual ~Colleague() = default;
};

// Конкретна реалізація посередника
class ConcreteMediator : public Mediator {
private:
    vector<Colleague*> colleagues;

public:
    void addColleague(Colleague* colleague) {
        colleagues.push_back(colleague);
    }

    void sendMessage(const string& message, Colleague* colleague) override {
        // Кожен колега отримує повідомлення, окрім того, хто його надіслав
        for (auto c : colleagues) {
            if (c != colleague) {
                c->receive(message);
            }
        }
    }
};

// Конкретний колега (користувач чату)
class ConcreteColleague : public Colleague {
private:
    string name;

public:
    ConcreteColleague(Mediator* mediator, const string& name) : Colleague(mediator), name(name) {}

    void send(const string& message) override {
        cout << name << " відправляє повідомлення: " << message << endl;
        mediator->sendMessage(message, this);
    }

    void receive(const string& message) override {
        cout << name << " отримав повідомлення: " << message << endl;
    }
};


int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Створення посередника
    ConcreteMediator* mediator = new ConcreteMediator();

    // Створення колег (користувачів)
    ConcreteColleague* user1 = new ConcreteColleague(mediator, "Іван");
    ConcreteColleague* user2 = new ConcreteColleague(mediator, "Марія");
    ConcreteColleague* user3 = new ConcreteColleague(mediator, "Андрій");

    // Додавання колег до посередника
    mediator->addColleague(user1);
    mediator->addColleague(user2);
    mediator->addColleague(user3);

    // Користувачі відправляють повідомлення
    user1->send("Привіт, як справи?");
    user2->send("Добре, дякую! Як у тебе?");
    user3->send("Привіт, радий вас бачити!");


    delete user1;
    delete user2;
    delete user3;
    delete mediator;

}
