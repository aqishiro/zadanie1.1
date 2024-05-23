#ifndef MainH
#define MainH

#include "Patterns.h"

enum class PhoneBrand
{
    Apple,
    Google,
    Xiaomi,
    Samsung,
};

enum class ColorEnum
{
    Black,
    White,
    Red,
    Unknown,
};


enum class SizeEnum
{
    Big,
    Small,
};

enum class WeightEnum
{
    Heavy,
    Light,
};

enum class AgeEnum
{
    New,
    Old,
};

class Phone
{
protected:
    ColorEnum Color;
    SizeEnum Size;
    WeightEnum Weight;
    AgeEnum Age;

    Phone();

public:
    ColorEnum GetColor() const {return Color;}
    SizeEnum GetSize() const {return Size;}
    WeightEnum GetWeight() const {return Weight;}
    AgeEnum GetAge() const {return Age;}
    virtual PhoneBrand GetBrand() const = 0;
    virtual void Buy() = 0;
    virtual void Sell() = 0;

};

typedef Phone * PhonePtr;

class Apple : public Phone
{
public:
    Apple() : Phone() {Color = ColorEnum::Black;
    Size = SizeEnum::Big;
    Weight = WeightEnum::Heavy;
    Age = AgeEnum::New;}
    Apple(ColorEnum color) : Phone() { Color = color; }
    Apple(SizeEnum SIze) : Phone() { Size = SIze; }
    Apple(WeightEnum weight) : Phone() { Weight = weight; }
    Apple(AgeEnum age) : Phone() { Age = age; }
    PhoneBrand GetBrand () const { return PhoneBrand::Apple; }
    void Buy() { wcout << L"Купили телефон бренда Apple"; }
    void Sell() { wcout << L"Продали телефон бренда Apple"; }
};

class Google : public Phone
{
public:
    Google() : Phone() {Color = ColorEnum::White;
    Size = SizeEnum::Small;
    Weight = WeightEnum::Light;
    Age = AgeEnum::Old;}
    Google(ColorEnum color) : Phone() { Color = color; }
    Google(SizeEnum SIze) : Phone() { Size = SIze; }
    Google(WeightEnum weight) : Phone() { Weight = weight; }
    Google(AgeEnum age) : Phone() { Age = age; }
    PhoneBrand GetBrand () const { return PhoneBrand::Google; }
    void Buy() { wcout << L"Купили телефон бренда Google"; }
    void Sell() { wcout << L"Продали телефон бренда Google"; }
};

class Xiaomi : public Phone
{
public:
    Xiaomi() : Phone() {Color = ColorEnum::Red;
    Size = SizeEnum::Big;
    Weight = WeightEnum::Light;
    Age = AgeEnum::New;}
    Xiaomi(ColorEnum color) : Phone() { Color = color; }
    Xiaomi(SizeEnum SIze) : Phone() { Size = SIze; }
    Xiaomi(WeightEnum weight) : Phone() { Weight = weight; }
    Xiaomi(AgeEnum age) : Phone() { Age = age; }
    PhoneBrand GetBrand () const { return PhoneBrand::Xiaomi; }
    void Buy() { wcout << L"Купили телефон бренда Xiaomi"; }
    void Sell() { wcout << L"Продали телефон бренда Xiaomi"; }
};

class Samsung : public Phone
{
public:
    Samsung() : Phone() {Color = ColorEnum::Red;
    Size = SizeEnum::Small;
    Weight = WeightEnum::Heavy;
    Age = AgeEnum::Old;}
    Samsung(ColorEnum color) : Phone() { Color = color; }
    Samsung(SizeEnum SIze) : Phone() { Size = SIze; }
    Samsung(WeightEnum weight) : Phone() { Weight = weight; }
    Samsung(AgeEnum age) : Phone() { Age = age; }
    PhoneBrand GetBrand () const { return PhoneBrand::Samsung; }
    void Buy() { wcout << L"Купили телефон бренда Samsung"; }
    void Sell() { wcout << L"Продали телефон бренда Samsung"; }
};

