#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <deque>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <thread>
#include <chrono>
#include <cmath>

// Función para intercambiar dos elementos
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Función para dibujar el array en la ventana
void drawArray(const std::vector<int>& originalArr, const std::vector<int>& arr, sf::RenderWindow& window, sf::Font& font, int index1 = -1, int index2 = -1, bool swapping = false) {
    window.clear();

    // Mostrar el array original en la parte superior
    for (size_t i = 0; i < originalArr.size(); i++) {
        sf::Text originalText;
        originalText.setFont(font);
        originalText.setString(std::to_string(originalArr[i]));
        originalText.setCharacterSize(24);
        originalText.setPosition(50 + i * 30, 100);
        originalText.setFillColor(sf::Color::Blue); // Color azul para el array original
        window.draw(originalText);
    }

    // Mostrar el array actual en proceso de ordenamiento
    for (size_t i = 0; i < arr.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(arr[i]));
        text.setCharacterSize(24);
        text.setPosition(50 + i * 30, 300);

        if (i == index1 || i == index2) {
            text.setFillColor(swapping ? sf::Color::Red : sf::Color::Yellow); // Rojo si se intercambian, amarillo si solo se comparan
        } else {
            text.setFillColor(sf::Color::White);
        }

        window.draw(text);
    }

    window.display();
    sf::sleep(sf::milliseconds(1000)); // Pausa breve para visualizar el cambio
}

void drawBinary(const std::vector<int>& originalArr, const std::vector<int>& arr, sf::RenderWindow& window, sf::Font& font, int low = -1, int high = -1, int mid = -1, int target = -1) {
    window.clear();

    // Mostrar el array original en la parte superior
    for (size_t i = 0; i < originalArr.size(); i++) {
        sf::Text originalText;
        originalText.setFont(font);
        originalText.setString(std::to_string(originalArr[i]));
        originalText.setCharacterSize(24);
        originalText.setPosition(50 + i * 30, 100);
        originalText.setFillColor(sf::Color::Blue); // Azul para el array original
        window.draw(originalText);
    }

    // Mostrar el array actual en proceso de búsqueda
    for (size_t i = 0; i < arr.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(arr[i]));
        text.setCharacterSize(24);
        text.setPosition(50 + i * 30, 300);

        // Cambiar el color en función de los índices especiales
        if (i == mid && arr[i] == target) {
            text.setFillColor(sf::Color::Red); // Rojo para el índice central si contiene el objetivo
        } else if (i == mid) {
            text.setFillColor(sf::Color::Cyan); // Cyan para el índice central (si no es el objetivo)
        } else if (i == low || i == high) {
            text.setFillColor(sf::Color::Yellow); // Amarillo para los extremos (low y high)
        } else {
            text.setFillColor(sf::Color::White); // Blanco para los demás
        }

        window.draw(text);
    }

    window.display();
    sf::sleep(sf::milliseconds(1000)); // Pausa breve para visualizar el cambio
}

//Draw linear
void drawLinearSearch(const std::vector<int>& originalArr, const std::vector<int>& arr, sf::RenderWindow& window, sf::Font& font, int num = -1, int t = -1) {
    window.clear();

    // Mostrar el array original en la parte superior
    for (size_t i = 0; i < originalArr.size(); i++) {
        sf::Text originalText;
        originalText.setFont(font);
        originalText.setString(std::to_string(originalArr[i]));
        originalText.setCharacterSize(24);
        originalText.setPosition(50 + i * 30, 100);
        originalText.setFillColor(sf::Color::Blue); // Color azul para el array original
        window.draw(originalText);
    }

    // Mostrar el array actual en proceso de búsqueda
    for (size_t i = 0; i < arr.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(arr[i]));
        text.setCharacterSize(24);
        text.setPosition(50 + i * 30, 300);

        // Cambiar el color en función del índice actual y del valor encontrado
        if (i == num && arr[i] == t) {
            text.setFillColor(sf::Color::Red); // Rojo para el elemento que coincide con el objetivo
        } else if (i == num) {
            text.setFillColor(sf::Color::Yellow); // Amarillo para el índice actual
        } else {
            text.setFillColor(sf::Color::White); // Blanco para los demás
        }

        window.draw(text);
    }

    window.display();
    sf::sleep(sf::milliseconds(1000)); // Pausa breve para visualizar el cambio
}

// Algoritmos de ordenamiento con visualización

void bubbleSort(std::vector<int>& arr, const std::vector<int>& originalArr, sf::RenderWindow& window, sf::Font& font, bool &isSorted) {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        for (size_t j = 0; j < arr.size() - i - 1; j++) {
            drawArray(originalArr, arr, window, font, j, j + 1);
            if (arr[j] > arr[j + 1]) {
                drawArray(originalArr, arr, window, font, j, j + 1, true);
                swap(arr[j], arr[j + 1]);
                drawArray(originalArr, arr, window, font);
            }
        }
    }
    isSorted = true;
}

void selectionSort(std::vector<int>& arr, const std::vector<int>& originalArr, sf::RenderWindow& window, sf::Font& font, bool &isSorted) {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < arr.size(); j++) {
            drawArray(originalArr, arr, window, font, minIndex, j);
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
                drawArray(originalArr, arr, window, font, i, minIndex, true);
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
            drawArray(originalArr, arr, window, font);
        }
    }
    isSorted = true;
}

