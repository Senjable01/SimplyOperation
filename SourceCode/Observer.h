#ifndef INCLUDED_OBSERVER_H
#define INCLUDED_OBSERVER_H

//------< include >-----------------------------------------------------------------------
#include <vector>
#include <algorithm>

//========================================================================================
// 
//      Observer
// 
//========================================================================================
template<typename Report>
class Observer
{
public:
    Observer() {}

    // �ʒm���ꂽ���̏���
    virtual void OnNotify(const Report& report) = 0;
};

//========================================================================================
// 
//      Subject
// 
//========================================================================================
template<class Report>
class Subject
{
private:
    std::vector<Observer<Report>*> observers;

public:
    Subject() {}

    void AddObserver(Observer<Report>* observer)
    {
        auto result = std::find(observers.begin(), observers.end(), observer);
        if (result == observers.end())
        {
            observers.emplace_back(observer);
        }
    }
    // �ʒm
    void Notify(const Report& report)
    {
        for (auto& observer : observers)
        {
            observer->OnNotify(report);
        }
    }
    void RemoveObserver(Observer<Report>* observer)
    {
        // �w��v�f������Ύ�菜���H
        std::remove(observers.begin(), observers.end(), observer);
    }

};

#endif // !INCLUDED_OBSERVER_H