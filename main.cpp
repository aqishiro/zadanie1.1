#include <iostream>
#include <windows.h>
#include <vector>
#include <list>
#include <ctime>
using namespace std;

#include "main.h"

Phone::Phone()
{

    Color = ColorEnum::Unknown;

}

PhoneContainer::PhoneContainer(int maxSize)
{
    PhoneBox = new PhonePtr[maxSize];

    for(int i = 0; i < maxSize; i++)
    {
        PhoneBox[i] = NULL;
    }

    PhoneCount = 0;
    MaxSize = maxSize;
}

PhoneContainer::~PhoneContainer()
{
    for(int i = 0; i < MaxSize; i++)
    {
        if(PhoneBox[i] != NULL)
        {
            delete PhoneBox[i];
            PhoneBox[i] = NULL;
        }
    }

    delete [] PhoneBox;
}

void PhoneContainer::AddPhone(PhonePtr newPhone )
{
    PhoneBox[PhoneCount] = newPhone;
    PhoneCount++;
}

wstring PrintPhoneBrand(const PhoneBrand brand)
{
    switch(brand)
    {
        case PhoneBrand::Apple: return L"Apple ";
        case PhoneBrand::Google: return L"Google ";
        case PhoneBrand::Xiaomi: return L"Xiaomi ";
        case PhoneBrand::Samsung: return L"Samsung ";
        default: return L"неизвестный бренд телефона ";
    }
}

wstring PrintPhoneColor(const ColorEnum color)
{
    switch(color)
    {
        case ColorEnum::Black: return L"черный ";
        case ColorEnum::White: return L"белый ";
        case ColorEnum::Red: return L"красный ";
        default: return L"неизвестный цвет телефона ";
    }
}

wstring PrintPhoneSize(const SizeEnum SIze)
{
    switch(SIze)
    {
        case SizeEnum::Big: return L"большой ";
        case SizeEnum::Small: return L"маленький ";
        default: return L"неизвестный размер телефона ";
    }
}

wstring PrintPhoneWeight(const WeightEnum weight)
{
    switch(weight)
    {
        case WeightEnum::Heavy: return L"тяжёлый ";
        case WeightEnum::Light: return L"лёгкий ";
        default: return L"неизвестный вес телефона ";
    }
}

wstring PrintPhoneAge(const AgeEnum age)
{
    switch(age)
    {
        case AgeEnum::New: return L"новый ";
        case AgeEnum::Old: return L"старый ";
        default: return L"неизвестный возраст телефона ";
    }
}


void Task_It(Iterator<PhonePtr> *it)
{

   for(it->First(); !it->IsDone(); it->Next())
    {
        const PhonePtr currentPhone = it->GetCurrent();
        wcout << L" (" << PrintPhoneBrand(currentPhone->GetBrand()) << L")" << endl;
    }
}


int main()
{
    srand(time(NULL));
    int A, G, X, S, sum;
    A = rand() % 20;
    G = rand () % 20;
    X = rand () % 20;
    S = rand () % 20;
    sum = A+G+X+S;

    setlocale(LC_ALL, "Russian");
    wcout << L"Телефоны" << endl;


    PhoneContainer phoneBox(sum);
    for(int i = 0; i < A; i++)
    {
        phoneBox.AddPhone(new Apple);
    }
    for(int i = 0; i < G; i++)
    {
        phoneBox.AddPhone(new Google);
    }

    for(int i = 0; i < X; i++)
    {
        phoneBox.AddPhone(new Xiaomi);
    }

    for(int i = 0; i < S; i++)
    {
        phoneBox.AddPhone(new Samsung);
    }

    //вывод из контейнера по условиям

    Iterator<PhonePtr> *it = new PhoneColorIteratorDecorator(phoneBox.GetIterator(), ColorEnum::Red); //красные телефоны
    //Iterator<PhonePtr> *it = new PhoneColorIteratorDecorator(new PhoneSizeIteratorDecorator(phoneBox.GetIterator(), SizeEnum::Small), ColorEnum::Red); //Маленькие и красные
    //Iterator<PhonePtr> *it = new PhoneSizeIteratorDecorator(new PhoneAgeIteratorDecorator(phoneBox.GetIterator(), AgeEnum::New), SizeEnum::Big); //Новые и большие
    Task_It(it);
    delete it;

    wcout << endl << endl;

}


