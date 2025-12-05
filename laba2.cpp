#include <iostream>
#include <iomanip> 

using namespace std;

const int MAX_SIZE = 20;
const double MIN_VALUE = 0.0;
const double MAX_VALUE = 100.0;

class Stack {
private:
    double array[MAX_SIZE];
    int top;

public:
    Stack() : top(-1) {}

    bool push(double value) {
        if (value <= MIN_VALUE || value >= MAX_VALUE) {
            cout << "Ошибка: значение " << fixed << setprecision(3) << value << " не удовлетворяет ограничению 0 < x < 100." << endl;
            return false;
        }
        if (top >= MAX_SIZE - 1) {
            cout << "Ошибка: стек переполнен. Максимальный размер 20." << endl;
            return false;
        }
        array[++top] = value;
        return true;
    }

    double pop() {
        if (isEmpty()) {
            cout << "Ошибка: попытка извлечь элемент из пустого стека." << endl;
            return -1;
        }
        return array[top--];
    }

    double peek() const {
        if (isEmpty()) {
            cout << "Ошибка: попытка получить вершину пустого стека." << endl;
            return -1;
        }
        return array[top];
    }

    int size() const { return top + 1; }
    
    void clear() { top = -1; }

    bool isEmpty() const { return top == -1; }

    void print() const {
        if (isEmpty()) {
            cout << "Стек пуст.";
        } else {
            cout << "[ ";
            for (int i = 0; i <= top; ++i) {
                cout << fixed << setprecision(3) << array[i];
                if (i != top) cout << ", ";
            }
            cout << " ]";
        }
        cout << endl;
    }
};

class Queue {
private:
    double array[MAX_SIZE];
    int front_idx;
    int rear_idx;
    int count;

public:
    Queue() : front_idx(0), rear_idx(0), count(0) {}

    bool enqueue(double value) {
        if (value <= MIN_VALUE || value >= MAX_VALUE) {
            cout << "Ошибка: значение " << fixed << setprecision(3) << value << " не удовлетворяет ограничению 0 < x < 100." << endl;
            return false;
        }
        if (count >= MAX_SIZE) {
            cout << "Ошибка: очередь переполнена. Максимальный размер 20." << endl;
            return false;
        }
        array[rear_idx] = value;
        rear_idx = (rear_idx + 1) % MAX_SIZE;
        count++;
        return true;
    }

    double dequeue() {
        if (isEmpty()) {
            cout << "Ошибка: попытка извлечь элемент из пустой очереди." << endl;
            return -1;
        }
        double value = array[front_idx];
        front_idx = (front_idx + 1) % MAX_SIZE;
        count--;
        return value;
    }

    double front() const {
        if (isEmpty()) {
            cout << "Ошибка: попытка получить начало пустой очереди." << endl;
            return -1;
        }
        return array[front_idx];
    }

    int size() const { return count; }
    
    void clear() { front_idx = rear_idx = count = 0; }

    bool isEmpty() const { return count == 0; }

    void print() const {
        if (isEmpty()) {
            cout << "Очередь пуста.";
        } else {
            cout << "[ ";
            int temp_idx = front_idx;
            for (int i = 0; i < count; ++i) {
                cout << fixed << setprecision(3) << array[temp_idx];
                if (i != count - 1) {
                    temp_idx = (temp_idx + 1) % MAX_SIZE;
                }
            }
            cout << " ]";
        }
        cout << endl;
    }
};

class MinHeap {
private:
    double array[MAX_SIZE];
    int heap_size;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (array[parent] <= array[index]) break;
            swap(array[parent], array[index]);
            index = parent;
        }
    }

    void heapifyDown(int index) {
        while (true) {
            int smallest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            if (left < heap_size && array[left] < array[smallest])
                smallest = left;
            if (right < heap_size && array[right] < array[smallest])
                smallest = right;

            if (smallest == index) break;

            swap(array[index], array[smallest]);
            index = smallest;
        }
    }

public:
    MinHeap() : heap_size(0) {}

    bool insert(double value) {
        if (value <= MIN_VALUE || value >= MAX_VALUE) {
            cout << "Ошибка: значение " << fixed << setprecision(3) << value << " не удовлетворяет ограничению 0 < x < 100." << endl;
            return false;
        }
        if (heap_size >= MAX_SIZE) {
            cout << "Ошибка: куча переполнена. Максимальный размер 20." << endl;
            return false;
        }
        array[heap_size] = value;
        heapifyUp(heap_size);
        heap_size++;
        return true;
    }

    double extractMin() {
        if (isEmpty()) {
            cout << "Ошибка: попытка извлечь минимум из пустой кучи." << endl;
            return -1;
        }
        double min_val = array[0];
        array[0] = array[heap_size - 1];
        heap_size--;
        if (!isEmpty()) {
            heapifyDown(0);
        }
        return min_val;
    }

    double getMin() const {
        if (isEmpty()) {
            cout << "Ошибка: попытка получить минимум из пустой кучи." << endl;
            return -1;
        }
        return array[0];
    }

    int size() const { return heap_size; }
    
    void clear() { heap_size = 0; }

    bool isEmpty() const { return heap_size == 0; }

    void print() const {
        if (isEmpty()) {
            cout << "Куча пуста.";
        } else {
            cout << "[ ";
            for (int i = 0; i < heap_size; ++i) {
                cout << fixed << setprecision(3) << array[i];
                if (i != heap_size - 1) cout << ", ";
            }
            cout << " ]";
        }
        cout << endl;
    }
};


int main() {
    Stack stack;
    Queue queue;
    MinHeap heap;

    cout << "=== Тестирование Стека ===" << endl;
    stack.push(10.5); stack.push(20.7); stack.push(5.2);
    cout << "Размер стека: " << stack.size() << endl;
    cout << "Содержимое стека: "; stack.print();
    cout << "Peek: " << fixed << setprecision(3) << stack.peek() << endl;
    cout << "Pop: " << stack.pop() << endl;
    cout << "Содержимое после pop: "; stack.print();

    cout << "\n=== Тестирование Очереди ===" << endl;
    queue.enqueue(15.3); queue.enqueue(30.6); queue.enqueue(45.9);
    cout << "Размер очереди: " << queue.size() << endl;
    cout << "Содержимое очереди: "; queue.print();
    cout << "Front: " << fixed << setprecision(3) << queue.front() << endl;
    cout << "Dequeue: " << queue.dequeue() << endl;
    cout << "Содержимое после dequeue: "; queue.print();

    cout << "\n=== Тестирование Минимальной Кучи ===" << endl;
    heap.insert(25.8); heap.insert(12.4); heap.insert(37.1); heap.insert(8.9);
    cout << "Размер кучи: " << heap.size() << endl;
    cout << "Массив кучи: "; heap.print();
    cout << "Get Min: " << fixed << setprecision(3) << heap.getMin() << endl;
    cout << "Extract Min: " << heap.extractMin() << endl;
    cout << "Массив кучи после extract_min: "; heap.print();

    cout << "\n=== Тестирование граничных условий ===" << endl;
    Stack big_stack;
    for (int i = 0; i < 21; ++i) {
        big_stack.push(1.0 + i);
    }
    queue.enqueue(-5.5);

    return 0;
}
