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

    // 通知された時の処理
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
    // 通知
    void Notify(const Report& report)
    {
        for (auto& observer : observers)
        {
            observer->OnNotify(report);
        }
    }
    void RemoveObserver(Observer<Report>* observer)
    {
        // 指定要素があれば取り除く？
        std::remove(observers.begin(), observers.end(), observer);
    }

};

#endif // !INCLUDED_OBSERVER_H