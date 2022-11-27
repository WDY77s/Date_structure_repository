#include "pch.h"
#include "HuffmanTree.h"
void HuffmanTree::SelectSmall(int &least, int &less, int i)
{
	int a[2];
	double b[2];
	int k = 0, j = 0;
	//�ȼٶ������ǰ��λ�еĽ�С����least���ϴ����less
	for (j; j < i; j++)//�ҳ�ǰ��λparentΪ-1��
	{
		if (hufftree[j].parent == -1)
		{
			b[k] = hufftree[j].weight;
			a[k] = j;
			k++;
		}
		if (k == 2)
			break;
	}
	if (b[0] > b[1])
	{
		least = a[1];
		less = a[0];
	}
	else
	{
		least = a[0];
		less = a[1];
	}
	//ѭ����������Ԫ��
	//����Ԫ��С����С������С��Ϊ��С����Ԫ�س�Ϊ��С
	//�������ж���Ԫ���Ƿ�С�ڴ�С���ǣ�����Ԫ�ر�Ϊ��С
	for (++j; j < i; j++)
	{
		if (hufftree[j].parent == -1)
		{
			if (hufftree[j].weight < hufftree[least].weight)
			{
				less = least;
				least = j;

			}
			else if (hufftree[j].weight < hufftree[less].weight)
			{
				less = j;
			}
		}
	}
}
HuffmanTree::HuffmanTree(vector< HuffmanNode> &leafs)		//���캯��
{
	n = leafs.size();
	hufftree.resize(2 * n - 1);
	for (int i = 0; i < n; i++)	 // ��ʼ��n��������
	{
		hufftree[i].data = leafs[i].data;
		hufftree[i].weight = leafs[i].weight;
		hufftree[i].parent = hufftree[i].lchild = hufftree[i].rchild = -1;
	}
	for (int i = n; i < 2 * n - 1; i++)
	{
		int least, less;				//��С����С�ĸ�����±�
		SelectSmall(least, less, i);	// �ҵ���С����С�ĸ�����±�,ֻ���Ҹ���㣬Ҷ�ӽ�����ȥ��
		//ÿ�θ���㶼��䣬��leafs�Ǵ��
		hufftree[least].parent = hufftree[less].parent = i;
		hufftree[i].parent = -1;
		hufftree[i].lchild = least;
		hufftree[i].rchild = less;
		hufftree[i].weight = hufftree[least].weight + hufftree[less].weight;
	}
}

vector<int> HuffmanTree::GetCode(int i)					//Huffman�����㷨
{
	vector<int> code;		// ��i�����ŵı�������
	int p = i;				// p�ǵ�ǰ�����±�
	int parent = hufftree[i].parent;	// parent�ǵ�ǰ���ĸ������±�
	while (parent != -1)		// ֻ�и�����parent��Ϊ-1
	{
		if (hufftree[parent].lchild == p)
			code.insert(code.begin(), 0);	// �ڱ��������ײ�����0
		else
			code.insert(code.begin(), 1);	// �ڱ��������ײ�����1
		p = parent;
		parent = hufftree[parent].parent;	// �ظ�ָ������
	}
	return code;
}

void HuffmanTree::Decode(vector<int>&source, vector<char>&result)			//Huffman�����㷨
{
	//string target = "";		// �����Ŀ�꣺ԭ��Ϣ���Ŵ�
	int root = hufftree.size() - 1;
	int p = root;
	for (unsigned int i = 0; i < source.size(); i++)
	{
		if (source[i] == 0)
			p = hufftree[p].lchild;	// ��0����������
		else
			p = hufftree[p].rchild;	// ��1���Һ�������
		if (hufftree[p].lchild == -1 && hufftree[p].rchild == -1)
		{
			//target = target + hufftree[p].data;
			result.push_back(hufftree[p].data);
			p = root;
		}
	}
}