#pragma once

#include<string>

namespace bst
{

class Person
{
public:
    Person(int a_id, std::string a_name = "name")
    : m_id(a_id), m_name(a_name)
    {

    }

    bool operator<(const Person& a_other)const
    {
        return m_id < a_other.m_id;
    }

    bool operator==(Person& a_other)
    {
        return m_id == a_other.m_id;
    }
   
    bool operator!=(Person& a_other)
    {
        return m_id != a_other.m_id;
    }

    int id()
    {
        return m_id;
    }

    std::string name()
    {
        return m_name;;
    }

private:
    int m_id;
    std::string m_name;
};


}// bst namespace