void merge(std::vector<int>& leftArray, std::vector<int>& rightArray, std::vector<int>& arr, const std::vector<int>& originalArr, sf::RenderWindow& window, sf::Font& font) {
    int leftSize = leftArray.size();
    int rightSize = rightArray.size();
    int i = 0, l = 0, r = 0;

    while (l < leftSize && r < rightSize) {
        drawArray(originalArr, arr, window, font, l, r);
        if (leftArray[l] < rightArray[r]) {
            arr[i++] = leftArray[l++];
        } else {
            arr[i++] = rightArray[r++];
        }
        drawArray(originalArr, arr, window, font, i - 1, -1, true);
    }

    while (l < leftSize) {
        arr[i++] = leftArray[l++];
        drawArray(originalArr, arr, window, font, i - 1, -1, true);
    }
    while (r < rightSize) {
        arr[i++] = rightArray[r++];
        drawArray(originalArr, arr, window, font, i - 1, -1, true);
    }
}

void mergeSort(std::vector<int>& arr, const std::vector<int>& originalArr, sf::RenderWindow& window, sf::Font& font, bool &isSorted) {
    int n = arr.size();
    if (n <= 1) return;

    int mid = n / 2;
    std::vector<int> leftArray(arr.begin(), arr.begin() + mid);
    std::vector<int> rightArray(arr.begin() + mid, arr.end());

    mergeSort(leftArray, originalArr, window, font, isSorted);
    mergeSort(rightArray, originalArr, window, font, isSorted);
    merge(leftArray, rightArray, arr, originalArr, window, font);
    isSorted = true;
}

int partition(std::vector<int>& arr, int low, int high, const std::vector<int>& originalArr, sf::RenderWindow& window, sf::Font& font) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        drawArray(originalArr, arr, window, font, j, high);
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
            drawArray(originalArr, arr, window, font, i, j, true);
        }
    }
    swap(arr[i + 1], arr[high]);
    drawArray(originalArr, arr, window, font, i + 1, high, true);
    return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high, const std::vector<int>& originalArr, sf::RenderWindow& window, sf::Font& font, bool &isSorted) {
    if (low < high) {
        int pivot = partition(arr, low, high, originalArr, window, font);
        quickSort(arr, low, pivot - 1, originalArr, window, font, isSorted);
        quickSort(arr, pivot + 1, high, originalArr, window, font, isSorted);
    }
    isSorted = true;
}

void insertionSort(std::vector<int>& arr, const std::vector<int>& originalArr, sf::RenderWindow& window, sf::Font& font, bool &isSorted) {
    for (size_t i = 1; i < arr.size(); i++) {
        int key = arr[i];
        size_t j = i - 1;

        // Mostrar el estado actual del array antes de realizar cambios
        drawArray(originalArr, arr, window, font, i);

        // Mover los elementos mayores al key hacia la derecha
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            drawArray(originalArr, arr, window, font, j, j + 1, true);
            j--;
        }

        arr[j + 1] = key;

        // Dibujar el estado del array después de insertar el key
        drawArray(originalArr, arr, window, font, j + 1);
    }
    isSorted = true;
}


// Algoritmo de busqueda binaria
int binarySearch(const std::vector<int>& arr, int target, sf::RenderWindow& window, sf::Font& font) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Dibujar el estado actual
        drawBinary(arr, arr, window, font, low, high, mid, target);

        // Verificar si el número está en la posición media
        if (arr[mid] == target) {
            // Mostrar el resultado en pantalla
            sf::Text resultText("Numero encontrado en la posicion: " + std::to_string(mid), font, 24);
            resultText.setFillColor(sf::Color::Green);
            resultText.setPosition(10, 10);

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return -1;
                    }
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                        return mid; // Volver al menú
                    }
                }

                window.clear();
                window.draw(resultText);
                window.display();
            }
        } else if (arr[mid] < target) {
            low = mid + 1; // Buscar en la mitad derecha
        } else {
            high = mid - 1; // Buscar en la mitad izquierda
        }
    }

    // Mostrar mensaje si no se encuentra el número
    sf::Text notFoundText("Numero no encontrado. Presiona Escape para regresar.", font, 24);
    notFoundText.setFillColor(sf::Color::Red);
    notFoundText.setPosition(10, 10);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                return -1; // Volver al menú
            }
        }

        window.clear();
        window.draw(notFoundText);
        window.display();
    }

    return -1;
}

int linearSearch(const std::vector<int>& vec, int target, const std::vector<int>& originalArr, sf::RenderWindow& window, sf::Font& font) {
    int n = vec.size();

    for (int i = 0; i < n; i++) {
        // Dibujar el estado actual
        drawLinearSearch(originalArr, vec, window, font, i, target);

        // Verificar si el número está en la posición actual
        if (vec[i] == target) {
            // Mostrar el resultado en pantalla
            sf::Text resultText("Numero encontrado en la posicion: " + std::to_string(i), font, 24);
            resultText.setFillColor(sf::Color::Green);
            resultText.setPosition(10, 10);

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return -1;
                    }
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                        return i; // Volver al menú
                    }
                }

                window.clear();
                window.draw(resultText);
                window.display();
            }
        }
    }

    // Mostrar mensaje si no se encuentra el número
    sf::Text notFoundText("Numero no encontrado. Presiona Escape para regresar.", font, 24);
    notFoundText.setFillColor(sf::Color::Red);
    notFoundText.setPosition(10, 10);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                return -1; // Volver al menú
            }
        }

        window.clear();
        window.draw(notFoundText);
        window.display();
    }

    return -1;
}

