#include<iostream>
#include<fstream>
#include<unordered_map>
#include<string>
#include <cstdlib> 
#include <ctime>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

string bin_to_hex(string binary) {
    if (binary.length() == 0) {
        return "0";
    }
    while(binary.length() % 4 != 0){
        binary = "0" + binary;
    }
    unordered_map<string, char> hex_dict;
    hex_dict["0000"] = '0';
    hex_dict["0001"] = '1';
    hex_dict["0010"] = '2';
    hex_dict["0011"] = '3';
    hex_dict["0100"] = '4';
    hex_dict["0101"] = '5';
    hex_dict["0110"] = '6';
    hex_dict["0111"] = '7';
    hex_dict["1000"] = '8';
    hex_dict["1001"] = '9';
    hex_dict["1010"] = 'A';
    hex_dict["1011"] = 'B';
    hex_dict["1100"] = 'C';
    hex_dict["1101"] = 'D';
    hex_dict["1110"] = 'E';
    hex_dict["1111"] = 'F';
    string hexadecimal;
    for (size_t i = 0; i < binary.length(); i += 4) {
        string group = binary.substr(i, 4);
        hexadecimal += hex_dict[group];
    }
    return hexadecimal;
}

string convert_to_binary(string address){
    address = address.substr(2);
    string binary = "";
    unordered_map<char, string> hex_to_bin_dict;
    hex_to_bin_dict['0'] = "0000";
    hex_to_bin_dict['1'] = "0001";
    hex_to_bin_dict['2'] = "0010";
    hex_to_bin_dict['3'] = "0011";
    hex_to_bin_dict['4'] = "0100";
    hex_to_bin_dict['5'] = "0101";
    hex_to_bin_dict['6'] = "0110";
    hex_to_bin_dict['7'] = "0111";
    hex_to_bin_dict['8'] = "1000";
    hex_to_bin_dict['9'] = "1001";
    hex_to_bin_dict['A'] = "1010";
    hex_to_bin_dict['B'] = "1011";
    hex_to_bin_dict['C'] = "1100";
    hex_to_bin_dict['D'] = "1101";
    hex_to_bin_dict['E'] = "1110";
    hex_to_bin_dict['F'] = "1111";
    for (char digit : address) {
        binary += hex_to_bin_dict[toupper(digit)];
    }
    return binary;
}

class DirectMappingCache{
    public:
    int blocks;
    vector<string> cache;
    DirectMappingCache() {}
    DirectMappingCache(int blocks) {
        if (blocks <= 0)
        {
            std::cout << "Invalid number of blocks" << std::endl;
            return;
        }
        this->blocks = blocks;
        this->cache = vector<string> (blocks, "-1");
    }
    void check_and_insert(string tag,string set,string address){
        int index = stoi(set, nullptr, 2);
        string hex_tag = bin_to_hex(tag);
        string hex_set = bin_to_hex(set);
        if (cache[index] == tag){
            cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Hit ,Tag: 0x"<<hex_tag<<endl;
        }
        else{
            cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Miss ,Tag: 0x"<<hex_tag<<endl;
            cache[index] = tag;
        }
    }


    void check(string tag,string set,string address){
        int index = stoi(set, nullptr, 2);
        string hex_tag = bin_to_hex(tag);
        string hex_set = bin_to_hex(set);
        if (cache[index] == tag){
            cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Hit ,Tag: 0x"<<hex_tag<<endl;
        }
        else{
            cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Miss ,Tag: 0x"<<hex_tag<<endl;
        }
    }
};
int Direct_Mapping(int cache_size,int block_size,int associativity, string replacement_policy, string write_policy){
    int num_blocks = cache_size/block_size;
    // cout<<num_blocks<<endl;
    // cache = vector<string>(num_blocks, "-1");
    int offset_bits = log2(block_size); // 4
    int set_bits = log2(num_blocks); // 8
    int tag_bits = 32 - offset_bits - set_bits; // 32 - 4 - 8 = 20
    string accessfile = "cache.access";
    ifstream access(accessfile);
    string mode, address, tag, set;
    DirectMappingCache cache(num_blocks);
    while (access >> mode >> address) {
        mode = mode.substr(0,1);
        string binary = convert_to_binary(address);
        string tag = binary.substr(0,tag_bits); 
        string set = binary.substr(tag_bits, set_bits);
        if (write_policy == "WB"){
            cache.check_and_insert(tag, set,address);
        }
        if (write_policy == "WT" and mode == "R"){
            cache.check_and_insert(tag, set,address);
        }
        if (write_policy == "WT" and mode == "W"){
            cache.check(tag, set,address);
        }
    }
    access.close();
    return 0;
}

