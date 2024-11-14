#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct SNode{
    string data;
    SNode* next;
};

struct LSNode{
    string data;
    LSNode* next;
};

struct LDNode{
    string data;
    LDNode* next;
    LDNode* prev;
};

struct QNode{
    string data;
    QNode* next;
    QNode* prev;
};

struct HNode{
    string key;
    string data;
    HNode* next;
};

struct TNode{
    string data;
    TNode* left;
    TNode* right;
};

struct Stk{
    SNode* head;

    Stk() : head(nullptr) {}

    bool is_empty(){
        return head == nullptr;
    }

    void SPUSH(string data){
    SNode* new_node = new SNode();
    new_node->data = data;
    new_node->next = head;
    head = new_node;
    }

    void SPOP(){
        SNode* new_head = head;
        head = head->next;
        delete new_head;
    }
    
    void printStack() const {
        SNode* current = head;
        cout << "Stack output:" << endl;
        while (current != nullptr) {
            cout << current->data << endl;
            current = current->next;
        }
        cout << endl;
    }
    
    void SWrite(string& read, string filename, int ind_start, int end){
        ofstream in;
        in.open(filename);
        if (is_empty()){
            cout << "Stack is empty" << endl;
            in << read;
            in.close();
            return;
        }
        SNode* current = head;
        while (current->next != nullptr){
            read.insert(ind_start+1, '\"' + current->data + '\"' + ';' + '\n');
            ind_start += current->data.size() + 4;
            current = current->next;
        }
        read.insert(ind_start+1, '\"' + current->data + '\"');
        in << read;
        in.close();
        return;
    }

    void SRead(string& read, int& ind_start, int& ind){
        for (ind; read[ind] != '{' && ind < read.size(); ind++);
        ind_start = ind;
        ind++;
        if (read[ind] == '}'){
            return;
        }
        Stk flip;
        string datas = "";
        for (ind; read[ind] != '}' && read[ind] != '\n' && ind < read.size(); ind++){
            for (ind; read[ind] != '\"' && read[ind] != '}' && ind < read.size(); ind++);
            ind++;
            for (ind; read[ind] != '\"' && read[ind] != '}' && ind < read.size(); ind++){
                datas += read[ind];
            }
            flip.SPUSH(datas);
            datas = "";
        }
        while(flip.head != nullptr){
            SPUSH(flip.head->data);
            flip.head = flip.head->next;
        }
        read.erase(ind_start + 1, ind - ind_start - 1);
        return;
    }
};

struct LIST_S {
    LSNode* Lhead;


    bool is_empty(){
        return Lhead == nullptr;
    }

    void LsPRINT(){
        LSNode* current = Lhead;
        if (is_empty()){
            cout << "List is empty!" << endl;
            return;
        }
        cout << "List output" << endl;
        while (current != nullptr) {
            cout << current->data << endl;
            current = current->next;
        }

    }

    void LsPUSH_end(string new_data){
        LSNode* new_node = new LSNode{new_data, nullptr};
        LSNode* current = Lhead;
        if (is_empty()){
            Lhead = new_node;
            return;
        }
        else {
            while (current->next != nullptr){
                current = current->next;
            }
            current->next = new_node;
        }
    }

    void LsPUSH_front(string new_data){
        LSNode* new_node = new LSNode{new_data, nullptr};
        if (!is_empty()){
            new_node->next = Lhead;
            Lhead = new_node;
        }
        else{
            Lhead = new_node;
        }
    }

    void LsPOP_head(){
        if (is_empty()){
            cout << "List is empty!";
            return;
        }
        LSNode* kill_node = Lhead;
        Lhead = Lhead->next;
        delete kill_node;
    }

    void LsPOP_end(){
        LSNode* kill_node;
        LSNode* current = Lhead;
        if (is_empty()){
            cout << "List is empty!";
            return;
        }
        if (current->next == nullptr){
            LsPOP_head();
            return;
        }
        while (current->next->next != nullptr){
            current = current->next;
        }
        kill_node = current->next->next;
        delete current->next;
        current->next = kill_node;
    }

    void LsPOP_data(string kill_data){
        LSNode* current = Lhead;
        bool is_having = 0;
        if (is_empty()){
            cout << "LIST IS EMPTY!!!" << endl;
            return;
        }
        if (current->data == kill_data){
            while(current->data == kill_data){
                LsPOP_head();
                if (is_empty()){
                    return;
                }
                current = current->next;
            }
        }
        if (is_empty()){
            return;
        }
        while (current->next->next != nullptr){
            if (current->next->data == kill_data){
                LSNode* kill_node = current->next;
                current->next = current->next->next;
                delete kill_node;
                is_having = 1;
            }
            current = current->next; 
            if (current->next == nullptr){
                break;
            }             
        }
        if (current->next == nullptr){
            if (current->data == kill_data){
                LsPOP_end();
                is_having = 1;
            }
        }
        else if (current->next->data == kill_data){
            LsPOP_end();
            is_having = 1;
        }            
        if (is_having == 0){
            cout << "List don't have that position" << endl;
            return;
        }
    }
    

    void LsGET(string get_data){
        LSNode* current = Lhead;
        int ind = 0;
        bool is_having = 0;
        if (is_empty()){
            cout << "List is empty!" << endl;
            return;
        }
        cout << "Elements with data " << get_data << ":" << endl;
        while (current->next != nullptr){
            if (current->data == get_data){
                cout << ind << endl;
                is_having = 1;
            }
            current = current->next;
            ind++;
        }
        if (current->data == get_data){
            cout << ind << endl;
            is_having = 1;
        }
        if (is_having == 0){
            cout << "List don't has them" << endl;
        }
    }