// Función para convertir el array en una cadena de texto
std::string vectorToString(const std::vector<int>& arr) {
    std::ostringstream oss;
    for (int num : arr) {
        oss << num << " ";
    }
    return oss.str();
}


//Stack
class Stack {
    std::vector<int> stack;
    sf::RenderWindow& window;
    sf::Font& font;

public:
    Stack(sf::RenderWindow& win, sf::Font& f) : window(win), font(f) {}

    bool isEmpty() const {
        return stack.empty();
    }

    void push(int value) {
        stack.push_back(value);
        drawStack(window,font);
    }

    int pop() {
        if (!stack.empty()) {
            int topElement = stack.back();
            stack.pop_back();
            drawStack(window,font);
            return topElement;
        }
        return -1; // Indicador de error al intentar extraer de una pila vacía
    }

    void drawStack(sf::RenderWindow& window, sf::Font& font) {
        int y = 300; // Posición inicial para dibujar
        for (const auto& value : this->stack) { // Itera por los elementos de la pila
            sf::Text text(std::to_string(value), font, 24);
            text.setPosition(50, y); // Ajusta las posiciones verticales
            text.setFillColor(sf::Color::White);
            window.draw(text); // Dibuja cada elemento
            y -= 30; // Incrementa la posición para el próximo elemento
        }
    }

};

//Queue
class Queue {
    sf::RenderWindow& window;
    sf::Font& font;

public:
    std::deque<int> queue;

    Queue(sf::RenderWindow& win, sf::Font& f) : window(win), font(f) {}

    void enqueue(int value) {
        queue.push_back(value);
        drawQueue(window,font);
    }

    void dequeue() {
        if (!queue.empty()) {
            queue.pop_front();
            drawQueue(window,font);
        }
    }

    void drawQueue(sf::RenderWindow& window, sf::Font& font) {
        int x = 50; // Posición horizontal inicial
        for (const auto& value : this->queue) {
            sf::Text text(std::to_string(value), font, 24);
            text.setPosition(x, 150); // Dibuja todos los elementos en una fila
            text.setFillColor(sf::Color::White);
            window.draw(text);
            x += 50; // Incrementa la posición horizontal para el próximo elemento
        }
    }
};

//Linked List
struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};
class LinkedList {
    Node* head;
    sf::RenderWindow& window;
    sf::Font& font;

public:
    LinkedList(sf::RenderWindow& win, sf::Font& f) : head(nullptr), window(win), font(f) {}

    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insert(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        drawList(window,font);
    }

    void remove(int value) {
        if (!head) return;

        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            drawList(window,font);
            return;
        }

        Node* current = head;
        while (current->next && current->next->data != value) {
            current = current->next;
        }

        if (current->next) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            drawList(window,font);
        }
    }

    void drawList(sf::RenderWindow& window, sf::Font& font) {
        Node* current = this->head;
        int x = 50; // Posición horizontal inicial
        while (current != nullptr) {
            sf::Text text(std::to_string(current->data), font, 24);
            text.setPosition(x, 150);
            text.setFillColor(sf::Color::White);
            window.draw(text);
            x += 50; // Incrementa la posición para el siguiente nodo
            current = current->next;
        }
    }
};

struct AVLNode {
    int value;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int val) : value(val), left(nullptr), right(nullptr), height(1) {}
};
class AVLTree {
    AVLNode* root;
    sf::RenderWindow& window;
    sf::Font& font;

public:
    AVLTree(sf::RenderWindow& win, sf::Font& f) : root(nullptr), window(win), font(f) {}

    int getHeight(AVLNode* node) {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    AVLNode* insertNode(AVLNode* node, int value) {
        if (!node) return new AVLNode(value);

        if (value < node->value)
            node->left = insertNode(node->left, value);
        else if (value > node->value)
            node->right = insertNode(node->right, value);
        else
            return node;

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && value < node->left->value)
            return rotateRight(node);

        if (balance < -1 && value > node->right->value)
            return rotateLeft(node);

        if (balance > 1 && value > node->left->value) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && value < node->right->value) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void insert(int value) {
        root = insertNode(root, value);
    }

    void remove(int value) {
        root = removeNode(root, value);
    }

    AVLNode* removeNode(AVLNode* node, int value) {
        if (!node) return node;

        if (value < node->value)
            node->left = removeNode(node->left, value);
        else if (value > node->value)
            node->right = removeNode(node->right, value);
        else {
            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                AVLNode* temp = minValueNode(node->right);
                node->value = temp->value;
                node->right = removeNode(node->right, temp->value);
            }
        }

        if (!node) return node;

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0)
            return rotateRight(node);

        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0)
            return rotateLeft(node);

        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current && current->left)
            current = current->left;
        return current;
    }

    void drawTree() {
        window.clear();
        drawNode(root, window.getSize().x / 2, 50, window.getSize().x / 4);
        window.display();
    }

