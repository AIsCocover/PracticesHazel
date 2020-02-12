#pragma once

#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Core/MouseCodes.h"

/*
	default��delete�ؼ���
		��C++11�У���������Ҫ����ֹʹ�á��������Ա�����������"= delete;"������Ҫ�����ļ�"= default;"���߲���ȡ������
		�����Ա����ָ����C++98����������ʽ�������ĸ�������ȱʡ���캯���������������������캯����������ֵ���ӣ��Լ�C++11�е��ƶ����캯���Լ��ƶ���ֵ���ӡ�
*/
namespace Hazel {
	class Input
	{
	protected:
		Input() = default;
	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

	protected:

	private:
		
	};
}