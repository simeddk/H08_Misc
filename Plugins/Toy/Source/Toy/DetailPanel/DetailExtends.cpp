#include "DetailExtends.h"

TSharedRef<class IDetailCustomization> FDetailExtends::MakeInstance()
{
	return MakeShareable(new FDetailExtends());
}

void FDetailExtends::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	//Todo... ��ư UI�� �����ؼ� �ٿ�����..

}