class SetAssociatedCache{
    public:
    int blocks;
    string replacement_policy;
    int association;
    vector<vector<string> > cache;
    SetAssociatedCache() {}
    SetAssociatedCache(int blocks, string replacement_policy,int association) {
        if (replacement_policy != "LRU" && replacement_policy != "FIFO" && replacement_policy != "RANDOM")
        {
            std::cout << "Invalid replacement policy" << std::endl;
            return;
        }
        if (blocks <= 0)
        {
            std::cout << "Invalid number of blocks" << std::endl;
            return;
        }
        this->blocks = blocks;
        this->replacement_policy = replacement_policy;
        this->association = association;
        this->cache = vector <vector<string> > (blocks, vector<string> (association, "-1"));
        srand(static_cast<unsigned>(time(0)));
    }

    void update_LRU(string tag, int set) {
        for (int i = 0; i < this->association; i++) {
            if (cache[set][i] == tag) {
                string temp_tag = cache[set][i];
                for (int j = i; j < association - 1; j++) {
                    cache[set][j] = cache[set][j + 1];
                }
                cache[set][association - 1] = temp_tag;
                break;
            }
        }
    }
    void check_and_insert_LRU(string tag, string set, string address){
        string hex_tag = bin_to_hex(tag);
        string hex_set = bin_to_hex(set);
        int index = stoi(set, nullptr, 2);
        for (int i = 0; i < association; i++) {
            if (cache[index][i] == tag) {
                cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Hit ,Tag: 0x"<<hex_tag<<endl;
                update_LRU(tag, index);
                return;
            }
        }
        cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Miss ,Tag: 0x"<<hex_tag<<endl;
        for (int i = 0; i < association - 1; i++) {
            cache[index][i] = cache[index][i + 1];
        }
        cache[index][association - 1] = tag;
        return;
    }
    void check_LRU(string tag, string set, string address){
        string hex_tag = bin_to_hex(tag);
        string hex_set = bin_to_hex(set);
        int index = stoi(set, nullptr, 2);
        for (int i = 0; i < association; i++) {
            if (cache[index][i] == tag) {
                cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Hit ,Tag: 0x"<<hex_tag<<endl;
                update_LRU(tag, index);
                return;
            }
        }
        cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Miss ,Tag: 0x"<<hex_tag<<endl;
        return;
    }

    void check_and_insert_FIFO(string tag, string set, string address){
        string hex_tag = bin_to_hex(tag);
        string hex_set = bin_to_hex(set);
        int index = stoi(set, nullptr, 2);
        for (int i = 0; i < association; i++) {
            if (cache[index][i] == tag) {
                cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Hit ,Tag: 0x"<<hex_tag<<endl;
                return;
            }
        }
        cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Miss ,Tag: 0x"<<hex_tag<<endl;
        for (int i = 0; i < association - 1; i++) {
            cache[index][i] = cache[index][i + 1];
        }
        cache[index][association - 1] = tag;
        return;
    }
    void check_FIFO(string tag, string set, string address){
        string hex_tag = bin_to_hex(tag);
        string hex_set = bin_to_hex(set);
        int index = stoi(set, nullptr, 2);
        for (int i = 0; i < association; i++) {
            if (cache[index][i] == tag) {
                cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Hit ,Tag: 0x"<<hex_tag<<endl;
                return;
            }
        }
        cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Miss ,Tag: 0x"<<hex_tag<<endl;
        for (int i = 0; i < association - 1; i++) {
            cache[index][i] = cache[index][i + 1];
        }
        cache[index][association - 1] = tag;
        return;
    }

