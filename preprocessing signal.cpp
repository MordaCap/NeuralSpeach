#include <iostream>
#include "wav.hpp"
#include <cmath>

using namespace std;
const float pi = 3.14, fc = /*�������� - ��� ��������� ����� � �������� ������� �������������*/
//������ � ����� ��������

float w(i, M){
	return (0.42 - 0.5 * cos(2*pi*i/M)+0.08*cos(4*pi*i/M))
}

float h(int i, int M){
	if i != M/2
		return (sin(2 * fc*pi*(i - M / 2)) / (i - M / 2))*w(i,M)
	else
		return (2 * pi*fc)*w(i,M)
}

void main(int argc, char* argv[])
{
	// ���� � ����� �������� ���������� ��������� ������.
	if (argc < 2) return 0;

	char *src = argv[1];

	vector<float> data = wav::loadFloatFirstChannel(src);
	
	int sum = 0, n = 0;
	for (auto i : data){
		sum += i;
		n += 1;
	}
	// �������� dc-offset
	for (auto i : data)
		i -= sum / n
	
	// ��������� ���������� ���������, ����� �������  � ��������� ������� ������
	int M /*��������, ������������ ������������ i=0*/, k = 0;
	for (auto i : data){
		i *= h(k, M);
		k += 1;
	}

}