class PhoneContainerIterator : public Iterator<PhonePtr>
{
private:
    const PhonePtr *PhoneBox;
    int Pos;
    int Count;

public:
    PhoneContainerIterator(const PhonePtr *phoneBox, int count)
    {
        PhoneBox = phoneBox;
        Count = count;
        Pos = 0;
    }

    void First() { Pos = 0; }
    void Next() { Pos++; }
    bool IsDone() const { return Pos >= Count; }
    PhonePtr GetCurrent() const { return PhoneBox[Pos]; }
};

class PhoneContainer
{
private:
    PhonePtr *PhoneBox;
    int PhoneCount;
    int MaxSize;

public:
    PhoneContainer(int maxSize);
    virtual ~PhoneContainer();
    void AddPhone(PhonePtr newPhone);
    int GetCount() const { return PhoneCount; }
    PhonePtr GetByIndex(int index) const { return PhoneBox[index]; }

    Iterator<PhonePtr> *GetIterator()
    {
        return new PhoneContainerIterator(PhoneBox, PhoneCount);
    }
};

class MegaPhoneContainerIterator : public Iterator<PhonePtr>
{

private:
    const std::list<PhonePtr> *PhoneBox;
    std::list<PhonePtr>::const_iterator it;

public:
    MegaPhoneContainerIterator(const std::list<PhonePtr> *phoneBox)
    {        PhoneBox = phoneBox;
        it = PhoneBox->begin();
    }

    void First() { it = PhoneBox->begin(); }
    void Next() { it++; }
    bool IsDone()  const { it !=PhoneBox->end(); }
    PhonePtr GetCurrent() const { return *it; }
};
class MegaPhoneContainer
{

private:
    vector<PhonePtr> PhoneBox;
    std::list<PhonePtr> phoneBox;

public:
    void AddPhone(PhonePtr newPhone) { PhoneBox.push_back(newPhone); }
    int GetCount() const { return PhoneBox.size(); }

    Iterator<PhonePtr> *GetIterator()
    {
        return new MegaPhoneContainerIterator(&phoneBox);
    }
};

class PhoneColorIteratorDecorator : public IteratorDecorator<PhonePtr>
{

private:
    ColorEnum TargetColor;

public:
    PhoneColorIteratorDecorator(Iterator<PhonePtr> *it, ColorEnum targetColor)
    : IteratorDecorator(it)
    {
        TargetColor = targetColor;
    }

    void First()
    {
        It->First();
        while(!It->IsDone() &&
              It->GetCurrent()->GetColor() != TargetColor)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() &&
                It->GetCurrent()->GetColor() != TargetColor);
    }


};
class PhoneSizeIteratorDecorator : public IteratorDecorator<PhonePtr>
{
private:
    SizeEnum TargetSize;

public:
    PhoneSizeIteratorDecorator(Iterator<PhonePtr> *it, SizeEnum targetSize)
    : IteratorDecorator(it)
    {
        TargetSize = targetSize;
    }

    void First()
    {
        It->First();
        while(!It->IsDone() &&
              It->GetCurrent()->GetSize() != TargetSize)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() &&
                It->GetCurrent()->GetSize() != TargetSize);
    }


};

class PhoneWeightIteratorDecorator : public IteratorDecorator<PhonePtr>
{
private:
    WeightEnum TargetWeight;

public:
    PhoneWeightIteratorDecorator(Iterator<PhonePtr> *it, WeightEnum targetWeight)
    : IteratorDecorator(it)
    {
        TargetWeight = targetWeight;
    }

    void First()
    {
        It->First();
        while(!It->IsDone() &&
              It->GetCurrent()->GetWeight() != TargetWeight)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() &&
                It->GetCurrent()->GetWeight() != TargetWeight);
    }


};

class PhoneAgeIteratorDecorator : public IteratorDecorator<PhonePtr>
{
private:
    AgeEnum TargetAge;

public:
    PhoneAgeIteratorDecorator(Iterator<PhonePtr> *it, AgeEnum targetAge)
    : IteratorDecorator(it)
    {
        TargetAge = targetAge;
    }

    void First()
    {
        It->First();
        while(!It->IsDone() &&
              It->GetCurrent()->GetAge() != TargetAge)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() &&
                It->GetCurrent()->GetAge() != TargetAge);
    }


};
#endif // MainH
