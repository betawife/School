#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>

using namespace std;

// ������������ڵ�ṹ
struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode* left, * right; // �����ӽڵ�ָ��
    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// �Ƚ����������ȶ��У�ȷ��Ƶ����С�Ľڵ��ڶ���ǰ��
struct compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return (l->freq > r->freq);
    }
};

// �ݹ����ɹ����������
void generateCodes(HuffmanNode* root, string str, unordered_map<char, string>& huffmanCode) {
    if (!root) return; // ����ڵ�Ϊ�գ�����
    if (!root->left && !root->right) { // �����Ҷ�ӽڵ�
        huffmanCode[root->ch] = str; // ���ַ��Ͷ�Ӧ�ı����������������
    }
    generateCodes(root->left, str + "0", huffmanCode); // �ݹ鴦���������������'0'
    generateCodes(root->right, str + "1", huffmanCode); // �ݹ鴦���������������'1'
}

// ��������������ļ�
void saveTreeToFile(HuffmanNode* root, ofstream& outFile) {
    if (!root) {
        outFile << '#'; // ʹ��'#'��ʾ�սڵ�
        return;
    }
    outFile << root->ch; // �����ǰ�ڵ���ַ�
    saveTreeToFile(root->left, outFile); // �ݹ鱣��������
    saveTreeToFile(root->right, outFile); // �ݹ鱣��������
}

// ��ȡ�����������ļ�
HuffmanNode* loadTreeFromFile(ifstream& inFile) {
    char ch;
    inFile >> ch;
    if (ch == '#') return nullptr; // ����ַ���'#'�����ؿսڵ�
    HuffmanNode* node = new HuffmanNode(ch, 0); // �����½ڵ�
    node->left = loadTreeFromFile(inFile); // �ݹ��ȡ������
    node->right = loadTreeFromFile(inFile); // �ݹ��ȡ������
    return node;
}

// ������
int main() {
    string text;
    cout << "������һ��Ӣ���ַ���" << endl;
    getline(cin, text);

    // ͳ��Ƶ��
    unordered_map<char, int> freq;
    for (char ch : text) {
        if (ch != ' ') freq[ch]++;
    }

    // �������ȶ��в�������������
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> pq;
    for (auto pair : freq) {
        pq.push(new HuffmanNode(pair.first, pair.second)); // ��ÿ���ַ�����Ƶ����Ϊ�ڵ�������ȶ���
    }

    while (pq.size() != 1) {
        HuffmanNode* left = pq.top(); pq.pop(); // ȡ��Ƶ����С�������ڵ�
        HuffmanNode* right = pq.top(); pq.pop();
        HuffmanNode* top = new HuffmanNode('$', left->freq + right->freq); // ����һ���µ��ڲ��ڵ㣬��Ƶ��Ϊ�����ӽڵ�Ƶ��֮��
        top->left = left; // �������ӽڵ�
        top->right = right; // �������ӽڵ�
        pq.push(top); // ���½ڵ�������ȶ���
    }

    HuffmanNode* root = pq.top(); // ���յĸ��ڵ㼴Ϊ���������ĸ��ڵ�

    // ���ɹ����������
    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode); // ���õݹ麯�����ɱ����

    // �������������浽�ļ�
    ofstream treeFile("huffman_tree.txt");
    saveTreeToFile(root, treeFile);
    treeFile.close();

    // �����������浽�ļ�
    ofstream codeFile("huffman_codes.txt");
    for (auto pair : huffmanCode) {
        codeFile << pair.first << ": " << pair.second << endl;
    }
    codeFile.close();

    // ��ʾ������
    cout << "�ַ��Ĺ���������Ϊ��" << endl;
    for (auto pair : huffmanCode) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // ���������ı�
    string encodedString;
    for (char ch : text) {
        if (ch != ' ') encodedString += huffmanCode[ch]; // ���ݱ������ı����б���
    }
    cout << "�������ַ���Ϊ��" << encodedString << endl;

    // �������
    string inputSequence;
    cout << "������Ҫ�����01���У�" << endl;
    cin >> inputSequence;

    // ���ع����������н���
    ifstream treeInFile("huffman_tree.txt");
    HuffmanNode* loadedRoot = loadTreeFromFile(treeInFile); // ���ļ����ع�������
    treeInFile.close();

    string decodedString;
    HuffmanNode* current = loadedRoot;
    for (char bit : inputSequence) {
        if (bit == '0') current = current->left; // ���λ��'0'���ƶ������ӽڵ�
        else current = current->right; // ���λ��'1'���ƶ������ӽڵ�
        if (!current->left && !current->right) { // �������Ҷ�ӽڵ�
            decodedString += current->ch; // ����ַ��������ַ�����
            current = loadedRoot; // ���õ�ǰ�ڵ�Ϊ���ڵ㣬׼��������һ���ַ�
        }
    }
    cout << "�������ַ���Ϊ��" << decodedString << endl;

    return 0;
}