    void check_and_insert_RANDOM(string tag, string set, string address){
        string hex_tag = bin_to_hex(tag);
        string hex_set = bin_to_hex(set);
        int index = stoi(set, nullptr, 2);
        for (int i = 0; i < association; i++) {
            if (cache[index][i] == tag) {
                cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Hit ,Tag: 0x"<<hex_tag<<endl;
                return;
            }
        }
        cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Miss ,Tag: 0x"<<hex_tag<<endl;
        int randomIndex = rand() % association;
        cache[index][randomIndex] = tag;
        return;
    }
    void check_RANDOM(string tag, string set, string address){
        string hex_tag = bin_to_hex(tag);
        string hex_set = bin_to_hex(set);
        int index = stoi(set, nullptr, 2);
        for (int i = 0; i < association; i++) {
            if (cache[index][i] == tag) {
                cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Hit ,Tag: 0x"<<hex_tag<<endl;
                return;
            }
        }
        cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Miss ,Tag: 0x"<<hex_tag<<endl;
        return;
    }

    public:
        void check_and_insert(string tag, string set, string address){
            if (this->replacement_policy == "LRU") {
                check_and_insert_LRU(tag, set, address);
            }
            else if (this->replacement_policy == "FIFO") {
                check_and_insert_FIFO(tag, set, address);
            }
            else if (this->replacement_policy == "RANDOM") {
                check_and_insert_RANDOM(tag, set, address);
            }
        }
        void check(string tag, string set, string address) {
            if (this->replacement_policy == "LRU") {
                check_LRU(tag, set, address);
            }
            else if (this->replacement_policy == "FIFO") {
                check_FIFO(tag, set, address);
            }
            else if (this->replacement_policy == "RANDOM") {
                check_RANDOM(tag, set, address);
            }
        }
};
int Set_Associated(int cache_size,int block_size,int associativity, string replacement_policy, string write_policy){
    int num_blocks = cache_size/block_size;
    // cout<<num_blocks<<endl;
    int offset_bits = log2(block_size); // 4
    int set_bits = log2(num_blocks/associativity); // 8
    int tag_bits = 32 - offset_bits - set_bits; // 32 - 4 - 8 = 20
    string accessfile = "cache.access";
    ifstream access(accessfile);
    string mode, address, tag, set;
    SetAssociatedCache cache(num_blocks,replacement_policy,associativity);
    // cout<< num_blocks << " " << offset_bits << " " << set_bits << " " << tag_bits << endl;
    // cout<< "Replacement Policy: " << replacement_policy << endl;
    // cout<<"Associativity: "<<associativity<<endl;
    while (access >> mode >> address) {
        mode = mode.substr(0,1);
        string binary = convert_to_binary(address);
        string tag = binary.substr(0,tag_bits); 
        string set = binary.substr(tag_bits, set_bits);
        if (write_policy == "WB"){
            cache.check_and_insert(tag, set,address);
        }
        else if (write_policy == "WT" and mode == "R"){
            cache.check_and_insert(tag, set,address);
        }
        else if (write_policy == "WT" and mode == "W"){
            cache.check(tag, set,address);
        }
    }   
    access.close();
    return 0;
}

class FullyAssociatedCache{
    public:
    int blocks;
    string replacement_policy;
    vector<pair <string, string> > cache;
    FullyAssociatedCache() {}
    FullyAssociatedCache(int blocks, string replacement_policy) {
        if (replacement_policy != "LRU" && replacement_policy != "FIFO" && replacement_policy != "RANDOM")
        {
            std::cout << "Invalid replacement policy" << std::endl;
            return;
        }
        if (blocks <= 0)
        {
            std::cout << "Invalid number of blocks" << std::endl;
            return;
        }
        this->blocks = blocks;
        this->replacement_policy = replacement_policy;
        this->cache = vector<pair <string, string> > (blocks, make_pair("-1","-1"));
        srand(static_cast<unsigned>(time(0)));
    }