    void LsWrite(string& read, string filename, int ind_start, int end){
        ofstream in;
        in.open(filename);
        if (is_empty()){
            cout << "List is empty" << endl;
            in << read;
            in.close();
            return;
        }
        LSNode* current = Lhead;
        while (current->next != nullptr){
            read.insert(ind_start+1, '\"' + current->data + '\"' + ';');
            ind_start += current->data.size() + 3;
            current = current->next;
        }
        read.insert(ind_start+1, '\"' + current->data + '\"');
        in << read;
        in.close();
        return;
    }

    void LsRead(string& read, int& ind_start, int& ind){
        for (ind; read[ind] != '{' && ind < read.size(); ind++);
        ind_start = ind;
        ind++;
        if (read[ind] == '}'){
            return;
        }
        string datas = "";
        for (ind; read[ind] != '}' && read[ind] != '\n' && ind < read.size(); ind++){
            for (ind; read[ind] != '\"' && read[ind] != '}' && ind < read.size(); ind++);
            ind++;
            for (ind; read[ind] != '\"' && read[ind] != '}' && ind < read.size(); ind++){
                datas += read[ind];
            }
            LsPUSH_end(datas);
            datas = "";
        }
        read.erase(ind_start + 1, ind - ind_start - 1);
        return;
    }
};

struct LIST_d{
    LDNode* Lhead;
    LDNode* Ltail;

    bool is_empty(){
        return Lhead == nullptr;
    }

    void LdPRINT(){
        LDNode* current = Lhead;
        if (is_empty()){
            cout << "List is empty!" << endl;
            return;
        }
        cout << "List output" << endl;
        while (current != nullptr) {
            cout << current->data << endl;
            current = current->next;
        }

    }

    void LdPUSH_end(string new_data){
        LDNode* new_node = new LDNode{new_data, nullptr, nullptr};
        if (is_empty()){
            Lhead = new_node;
            Ltail = new_node;
            return;
        }
        else {
            new_node->prev = Ltail;
            Ltail->next = new_node;
            Ltail = new_node;
        }
    }

    void LdPUSH_front(string new_data){
        LDNode* new_node = new LDNode{new_data, nullptr, nullptr};
        if (!is_empty()){
            new_node->next = Lhead;
            Lhead->prev = new_node;
            Lhead = new_node;
        }
        else{
            Lhead = new_node;
            Ltail = new_node;
        }
    }

    void LdPOP_head(){
        if (is_empty()){
            cout << "List is empty!" << endl;
            return;
        }
        if (Lhead == Ltail){
            Ltail = Ltail->next;
            Lhead = Ltail;
            return;
        }
        LDNode* kill_node = Lhead;
        Lhead->next->prev = nullptr;
        Lhead = Lhead->next;
        delete kill_node;
    }

    void LdPOP_end(){
        if (is_empty()){
            cout << "List is empty!" << endl;
            return;
        }
        LDNode* kill_node = Ltail;
        if (Ltail == Lhead){
            LdPOP_head();
            return;
        }
        Ltail = Ltail->prev;
        Ltail->next = nullptr;
        delete kill_node;
    }

    void LdPOP_data(string kill_data){
        bool is_having;
        LDNode* current = Lhead;
        LDNode* kill_node = new LDNode();
        if (is_empty()){
            cout << "LIST IS EMPTY!!!" << endl;
            return;
        }
        if (Lhead->data == kill_data){
            while (Lhead->data == kill_data){
                LdPOP_head();
                if(is_empty()){
                    return;
                }
            }
            current = Lhead;
            is_having = 1;
        }
        while (current->next != nullptr) {             
            if (current->data == kill_data){
                kill_node = current;
                current->next->prev = current->prev;
                current->prev->next = current->next; 
                delete kill_node;
                is_having = 1;
            }
            current = current->next;            
        }
        if (Ltail->data == kill_data){
            LdPOP_end();
            is_having = 1;         
        }
        if (is_having == 0){
            cout << "List don't have that data" << endl;
            return;
        }            

    }

    void LdGET(string get_data){
        LDNode* current = Lhead;
        bool is_having = 0;
        int ind = 0;
        if (is_empty()){
            cout << "List is empty!" << endl;
            return;
        }
        cout << "Elements with data " << get_data << ":" << endl;
        while (current->next != nullptr){
            if (current->data == get_data){
                cout << ind << endl;
                is_having = 1;
            }
            current = current->next;
            ind++;
        }
        if (Ltail->data == get_data){
            cout << ind << endl;
            is_having = 1;
        }
        if (is_having == 0){
            cout << "List don't have that" << endl;
            return;
        }
    }

    void LdWrite(string& read, string filename, int ind_start, int end){
        ofstream in;
        in.open(filename);
        if (is_empty()){
            cout << "List is empty" << endl;
            in << read;
            in.close();
            return;
        }
        LDNode* current = Lhead;
        while (current != Ltail){
            read.insert(ind_start+1, '\"' + current->data + '\"' + ';');
            ind_start += current->data.size() + 3;
            current = current->next;
        }
        read.insert(ind_start+1, '\"' + Ltail->data + '\"');
        in << read;
        in.close();
        return;
    }

