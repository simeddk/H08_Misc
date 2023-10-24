#include "DetailExtends.h"

TSharedRef<class IDetailCustomization> FDetailExtends::MakeInstance()
{
	return MakeShareable(new FDetailExtends());
}

void FDetailExtends::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	//Todo... 버튼 UI를 생성해서 붙여보자..

}