private:
    void drawNode(AVLNode* node, float x, float y, float offset) {
        if (!node) return;

        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color::Blue);
        circle.setPosition(x - 20, y - 20);
        window.draw(circle);

        sf::Text text(std::to_string(node->value), font, 20);
        text.setPosition(x - 10, y - 10);
        text.setFillColor(sf::Color::White);
        window.draw(text);

        if (node->left) {
            sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(x, y), sf::Color::White),
                    sf::Vertex(sf::Vector2f(x - offset, y + 50), sf::Color::White)
            };
            window.draw(line, 2, sf::Lines);
            drawNode(node->left, x - offset, y + 50, offset / 2);
        }

        if (node->right) {
            sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(x, y), sf::Color::White),
                    sf::Vertex(sf::Vector2f(x + offset, y + 50), sf::Color::White)
            };
            window.draw(line, 2, sf::Lines);
            drawNode(node->right, x + offset, y + 50, offset / 2);
        }
    }
};

class DijkstraGraph {
    std::vector<std::vector<std::pair<int, int>>> graph; // Grafo como lista de adyacencia
    // Número de nodos
    sf::RenderWindow& window;
    sf::Font& font;

public:
    DijkstraGraph(sf::RenderWindow& win, sf::Font& f)
            : window(win), font(f) {
    }

    void addNode(int id) {
        if (id >= graph.size()) {
            graph.resize(id + 1);
            numNodes = graph.size();
        }
    }


    void addEdge(int u, int v, int weight) {
        graph[u].emplace_back(v, weight);
        graph[v].emplace_back(u, weight); // Si es no dirigido
    }

    std::vector<int> calculateShortestPaths(int startNode) {
        std::vector<int> distances(numNodes, std::numeric_limits<int>::max());
        std::vector<int> parents(numNodes, -1);
        distances[startNode] = 0;

        using NodeDistPair = std::pair<int, int>;
        std::priority_queue<NodeDistPair, std::vector<NodeDistPair>, std::greater<>> pq;
        pq.emplace(0, startNode);

        while (!pq.empty()) {
            auto [currentDist, currentNode] = pq.top();
            pq.pop();

            if (currentDist > distances[currentNode]) continue;

            for (const auto& [neighbor, weight] : graph[currentNode]) {
                if (distances[currentNode] + weight < distances[neighbor]) {
                    distances[neighbor] = distances[currentNode] + weight;
                    parents[neighbor] = currentNode;
                    pq.emplace(distances[neighbor], neighbor);
                }
            }
        }
        return parents;
    }

    std::pair<std::vector<int>, std::vector<int>> run(int source) {
        std::vector<int> distances(numNodes, std::numeric_limits<int>::max());
        std::vector<int> parents(numNodes, -1);
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

        distances[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (const auto &[v, weight] : graph[u]) {
                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    parents[v] = u;
                    pq.push({distances[v], v});
                }
            }
        }

        return {parents, distances};
    }

    int numNodes;
};

class Graph {
private:
    std::map<int, std::vector<int>> adj; // Lista de adyacencia
    sf::RenderWindow& window;
    sf::Font& font;

    void pauseVisualization() {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

public:
    Graph(sf::RenderWindow& win, sf::Font& f) : window(win), font(f) {}

    // Agregar una arista al grafo (no dirigido)
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Si el grafo es no dirigido
    }

    // DFS Visualizado
    void dfs(int start) {
        std::set<int> visited;
        std::stack<int> stack;
        stack.push(start);

        while (!stack.empty()) {
            int node = stack.top();
            stack.pop();

            if (!visited.count(node)) {
                visited.insert(node);

                // Dibujar grafo con estado actual
                drawGraph(visited, node);
                pauseVisualization();

                for (int neighbor : adj[node]) {
                    if (!visited.count(neighbor)) {
                        stack.push(neighbor);
                    }
                }
            }
        }

        // Mostrar grafo final
        drawGraph(visited);
    }

    // BFS Visualizado
    void bfs(int start) {
        std::set<int> visited;
        std::queue<int> queue;
        queue.push(start);
        visited.insert(start);

        while (!queue.empty()) {
            int node = queue.front();
            queue.pop();

            // Dibujar grafo con estado actual
            drawGraph(visited, node);
            pauseVisualization();

            for (int neighbor : adj[node]) {
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    queue.push(neighbor);
                }
            }
        }

        // Mostrar grafo final
        drawGraph(visited);
    }

// Método auxiliar para dibujar el grafo
void drawGraph(const std::set<int>& visited = {}, int current = -1) {
    window.clear();

    // Coordenadas de nodos (ejemplo estático, puedes generalizar)
    std::map<int, sf::Vector2f> nodePositions = {
            {0, {200, 100}}, {1, {400, 100}}, {2, {600, 100}},
            {3, {200, 300}}, {4, {400, 300}}, {5, {600, 300}}
    };

    // Dibujar aristas
    for (const auto& [u, neighbors] : adj) {
        for (int v : neighbors) {
            sf::Vertex line[] = {
                    sf::Vertex(nodePositions[u], sf::Color::White),
                    sf::Vertex(nodePositions[v], sf::Color::White)
            };
            window.draw(line, 2, sf::Lines);
        }
    }

    // Dibujar nodos
    for (const auto& [node, pos] : nodePositions) {
        sf::CircleShape circle(20);
        circle.setPosition(pos.x - 20, pos.y - 20);

        if (visited.count(node)) {
            circle.setFillColor(sf::Color::Green);
        } else if (node == current) {
            circle.setFillColor(sf::Color::Red);
        } else {
            circle.setFillColor(sf::Color::Blue);
        }

        window.draw(circle);

        sf::Text text(std::to_string(node), font, 20);
        text.setPosition(pos.x - 10, pos.y - 15);
        text.setFillColor(sf::Color::White);
        window.draw(text);
    }

    window.display();
}
};

