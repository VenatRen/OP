#include <iostream>
#include <bitset>
#include <fstream>
#include <sstream>

using namespace std;

// Определение класса для объектов
class Object {
    private:
        string name;
        int id;
        float price;
        bool available;
        bitset<8> flags;
        
    public:
        // Конструктор по умолчанию
        Object() {
            name = "";
            id = 0;
            price = 0.0;
            available = false;
            flags.reset();
        }
        
        // Конструктор с аргументами
        Object(string n, int i, float p, bool a, bitset<8> f) {
            name = n;
            id = i;
            price = p;
            available = a;
            flags = f;
        }
        
        // Добытчики и установщики
        string getName() { return name; }
        void setName(string n) { name = n; }
        
        int getId() { return id; }
        void setId(int i) { id = i; }
        
        float getPrice() { return price; }
        void setPrice(float p) { price = p; }
        
        bool isAvailable() { return available; }
        void setAvailable(bool a) { available = a; }
        
        bitset<8> getFlags() { return flags; }
        void setFlags(bitset<8> f) { flags = f; }
        
        // Вывод объекта
        void print() {
            cout << "Name: " << name << endl;
            cout << "ID: " << id << endl;
            cout << "Price: " << price << endl;
            cout << "Available: " << available << endl;
            cout << "Flags: " << flags << endl;
        }
};

// Определение системы для хранения информации о классах объектов
class ObjectSystem {
    private:
        Object objects[100];
        int numObjects;
        
    public:
        // Конструктор по умолчанию
        ObjectSystem() {
            numObjects = 0;
        }
        
        // Добавить объект в систему
        void addObject(Object o) {
            if (numObjects < 100) {
                objects[numObjects] = o;
                numObjects++;
            }
        }
        
        // Вывод всех объектов в системе
        void printObjects() {
            for (int i = 0; i < numObjects; i++) {
                objects[i].print();
                cout << endl;
            }
        }
        
        // Удалить объект из системы
        void deleteObject(int id) {
            for (int i = 0; i < numObjects; i++) {
                if (objects[i].getId() == id) {
                    for (int j = i; j < numObjects - 1; j++) {
                        objects[j] = objects[j+1];
                    }
                    numObjects--;
                    break;
                }
            }
        }
        
        // Редактирование объекта в системе
        void editObject(int id, Object o) {
            for (int i = 0; i < numObjects; i++) {
                if (objects[i].getId() == id) {
                    objects[i] = o;
                    break;
                }
            }
        }
        
        // Сохранение объектов в файл
        void saveToFile(string filename) {
            ofstream file(filename);
            if (file.is_open()) {
                for (int i = 0; i < numObjects; i++) {
                    file << objects[i].getName() << ",";
                    file << objects[i].getId() << ",";
                    file << objects[i].getPrice() << ",";
                    file << objects[i].isAvailable() << ",";
                    file << objects[i].getFlags().to_ulong() << endl;
                }
                file.close();
            }
        }
        
        // Загрузка объектов из файла
        void loadFromFile(string filename) {
            ifstream file(filename);
            if (file.is_open()) {
                string line;
                while (getline(file, line)) {
                    stringstream ss(line);
                    string name;
                    int id;
                    float price;
                    bool available;
                    unsigned long flags;
                    getline(ss, name, ',');
                    ss >> id;
                    ss.ignore();
                    ss >> price;
                    ss.ignore();
                    ss >> available;
                    ss.ignore();
                    ss >> flags;
                    Object o(name, id, price, available, bitset<8>(flags));
                    addObject(o);
                }
                file.close();
            }
        }
};

int main() {
    // Создание нескольких объектов
    Object o1("Object 1", 1, 10.0, true, bitset<8>("00000001"));
    Object o2("Object 2", 2, 20.0, false, bitset<8>("00000010"));
    Object o3("Object 3", 3, 30.0, true, bitset<8>("00000100"));
    
    // Создание объектной системы
    ObjectSystem system;
    
    // Добавление объектов в систему
    system.addObject(o1);
    system.addObject(o2);
    system.addObject(o3);
    
    // Вывод объектов в системе
    system.printObjects();
    
    // Удалить объект из системы
    system.deleteObject(2);
    
    // Вывод объектов в системе
    system.printObjects();
    
    // Редактирование объеков в системе
    Object o4("Object 4", 4, 40.0, false, bitset<8>("00001000"));
    system.editObject(1, o4);
    
    // Вывод объектов в системе
    system.printObjects();
    
    // Сохранение объектов в файл
    system.saveToFile("objects.txt");
    
    // Очистка системы
    system = ObjectSystem();
    
    // Загрузка объекта из файла
    system.loadFromFile("objects.txt");
    
    // Вывод объектов в системе
    system.printObjects();
    
    return 0;
}