#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <bitset>
using namespace std;

// 哈夫曼树节点
struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char character, int frequency) : ch(character), freq(frequency), left(nullptr), right(nullptr) {}
};

// 比较函数，用于优先队列
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

// 哈夫曼编码函数
void buildHuffmanCodes(HuffmanNode* root, const string& code, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCodes[root->ch] = code;
    }

    buildHuffmanCodes(root->left, code + "0", huffmanCodes);
    buildHuffmanCodes(root->right, code + "1", huffmanCodes);
}

// 释放哈夫曼树
void freeHuffmanTree(HuffmanNode* root) {
    if (!root) return;
    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);
    delete root;
}

int main() {
    // 读取文本文件
    ifstream inputFile("/home/shur/CLionProjects/t7/1.txt");
    if (!inputFile.is_open()) {
        cerr << "11" << endl;
        return 1;
    }

    // 统计字符频率
    unordered_map<char, int> freqMap;
    string content((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();

    for (char ch : content) {
        freqMap[ch]++;
    }

    // 构建哈夫曼树
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    for (const auto& pair : freqMap) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();

        HuffmanNode* sum = new HuffmanNode('\0', left->freq + right->freq);
        sum->left = left;
        sum->right = right;
        pq.push(sum);
    }

    HuffmanNode* root = pq.top();

    // 构建哈夫曼编码表
    unordered_map<char, string> huffmanCodes;
    buildHuffmanCodes(root, "", huffmanCodes);

    // 编码文本
    string encodedText;
    for (char ch : content) {
        encodedText += huffmanCodes[ch];
    }

    // 输出编码后的文件
    ofstream encodedFile("encoded.txt", ios::binary);
    encodedFile << encodedText;
    encodedFile.close();

    // 输出压缩比
    cout << "yuanwenjian: " << content.size() << " 字节" << endl;
    cout << "bianmawenjian: " << encodedText.size() / 8.0 << " 字节" << endl;
    cout << "yasuobi: " << (encodedText.size() / 8.0) / content.size() << endl;

    // 解码文件
    string decodedText;
    HuffmanNode* current = root;
    for (char bit : encodedText) {
        current = (bit == '0') ? current->left : current->right;
        if (!current->left && !current->right) {
            decodedText += current->ch;
            current = root;
        }
    }

    // 输出解码后的第四章内容
    size_t chapter4Pos = decodedText.find("BOOK FOUR: 1806"); // 第四章标题定位
    if (chapter4Pos != string::npos) {
        cout << "disizhang:" << endl;
        cout << decodedText.substr(chapter4Pos, 500) << "..." << endl; // 输出部分内容
    } else {
        cout << "meizhaodao！" << endl;
    }

    // 释放哈夫曼树
    freeHuffmanTree(root);

    return 0;
}