    void LdRead(string& read, int& ind_start, int& ind){
        for (ind; read[ind] != '{' && ind < read.size(); ind++);
        ind_start = ind;
        ind++;
        if (read[ind] == '}'){
            return;
        }
        string datas = "";
        for (ind; read[ind] != '}' && read[ind] != '\n' && ind < read.size(); ind++){
            for (ind; read[ind] != '\"' && read[ind] != '}' && ind < read.size(); ind++);
            ind++;
            for (ind; read[ind] != '\"' && read[ind] != '}' && ind < read.size(); ind++){
                datas += read[ind];
            }
            LdPUSH_end(datas);
            datas = "";
        }
        read.erase(ind_start + 1, ind - ind_start - 1);
        return;
    }

};

struct Queue{
    QNode* Qhead;
    QNode* Qtail;

    bool is_empty(){
        return Qhead == nullptr;
    }

    void QPrint(){
        if (is_empty()){
            cout << "Queue is empty" << endl;
            return;
        }
        cout << "Queue output:" << endl;
        QNode* current = Qhead;

        while (current != nullptr){
            cout << current->data << endl;
            current = current->next;
        }
    }
    void QPush(string new_data){
        QNode* new_node = new QNode{new_data, nullptr, nullptr};
        if (is_empty()){
            Qhead = new_node;
            Qtail = new_node;
        } else {
            new_node->prev = Qtail;
            Qtail->next = new_node;
            Qtail->prev = nullptr;
            Qtail = new_node;
        }
    }

    void QPop(){
        if (is_empty()){
            cout << "Queue is empty" << endl;
            return;
        }
        QNode* kill_node = Qhead;
        Qhead = Qhead->next;
        delete kill_node;
    }

    void QWrite(string& read, string filename, int ind_start, int end){
        ofstream in;
        in.open(filename);
        if (is_empty()){
            cout << "Queue is empty" << endl;
            in << read;
            in.close();
            return;
        }
        QNode* current = Qhead;
        while (current != Qtail){
            read.insert(ind_start+1, '\"' + current->data + '\"' + ';');
            ind_start += current->data.size() + 3;
            current = current->next;
        }
        read.insert(ind_start+1, '\"' + Qtail->data + '\"');
        in << read;
        in.close();
        return;
    }

    void QRead(string& read, int& ind_start, int& ind){
        for (ind; read[ind] != '{' && ind < read.size(); ind++);
        ind_start = ind;
        ind++;
        if (read[ind] == '}'){
            return;
        }
        string datas = "";
        for (ind; read[ind] != '}' && read[ind] != '\n' && ind < read.size(); ind++){
            for (ind; read[ind] != '\"' && read[ind] != '}' && ind < read.size(); ind++);
            ind++;
            for (ind; read[ind] != '\"' && read[ind] != '}' && ind < read.size(); ind++){
                datas += read[ind];
            }
            QPush(datas);
            datas = "";
        }
        read.erase(ind_start + 1, ind - ind_start - 1);
        return;
    }
};

struct Massive{
    int size;
    string* elements = new string[size];

    string operator[] (int i){
        return elements[i];
    }

    bool is_empty(){
        return size == 0;
    }

    void MPrint(){
        if(is_empty()){
            cout << "Massive is empty" << endl;
            return;
        }
        int i = 0;
        cout << "Massive output:" << endl;
        while (i < size){
            cout << elements[i] << endl;
            i++;
        }
    }

    void MPushback(string element){
        size++;
        string* new_elements = new string[size];
        for (int i = 0; i < size-1; i++){
            new_elements[i] = elements[i];
        }
        delete[] elements;
        new_elements[size-1] = element;
        elements = new_elements;
    }

    void MPushind(int ind, string element){
        size++;
        if(is_empty()){
            cout << "Massive is empty" << endl;
            return;
        }
        if(ind > size-1){
            cout << "Index is bigger than massive has" << endl;
            return;
        }
        if(ind == size){
            MPushback(element);
            return;
        }
        string* new_elements = new string[size];
        for (int i = 0; i < ind; i++){
            new_elements[i] = elements[i];
        }
        new_elements[ind] = element;
        for (int i = ind; i < size-1; i++){
            new_elements[i+1] = elements[i];
        }
        delete[] elements;
        elements = new_elements;
    }

    void MPopind(int ind){
        size--;
        if(is_empty()){
            cout << "Massive is empty" << endl;
            return;
        }
        if(ind > size){
            cout << "Index is bigger than massive has" << endl;
            return;
        }
        string* new_elements = new string[size];
        if(ind == size+1){
            for (int i = 0; i < size; i++){
                new_elements[i] = elements[i];
            }
            delete[] elements;
            elements = new_elements;
            return;
        }
        for (int i = 0; i < ind; i++){
            new_elements[i] = elements[i];
        }
        for (int i = ind; i < size; i++){
            new_elements[i] = elements[i+1];
        }
        delete[] elements;
        elements = new_elements;
    }

    void MChange(int ind, string element){
        string* new_elements = new string[size];
        if(is_empty()){
            cout << "Massive is empty" << endl;
            return;
        }
        if(ind >= size){
            cout << "Index is bigger than massive has" << endl;
            return;
        }
        for(int i = 0; i < ind; i++){
            new_elements[i] = elements[i];
        }
        new_elements[ind] = element;
        for(int i = ind+1; i < size; i++){
            new_elements[i] = elements[i];
        }
        delete[] elements;
        elements = new_elements;
    }

