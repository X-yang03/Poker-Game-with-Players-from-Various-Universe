#include"Data.h"

Data::Data(int type,int tar,int from)
{

   data+=QString::number(type);
   data+=QString::number(tar);
   data+=QString::number(from);
   data+="/";
}

Data::Data(char c,int tar)
{
    data+=c;
    data+=QString::number(tar);
    data+="/";
}


Data::~Data()
{

}
