#include <iostream>

using namespace std;

// Обработчики без аргументов
struct EventSystem {
    void (**handlers)();
    int count;
    int capacity;

    EventSystem(int handler_capacity) : count(0), capacity(handler_capacity) {
        handlers = new (void (*[capacity])());
    }

    ~EventSystem() {
        delete[] handlers;
    }

    void registerHandler(void(*handler)()) {
        if (count >= capacity)
        {
            cout << "! Массив обработчиков переполнен." << endl;
            return;
        }
        handlers[count] = handler;
        count++;
    }

    void triggerEvent() {
        for (int i = 0; i < count; i++)
        {
            handlers[i]();
        }
    }
};

void onUserLogin() {
    cout << "Пользователь вошёл в систему" << endl;
}

void onUserLogout() {
    cout << "Пользователь вышел из системы" << endl;
}

void onError() {
    cout << "Произошла ошибка!" << endl;
}

// Обработчики с аргументами
struct StringEventSystem {
    void (**handlers)(const string &);
    int count;
    int capacity;

    StringEventSystem(int handler_capacity) : count(0), capacity(handler_capacity) {
        handlers = new (void (*[capacity])(const string &));
    }

    ~StringEventSystem() {
        delete[] handlers;
    }

    void registerHandler(void(*handler)(const string &)) {
        if (count >= capacity)
        {
            cout << "! Массив обработчиков переполнен." << endl;
            return;
        }
        handlers[count] = handler;
        count++;
    }

    void triggerEvent(const string &context) {
        for (int i = 0; i < count; i++)
        {
            handlers[i](context);
        }
    }
};

void handleString1(const string &message) {
    cout << "handleString1: Сообщение \"" << message << "\"" << endl;
}

void handleString2(const string &message) {
    cout << "handleString2: Сообщение \"" << message << "\"" << endl;
}
void handleString3(const string &message) {
    cout << "handleString3: Сообщение \"" << message << "\"" << endl;
}

int main()
{
    setlocale(LC_ALL, "RU-ru");

    // Без аргументов
    EventSystem system(2);
    
    system.registerHandler(onUserLogin);
    system.registerHandler(onUserLogout);
    system.registerHandler(onError);

    system.triggerEvent();

    // С аргументами
    StringEventSystem string_system(2);

    string_system.registerHandler(handleString1);
    string_system.registerHandler(handleString2);
    string_system.registerHandler(handleString3);

    string_system.triggerEvent("Тестовое сообщение");
}