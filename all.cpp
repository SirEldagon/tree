#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Узел Trie
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool is_end_of_word;

    TrieNode() : is_end_of_word(false) {}
};

// Класс Trie
class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Вставка слова
    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->is_end_of_word = true;
    }

    // Поиск узла по префиксу
    TrieNode* searchPrefix(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            if (node->children.find(ch) == node->children.end()) {
                return nullptr;
            }
            node = node->children[ch];
        }
        return node;
    }

    // Рекурсивный обход для поиска всех слов с данным префиксом
    void autocomplete(TrieNode* node, const string& prefix, vector<string>& results) {
        if (node->is_end_of_word) {
            results.push_back(prefix);
        }
        for (auto& pair : node->children) {
            autocomplete(pair.second, prefix + pair.first, results);
        }
    }

    // Получение всех слов по префиксу
    vector<string> getSuggestions(const string& prefix) {
        vector<string> results;
        TrieNode* node = searchPrefix(prefix);
        if (node) {
            autocomplete(node, prefix, results);
        }
        return results;
    }

private:
    TrieNode* root;
};

int main() {
    // Изначальный словарь
    vector<string> dictionary = {
        "кот", "кошка", "космос", "компьютер", "книга",
        "класс", "классика", "красота", "красный", "красивый"
    };

    Trie trie;
    // Построение дерева
    for (const auto& word : dictionary) {
        trie.insert(word);
    }

    cout << "Автодополнение. Введите часть слова (для выхода введите 'exit'):" << endl;

    string input;
    while (true) {
        cout << "Введите часть слова: ";
        getline(cin, input);
        if (input == "exit") {
            break;
        }

        vector<string> suggestions = trie.getSuggestions(input);
        if (!suggestions.empty()) {
            cout << "Варианты продолжения:" << endl;
            for (const auto& suggestion : suggestions) {
                cout << "  " << suggestion << endl;
            }
        } else {
            cout << "Нет подходящих вариантов." << endl;
        }
    }

    return 0;
}