    void MGet(int ind){
        if(is_empty()){
            cout << "Massive is empty" << endl;
            return;
        }
        if(ind >= size){
            cout << "Index is bigger than massive has" << endl;
            return;
        }
        cout << "Element with index " << ind << ":" << endl;
        cout << elements[ind] << endl;
    }

    int Size(){
        return size;
    }
    
    void MWrite(string& read, string filename, int ind_start, int end){
        ofstream in;
        in.open(filename);
        if (is_empty()){
            cout << "Massive is empty" << endl;
            in << read;
            in.close();
            return;
        }
        int i = 0;
        while (i < size - 1){
            read.insert(ind_start+1, '\"' + elements[i] + '\"' + ';');
            ind_start += elements[i].size() + 3;
            i++;
        }
        read.insert(ind_start+1, '\"' + elements[size - 1] + '\"');
        in << read;
        in.close();
        return;
    }

    void MRead(string& read, int& ind_start, int& ind){
        for (ind; read[ind] != '{' && ind < read.size(); ind++);
        ind_start = ind;
        ind++;
        if (read[ind] == '}'){
            return;
        }
        string datas = "";
        for (ind; read[ind] != '}' && read[ind] != '\n' && ind < read.size(); ind++){
            for (ind; read[ind] != '\"' && read[ind] != '}' && ind < read.size(); ind++);
            ind++;
            for (ind; read[ind] != '\"' && read[ind] != '}' && ind < read.size(); ind++){
                datas += read[ind];
            }
            MPushback(datas);
            datas = "";
        }
        read.erase(ind_start + 1, ind - ind_start - 1);
        return;
    }

};

struct Hash{
    int size = 7;
    HNode** tabs = new HNode*[size];

    Hash () {
        for (int i = 0; i < size; i++){
            tabs[i] = nullptr;
        }
    }
    bool is_empty(){
        for (int i = 0; i < size; i++){
            if (tabs[i] != nullptr){
                return false;
            }
        }
        return true;
    }
    void HPrint(){
        int ind = 0;
        if (is_empty()){
            cout << "Empty" << endl;
            return;
        }
        cout << "Output: " << endl;
        while (ind < size){
            cout << "num " << ind << endl;
            if (tabs[ind] == nullptr) cout << "Empty" << endl;
            if (tabs[ind] != nullptr){
                HNode* current = tabs[ind];
                cout << "[ ";
                while (current != nullptr){
                    cout << "<" << current->key << ", " << current->data << "> ";
                    current = current->next;
                }
                cout << "]" << endl;
            }
            ind++;
        }
    }

    int Htrans (string new_key){
        int sum = 0;
        for (int i = 0; i < new_key.size(); i++){
            sum += new_key[i];
        }
        return sum % size;
    }

    void HPush(string new_key_s, string new_data){
        int new_key = Htrans(new_key_s);
        HNode* new_node = new HNode{new_key_s, new_data, nullptr};
        if (tabs[new_key] != nullptr){
            if (tabs[new_key]->key == new_key_s){
                new_node->next = tabs[new_key]->next;
                delete tabs[new_key];
                tabs[new_key] = new_node;
                return;
            }
            HNode* current = tabs[new_key];
            while (current->next != nullptr){
                if (current->next->key == new_key_s){
                    new_node->next = current->next->next;
                    delete current->next;
                    current->next = new_node;
                    return;
                }
                current = current->next;
            }
        }      
        new_node->next = tabs[new_key];
        tabs[new_key] = new_node;
    }

    string HGet(string key_s){
        if (is_empty()){
            cout << "Hash is Empty" << endl;
            return "";
        }
        int new_key = Htrans(key_s);
        if (tabs[new_key] == nullptr){
            cout << "Don't have data with this key" << endl;
            return "";
        }
        HNode* current = tabs[new_key];
        while (current != nullptr){
            if (current->key == key_s){
                return current->data;
            }
            current = current->next;
        }
        if (current == nullptr){
            cout << "Don't have data with this key" << endl;
            return "";
        }
        return "";
    }

    void HPop(string key_s){
        if (is_empty()){
            cout << "Hash is Empty" << endl;
            return;
        }
        int new_key = Htrans(key_s);
        if (tabs[new_key] == nullptr){
            cout << "Don't have data with this key" << endl;
            return;
        }
        HNode* current = tabs[new_key];
        if (tabs[new_key]->key == key_s){
            current = tabs[new_key];
            delete current;
            tabs[new_key] = tabs[new_key]->next;
            return;
        }
        while (current->next != nullptr){
            if (current->next->key == key_s){
                HNode* kill_node = current->next;
                delete kill_node;
                current->next = current->next->next;
                return;
            }
            current = current->next;
        }
        if (current->next == nullptr){
            cout << "Don't have data with this key" << endl;
            return;
        }
    }

    void HWrite(string& read, string filename, int ind_start, int end){
        ofstream in;
        in.open(filename);
        if (is_empty()){
            cout << "Hash is empty" << endl;
            in << read;
            in.close();
            return;
        }
        int i = 0;
        while (i < size){
            if (tabs[i] != nullptr){
                HNode* current = tabs[i];
                while(current != nullptr){
                    read.insert(ind_start+1, '(' + current->key + ',' + current->data + ')');
                    ind_start += current->key.size() + current->data.size() + 3;
                    current = current->next;
                }
            }
            i++;
        }
        in << read;
        in.close();
        return;
    }

