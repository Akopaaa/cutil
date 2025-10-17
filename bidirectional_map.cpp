#include <iostream>
#include <map>

template<typename K, typename V>
class bidirectional_map {

    public:

    std::map<K, V*> keys;
    std::map<V, K*> values;

    bidirectional_map() {
        this->keys = std::map<K, V*>();
        this->values = std::map<V, K*>();
    }

    void add_pair(const K key, const V value) {
        auto [ itKey, _ ] = this->keys.emplace(key, nullptr);
        auto [ itValue, __ ] = this->values.emplace(value, nullptr);

        itKey->second = const_cast<V*>(&(itValue->first));
        itValue->second = const_cast<K*>(&(itKey->first));
    }

    void add_key(const K key, const V* value_ptr = nullptr) {
        this->keys.emplace(key, value_ptr);
    }

    void add_value(const V value, const K* key_ptr = nullptr) {
        this->values.emplace(value, key_ptr);
    }

    void remove_w_key(const K key) {
        this->values.erase(*this->keys[key]);
        this->keys.erase(key);
    }

    void remove_w_value(const V value) {
        this->keys.erase(*this->values[value]);
        this->values.erase(value);
    }

};

int main() {

    bidirectional_map bimap = bidirectional_map<int, int>();

    bimap.add_pair(5, 3);
    bimap.add_pair(6, 7);
    bimap.remove_w_key(5);

    std::cout << bimap.keys[5];

    return 0;

}