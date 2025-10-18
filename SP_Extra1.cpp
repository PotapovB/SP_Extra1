#include <iostream>

using namespace std;

// Обработчики без аргументов
struct EventSystem {
    void (**handlers)();
    int count;
    int capacity;

    EventSystem(int handler_capacity) : handlers(nullptr), count(0), capacity(0) {
        setCapacity(handler_capacity);
    }

    ~EventSystem() {
        clear();
    }

    void registerHandler(void(*handler)()) {
        if (count >= capacity)
        {
            cout << "! Массив обработчиков переполнен. Расширяем массив вдвое." << endl;
            setCapacity(capacity * 2);
        }
        handlers[count] = handler;
        count++;
    }

    void setCapacity(int new_capacity) {
        if (new_capacity <= 0) {
            clear();
            return;
        }

        void (**new_handlers)() = new (void(*[new_capacity])());

        int elements_to_copy = (count < new_capacity) ? count : new_capacity;
        for (int i = 0; i < elements_to_copy; i++) {
            new_handlers[i] = handlers[i];
        }

        if (handlers != nullptr) {
            delete[] handlers;
        }

        handlers = new_handlers;
        capacity = new_capacity;

        if (count > capacity) {
            count = capacity;
        }
    }

    void clear() {
        if (handlers == nullptr)
        {
            return;
        }
        delete[] handlers;
        capacity = 0;
        count = 0;
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

    StringEventSystem(int handler_capacity) : handlers(nullptr), count(0), capacity(0) {
        setCapacity(handler_capacity);
    }

    ~StringEventSystem() {
        delete[] handlers;
    }

    void setCapacity(int new_capacity) {
        if (new_capacity <= 0) {
            clear();
            return;
        }

        void (**new_handlers)(const string &) = new (void(*[new_capacity])(const string &));

        int elements_to_copy = (count < new_capacity) ? count : new_capacity;
        for (int i = 0; i < elements_to_copy; i++) {
            new_handlers[i] = handlers[i];
        }

        if (handlers != nullptr) {
            delete[] handlers;
        }

        handlers = new_handlers;
        capacity = new_capacity;

        if (count > capacity) {
            count = capacity;
        }
    }

    void clear() {
        if (handlers == nullptr)
        {
            return;
        }
        delete[] handlers;
        capacity = 0;
        count = 0;
    }

    void registerHandler(void(*handler)(const string &)) {
        if (count >= capacity)
        {
            cout << "! Массив обработчиков переполнен. Расширяем массив вдвое." << endl;
            setCapacity(capacity * 2);
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