    void HRead(string& read, int& ind_start, int& ind){
        for (ind; read[ind] != '{' && ind < read.size(); ind++);
        ind_start = ind;
        ind++;
        if (read[ind] == '}'){
            return;
        }
        string datas = "";
        string key = "";
        for (ind; read[ind] != '}' && read[ind] != '\n' && ind < read.size(); ind++){
            for (ind; read[ind] != '(' && read[ind] != '}' && ind < read.size(); ind++);
            ind++;
            for (ind; read[ind] != ',' && read[ind] != ')' && ind < read.size(); ind++){
                key += read[ind];
            }
            ind++;
            for (ind; read[ind] != ')' && read[ind] != '}' && ind < read.size(); ind++){
                datas += read[ind];
            }
            HPush(key, datas);
            datas = "";
            key = "";
        }
        read.erase(ind_start + 1, ind - ind_start - 1);
        return;
    }
};

struct Tree{
    TNode* root;

    bool is_empty(){
        return root == nullptr;
    }

    void TPush(TNode* current, string new_data){
        if (is_empty()){
            root = new TNode{new_data, nullptr, nullptr};
            return;
        }
        if (current->left == nullptr){
            current->left = new TNode{new_data, nullptr, nullptr};
            return;
        }
        if (current->right == nullptr){
            current->right = new TNode{new_data, nullptr, nullptr};
            return;
        }
        if (new_data >= current->data){
            TPush(current->right, new_data);
            return;
        } else {
            TPush(current->left, new_data);
            return;
        }
    }

    bool TFind(TNode* current, string find_data){
        if (is_empty()){
            cout << "Tree is empty" << endl;
            return false;
        }
        if (current->data == find_data){
            return true;
        }
        bool is_here = false;
        while ((current != nullptr) && (current->right != nullptr && current->left != nullptr)){
            if (current->left->data == find_data || current->right->data == find_data){
                is_here = true;
                break;
            }
            if (find_data > current->data){
                current = current->right;
            } else {
                current = current->left;
            }
        }
        return is_here;
    }
    
    bool is_full(TNode* current){
        if (is_empty()){
            cout << "List is empty" << endl;
            return false;
        }
        if (current == nullptr){
            return true;
        }
        if (current->left == nullptr && current->right == nullptr){
            return true;
        }

        if (current->right != nullptr && current->left != nullptr){
            return is_full(current->left) && is_full(current->right);
        }

        return false;

    }
    void print_Tree(TNode* root, int level)
    {
        if (root != NULL)
        {
            print_Tree(root->right, level + 1);
            for (int i = 0; i < level * 4; i++) cout << "   ";
            cout << root->data << endl;
            print_Tree(root->left, level + 1);
        }
    }

    void TWrite(string& read, string filename, int ind_start, int ind, string data){
        ofstream in;
        in.open(filename);
        if (is_empty()){
            cout << "List is empty" << endl;
            in << read;
            in.close();
            return;
        }
        if (read[ind_start+1] == '}') read.insert(ind_start + 1, '\"' + data + '\"');
        else {
            read.insert(ind, '\"' + data + '\"');
        }
        in << read;
        in.close();
        return;
    }   

    int TRead(string& read, int& ind_start, int& ind){
        for (ind; read[ind] != '{' && ind < read.size(); ind++);
        ind_start = ind;
        ind++;
        if (read[ind] == '}'){
            return 0;
        }
        int count = 1;
        string datas = "";
        for (ind; read[ind] != '}' && read[ind] != '\n' && ind < read.size(); ind++){
            count++;
            for (ind; read[ind] != '\"' && read[ind] != '}' && read[ind] != '\n'; ind++) count++;
            ind++;
            for (ind; read[ind] != '\"' && read[ind] != '}' && read[ind] != '\n'; ind++){
                datas += read[ind];
                count++;
            }
            TPush(root, datas);
            datas = "";
        }
        return count;
    }
};

string READ (string filename){
    ifstream out;
    out.open(filename);
    string read = "";
    getline(out, read, '\0');
    out.close();
    return read;
}
bool is_same_name (string name, int& ind, string filename){
        string name_chek = "";
        bool is_same = 0;
        string read = READ(filename);
        while(ind < read.size()){
            while (read[ind] != '[' && ind < read.size()){
                ind++;
            }
            ind++;
            while (read[ind] != ']' && ind < read.size()){
                name_chek += read[ind];
                ind++;
            }
            if (name_chek == name){
                is_same = 1;
                return is_same;
            }
            name_chek = "";
            ind++;
        }
        return is_same;
}

bool is_same_type (string struc_type, int& ind, string read){
    string type_chek = "";
    while (read[ind] != '<'){
        ind++;
    }
    ind++;
    while (read[ind] != '>'){
        type_chek += read[ind];
        ind++;
    }
    if (type_chek == struc_type){
        return true;
    } else {
        return false;
    }
}