void executeSubMenuOption(int menuType, int option, sf::RenderWindow& window, sf::Font& font, Stack& stack, Queue& queue, LinkedList& list,AVLTree& avl, Graph& graph, DijkstraGraph& dijkstra) {
    sf::Text inputText("", font, 24);
    inputText.setPosition(50, 20);
    inputText.setFillColor(sf::Color::White);
    std::string inputBuffer;

    sf::Text resultText("", font, 24);
    resultText.setPosition(50, 100);
    resultText.setFillColor(sf::Color::Green);

    auto handleInput = [&window, &inputText, &inputBuffer]() -> int {
        bool enteringNumber = true;
        while (window.isOpen() && enteringNumber) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::TextEntered) {
                    if (std::isdigit(event.text.unicode)) {
                        inputBuffer += static_cast<char>(event.text.unicode);
                        inputText.setString("Ingresa un numero: " + inputBuffer);
                    } else if (event.text.unicode == '\b' && !inputBuffer.empty()) {
                        inputBuffer.pop_back();
                        inputText.setString("Ingresa un numero: " + inputBuffer);
                    }
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter && !inputBuffer.empty()) {
                        enteringNumber = false;
                        return std::stoi(inputBuffer);
                    }
                    if (event.key.code == sf::Keyboard::Escape) {
                        enteringNumber = false;
                    }
                }
            }
            window.clear();
            window.draw(inputText);
            window.display();
        }
        return -1; // Código para cancelar
    };

    switch (menuType) {
        case 0: { // Stack
            if (option == 0) { // Push
                inputText.setString("Ingresa el numero a agregar a la stack: ");
                int value = handleInput();
                if (value != -1) {
                    stack.push(value);
                    resultText.setString("Numero " + std::to_string(value) + " agregado a la stack.");
                } else {
                    resultText.setString("Operacion cancelada.");
                }
            } else if (option == 1) { // Pop
                if (!stack.isEmpty()) {
                    int value = stack.pop();
                    resultText.setString("Numero " + std::to_string(value) + " eliminado de la stack.");
                } else {
                    resultText.setString("La stack está vacia.");
                }
            } else if (option == 2) { // Display
                window.clear();
                stack.drawStack(window,font);
                window.display();
                sf::sleep(sf::seconds(3)); // Pausa para mostrar la estructura
                return;
            }
            break;
        }
        case 1: { // Queue
            if (option == 0) { // Enqueue
                inputText.setString("Ingresa el numero a agregar a la queue: ");
                int value = handleInput();
                if (value != -1) {
                    queue.enqueue(value);
                    resultText.setString("Numero " + std::to_string(value) + " agregado a la queue.");
                } else {
                    resultText.setString("Operacion cancelada.");
                }
            } else if (option == 1) { // Dequeue
                if (!queue.queue.empty()) {
                    queue.dequeue();
                    resultText.setString("Primer elemento eliminado de la queue.");
                } else {
                    resultText.setString("La queue está vacia.");
                }
            } else if (option == 2) { // Display
                window.clear();
                queue.drawQueue(window,font);
                window.display();
                sf::sleep(sf::seconds(3)); // Pausa para mostrar la estructura
                return;
            }
            break;
        }
        case 2: { // LinkedList
            if (option == 0) { // Insert
                inputText.setString("Ingresa el numero a agregar a la lista: ");
                int value = handleInput();
                if (value != -1) {
                    list.insert(value);
                    resultText.setString("Numero " + std::to_string(value) + " agregado a la lista.");
                } else {
                    resultText.setString("Operacion cancelada.");
                }
            } else if (option == 1) { // Delete
                inputText.setString("Ingresa el numero a eliminar de la lista: ");
                int value = handleInput();
                if (value != -1) {
                    list.remove(value);
                    resultText.setString("Numero " + std::to_string(value) + " eliminado de la lista.");
                } else {
                    resultText.setString("Operacion cancelada.");
                }
            } else if (option == 2) { // Display
                window.clear();
                list.drawList(window,font);
                window.display();
                sf::sleep(sf::seconds(3)); // Pausa para mostrar la estructura
                return;
            }
            break;
        }
        case 3: { // AVLTree
            if (option == 0) { // Insertar en AVL
                inputText.setString("Ingresa el numero a insertar en el AVL: ");
                int value = handleInput();
                if (value != -1) {
                    avl.insert(value);
                    resultText.setString("Numero " + std::to_string(value) + " insertado en el AVL.");
                } else {
                    resultText.setString("Operacion cancelada.");
                }
            } else if (option == 1) { // Eliminar de AVL
                inputText.setString("Ingresa el numero a eliminar del AVL: ");
                int value = handleInput();
                if (value != -1) {
                    avl.remove(value);
                    resultText.setString("Numero " + std::to_string(value) + " eliminado del AVL.");
                } else {
                    resultText.setString("Operacion cancelada.");
                }
            } else if (option == 2) { // Mostrar AVL
                avl.drawTree();
                sf::sleep(sf::seconds(3)); // Pausa para mostrar
                return;
            }
            break;
        }
        case 4: { // Graph
            if (option == 0) { // Agregar nodo (debe ser implementado)
                inputText.setString("Ingresa el ID del nodo a agregar: ");
                int id = handleInput();
                if (id != -1) {
                    graph.addEdge(id, id); // Si el grafo no tiene nodos explícitos
                    resultText.setString("Nodo " + std::to_string(id) + " agregado.");
                } else {
                    resultText.setString("Operacion cancelada.");
                }
            } else if (option == 1) { // Agregar arista
                inputText.setString("Ingresa ID de nodo origen: ");
                int src = handleInput();
                inputText.setString("Ingresa ID de nodo destino: ");
                int dest = handleInput();
                if (src != -1 && dest != -1) {
                    graph.addEdge(src, dest);
                    resultText.setString("Arista agregada entre " + std::to_string(src) + " y " + std::to_string(dest));
                } else {
                    resultText.setString("Operacion cancelada.");
                }
            } else if (option == 2) { // BFS
                inputText.setString("Ingresa el nodo inicial para BFS: ");
                int start = handleInput();
                if (start != -1) {
                    graph.bfs(start);
                    resultText.setString("Se completó BFS desde el nodo " + std::to_string(start));
                } else {
                    resultText.setString("Operacion cancelada.");
                }
            } else if (option == 3) { // DFS
                inputText.setString("Ingresa el nodo inicial para DFS: ");
                int start = handleInput();
                if (start != -1) {
                    graph.dfs(start);
                    resultText.setString("Se completó DFS desde el nodo " + std::to_string(start));
                } else {
                    resultText.setString("Operacion cancelada.");
                }
            } else if (option == 4) { // Mostrar grafo
                graph.drawGraph();
                sf::sleep(sf::seconds(3)); // Pausa para mostrar
                return;
            }
            break;
        }
        case 5: { // Dijkstra
            if (option == 0) { // Agregar nodo
                inputText.setString("Ingresa el ID del nodo a agregar: ");
                int id = handleInput();
                if (id != -1) {
                    dijkstra.addNode(id); // Necesitarás implementar este método
                    resultText.setString("Nodo " + std::to_string(id) + " agregado.");
                } else {
                    resultText.setString("Operación cancelada.");
                }
            } else if (option == 1) { // Agregar arista
                inputText.setString("Ingresa ID de nodo origen: ");
                int src = handleInput();
                inputText.setString("Ingresa ID de nodo destino: ");
                int dest = handleInput();
                inputText.setString("Ingresa el peso de la conexion: ");
                int weight = handleInput();
                if (src != -1 && dest != -1 && weight >= 0) {
                    dijkstra.addEdge(src, dest, weight);
                    resultText.setString("Arista agregada entre " + std::to_string(src) + " y " + std::to_string(dest));
                } else {
                    resultText.setString("Operación cancelada o peso inválido.");
                }
            } else if (option == 2) { // Ejecutar Dijkstra
                inputText.setString("Ingresa el nodo inicial: ");
                int start = handleInput();
                if (start >= 0 && start < dijkstra.numNodes) { // Verifica si el nodo es válido
                    auto [parents, distances] = dijkstra.run(start); // Ejecuta el algoritmo
                    std::ostringstream result;

                    // Construir texto con los resultados
                    result << "Resultados de Dijkstra desde el nodo " << start << ":\n";
                    for (int i = 0; i < distances.size(); ++i) {
                        result << "Nodo " << i << ": Distancia = " << distances[i] << ", Camino = ";

                        // Reconstruir el camino desde el nodo inicial hasta el nodo actual
                        std::vector<int> path;
                        for (int current = i; current != -1; current = parents[current]) {
                            path.push_back(current);
                        }
                        std::reverse(path.begin(), path.end());

                        // Mostrar el camino
                        if (path.front() == start) {
                            for (size_t j = 0; j < path.size(); ++j) {
                                result << path[j];
                                if (j < path.size() - 1) result << " -> ";
                            }
                        } else {
                            result << "No hay camino";
                        }

                        result << "\n";
                    }

                    resultText.setString(result.str());

                } else {
                    resultText.setString("Nodo inicial inválido o no existe.");
                }
            }
            break;
        }
        default:
            resultText.setString("Opcion no válida.");
            break;
    }

    // Renderizar texto del resultado para las opciones que no sean display
    window.clear();
    window.draw(resultText);
    window.display();
    sf::sleep(sf::seconds(2)); // Pausa para que el usuario lea el resultado
}