    void update_LRU(string set) {
        for (int i = 0; i < this->blocks; i++) {
            if (cache[i].second == set) {
                pair<string, string> temp = cache[i];
                for (int j = i; j < blocks - 1; j++) {
                    cache[j] = cache[j + 1];
                }
                cache[blocks - 1] = temp;
                break;
            }
        }
    }
    void check_and_insert_LRU(string tag, string set, string address){
        string hex_tag = bin_to_hex(tag);
        string hex_set = bin_to_hex(set);
        for (int i = 0; i < blocks; i++) {
            if (cache[i].first == tag && cache[i].second == set) {
                cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Hit ,Tag: 0x"<<hex_tag<<endl;
                update_LRU(set);
                return;
            }
        }
        cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Miss ,Tag: 0x"<<hex_tag<<endl;
        for (int i = 0; i < blocks - 1; i++) {
            cache[i] = cache[i + 1];
        }
        cache[blocks - 1] = make_pair(tag, set);
    }
    void check_LRU(string tag, string set, string address){
        string hex_tag = bin_to_hex(tag);
        string hex_set = bin_to_hex(set);
        for (int i = 0; i < blocks; i++) {
            if (cache[i].first == tag && cache[i].second == set) {
                cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Hit ,Tag: 0x"<<hex_tag<<endl;
                update_LRU(set);
                return;
            }
        }
        cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Miss ,Tag: 0x"<<hex_tag<<endl;
        return;
    }

    void check_and_insert_FIFO(string tag, string set, string address){
        string hex_tag = bin_to_hex(tag);
        string hex_set = bin_to_hex(set);
        for (int i = 0; i < blocks; i++) {
            if (cache[i].first == tag && cache[i].second == set) {
                cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Hit ,Tag: 0x"<<hex_tag<<endl;
                return;
            }
        }
        cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Miss ,Tag: 0x"<<hex_tag<<endl;
        for (int i = 0; i < blocks - 1; i++) {
            cache[i] = cache[i + 1];
        }
        cache[blocks - 1] = make_pair(tag, set);
        return;
    }
    void check_FIFO(string tag, string set, string address){
        string hex_tag = bin_to_hex(tag);
        string hex_set = bin_to_hex(set);
        for (int i = 0; i < blocks; i++) {
            if (cache[i].first == tag && cache[i].second == set) {
                cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Hit ,Tag: 0x"<<hex_tag<<endl;
                return;
            }
        }
        cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Miss ,Tag: 0x"<<hex_tag<<endl;
        return;
    }

    void check_and_insert_RANDOM(string tag, string set, string address){
        string hex_tag = bin_to_hex(tag);
        string hex_set = bin_to_hex(set);
        for (int i = 0; i < blocks; i++) {
            if (cache[i].first == tag && cache[i].second == set) {
                cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Hit ,Tag: 0x"<<hex_tag<<endl;
                return;
            }
        }
        cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Miss ,Tag: 0x"<<hex_tag<<endl;
        int index = rand() % blocks;
        cache[index] = make_pair(tag, set);     
        return;
    }
    void check_RANDOM(string tag, string set, string address){
        string hex_tag = bin_to_hex(tag);
        string hex_set = bin_to_hex(set);
        for (int i = 0; i < cache.size(); i++) {
            if (cache[i].first == tag && cache[i].second == set) {
                cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Hit ,Tag: 0x"<<hex_tag<<endl;
                return;
            }
        }
        cout<<"Address: "<<address<<" , Set: 0x"<<hex_set<<" ,Miss ,Tag: 0x"<<hex_tag<<endl;    
        return;
    }    

