#pragma once
#include<vector>
#include<string>
using namespace std;
struct HuffmanNode	// �����������Ķ���
{
	char data; // ������ķ���		
	double weight;		// ���ų��ֵ�Ƶ�� 
	int parent, lchild, rchild;	// ����㡢���Һ��ӽ���λ��
};

class HuffmanTree
{
private:
	vector<HuffmanNode> hufftree;	// �������н��Ĵ洢�ռ�
	int n;						// Ҷ�ӽ����
	void SelectSmall(int &least, int &less, int i);//ѡ��һ����������С�ĺʹ�С����
public:
	HuffmanTree(vector<HuffmanNode> &leafs);//���캯��
	vector<int>GetCode(int i);//huffman�����㷨
	void Decode(vector<int> &source, vector<char>&result);//huffman�����㷨
};