int main(int size, char* inter[]) {

    string enter = inter[4];
    string filename = inter[2];
    string command = "";
    string name = "";
    string new_data = "";
    string key = "";
    int i = 0;
    while (enter[i] != ' '){
        if(i == enter.size()){
            cout << "Inccorect enter" << endl;
            return 0;
        }
        command += enter[i];
        i++;
    }
    i++;
    if(command == "TPUSH"){
        while (enter[i] != ' '){
           if(i == enter.size()){
                cout << "Inccorect enter" << endl;
                return 0;
            }
            name += enter[i];
            i++;
        }
        i++;
        while (i < enter.size()){
            new_data += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        Tree derevo{nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("t", ind, read)){
                derevo.TRead(read, ind_start, ind);
                derevo.TPush(derevo.root, new_data);
                derevo.TWrite(read, filename, ind_start, ind, new_data);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
            
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if(command == "TFIND"){
        while (enter[i] != ' '){
           if(i == enter.size()){
                cout << "Inccorect enter" << endl;
                return 0;
            }
            name += enter[i];
            i++;
        }
        i++;
        while (i < enter.size()){
            new_data += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        Tree derevo{nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("t", ind, read)){
                derevo.TRead(read, ind_start, ind);
                if (derevo.TFind(derevo.root, new_data)) cout << "Tree has it" << endl;
                else {
                    cout << "Don't have" << endl;
                }
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
            
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if(command == "TISFULL"){
        while (i < enter.size()){
            name += enter[i];
            i++;
        }
        i++;
        int ind = 0;
        int ind_start = 0;
        Tree derevo{nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("t", ind, read)){
                derevo.TRead(read, ind_start, ind);
                if (derevo.is_full(derevo.root)) cout << "IS FULL" << endl;
                if (!derevo.is_full(derevo.root)) cout << "NOT FULL" << endl;
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
            
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if(command == "TFIND"){
        while (enter[i] != ' '){
           if(i == enter.size()){
                cout << "Inccorect enter" << endl;
                return 0;
            }
            name += enter[i];
            i++;
        }
        i++;
        while (i < enter.size()){
            new_data += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        Tree derevo{nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("t", ind, read)){
                derevo.TRead(read, ind_start, ind);
                if (derevo.TFind(derevo.root, new_data)) cout << "Tree has it" << endl;
                else {
                    cout << "Don't have" << endl;
                }
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
            
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if(command == "TPRINT"){
        while (i < enter.size()){
            name += enter[i];
            i++;
        }
        i++;
        int ind = 0;
        int ind_start = 0;
        Tree derevo{nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("t", ind, read)){
                derevo.TRead(read, ind_start, ind);
                derevo.print_Tree(derevo.root, 0);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
            
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "SPUSH"){
        while (enter[i] != ' '){
           if(i == enter.size()){
                cout << "Inccorect enter" << endl;
                return 0;
            }
            name += enter[i];
            i++;
        }
        i++;
        while (i < enter.size()){
            new_data += enter[i];
            i++;
        } 
        int ind = 0;
        int ind_start = 0;
        Stk stack;
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("s", ind, read)){
                stack.SRead(read, ind_start, ind);
                stack.SPUSH(new_data);
                stack.SWrite(read, filename, ind_start, ind);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
            
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "SPOP"){
        while (i < enter.size()){
            name += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        Stk stack;
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("s", ind, read)){
                stack.SRead(read, ind_start, ind);
                if (stack.is_empty()){
                    cout << "Stack is empty" << endl;
                    return 0;
                }
                stack.SPOP();
                stack.SWrite(read, filename, ind_start, ind);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
            
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "SPRINT"){
        while (i < enter.size()){
            name += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        Stk stack;
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("s", ind, read)){
                stack.SRead(read, ind_start, ind);
                if (stack.is_empty()){
                    cout << "Stack is empty" << endl;
                    return 0;
                }
                stack.printStack();
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
            
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "LSPUSH_h"){
        while (enter[i] != ' '){
           if(i == enter.size()){
                cout << "Inccorect enter" << endl;
                return 0;
            }
            name += enter[i];
            i++;
        }
        i++;
        while (i < enter.size()){
            new_data += enter[i];
            i++;
        } 
        int ind = 0;
        int ind_start = 0;
        LIST_S list{nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("l", ind, read)){
                list.LsRead(read, ind_start, ind);
                list.LsPUSH_front(new_data);
                list.LsWrite(read, filename, ind_start, ind);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
            
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "LSPUSH_b"){
        while (enter[i] != ' '){
            if(i == enter.size()){
                cout << "Inccorect enter" << endl;
                return 0;
            }
            name += enter[i];
            i++;
        }
        i++;
        while (i < enter.size()){
            new_data += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        LIST_S list{nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("l", ind, read)){
                list.LsRead(read, ind_start, ind);
                list.LsPUSH_end(new_data);
                list.LsWrite(read, filename, ind_start, ind);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
            
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "LSPOP_h"){
        while (i < enter.size()){
            name += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        LIST_S list{nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("l", ind, read)){
                list.LsRead(read, ind_start, ind);
                list.LsPOP_head();
                list.LsWrite(read, filename, ind_start, ind);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
            
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "LSPOP_b"){
        while (i < enter.size()){
            name += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        LIST_S list{nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("l", ind, read)){
                list.LsRead(read, ind_start, ind);
                list.LsPOP_end();
                list.LsWrite(read, filename, ind_start, ind);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
            
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "LSPOP_data"){
        while (enter[i] != ' '){
            if(i == enter.size()){
                cout << "Inccorect enter" << endl;
                return 0;
            }
            name += enter[i];
            i++;
        }
        i++;
        while (i < enter.size()){
            new_data += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        LIST_S list{nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("l", ind, read)){
                list.LsRead(read, ind_start, ind);
                list.LsPOP_data(new_data);
                list.LsWrite(read, filename, ind_start, ind);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
            
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "LSISMEMBER"){
        while (enter[i] != ' '){
            if(i == enter.size()){
                cout << "Inccorect enter" << endl;
                return 0;
            }
            name += enter[i];
            i++;
        }
        i++;
        while (i < enter.size()){
            new_data += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        LIST_S list{nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("l", ind, read)){
                list.LsRead(read, ind_start, ind);
                list.LsGET(new_data);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
            
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "LSPRINT"){
        while (i < enter.size()){
            name += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        LIST_S list {nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("l", ind, read)){
                list.LsRead(read, ind_start, ind);
                list.LsPRINT();
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "LDPUSH_h"){
        while (enter[i] != ' '){
            if(i == enter.size()){
                cout << "Inccorect enter" << endl;
                return 0;
            }
            name += enter[i];
            i++;
        }
        i++;
        while (i < enter.size()){
            new_data += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        LIST_d list{nullptr};
        string read = READ(filename);
        cout << "proverka" << read << endl;
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("l", ind, read)){
                list.LdRead(read, ind_start, ind);
                list.LdPUSH_front(new_data);
                list.LdWrite(read, filename, ind_start, ind);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
            
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "LDPUSH_b"){
        while (enter[i] != ' '){
            if(i == enter.size()){
                cout << "Inccorect enter" << endl;
                return 0;
            }
            name += enter[i];
            i++;
        }
        i++;
        while (i < enter.size()){
            new_data += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        LIST_d list{nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("l", ind, read)){
                list.LdRead(read, ind_start, ind);
                list.LdPUSH_end(new_data);
                list.LdWrite(read, filename, ind_start, ind);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
            
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "LDPOP_h"){
        while (i < enter.size()){
            name += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        LIST_d list{nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("l", ind, read)){
                list.LdRead(read, ind_start, ind);
                list.LdPOP_head();
                list.LdWrite(read, filename, ind_start, ind);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
            
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "LDPOP_b"){
        while (i < enter.size()){
            name += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        LIST_d list{nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("l", ind, read)){
                list.LdRead(read, ind_start, ind);
                list.LdPOP_end();
                list.LdWrite(read, filename, ind_start, ind);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
            
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "LDPOP_data"){
        while (enter[i] != ' '){
            if(i == enter.size()){
                cout << "Inccorect enter" << endl;
                return 0;
            }
            name += enter[i];
            i++;
        }
        i++;
        while (i < enter.size()){
            new_data += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        LIST_d list{nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("l", ind, read)){
                list.LdRead(read, ind_start, ind);
                list.LdPOP_data(new_data);
                list.LdWrite(read, filename, ind_start, ind);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
            
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "LDISMEMBER"){
        while (enter[i] != ' '){
            if(i == enter.size()){
                cout << "Inccorect enter" << endl;
                return 0;
            }
            name += enter[i];
            i++;
        }
        i++;
        while (i < enter.size()){
            new_data += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        LIST_d list{nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("l", ind, read)){
                list.LdRead(read, ind_start, ind);
                list.LdGET(new_data);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
            
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "LDPRINT"){
        while (i < enter.size()){
            name += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        LIST_d list {nullptr, nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("l", ind, read)){
                list.LdRead(read, ind_start, ind);
                list.LdPRINT();
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "MPUSH_b"){
        while (enter[i] != ' '){
            if(i == enter.size()){
                cout << "Inccorect enter" << endl;
                return 0;
            }
            name += enter[i];
            i++;
        }
        i++;
        while (i < enter.size()){
            new_data += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        Massive mas{0, nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("m", ind, read)){
                mas.MRead(read, ind_start, ind);
                mas.MPushback(new_data);
                mas.MWrite(read, filename, ind_start, ind);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "MPUSH_ind"){
        while (enter[i] != ' '){
            if(i == enter.size()){
                cout << "Inccorect enter" << endl;
                return 0;
            }
            name += enter[i];
            i++;
        }
        i++;
        while (enter[i] != ' '){
            if(i == enter.size()){
                cout << "Incorrect enter" << endl;
                return 0;
            }
            key += enter[i];
            i++;
        }
        i++;
        for (int index_check = 0; index_check < key.size(); index_check++){
            if(!isdigit(key[index_check])){
                cout << "Not correct index" <<endl;
                return 0;
            }
        }
        istringstream is(key);
        int index = 0;
        is >> index;
        while (i < enter.size()){
            new_data += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        Massive mas{0, nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("m", ind, read)){
                mas.MRead(read, ind_start, ind);
                if (index > mas.Size()){
                    cout << "Index is too BIG" << endl;
                    return 0;
                }
                mas.MPushind(index, new_data);
                mas.MWrite(read, filename, ind_start, ind);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "MPOP"){
        while (enter[i] != ' '){
            if(i == enter.size()){
                cout << "Inccorect enter" << endl;
                return 0;
            }
            name += enter[i];
            i++;
        }
        i++;
        while (i < enter.size()){
            key += enter[i];
            i++;
        }
        i++;
        for (int index_check = 0; index_check < key.size(); index_check++){
            if(!isdigit(key[index_check])){
                cout << "Not correct index" <<endl;
                return 0;
            }
        }
        istringstream is(key);
        int index = 0;
        is >> index;
        while (i < enter.size()){
            new_data += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        Massive mas{0, nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("m", ind, read)){
                mas.MRead(read, ind_start, ind);
                if (index > mas.Size()){
                    cout << "Index is too BIG" << endl;
                    return 0;
                }
                mas.MPopind(index);
                mas.MWrite(read, filename, ind_start, ind);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }
    
    if (command == "MCHANGE"){
        while (enter[i] != ' '){
            if(i == enter.size()){
                cout << "Inccorect enter" << endl;
                return 0;
            }
            name += enter[i];
            i++;
        }
        i++;
        while (enter[i] != ' '){
            if(i == enter.size()){
                cout << "Incorrect enter" << endl;
                return 0;
            }
            key += enter[i];
            i++;
        }
        i++;
        for (int index_check = 0; index_check < key.size(); index_check++){
            if(!isdigit(key[index_check])){
                cout << "Not correct index" <<endl;
                return 0;
            }
        }
        istringstream is(key);
        int index = 0;
        is >> index;
        while (i < enter.size()){
            new_data += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        Massive mas{0, nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("m", ind, read)){
                mas.MRead(read, ind_start, ind);
                if (index > mas.Size()){
                    cout << "Index is too BIG" << endl;
                    return 0;
                }
                mas.MChange(index, new_data);
                mas.MWrite(read, filename, ind_start, ind);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "MGET"){
        while (enter[i] != ' '){
            if(i == enter.size()){
                cout << "Inccorect enter" << endl;
                return 0;
            }
            name += enter[i];
            i++;
        }
        i++;
        while (i < enter.size()){
            key += enter[i];
            i++;
        }
        i++;
        for (int index_check = 0; index_check < key.size(); index_check++){
            if(!isdigit(key[index_check])){
                cout << "Not correct index" <<endl;
                return 0;
            }
        }
        istringstream is(key);
        int index = 0;
        is >> index;
        while (i < enter.size()){
            new_data += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        Massive mas{0, nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("m", ind, read)){
                mas.MRead(read, ind_start, ind);
                if (index > mas.Size()){
                    cout << "Index is too BIG" << endl;
                    return 0;
                }
                mas.MGet(index);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "MSIZE"){
        while (i < enter.size()){
            name += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        Massive mas{0, nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("m", ind, read)){
                mas.MRead(read, ind_start, ind);
                cout << "Size = " << mas.Size() << endl;
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "MPRINT"){
        while (i < enter.size()){
            name += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        Massive mas{0, nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("m", ind, read)){
                mas.MRead(read, ind_start, ind);
                mas.MPrint();
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "QPUSH"){
        while (enter[i] != ' '){
            if(i == enter.size()){
                cout << "Inccorect enter" << endl;
                return 0;
            }
            name += enter[i];
            i++;
        }
        i++;
        while (i < enter.size()){
            new_data += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        Queue que{nullptr, nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("q", ind, read)){
                que.QRead(read, ind_start, ind);
                que.QPush(new_data);
                que.QWrite(read, filename, ind_start, ind);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "QPOP"){
        while (i < enter.size()){
            name += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        Queue que{nullptr, nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("q", ind, read)){
                que.QRead(read, ind_start, ind);
                que.QPop();
                que.QWrite(read, filename, ind_start, ind);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "QPRINT"){
        while (i < enter.size()){
            name += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        Queue que{nullptr, nullptr};
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("q", ind, read)){
                que.QRead(read, ind_start, ind);
                que.QPrint();
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "HPUSH"){
        while (enter[i] != ' '){
            if(i == enter.size()){
                cout << "Inccorect enter" << endl;
                return 0;
            }
            name += enter[i];
            i++;
        }
        i++;
        while (enter[i] != ' '){
            if(i == enter.size()){
                cout << "Inccorect enter" << endl;
                return 0;
            }
            key += enter[i];
            i++;
        }
        i++;
        while (i < enter.size()){
            new_data += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        Hash hash;
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("h", ind, read)){
                hash.HRead(read, ind_start, ind);
                hash.HPush(key, new_data);
                hash.HWrite(read, filename, ind_start, ind);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "HPOP"){
        while (enter[i] != ' '){
            if(i == enter.size()){
                cout << "Inccorect enter" << endl;
                return 0;
            }
            name += enter[i];
            i++;
        }
        i++;
        while (i < enter.size()){
            key += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        Hash hash;
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("h", ind, read)){
                hash.HRead(read, ind_start, ind);
                hash.HPop(key);
                hash.HWrite(read, filename, ind_start, ind);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "HGET"){
        while (enter[i] != ' '){
            if(i == enter.size()){
                cout << "Inccorect enter" << endl;
                return 0;
            }
            name += enter[i];
            i++;
        }
        i++;
        while (i < enter.size()){
            key += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        Hash hash;
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("h", ind, read)){
                hash.HRead(read, ind_start, ind);
                cout << "element with key = " << key << endl << hash.HGet(key) << endl;
                hash.HWrite(read, filename, ind_start, ind);
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }

    if (command == "HPRINT"){
        while (i < enter.size()){
            name += enter[i];
            i++;
        }
        int ind = 0;
        int ind_start = 0;
        Hash hash;
        string read = READ(filename);
        if (is_same_name(name, ind, filename) == 1){
            if (is_same_type("h", ind, read)){
                hash.HRead(read, ind_start, ind);
                hash.HPrint();
                return 1;
            } else {
                cout << "Structure has a different type" << endl;
                return 0;
            }
        } else {
            cout << "file don't have struct with this name." << endl;
            return 0;
        }
        return 1;
    }
}