    public:
        void check_and_insert(string tag, string set, string address){
            if (this->replacement_policy == "LRU") {
                check_and_insert_LRU(tag, set, address);
            }
            else if (this->replacement_policy == "FIFO") {
                check_and_insert_FIFO(tag, set, address);
            }
            else if (this->replacement_policy == "RANDOM") {
                check_and_insert_RANDOM(tag, set, address);
            }
        }
        void check(string tag, string set, string address) {
            if (this->replacement_policy == "LRU") {
                check_LRU(tag, set, address);
            }
            else if (this->replacement_policy == "FIFO") {
                check_FIFO(tag, set, address);
            }
            else if (this->replacement_policy == "RANDOM") {
                check_RANDOM(tag, set, address);
            }
        }
};
int Full_Associated(int cache_size,int block_size,int associativity, string replacement_policy, string write_policy){
    int num_blocks = cache_size/block_size;
    int offset_bits = log2(block_size); // 9
    int set_bits = 0;
    int tag_bits = 32 - offset_bits - set_bits; // 32 - 5 - 9 = 18
    string accessfile = "cache.access";
    ifstream access(accessfile);
    string mode, address, tag, set;
    FullyAssociatedCache cache(num_blocks,replacement_policy);
    while (access >> mode >> address) {
        mode = mode.substr(0,1);
        string binary = convert_to_binary(address);
        string tag = binary.substr(0,tag_bits); 
        string set = binary.substr(tag_bits, set_bits);
        if (write_policy == "WB"){
            cache.check_and_insert(tag, set,address);
        }
        else if (write_policy == "WT" and mode == "R"){
            cache.check_and_insert(tag, set,address);
        }
        else if (write_policy == "WT" and mode == "W"){
            cache.check(tag, set,address);
        }
    }   
    access.close();
    return 0;
}

int main(){
    int cache_size,block_size,associativity;
    string  replacement_policy,write_policy;
    // Read from cache.config

    string filename = "cache.config";
    ifstream file(filename);
    if (file.is_open()){
        file>>cache_size>>block_size>>associativity>>replacement_policy>>write_policy;
        file.close();
    }
    else{
        cout<<"Unable to open file";
    }
    if (replacement_policy != "LRU" && replacement_policy != "FIFO" && replacement_policy != "RANDOM")
    {
        std::cout << "Invalid replacement policy" << std::endl;
        return 0;
    }
    if (write_policy != "WB" && write_policy != "WT")
    {
        std::cout << "Invalid write policy" << std::endl;
        return 0;
    }

    // std::cout << "SIZE_OF_CACHE: " << cache_size << std::endl;
    // std::cout << "BLOCK_SIZE: " << block_size << std::endl;
    // std::cout << "ASSOCIATIVITY: " << associativity << std::endl;
    // std::cout << "REPLACEMENT_POLICY: " << replacement_policy << std::endl;
    // std::cout << "WRITEBACK_POLICY: " << write_policy << std::endl;

    // if (associativity == 1) {
    //     cout << "Direct Mapped" << endl;
    // }
    // else if (associativity == 0) {
    //     cout << "Fully Associative" << endl;
    // }
    // else {
    //     cout << "Set Associative" << endl;
    // }


    // Direct Mapped
    if (associativity == 1 ){
        // cout<<"Direct Mapped"<<endl;
        Direct_Mapping(cache_size,block_size,associativity,replacement_policy,write_policy);
    }
    else if (associativity == 0){
        // cout<<"Fully Associative"<<endl;
        Full_Associated(cache_size,block_size,associativity,replacement_policy,write_policy);
    }
    else{
        // cout<<"Set Associative"<<endl;
        Set_Associated(cache_size,block_size,associativity,replacement_policy,write_policy);
    }
    // string accessfile = "cache.access";
    // ifstream access(accessfile);
    // string mode, address, tag, set;
    // while (access >> mode >> address) {
    //     mode = mode.substr(0,1);
    //     tag = address.substr(0,8);
    //     set = "0x" + address.substr(8,10);
    //     cout << "Mode: " << mode << ", Address: " << address << ", Tag: " << tag << ", Set:" << set <<endl;
    // }
    // access.close();
    return 0;
}