// Menú de algoritmos
void executeAlgorithmMenu(sf::RenderWindow& window, sf::Font& font) {
    std::vector<std::string> sortingOptions = { "1. Bubble Sort", "2. Selection Sort", "3. Merge Sort", "4. Quick Sort", "5. Insertion Sort", "6. Binary Search", "7. Linear Search" };
    std::vector<sf::Text> optionsText;
    int selectedOption = 0;
    bool enteringNumbers = false;
    bool showingResult = false;
    std::vector<int> numbers;
    bool isSorted = false;
    int searchTarget = -1;

    sf::Text inputText("", font, 24);
    inputText.setPosition(50, 20);
    inputText.setFillColor(sf::Color::White);
    std::string inputBuffer;

    sf::Text resultText("", font, 24);
    resultText.setPosition(50, 100);
    resultText.setFillColor(sf::Color::Green);

    for (size_t i = 0; i < sortingOptions.size(); ++i) {
        sf::Text text(sortingOptions[i], font, 30);
        text.setPosition(200, 150 + i * 50);
        text.setFillColor(i == selectedOption ? sf::Color::Red : sf::Color::White);
        optionsText.push_back(text);
    }

    auto handleInput = [&window, &inputText, &inputBuffer]() -> int {
        bool enteringNumber = true;
        while (window.isOpen() && enteringNumber) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::TextEntered) {
                    if (std::isdigit(event.text.unicode)) {
                        inputBuffer += static_cast<char>(event.text.unicode);
                        inputText.setString("Ingresa un numero: " + inputBuffer);
                    } else if (event.text.unicode == '\b' && !inputBuffer.empty()) {
                        inputBuffer.pop_back();
                        inputText.setString("Ingresa un numero: " + inputBuffer);
                    }
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter && !inputBuffer.empty()) {
                        enteringNumber = false;
                        return std::stoi(inputBuffer);
                    }
                    if (event.key.code == sf::Keyboard::Escape) {
                        enteringNumber = false;
                    }
                }
            }
            window.clear();
            window.draw(inputText);
            window.display();
        }
        return -1; // Código para cancelar
    };


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Regresa al menú principal si se presiona Escape
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                return; // Salimos de la función para regresar al main
            }

            if (showingResult) {
                // Manejo del estado de mostrando resultados
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    showingResult = false;
                    isSorted = false;
                    selectedOption = 0;
                    inputText.setString("Selecciona el tipo de ordenamiento:");
                }
            } else if (enteringNumbers) {
                // Manejo del estado de ingresando números
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                        inputBuffer += static_cast<char>(event.text.unicode);
                        inputText.setString("Ingresa numeros separados por espacio, Enter para finalizar: " + inputBuffer);
                    } else if (event.text.unicode == ' ') {
                        numbers.push_back(std::stoi(inputBuffer));
                        inputBuffer.clear();
                    } else if (event.text.unicode == '\b' && !inputBuffer.empty()) {
                        inputBuffer.pop_back();
                        inputText.setString("Ingresa numeros separados por espacio, Enter para finalizar: " + inputBuffer);
                    }
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    if (!inputBuffer.empty()) {
                        numbers.push_back(std::stoi(inputBuffer));
                        inputBuffer.clear();
                    }
                    enteringNumbers = false;
                    showingResult = true;
                }
            } else {
                // Manejo del menú principal
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                    selectedOption = (selectedOption > 0) ? selectedOption - 1 : sortingOptions.size() - 1;
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
                    selectedOption = (selectedOption + 1) % sortingOptions.size();
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    enteringNumbers = true;
                    inputBuffer.clear();
                    inputText.setString("Ingresa numeros separados por espacio, Enter para finalizar:");
                    numbers.clear();
                }
            }
        }

        window.clear();
        if (showingResult) {
            if (!isSorted) {
                std::vector<int> originalNumbers = numbers;
                switch (selectedOption) {
                    case 0: bubbleSort(numbers, originalNumbers, window, font, isSorted); break;
                    case 1: selectionSort(numbers, originalNumbers, window, font, isSorted); break;
                    case 2: mergeSort(numbers, originalNumbers, window, font, isSorted); break;
                    case 3: quickSort(numbers, 0, numbers.size() - 1, originalNumbers, window, font, isSorted); break;
                    case 4: insertionSort(numbers, originalNumbers, window, font, isSorted); break;
                    case 5: { // Binary Search
                        quickSort(numbers, 0, numbers.size() - 1, originalNumbers, window, font, isSorted); // Ordenar antes de buscar
                        inputText.setString("Ingresa el numero a buscar (Binary Search): ");
                        int target = handleInput();

                        // Verificar si el usuario canceló con Escape
                        if (target == -1) {
                            resultText.setString("Operación cancelada. Regresando al menú...");
                            break;
                        }

                        // Ejecutar búsqueda binaria
                        int result = binarySearch(numbers, target, window, font);

                        if (result != -1) {
                            resultText.setString("Número encontrado en la posición: " + std::to_string(result));
                        } else {
                            resultText.setString("Número no encontrado.");
                        }
                        break;
                    }
                    case 6: { // Linear Search

                        inputText.setString("Ingresa el numero a buscar (Linear Search): ");
                        int target = handleInput();

                        // Verificar si el usuario canceló con Escape
                        if (target == -1) {
                            resultText.setString("Operación cancelada. Regresando al menú...");
                            break;
                        }

                        // Ejecutar búsqueda lineal
                        int result = linearSearch(numbers, target, originalNumbers, window, font);

                        if (result != -1) {
                            resultText.setString("Número encontrado en la posición: " + std::to_string(result));
                        } else {
                            resultText.setString("Número no encontrado.");
                        }
                        break;
                    }
                    default: break;
                }
                resultText.setString("Array ordenado: " + vectorToString(numbers) + " Presione Escape para volver al menu");
            }
            window.draw(resultText);
        } else if (enteringNumbers) {
            window.draw(inputText);
        } else {
            for (auto& text : optionsText) {
                text.setFillColor(sf::Color::White);
            }
            optionsText[selectedOption].setFillColor(sf::Color::Red);
            for (auto& text : optionsText) {
                window.draw(text);
            }
        }
        window.display();
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Estructuras de Datos y Algoritmos");
    sf::Font font;

    if (!font.loadFromFile("C:\\Users\\maugv\\Desktop\\C++\\SFML\\Open_Sans\\OpenSans-Italic-VariableFont_wdth,wght.ttf")) {
        std::cerr << "Error cargando la fuente" << std::endl;
        return EXIT_FAILURE;
    }

    // Crear instancias de las estructuras de datos
    Stack stack(window, font);      // Crear la pila
    Queue queue(window, font);      // Crear la cola
    LinkedList list(window, font);  // Crear la lista enlazada
    AVLTree avl(window, font);      // Crear el árbol AVL
    Graph graph(window, font);      // Crear el grafo
    DijkstraGraph dijkstra(window, font); // Crear DijkstraGraph

    // Opciones del menú principal
    std::vector<std::string> mainMenu = {
            "1. Stack", "2. Queue", "3. Linked List", "4. AVL Tree",
            "5. Graph", "6. Dijkstra", "7. Sorting and Searching Algorithms"
    };
    std::vector<sf::Text> mainMenuText;
    int mainMenuOption = 0;

    // Opciones de los submenús
    std::vector<std::string> stackMenu = { "Push", "Pop", "Display" };
    std::vector<std::string> queueMenu = { "Enqueue", "Dequeue", "Display" };
    std::vector<std::string> linkedListMenu = { "Insert", "Delete", "Display" };
    std::vector<std::string> avlMenu = { "Insert", "Delete", "Display" };
    std::vector<std::string> graphMenu = { "Add Node", "Add Edge", "BFS", "DFS", "Display" };
    std::vector<std::string> dijkstraMenu = { "Add Node", "Add Edge", "Run Dijkstra" };
    std::vector<sf::Text> subMenuText;
    int subMenuOption = 0;
    bool inSubMenu = false;

    // Crear el texto del menú principal
    for (size_t i = 0; i < mainMenu.size(); ++i) {
        sf::Text text(mainMenu[i], font, 30);
        text.setPosition(200, 150 + i * 50);
        text.setFillColor(i == mainMenuOption ? sf::Color::Red : sf::Color::White);
        mainMenuText.push_back(text);
    }

    // Bucle principal de la ventana
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (inSubMenu) {
                // Navegación en el submenú
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) {
                        subMenuOption = (subMenuOption > 0) ? subMenuOption - 1 : subMenuText.size() - 1;
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        subMenuOption = (subMenuOption + 1) % subMenuText.size();
                    }
                    if (event.key.code == sf::Keyboard::Escape) {
                        inSubMenu = false; // Salir del submenú
                    }
                    if (event.key.code == sf::Keyboard::Enter) {
                        // Ejecutar opción seleccionada del submenú
                        executeSubMenuOption(mainMenuOption, subMenuOption, window, font, stack, queue, list, avl, graph, dijkstra);
                    }
                }
            } else {
                // Navegación en el menú principal
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) {
                        mainMenuOption = (mainMenuOption > 0) ? mainMenuOption - 1 : mainMenu.size() - 1;
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        mainMenuOption = (mainMenuOption + 1) % mainMenu.size();
                    }
                    if (event.key.code == sf::Keyboard::Enter) {
                        // Cargar submenú correspondiente
                        subMenuText.clear();
                        std::vector<std::string>* selectedMenu = nullptr;

                        switch (mainMenuOption) {
                            case 0: selectedMenu = &stackMenu; break;
                            case 1: selectedMenu = &queueMenu; break;
                            case 2: selectedMenu = &linkedListMenu; break;
                            case 3: selectedMenu = &avlMenu; break;
                            case 4: selectedMenu = &graphMenu; break;
                            case 5: selectedMenu = &dijkstraMenu; break;
                            case 6: executeAlgorithmMenu(window, font); break;
                            default: break;
                        }

                        if (selectedMenu) {
                            for (size_t i = 0; i < selectedMenu->size(); ++i) {
                                sf::Text text((*selectedMenu)[i], font, 30);
                                text.setPosition(200, 150 + i * 50);
                                text.setFillColor(i == subMenuOption ? sf::Color::Red : sf::Color::White);
                                subMenuText.push_back(text);
                            }
                            inSubMenu = true; // Entrar al submenú
                        }
                    }
                }
            }
        }

        // Dibujar la ventana
        window.clear();
        if (inSubMenu) {
            for (auto& text : subMenuText) {
                text.setFillColor(sf::Color::White);
            }
            subMenuText[subMenuOption].setFillColor(sf::Color::Red);
            for (auto& text : subMenuText) {
                window.draw(text);
            }
        } else {
            for (auto& text : mainMenuText) {
                text.setFillColor(sf::Color::White);
            }
            mainMenuText[mainMenuOption].setFillColor(sf::Color::Red);
            for (auto& text : mainMenuText) {
                window.draw(text);
            }
        }
        window.display();
    }

    return EXIT_SUCCESS;
}